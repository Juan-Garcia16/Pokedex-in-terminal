#include <iostream>
#include <stdio.h>
#include <cstdlib>  // Para system()
#include <string>   // Para cin.ignore()
#include <cctype>

using namespace std;

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

char *archivo = (char *)"pokedex1.bin";

// Funcion para limpiar pantalla dependiendo del sistema operativo
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void menu(){
    clearScreen();
    cout << " Menu Principal \n";
    cout << " 1. Crear nuevo Pokemon \n";
    cout << " 2. Ver todos los Pokemon \n";
    cout << " 3. Consultar un Pokemon \n";
    cout << " 4. Modificar un Pokemon \n";
    cout << " 5. Ordenar los Pokemon \n";
    cout << " 6. Eliminar Pokemon \n";
    cout << " 7. Fitrar \n";
    cout << " 8. Salir \n";
    cout << " Su opcion : ";

}

void newPokemon() {
    FILE *archi;
    Pokemon pokemon;
    int lastId = 0; // Para anadir nuevo Pokemon en la siguiente posicion posible

    archi = fopen(archivo, "rb");

    if (archi != NULL) {
        while (fread(&pokemon, sizeof(Pokemon), 1, archi) == 1) {
        lastId = pokemon.id; // Guarda el ultimo id leisdo
        }
        fclose(archi);
    }

    // Reabrir en modo de adicion binaria para escribir
    archi = fopen(archivo, "ab");
    if (archi == NULL) {
        cout << "Error en la operación de archivo" << endl;
        return;
    }

    // Asignar el siguiente id al nuevo Pokemon
    pokemon.id = lastId + 1;

    // Limpiar el buffer
    cin.ignore();

    cout << "Ingrese el nombre del Pokemon: ";
    cin.getline(pokemon.name, sizeof(pokemon.name));

    int type;  // Variable para capturar la opción ingresada por el usuario
    cout << "Ingrese su tipo: \n";
    cout << "1. Planta" << "     5. Agua" << "         9.  Tierra" << "     13. Roca" << endl;
    cout << "2. Veneno" << "     6. Bicho" << "        10. Hada" << "       14. Acero" << endl;
    cout << "3. Fuego" << "      7. Normal" << "       11. Lucha" << "      15. Hielo" << endl;
    cout << "4. Volador" << "    8. Electrico" << "    12. Psiquico" << "   16. Fantasma" << endl;
    cin >> type;

    switch (type) {
        case 1: strcpy(pokemon.type, "Planta"); break;
        case 2: strcpy(pokemon.type, "Veneno"); break;
        case 3: strcpy(pokemon.type, "Fuego"); break;
        case 4: strcpy(pokemon.type, "Volador"); break;
        case 5: strcpy(pokemon.type, "Agua"); break;
        case 6: strcpy(pokemon.type, "Bicho"); break;
        case 7: strcpy(pokemon.type, "Normal"); break;
        case 8: strcpy(pokemon.type, "Electrico"); break;
        case 9: strcpy(pokemon.type, "Tierra"); break;
        case 10: strcpy(pokemon.type, "Hada"); break;
        case 11: strcpy(pokemon.type, "Lucha"); break;
        case 12: strcpy(pokemon.type, "Psiquico"); break;
        case 13: strcpy(pokemon.type, "Roca"); break;
        case 14: strcpy(pokemon.type, "Acero"); break;
        case 15: strcpy(pokemon.type, "Hielo"); break;
        case 16: strcpy(pokemon.type, "Fantasma"); break;
        default:
            cout << "Opción no válida. Se asignará 'Desconocido'." << endl;
            strcpy(pokemon.type, "Desconocido"); break;
    }

    cout << "\t\t\tESTADÍSTICAS\n\n";
    cout << "Ingrese su vida: ";
    cin >> pokemon.hp;

    cout << "Ingrese su ataque: ";
    cin >> pokemon.attack;

    cout << "Ingrese su defensa: ";
    cin >> pokemon.defense;

    cout << "Ingrese su ataque especial: ";
    cin >> pokemon.specialAttack;

    cout << "Ingrese su defensa especial: ";
    cin >> pokemon.specialDefense;

    cout << "Ingrese su velocidad: ";
    cin >> pokemon.speed;

    cin.ignore();

    cout << "Ingrese una breve descripcion del Pokemon: ";
    cin.getline(pokemon.description, sizeof(pokemon.description));

    // Posicionar el puntero al final del archivo para agregar el nuevo Pokomon
    fseek(archi, 0, SEEK_END);
    fwrite(&pokemon, sizeof(Pokemon), 1, archi);

    cout << "¡Pokemon anadido exitosamente con ID " << pokemon.id << "!" << endl;

    fclose(archi);
}


void listPokemon() {
    FILE *archi;
    Pokemon pokemon;
    archi = fopen(archivo, "rb");

    if (archi == NULL) {
        cout << "\nError en la operación de archivo\n";
    } else {
        while (fread(&pokemon, sizeof(Pokemon), 1, archi)) {
            // Imprimir los detalles de cada Pokemon 
            cout << "ID: " << pokemon.id << "\n";
            cout << "Nombre: " << pokemon.name << "\n";
            cout << "Tipo: " << pokemon.type << "\n";
            cout << "Vida: " << pokemon.hp << "\n";
            cout << "Ataque: " << pokemon.attack << "\n";
            cout << "Defensa: " << pokemon.defense << "\n";
            cout << "Ataque Especial: " << pokemon.specialAttack << "\n";
            cout << "Defensa Especial: " << pokemon.specialDefense << "\n";
            cout << "Velocidad: " << pokemon.speed << "\n";
            cout << "Descripción: " << pokemon.description << "\n";
            cout << "---------------------------------------------------------------------------------\n";
        }

        cout << "\n\nPresione Enter para continuar...";
        cin.ignore();
        cin.get();
    }
    fclose(archi);
}


void searchPokemon(){
    FILE *archi;
    int ID;
    Pokemon pokemon;
    char confirm;

    archi = fopen(archivo, "r+b");
    if (archi == NULL)
    {
        cout << "\n Error en la operacion de archivo";
    } else {
        do
        {
            rewind(archi); // Inicio del archivo
            int found = 0;

            cout << "Ingrese el ID a consultar";
            cin >> ID;
            cin.ignore();

            while (fread(&pokemon, sizeof(pokemon), 1, archi) && !found)
            {
                if (ID == pokemon.id) 
                {
                    found = 1;
                    break;
                }
                
            }

            if (!found)
            {
                cout << "\n El Pokemon no esta registrado";
                cout << "\nPresiones Enter para continuar...";
                cin.get();
            } else {
                cout << "Nombre: " << pokemon.name << "\n";
                cout << "Tipo: " << pokemon.type << "\n";
                cout << "Vida: " << pokemon.hp << "\n";
                cout << "Ataque: " << pokemon.attack << "\n";
                cout << "Defensa: " << pokemon.defense << "\n";
                cout << "Ataque Especial: " << pokemon.specialAttack << "\n";
                cout << "Defensa Especial: " << pokemon.specialDefense << "\n";
                cout << "Velocidad: " << pokemon.speed << "\n";
                cout << "Descripción: " << pokemon.description << "\n";
            }

            cout << "\n Desea consultar otro Pokemon S/N ";
            cin >> confirm;
            cin.ignore();

        } while (confirm == 's' || confirm == 'S');   
        fclose(archi);
    }
}

void modifyPokemon(){

}

void sortPokemon(){

}

void deletePokemon(){

}

void filterPokemon(){

}


int main() {
    int op;
    char exit = 0;
    do {
        menu();
        cin >> op;
          // Ignorar el salto de línea después de la entrada
        clearScreen();
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