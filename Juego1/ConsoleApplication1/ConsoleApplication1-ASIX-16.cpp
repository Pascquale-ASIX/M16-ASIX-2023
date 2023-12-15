#include <iostream>
#include <string>
#include <Windows.h>
#include <chrono>
#include <thread>

using namespace std;

// Función para simular una animación de escritura
void typeText(const string& text) {
    for (char c : text) {
        cout << c;
        cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));  // Pequeño retraso entre caracteres
    }
}

// Clase para representar a un personaje
class Character {
public:
    string name;
    int swordDamage;
    int magicDamage;
    int punchDamage;
    int HP;
    bool isAlive;

    // Agregamos una variable para llevar el seguimiento de los usos del ataque especial
    int specialAttackUses;

    Character(string _name, int _swordDamage, int _magicDamage, int _punchDamage, int _HP) {
        name = _name;
        swordDamage = _swordDamage;
        magicDamage = _magicDamage;
        punchDamage = _punchDamage;
        HP = _HP;
        isAlive = true;
        specialAttackUses = 3;  // Inicialmente el héroe tiene 3 usos del ataque especial
    }

    void Attack(Character& enemy, int attackType) {
        if (isAlive) {
            int attackDamage = 0;
            switch (attackType) {
            case 1:  // Espada
                attackDamage = swordDamage + (rand() % 30);
                break;
            case 2:  // Magia
                attackDamage = magicDamage + (rand() % 30);
                break;
            case 3:  // Puñetazo
                attackDamage = punchDamage + (rand() % 30);
                break;
            default:
                cout << "Ataque no válido" << endl;
                return;
            }

            enemy.HP -= attackDamage;

            if (enemy.HP <= 0) {
                enemy.HP = 0;
                enemy.isAlive = false;
            }

            cout << name << " le ha pegado un ataque de " << attackDamage << " a " << enemy.name << " y le quedan " << enemy.HP << " de vida." << endl;

            // Si el ataque fue el ataque especial = reducir el número de usos
            if (attackType == 3) {
                specialAttackUses--;
                if (specialAttackUses == 0) {
                    cout << "¡Ya no te quedan usos del ataque especial!" << endl;
                }
            }
        }
    }
};

// Función para letras en verde
void printGreen(const string& text) {
    cout << "\x1B[32m" << text << "\x1B[0m"; 
}

// Función para letras en rojo
void printRed(const string& text) {
    cout << "\x1B[31m" << text << "\x1B[0m"; 
}

int main() {
    srand(time(0));

    system("C:\\Users\\linoc\\OneDrive - Centre d'Estudis Monlau\\music.mp3");
    
    // Datos del personaje (héroe)
    Character hero("Heroe", 50, 70, 30, 500);

    // Datos del primer enemigo (jefe)
    Character boss("LLUCNEITOR", 40, 10, 20, 200);

    // Datos del segundo enemigo (basilisco)
    Character enemy2("BASILISCO", 30, 20, 10, 200);

    cout << "Escribe el nombre de tu personaje: ";
    cin >> hero.name;

    typeText("Bienvenido a mi juego de aventuras!\n");
    typeText("Te encuentras en un mundo lleno de desafios y peligros.\n");
    typeText("Debes enfrentarte a dos poderosos enemigos: LLUCNEITOR y BASILISCO.\n");
    typeText("Tu personaje, el valiente: " + hero.name + " , se embarca en esta epica mision.\n");
    typeText("Estas listo para la batalla? \n");

    while (hero.isAlive && (boss.isAlive || enemy2.isAlive)) {
        // Ataque del segundo enemigo (basilisco) al héroe
        if (enemy2.isAlive) {
            hero.HP -= enemy2.punchDamage + (rand() % 20); // Daño aleatorio
            if (hero.HP <= 0) {
                hero.HP = 0;
                hero.isAlive = false;
                printRed("Has muerto. GAME OVER\n");
                break;  // Salir del bucle si el héroe muere
            }
            else {
                cout << "El basilisco te ha pegado un tortazo y te quedan ";
                printGreen(to_string(hero.HP));
                cout << " de vida." << endl;
            }
        }

        // Ataque del jefe (LLUCNEITOR) al héroe
        if (boss.isAlive) {
            hero.HP -= boss.swordDamage + (rand() % 20); // Daño aleatorio
            if (hero.HP <= 0) {
                hero.HP = 0;
                hero.isAlive = false;
                printRed("Has muerto. GAME OVER\n");
                break;  // Salir del bucle si el héroe muere
            }
            else {
                cout << "LLUCNEITOR te ha pegado un espadazo y te quedan ";
                printGreen(to_string(hero.HP));
                cout << " de vida." << endl;
            }
        }

        if (hero.isAlive) {
            // Ataque del héroe al enemigo
            cout << "Elige el tipo de ataque para " << hero.name << ":\n";
            cout << "1- Espada (Valiente)\n";
            cout << "2- Magia (Cagon)\n";
            cout << "3- Fuletaso (Maestro) [Usos restantes: " << hero.specialAttackUses << "]\n";
            int attackType;
            cin >> attackType;

            if (attackType >= 1 && attackType <= 3) {
                cout << "A quien quieres atacar? 1- " << boss.name << " 2- " << enemy2.name << endl;
                int enemyChoice;
                cin >> enemyChoice;

                if (attackType == 3 && hero.specialAttackUses == 0) {
                    cout << "No te quedan usos del ataque especial, elige otro ataque." << endl;
                }
                else if (enemyChoice == 1 && boss.isAlive) {
                    hero.Attack(boss, attackType);
                    if (!boss.isAlive) {
                        printRed(hero.name + " ha matado a LLUCNEITOR, Felicidades!\n");
                    }
                }
                else if (enemyChoice == 2 && enemy2.isAlive) {
                    hero.Attack(enemy2, attackType);
                    if (!enemy2.isAlive) {
                        printRed(hero.name + " ha matado al basilisco, Felicidades!\n");
                    }
                }
                else {
                    cout << "Opcion no valida" << endl;
                }
            }
            else {
                cout << "Opcion no valida" << endl;
            }
        }
    }

    if (!boss.isAlive && !enemy2.isAlive) {
        printGreen("Has vencido el juego!\n");
    }

}









// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
