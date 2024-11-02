#include <iostream>
#include <stdio.h>
#include <cstdlib>  // Para system()
#include <string>   // Para cin.ignore()

struct Pokemon {
    int id;
    char name[20];
    char type[20];
    int hp;
    int attack;
    int defense;
    int specialAttack;
    int specialDefense;
    int speed;
    char description[200];
};

char *archivo = (char *)"conexion_api/pokedex1.bin.bin";

// Funcion para limpiar pantalla dependiendo del sistema operativo
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}


int main() {
    int op;
    char exit = 0;
    do {
        menu();
        cin >> op;
        cin.ignore();  // Ignorar el salto de línea después de la entrada
        clear_screen();
        switch (op) {
            case 1: newPokemon(); break;
            case 2: listPokemon(); break;
            case 3: searchPokemon(); break;
            case 4: modifyPokemon(); break;
            case 5: sortPokemon(); break; //esta en veremos
            case 6: deletePokemon(); break;
            case 7: filterPokemon(); break;
            case 8: exit = 1; break;
        }
    } while (!exit);
    return 0;
}