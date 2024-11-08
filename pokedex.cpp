#include <iostream>
#include <stdio.h>
#include <cstdlib>  // Para system()
#include <string>   // Para cin.ignore()
#include <cstring>
#include <cctype>
#include <locale>
#include <limits> // Para numeric_limits en readInt()

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

void playMusic(){
    #ifdef _WIN32
    // Reproducir el archivo de música en Windows
    system("start /min wmplayer Littleroot_Town.mp3");
    #elif defined(__APPLE__)
    // Reproducir el archivo de música en macOS
    system("afplay Littleroot_Town.mp3 &");
    #else
    std::cerr << "Error: sistema operativo no soportado." << std::endl;
    #endif
}

// Funcion para limpiar pantalla dependiendo del sistema operativo
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Menu principal
void menu(){
    clearScreen();
    cout << "                              \t\t⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n";
    cout << "                              \t\t⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣾⣿⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n";
    cout << "                              \t\t⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⣿⡿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n";
    cout << "                              \t\t⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⡟⠉⠀⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣴⣶⣿⡿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡤⢤\n";
    cout << "                              \t\t⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠋⠀⠐⠀⢰⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡴⠖⢉⣿⣿⣿⠟⠡⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⠖⠋⠀⡼\n";
    cout << "                              \t\t⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠰⡼⠀⠀⠈⢆⣸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡴⠊⠁⠀⠀⢸⣿⡿⠃⡄⠀⠀⠀⠀⠀⠀⠀⠀⢀⡴⠊⠁⠀⠀⠀⡇\n";
    cout << "                              \t\t⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣇⠀⠀⠀⠀⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣤⠞⠁⠀⠀⠀⠀⠀⣾⠟⠡⠀⠀⠀⠀⠀⠀⠀⠀⢀⡴⠋⠀⠀⠀⠀⠀⠀⡏\n";
    cout << "                              \t\t⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠃⠀⠀⠀⠄⢼⠀⠀⢀⣀⣤⠤⠤⠤⣤⣀⣀⡤⠋⠀⠀⠀⠀⠀⠀⢀⡼⠃⠀⠀⠀⠀⠀⠀⠀⠀⢀⡴⠋⠀⠀⠀⠀⠀⠀⠀⢀⡇\n";
    cout << "                              \t\t⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡠⠟⠚⠉⠁⠀⠀⠀⠀⠀⠀⣠⠋⠀⠀⠀⠀⠀⠀⠀⣠⠋⠀⠀⠀⠀⠀⠀⠀⠀⣠⠞⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡇\n";
    cout << "                              \t\t⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠍⣀⠴⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⠀⠀⠀⠀⡠⣠⠞⠁⠀⠀⠀⠀⠀⠀⠀⣠⠞⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀\n";
    cout << "                              \t\t⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠶⢷⡀⠀⠀⠀⠀⠀⠀⢀⠞⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡴⠃⠀⣸⠀\n";
    cout << "         POKEDEX              \t\t⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⢋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡹⣦⠀⠀⠀⢀⡴⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡤⠔⠚⠁⠀\n";
    cout << "                              \t\t⠀⠀⠀⠀⠀⠀⠀⠀⣠⠃⢸⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⠚⠀⠀⠀⠀⠀⠀⠀⠈⠁⠞⡹⢾⣧⣠⣠⠎⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡤⠔⠋⠁⠀⠀⠀⠀⠀\n";
    cout << " 1. Crear nuevo Pokemon       \t\t⠀⠀⠀⠀⢀⣴⠮⡍⡏⠀⣿⣽⡄⠀⠀⠀⠀⢀⠀⣠⢶⣿⣿⣧⠀⠀⢠⠞⠀⠀⢠⡏⣳⣯⠚⠉⠯⢽⣷⢤⡀⠀⠀⠀⠀⠀⢠⠴⠚⠁⠀⠃⠀⠀⠀⠀⠀⠀⠀\n";
    cout << " 2. Ver todos los Pokemon     \t\t⢸⡉⢆⣀⡏⡰⣦⣇⡟⣦⠹⠿⠿⠀⠀⠀⠀⠘⠞⠹⢾⣿⣿⢟⣠⣒⣿⠿⣭⣲⣼⡿⠘⠞⠠⠀⠁⠀⢳⡄⠉⠳⢦⡀⠀⠀⠈⠳⢆⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n";
    cout << " 3. Consultar un Pokemon      \t\t⠢⠇⣴⣆⣺⡵⢹⣿⣉⢿⣇⠀⠀⠀⠦⠀⠀⠀⠀⠀⠀⠀⢇⠀⣇⠈⠿⠒⢯⠀⠻⣃⠇⠀⠀⠀⠀⠀⣜⣿⡄⠀⠀⠈⠓⢦⡀⠀⠀⠙⢦⡀⠀⠀⠀⠀⠀⠀⠀\n";
    cout << " 4. Modificar un Pokemon      \t\t⠀⠀⠸⣑⢫⡵⠀⠈⠈⠳⣟⠀⠀⠙⠒⠒⠢⠤⠞⠁⠀⠀⠈⠀⠙⠣⠽⠶⠋⠀⠀⠚⠋⠀⠀⠀⠀⣼⣿⣿⣷⡀⠀⠀⢀⠜⠁⠀⠀⠀⠀⣹⠆⠀⠀⠀⠀⠀⠀\n";
    cout << " 5. Ordenar los Pokemon       \t\t⠀⠀⠀⠈⢪⠳⠀⠀⠀⠀⢈⠟⠂⣢⣄⡀⠀⠀⠀⠀⠀⠀⣀⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⠛⠛⠁⠀⢣⢠⡴⠋⠀⠀⠀⣠⠔⠋⡄⠐⠀⠀⠀⠀⠀⠀\n";
    cout << " 6. Eliminar Pokemon          \t\t⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⢏⡴⠋⠁⠹⠷⣆⠀⠀⠀⢰⠏⠇⠈⠙⠲⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣿⡏⠀⠀⣠⠖⠋⠀⠀⠀⠁⠀⠀⠀⠀⠀⠀⠀\n";
    cout << " 7. Filtrar por tipos puros   \t\t⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡟⠀⠀⠁⢀⠀⡹⠄⠀⠀⢸⡄⠈⠒⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⣿⣿⣿⣀⠀⠈⠷⠦⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n";
    cout << " 8. Salir                     \t\t⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢷⣀⠀⠀⣨⡷⢻⠀⠀⠀⠀⠹⣆⠀⠀⠀⠀⠀⠀⣀⣴⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⡏⣉⣾⣳⣬⣺⡷⠀⠀⠀⠀⠀⠀⠀⠀⠀\n";
    cout << "                              \t\t⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢩⠟⣇⠀⠁⠀⠀⠀⠀⠀⠈⠑⠢⠤⠤⠔⢊⠵⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⡿⠟⠋⢁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n";
    cout << "                              \t\t⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡟⠀⠸⠆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡼⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣷⡄⠀⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n";
    cout << "                              \t\t⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡿⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n";
    cout << "                              \t\t⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠳⣄⠀⠀⠈⠳⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠸⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n";
    cout << "                              \t\t⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣼⣗⡢⠤⠄⣈⣙⣲⣤⣀⡀⠀⠀⠀⠀⠀⠹⡀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣲⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n";
    cout << "                              \t\t⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢯⠏⣨⠎⣳⠤⠚⠉⠀⠀⠀⠉⠙⠓⠒⠒⠒⡒⠛⠲⢤⣀⣀⣀⣀⠤⠤⡾⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n";
    cout << "                              \t\t⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠁⠙⠉⠀⡄⠘⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⣓⡍⠉⡒⡾⢡⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n";
    cout << "                              \t\t⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠁⠑⠋⠙⡃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n";
    cout << "Su opcion: ";
}


// Funcion para validar la entrada de numeros positivos
int readInt() {
    int value;

    while (true) {
        cin >> value; // Recibe la entrada

        // Verifica si la entrada es válida y si es un número positivo dentro del maximo permitido
        if (cin.fail() || value <= 0 || value > numeric_limits<int>::max()) {
            // Si hay un error, se limpia el estado de error y el buffer
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada inválida. Por favor, ingrese un número positivo." << endl;
        } else {
            // Retorna el número válido
            return value;
        }
    }
}

// Funcion para validar la entrada de numeros permitidos para el tipo de Pokemon
int readType() {
    int value;

    while (true) {
        cin >> value; // Recibe la entrada

        // Verifica si la entrada es válida y si es un número positivo dentro del rango permitido
        if (cin.fail() || value <= 0 || value > 18) {
            // Si hay un error, se limpia el estado de error y el buffer
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada inválida. Por favor, ingrese un número entre 1 y 18." << endl;
        } else {
            // Retorna el número válido
            return value;
        }
    }
}

// Funcion para validar estadisticas reales de un pokemon
int readStats() {
    int value;

    while (true) {
        cin >> value; // Recibe la entrada

        // Verifica si la entrada es válida y si no se pasa del maximo
        if (cin.fail() || value <= 0 || value > 255) {
            // Si hay un error, se limpia el estado de error y el buffer
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada inválida, ingrese un numero. Valor minimo 1, valor maximo 255." << endl;
        } else {
            // Retorna el número válido
            return value;
        }
    }
}

// Funcion para adicionar un Pokemon
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

    // Validar que el nombre no esté vacío
    do {
        cout << "Ingrese el nombre del Pokemon: ";
        cin.getline(pokemon.name, sizeof(pokemon.name));
        if (strlen(pokemon.name) == 0) {
            cout << "El nombre no puede estar vacío. Inténtelo de nuevo." << endl;
        }
    } while (strlen(pokemon.name) == 0);

    int type;  // Variable para capturar la opción ingresada por el usuario
    cout << "Ingrese su tipo: \n";
    cout << "1. Planta" << "     7. Normal" << "       13. Roca" << endl;
    cout << "2. Veneno" << "     8. Eléctrico" << "    14. Acero" << endl;
    cout << "3. Fuego" << "      9.  Tierra" << "      15. Hielo" << endl;
    cout << "4. Volador" << "    10. Hada" << "        16. Fantasma" << endl;
    cout << "5. Agua" << "       11. Lucha" << "       17. Dragón" << endl;
    cout << "6. Bicho" << "      12. Psíquico" << "    18. Siniestro" << endl;

    cout << "Su opcion: ";
    type = readType();

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
        case 17: strcpy(pokemon.type, "Dragón"); break;
        case 18: strcpy(pokemon.type, "Siniestro"); break;
    }

    cout << "\t\t\tESTADÍSTICAS\n\n";
    cout << "Ingrese su vida: ";
    pokemon.hp = readStats();

    cout << "Ingrese su ataque: ";
    pokemon.attack = readStats();

    cout << "Ingrese su defensa: ";
    pokemon.defense = readStats();

    cout << "Ingrese su ataque especial: ";
    pokemon.specialAttack = readStats();

    cout << "Ingrese su defensa especial: ";
    pokemon.specialDefense = readStats();

    cout << "Ingrese su velocidad: ";
    pokemon.speed = readStats();

    cin.ignore();

    do
    {
        cout << "Ingrese una breve descripcion del Pokemon: ";
        cin.getline(pokemon.description, sizeof(pokemon.description));
        if (strlen(pokemon.description) == 0) {
            cout << "La descripcion no puede estar vacía. Inténtelo de nuevo." << endl;
        }
    } while (strlen(pokemon.description) == 0);
    
    

    // Posicionar el puntero al final del archivo para agregar el nuevo Pokomon
    fseek(archi, 0, SEEK_END);
    fwrite(&pokemon, sizeof(Pokemon), 1, archi);

    cout << "\n¡Pokemon anadido exitosamente con ID " << pokemon.id << "!" << endl;
    cout << "Presione Enter para continuar..." << endl;
    cin.get();  // Espera una entrada del usuario

    fclose(archi);
}

// Funcion para mostrar todos los Pokemon
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

        cout << "\nPresione Enter para continuar...";
        cin.ignore();
        cin.get();
    }
    fclose(archi);
}

// Funcion para buscar un Pokemon por su ID
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

            cout << "Ingrese el ID a consultar: ";
            ID = readInt();

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
                cout << "\n El Pokemon no esta registrado.";
                cin.get();
            } else {
                cout << "\n--------------------------------------------------------------------\n";
                cout << "Nombre: " << pokemon.name << "\n";
                cout << "Tipo: " << pokemon.type << "\n";
                cout << "Vida: " << pokemon.hp << "\n";
                cout << "Ataque: " << pokemon.attack << "\n";
                cout << "Defensa: " << pokemon.defense << "\n";
                cout << "Ataque Especial: " << pokemon.specialAttack << "\n";
                cout << "Defensa Especial: " << pokemon.specialDefense << "\n";
                cout << "Velocidad: " << pokemon.speed << "\n";
                cout << "Descripción: " << pokemon.description << "\n";
                cout << "--------------------------------------------------------------------\n";
            }

            cout << "\n Desea consultar otro Pokemon S/N :";
            cin >> confirm;
            cin.ignore();

        } while (confirm == 's' || confirm == 'S');   
        fclose(archi);
    }
}

// Funcion para modificar los datos de un Pokemon
void modifyPokemon() {
    FILE *archi;
    int ID, pos, k, found = 0;
    Pokemon pokemon;
    char confirm;

    archi = fopen(archivo, "r+b");
    if (archi == NULL) {
        cout << "\nError en la operacion de archivo";
    } else {
        do {
            rewind(archi);
            k = 0;
            cout << "Ingrese ID del Pokemon a modificar: ";
            ID = readInt();

            while (fread(&pokemon, sizeof(pokemon), 1, archi) && !found) {
                if (ID == pokemon.id) {
                    found = 1;
                    pos = k;
                    break;
                }
                k++;
            }

            if (!found) {
                cout << "El Pokemon no existe";
                cout << "\nPresione Enter para continuar...";
                cin.ignore();
                cin.get();
                return;
            }

            // Menu para seleccionar el campo a modificar
            int option;
            int type; // Declarar la variable type aquí
            do {
                cout << "\n---------------------------------------------";
                cout << "\nSeleccione el campo a modificar:\n";
                cout << "1. Nombre\n";
                cout << "2. Tipo\n";
                cout << "3. Vida\n";
                cout << "4. Ataque\n";
                cout << "5. Defensa\n";
                cout << "6. Ataque Especial\n";
                cout << "7. Defensa Especial\n";
                cout << "8. Velocidad\n";
                cout << "9. Descripción\n";
                cout << "10. Salir y Guardar\n";
                cout << "Opcion: ";
                option = readInt();

                switch (option) {
                    case 1:
                        cout << "\n---------------------------------------------\n";
                        do
                        {
                            cout << "Ingrese el nuevo nombre: ";
                            cin.ignore();
                            cin.getline(pokemon.name, sizeof(pokemon.name));
                            if (strlen(pokemon.name) == 0)
                            {
                                cout << "El nombre no puede estar vacío. Inténtelo de nuevo." << endl;
                            }
                            
                        } while (strlen(pokemon.name) == 0);
                        
                        break;
                    case 2:
                        cout << "\n---------------------------------------------\n";
                        cout << "Ingrese el nuevo tipo: \n";
                        cout << "1. Planta" << "     7. Normal" << "       13. Roca" << endl;
                        cout << "2. Veneno" << "     8. Eléctrico" << "    14. Acero" << endl;
                        cout << "3. Fuego" << "      9. Tierra" << "       15. Hielo" << endl;
                        cout << "4. Volador" << "    10. Hada" << "        16. Fantasma" << endl;
                        cout << "5. Agua" << "       11. Lucha" << "       17. Dragón" << endl;
                        cout << "6. Bicho" << "      12. Psíquico" << "    18. Siniestro" << endl;
                        cout << "Opcion: ";
                        type = readType();
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
                            case 17: strcpy(pokemon.type, "Dragon"); break;
                            case 18: strcpy(pokemon.type, "Siniestro"); break;
                            default: cout << "Tipo inválido. No se realizaron cambios.\n"; break;
                        }
                        break;
                    case 3:
                        cout << "\n---------------------------------------------\n";
                        cout << "Ingrese la nueva vida: ";
                        pokemon.hp = readStats();
                        break;
                    case 4:
                        cout << "\n---------------------------------------------\n";
                        cout << "Ingrese el nuevo ataque: ";
                        pokemon.attack = readStats();
                        break;
                    case 5:
                        cout << "\n---------------------------------------------\n";
                        cout << "Ingrese la nueva defensa: ";
                        pokemon.defense = readStats();
                        break;
                    case 6:
                        cout << "\n---------------------------------------------\n";
                        cout << "Ingrese el nuevo ataque especial: ";
                        pokemon.specialAttack = readStats();
                        break;
                    case 7:
                        cout << "\n---------------------------------------------\n";
                        cout << "Ingrese la nueva defensa especial: ";
                        pokemon.specialDefense = readStats();
                        break;
                    case 8:
                        cout << "\n---------------------------------------------\n";
                        cout << "Ingrese la nueva velocidad: ";
                        pokemon.speed = readStats();
                        break;
                    case 9:
                        cout << "\n---------------------------------------------\n";
                        do
                        {
                            cout << "Ingrese la nueva descripción: ";
                            cin.ignore();
                            cin.getline(pokemon.description, sizeof(pokemon.description));
                            if (strlen(pokemon.description) == 0) {
                                cout << "La descripción no puede estar vacía. Inténtelo de nuevo." << endl;
                            }    
                        } while (strlen(pokemon.description) == 0);
                        
                        break;
                    case 10:
                        break;
                    default:
                        cout << "Opción inválida. Inténtelo de nuevo.\n";
                }

                if (option != 10) {
                    // Escribir el registro modificado en el archivo
                    fseek(archi, pos * sizeof(Pokemon), SEEK_SET);
                    fwrite(&pokemon, sizeof(Pokemon), 1, archi);

                    cout << "\nPresione Enter para continuar...";
                    //cin.ignore();
                    cin.get();
                }
            } while (option != 10);
        } while (!found);
    }

    fclose(archi);
}

// Funcion para ordenar toda la Pokedex de distintos modos
void sortPokemon(){
    int op = 0;
    Pokemon pokemon;

    FILE *archi;
    archi = fopen(archivo, "rb");

    if (archi == NULL)
    {
        cout << "Error en la operacio de archivo";
    } else {
        do
        {
            cout << "\nComo desea ordenar los datos\n";
            cout << "\n 1. Por ID \n";
            cout << " 2. Por Nombre \n";
            cout << " 3. Por Vida \n";
            cout << " 4. Por Ataque \n";
            cout << " 5. Por Defensa \n";
            cout << " 6. Por Ataque especial \n";
            cout << " 7. Por Defensa especial \n";
            cout << " 8. Por Velocidad \n";
            cout << "Su opcion: "; 
            op = readInt();
        } while (op <= 0 || op > 8);

        // Contar la cantidad de registros
        int count = 0;
        
        while (fread(&pokemon, sizeof(Pokemon), 1, archi)) {
                count++;
            }

        Pokemon currentPokemon[count];
        rewind(archi);
        fread(currentPokemon, sizeof(Pokemon), count, archi);
        fclose(archi);

        switch (op)
        {

        // Ordenar por ID
        case 1 : 
            for (int i = 0; i < count - 1; i++) {
                for (int j = i + 1; j < count; j++) {

                    if (currentPokemon[i].id > currentPokemon[j].id) {
                        Pokemon tempId = currentPokemon[i];
                        currentPokemon[i] = currentPokemon[j];
                        currentPokemon[j] = tempId;
                    }
                }    
            } 
            break;

        
        // Ordenar por nombre
        case 2 : 
            for (int i = 0; i < count - 1; i++) {
                    for (int j = i + 1; j < count; j++) {

                        if (strcmp(currentPokemon[i].name, currentPokemon[j].name) > 0) {
                            Pokemon tempName = currentPokemon[i];
                            currentPokemon[i] = currentPokemon[j];
                            currentPokemon[j] = tempName;
                        }
                    }
                }
                break;
        
        // Ordenar por HP (vida)
        case 3 : 
            for (int i = 0; i < count - 1; i++) {
                for (int j = i + 1; j < count; j++) {

                    if (currentPokemon[i].hp > currentPokemon[j].hp) {
                        Pokemon tempHp = currentPokemon[i];
                        currentPokemon[i] = currentPokemon[j];
                        currentPokemon[j] = tempHp;
                    }
                }    
            } 
            break;

        // Ordenar por Ataque
        case 4 : 
            for (int i = 0; i < count - 1; i++) {
                for (int j = i + 1; j < count; j++) {

                    if (currentPokemon[i].attack > currentPokemon[j].attack) {
                        Pokemon tempAttack = currentPokemon[i];
                        currentPokemon[i] = currentPokemon[j];
                        currentPokemon[j] = tempAttack;
                    }
                }    
            } 
            break;

        //Ordenar por Defensa
        case 5 : 
            for (int i = 0; i < count - 1; i++) {
                for (int j = i + 1; j < count; j++) {

                    if (currentPokemon[i].defense > currentPokemon[j].defense) {
                        Pokemon tempDefense = currentPokemon[i];
                        currentPokemon[i] = currentPokemon[j];
                        currentPokemon[j] = tempDefense;
                    }
                }    
            } 
            break;

        //Ordenar por Ataque Especial
        case 6 : 
            for (int i = 0; i < count - 1; i++) {
                for (int j = i + 1; j < count; j++) {

                    if (currentPokemon[i].specialAttack > currentPokemon[j].specialAttack) {
                        Pokemon tempSAttack = currentPokemon[i];
                        currentPokemon[i] = currentPokemon[j];
                        currentPokemon[j] = tempSAttack;
                    }
                }    
            } 
            break;

        //Ordenar por Defensa Especial
        case 7 : 
            for (int i = 0; i < count - 1; i++) {
                for (int j = i + 1; j < count; j++) {

                    if (currentPokemon[i].specialDefense > currentPokemon[j].specialDefense) {
                        Pokemon tempSDefense = currentPokemon[i];
                        currentPokemon[i] = currentPokemon[j];
                        currentPokemon[j] = tempSDefense;
                    }
                }    
            } 
            break;

        //Ordenar por Velocidad
        case 8 : 
            for (int i = 0; i < count - 1; i++) {
                for (int j = i + 1; j < count; j++) {

                    if (currentPokemon[i].speed > currentPokemon[j].speed) {
                        Pokemon tempSpeed = currentPokemon[i];
                        currentPokemon[i] = currentPokemon[j];
                        currentPokemon[j] = tempSpeed;
                    }
                }    
            } 
            break;

        }

        // Guardar los datos ordenados de vuelta en el archivo
        archi = fopen(archivo, "wb");
        fwrite(currentPokemon, sizeof(Pokemon), count, archi);

        cout << "\n Los datos han sido ordenados y guardados correctamente.\n";
        cout << "Presione Enter para continuar..." << endl;
        cin.get();  // Espera una entrada del usuario
        fclose(archi);
        
    }
}

// Funcion para eliminar el registro de un Pokemon
void deletePokemon(){
    FILE *archi, *temp;
    int ID;
    Pokemon pokemon;
    int found = 0;

    archi = fopen(archivo, "rb");
    if (archi == NULL)
    {
        cout << "\n Error en la operacion de archivo";
        return;
    }
    
    // Crear un archivo temporal en modo escritura
    temp = fopen("temp.bin", "wb");
    if (temp == NULL)
    {
        cout << "\n Error al crear el archivo temporal";
        fclose(archi);
        return;
    }

    cout << "\n Ingrese el ID del Pokemon a eliminar: ";
    ID = readInt();

    // Leer y copiar solo los registros que no coincidan con el ID a eliminar
    while (fread(&pokemon, sizeof(Pokemon), 1, archi)) {
        if (pokemon.id == ID) {
            found = 1;
            cout << "\n El Pokemon con ID " << ID << " ha sido eliminado.\n";
        } else {
            fwrite(&pokemon, sizeof(Pokemon), 1, temp);
        }
    }

    fclose(archi);
    fclose(temp);
    
    // Si se encuentra el registro se escribe un nuevo archivo original
    if (found) {
        remove(archivo);  // eliminar el archivo original
        rename("temp.bin", archivo);  // eenombrar el archivo temporal al nombre original
    } else {
        cout << "\n No se encontro un Pokemon con el ID especificado." << endl;
        remove("temp.bin");  // eliminar el archivo temporal sin uso
    }

    cout << "Presione Enter para continuar..." << endl;
    cin.ignore(); // limpiar el buffer de entrada
    cin.get();  // Espera una entrada del usuario
}

// Funcion para filtrar Pokemon segun su tipo
void filterPokemon() {
    Pokemon pokemon;
    char filterType[20];
    FILE *archi, *temp;
    archi = fopen(archivo, "rb");

    // Crear un archivo temporal en modo escritura
    temp = fopen("type.bin", "wb");
    if (temp == NULL) {
        cout << "\n Error al crear el archivo temporal";
        fclose(archi);
        return;
    }

    if (archi == NULL) {
        cout << "Error en la operación de archivo";
        fclose(temp);  // Cerrar el archivo temporal si archi es NULL
        return;
    } else {
        int type;  // Variable para capturar la opción ingresada por el usuario
        cout << "\nQue tipo desea filtrar?: \n";
        cout << "1. Planta" << "     7. Normal" << "       13. Roca" << endl;
        cout << "2. Veneno" << "     8. Eléctrico" << "    14. Acero" << endl;
        cout << "3. Fuego" << "      9. Tierra" << "       15. Hielo" << endl;
        cout << "4. Volador" << "    10. Hada" << "        16. Fantasma" << endl;
        cout << "5. Agua" << "       11. Lucha" << "       17. Dragón" << endl;
        cout << "6. Bicho" << "      12. Psíquico" << "    18. Siniestro" << endl;
        cout << "\nSu opción: ";
        type = readType();

        switch (type) {
            case 1: strcpy(filterType, "Planta"); break;
            case 2: strcpy(filterType, "Veneno"); break;
            case 3: strcpy(filterType, "Fuego"); break;
            case 4: strcpy(filterType, "Volador"); break;
            case 5: strcpy(filterType, "Agua"); break;
            case 6: strcpy(filterType, "Bicho"); break;
            case 7: strcpy(filterType, "Normal"); break;
            case 8: strcpy(filterType, "Eléctrico"); break;
            case 9: strcpy(filterType, "Tierra"); break;
            case 10: strcpy(filterType, "Hada"); break;
            case 11: strcpy(filterType, "Lucha"); break;
            case 12: strcpy(filterType, "Psíquico"); break;
            case 13: strcpy(filterType, "Roca"); break;
            case 14: strcpy(filterType, "Acero"); break;
            case 15: strcpy(filterType, "Hielo"); break;
            case 16: strcpy(filterType, "Fantasma"); break;
            case 17: strcpy(filterType, "Dragón"); break;
            case 18: strcpy(filterType, "Siniestro"); break;
        }
        cout << "---------------------------------------------------------------------------------\n"; 

        // Leer y copiar solo los registros que coincidan con el tipo filtrado
        while (fread(&pokemon, sizeof(Pokemon), 1, archi) == 1) {
            if (strcmp(filterType, pokemon.type) == 0) {
                fwrite(&pokemon, sizeof(Pokemon), 1, temp);
                // Imprimir los detalles de cada Pokemon del tipo filtrado
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
        }

        // Cerrar archivos
        fclose(archi);
        fclose(temp);

        cout << "\n\nPresione Enter para continuar...";
        cin.ignore();
        cin.get();

        // Eliminar el archivo temporal
        remove("type.bin");
    }        
}

int main() {
    setlocale(LC_ALL, "es_ES.UTF-8");
    playMusic();
    int op;
    char exit = 0;
    do {

        menu();

        op = readInt();
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


