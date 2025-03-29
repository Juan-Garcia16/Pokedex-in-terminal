8/*
Realizar con manejo de archivos un micro proyecto que contenga  definición de estructuras de registro, el cual debe ser usado para Crear, guardar, borrar, actualizar, consultar y Ordenar,  a través de manejo de menús  y las funciones asociadas, como se han visto a lo largo de los diferentes ejemplos presentados,  los archivos pueden ser de texto o binarios; y con cualquier librería para este tipo de programas. 

Adicionar en un archivo de texto: explicación del manejo y el tema desarrollado, además de permitir o NO, que otros vean su código y lo mejoren. 

micro-PROYECTO  

Este proyecto consiste en desarrollar una Pokédex (base de datos Pokémon) interactiva
que permite a los usuarios gestionar y consultar información principalmente de los 151 Pokémon
de la primera generación de la franquicia. La aplicación permite realizar operaciones como
agregar, listar, consultar, modificar, ordenar, filtrar, combatir y eliminar registros de Pokémon en la base de datos.

La base de datos se almacena en un archivo binario y se maneja mediante estructuras de datos
definidas en C++. Cada Pokémon incluye atributos como id, nombre, tipo, y estadísticas
de combate, siguiendo el modelo clásico de las Pokédex de los videojuegos de Pokémon. 
La aplicación cuenta con un menú interactivo para facilitar la navegación y uso de sus funcionalidades.
**Características principales:**
- Carga automática de los 151 Pokémon de la primera generación, evitando que el usuario deba ingresar todo desde cero.
- Posibilidad de añadir nuevos Pokémon o actualizar los existentes.
- Manejo de archivos binarios para almacenar y recuperar los datos de la Pokédex.
- Operaciones CRUD: Crear, Leer, Actualizar y Eliminar registros.
- Funcionalidades de ordenamiento de registros para facilitar las consultas.



VSC ver 1.93.1 noviembre 13/2024          Juan Pablo García

*/
#include <iostream>
#include <cstdlib> // Para funciones del sistema
#include <string> // Para cin.ignore()
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



// Función para reproducir música
void playMusic(const char* filename) {
    #ifdef _WIN32
    // Reproducir el archivo de música en Windows
    string command = "start /min wmplayer ";
    command += filename;
    system(command.c_str());
    #elif defined(__APPLE__)
    // Reproducir el archivo de música en macOS
    string command = "afplay ";
    command += filename;
    command += " &";
    system(command.c_str());
    #else
    std::cerr << "Error: sistema operativo no soportado." << std::endl;
    #endif
}

void stopMusic() {
    #ifdef _WIN32
    // Detener la música en Windows
    system("taskkill /IM wmplayer.exe /F");
    #elif defined(__APPLE__)
    // Detener la música en macOS
    system("killall afplay");
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
    cout << " 8. Combate                   \t\t⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢷⣀⠀⠀⣨⡷⢻⠀⠀⠀⠀⠹⣆⠀⠀⠀⠀⠀⠀⣀⣴⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⡏⣉⣾⣳⣬⣺⡷⠀⠀⠀⠀⠀⠀⠀⠀⠀\n";
    cout << " 9. Salir                     \t\t⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢩⠟⣇⠀⠁⠀⠀⠀⠀⠀⠈⠑⠢⠤⠤⠔⢊⠵⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⡿⠟⠋⢁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n";
    cout << "                              \t\t⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡟⠀⠸⠆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡼⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣷⡄⠀⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n";
    cout << "                              \t\t⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡿⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n";
    cout << "                              \t\t⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠳⣄⠀⠀⠈⠳⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠸⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n";
    cout << "                              \t\t⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣼⣗⡢⠤⠄⣈⣙⣲⣤⣀⡀⠀⠀⠀⠀⠀⠹⡀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣲⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n";
    cout << "                              \t\t⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢯⠏⣨⠎⣳⠤⠚⠉⠀⠀⠀⠉⠙⠓⠒⠒⠒⡒⠛⠲⢤⣀⣀⣀⣀⠤⠤⡾⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n";
    cout << "                              \t\t⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠁⠙⠉⠀⡄⠘⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⣓⡍⠉⡒⡾⢡⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n";
    cout << "                              \t\t⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠁⠑⠋⠙⡃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n";
    cout << "Su opcion: ";
}


// Función para validar que el nombre solo contenga caracteres alfabéticos y espacios
bool validName(const char* name) {
    for (int i = 0; name[i] != '\0'; i++) {
        if (!isalpha(name[i]) && name[i] != ' ') {
            return false;
        }
    }
    return true;
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
        } else if (!validName(pokemon.name)) {
            cout << "El nombre solo puede contener caracteres alfabeticos. Inténtelo de nuevo." << endl;
        }
    } while (strlen(pokemon.name) == 0 || !validName(pokemon.name));

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
void searchPokemon() {
    FILE *archi;
    int ID;
    Pokemon pokemon;
    char confirm;

    archi = fopen(archivo, "rb");
    if (archi == NULL) {
        cout << "\nError en la operacion de archivo";
    } else {
        do {
            rewind(archi); // Inicio del archivo
            int found = 0;

            cout << "Ingrese el ID a consultar: ";
            ID = readInt();

            while (fread(&pokemon, sizeof(Pokemon), 1, archi) && !found) {
                if (ID == pokemon.id) {
                    found = 1;
                    break;
                }
            }

            if (!found) {
                cout << "\nEl Pokemon no está registrado.";
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

            // Validar la entrada del usuario para continuar consultando
            do {
                cout << "\nDesea consultar otro Pokemon (S/N): ";
                cin >> confirm;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer de entrada
                confirm = tolower(confirm);
                if (confirm != 's' && confirm != 'n') {
                    cout << "Entrada inválida. Por favor, ingrese 'S' para sí o 'N' para no." << endl;
                }
            } while (confirm != 's' && confirm != 'n');

        } while (confirm == 's');
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
void sortPokemon() {
    int op = 0;
    Pokemon *currentPokemon = nullptr; // Arreglo dinámico para almacenar los registros de Pokémon
    int count = 0; // Contador para el número de registros
    Pokemon temp; // Variable temporal para el intercambio de registros durante el ordenamiento

    FILE *archi;
    archi = fopen(archivo, "rb"); 

    if (archi == NULL) {
        cout << "Error en la operacion de archivo"; 
    } else {
        // Contar la cantidad de registros en el archivo
        while (fread(&temp, sizeof(Pokemon), 1, archi)) {
            count++;
        }

        // Reservar memoria para los registros segun los existentes
        currentPokemon = new Pokemon[count];

        // Leer todos los registros del archivo en el arreglo
        rewind(archi); // Volver al inicio del archivo
        fread(currentPokemon, sizeof(Pokemon), count, archi);
        fclose(archi);

        do {
            cout << "\nComo desea ordenar los datos\n";
            cout << "\n 1. Por ID \n";
            cout << " 2. Por Nombre \n";
            cout << " 3. Por Vida \n";
            cout << " 4. Por Ataque \n";
            cout << " 5. Por Defensa \n";
            cout << " 6. Por Ataque especial \n";
            cout << " 7. Por Defensa especial \n";
            cout << " 8. Por Velocidad \n";
            cout << " 9. Salir \n";
            cout << "Su opcion: ";
            op = readInt();

            // Ordenar el arreglo según la opción seleccionada
            switch (op) {
                case 1:
                    // Ordenar por ID
                    for (int i = 0; i < count - 1; i++) {
                        for (int j = i + 1; j < count; j++) {
                            if (currentPokemon[i].id > currentPokemon[j].id) {
                                temp = currentPokemon[i];
                                currentPokemon[i] = currentPokemon[j];
                                currentPokemon[j] = temp;
                            }
                        }
                    }
                    break;
                case 2:
                    // Ordenar por Nombre
                    for (int i = 0; i < count - 1; i++) {
                        for (int j = i + 1; j < count; j++) {
                            if (strcmp(currentPokemon[i].name, currentPokemon[j].name) > 0) {
                                temp = currentPokemon[i];
                                currentPokemon[i] = currentPokemon[j];
                                currentPokemon[j] = temp;
                            }
                        }
                    }
                    break;
                case 3:
                    // Ordenar por Vida
                    for (int i = 0; i < count - 1; i++) {
                        for (int j = i + 1; j < count; j++) {
                            if (currentPokemon[i].hp > currentPokemon[j].hp) {
                                temp = currentPokemon[i];
                                currentPokemon[i] = currentPokemon[j];
                                currentPokemon[j] = temp;
                            }
                        }
                    }
                    break;
                case 4:
                    // Ordenar por Ataque
                    for (int i = 0; i < count - 1; i++) {
                        for (int j = i + 1; j < count; j++) {
                            if (currentPokemon[i].attack > currentPokemon[j].attack) {
                                temp = currentPokemon[i];
                                currentPokemon[i] = currentPokemon[j];
                                currentPokemon[j] = temp;
                            }
                        }
                    }
                    break;
                case 5:
                    // Ordenar por Defensa
                    for (int i = 0; i < count - 1; i++) {
                        for (int j = i + 1; j < count; j++) {
                            if (currentPokemon[i].defense > currentPokemon[j].defense) {
                                temp = currentPokemon[i];
                                currentPokemon[i] = currentPokemon[j];
                                currentPokemon[j] = temp;
                            }
                        }
                    }
                    break;
                case 6:
                    // Ordenar por Ataque especial
                    for (int i = 0; i < count - 1; i++) {
                        for (int j = i + 1; j < count; j++) {
                            if (currentPokemon[i].specialAttack > currentPokemon[j].specialAttack) {
                                temp = currentPokemon[i];
                                currentPokemon[i] = currentPokemon[j];
                                currentPokemon[j] = temp;
                            }
                        }
                    }
                    break;
                case 7:
                    // Ordenar por Defensa especial
                    for (int i = 0; i < count - 1; i++) {
                        for (int j = i + 1; j < count; j++) {
                            if (currentPokemon[i].specialDefense > currentPokemon[j].specialDefense) {
                                temp = currentPokemon[i];
                                currentPokemon[i] = currentPokemon[j];
                                currentPokemon[j] = temp;
                            }
                        }
                    }
                    break;
                case 8:
                    // Ordenar por Velocidad
                    for (int i = 0; i < count - 1; i++) {
                        for (int j = i + 1; j < count; j++) {
                            if (currentPokemon[i].speed > currentPokemon[j].speed) {
                                temp = currentPokemon[i];
                                currentPokemon[i] = currentPokemon[j];
                                currentPokemon[j] = temp;
                            }
                        }
                    }
                    break;
                case 9:
                    cout << "Saliendo del ordenamiento...\n";
                    break;
                default:
                    cout << "Opción inválida. Inténtelo de nuevo.\n";
                    cout << "---------------------------------------------\n";
            }

            if (op >= 1 && op <= 8) {
                // Crear un archivo temporal para almacenar los registros ordenados
                FILE *tempFile = fopen("temp.bin", "wb");
                if (tempFile == NULL) {
                    cout << "Error al crear el archivo temporal";
                    delete[] currentPokemon;
                    return;
                }

                // Escribir los registros ordenados en el archivo temporal
                fwrite(currentPokemon, sizeof(Pokemon), count, tempFile);
                fclose(tempFile);

                // Mostrar los registros ordenados
                tempFile = fopen("temp.bin", "rb");
                if (tempFile == NULL) {
                    cout << "Error al abrir el archivo temporal";
                    delete[] currentPokemon;
                    return;
                }

                while (fread(&temp, sizeof(Pokemon), 1, tempFile)) {
                    cout << "ID: " << temp.id << "\n";
                    cout << "Nombre: " << temp.name << "\n";
                    cout << "Tipo: " << temp.type << "\n";
                    cout << "Vida: " << temp.hp << "\n";
                    cout << "Ataque: " << temp.attack << "\n";
                    cout << "Defensa: " << temp.defense << "\n";
                    cout << "Ataque Especial: " << temp.specialAttack << "\n";
                    cout << "Defensa Especial: " << temp.specialDefense << "\n";
                    cout << "Velocidad: " << temp.speed << "\n";
                    cout << "Descripción: " << temp.description << "\n";
                    cout << "---------------------------------------------\n";
                }
                fclose(tempFile);

                // Eliminar el archivo temporal
                remove("temp.bin");

                cout << "\nPresione Enter para continuar...";
                cin.ignore();
                cin.get();
            }
        } while (op != 9);

        // Liberar la memoria reservada
        delete[] currentPokemon;
    }
}

// Funcion para eliminar el registro de un Pokemon
void deletePokemon() {
    FILE *archi, *temp;
    int ID;
    Pokemon pokemon;
    int found = 0;

    archi = fopen(archivo, "rb");
    if (archi == NULL) {
        cout << "\nError en la operacion de archivo";
        return;
    }

    // Crear un archivo temporal en modo escritura
    temp = fopen("temp.bin", "wb");
    if (temp == NULL) {
        cout << "\nError al crear el archivo temporal";
        fclose(archi);
        return;
    }

    cout << "\nIngrese el ID del Pokemon a eliminar: ";
    ID = readInt(); // Validar que solo se ingresen números

    // Leer y copiar solo los registros que no coincidan con el ID a eliminar
    while (fread(&pokemon, sizeof(Pokemon), 1, archi)) {
        if (pokemon.id == ID) {
            found = 1;
            cout << "\nEl Pokemon con ID " << ID << " ha sido eliminado exitosamente.\n";
        } else {
            fwrite(&pokemon, sizeof(Pokemon), 1, temp);
        }
    }

    fclose(archi);
    fclose(temp);

    // Si se encontró el registro, reemplazar el archivo original con el temporal
    if (found) {
        remove(archivo);
        rename("temp.bin", archivo);
    } else {
        cout << "\nNo se encontró un Pokemon con el ID especificado.\n";
        remove("temp.bin");
    }

    cout << "\nPresione Enter para continuar...";
    cin.ignore();
    cin.get();
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

// Función para buscar un Pokémon por ID
bool findPokemonByID(int ID, Pokemon &pokemon) {
    FILE *archi = fopen(archivo, "rb");
    if (archi == NULL) {
        cout << "Error en la operacion de archivo";
        return false;
    }

    while (fread(&pokemon, sizeof(Pokemon), 1, archi)) {
        if (pokemon.id == ID) {
            fclose(archi);
            return true;
        }
    }

    fclose(archi);
    return false;
}

// Función para realizar un combate entre dos Pokémon
void combat() {
    int ID1, ID2;
    Pokemon pokemon1, pokemon2;
    int score1 = 0, score2 = 0;

    // Detener la música actual y reproducir la música de combate
    stopMusic();
    playMusic("assets/audio/Pokemon_combat.mp3");

    // Validar la entrada del primer Pokémon
    do {
        cout << "Ingrese el ID del primer Pokemon: ";
        ID1 = readInt();
        if (!findPokemonByID(ID1, pokemon1)) {
            cout << "El Pokemon con ID " << ID1 << " no está registrado. Inténtelo de nuevo." << endl;
        }
    } while (!findPokemonByID(ID1, pokemon1));

    // Validar la entrada del segundo Pokémon
    do {
        cout << "Ingrese el ID del segundo Pokemon: ";
        ID2 = readInt();
        if (ID1 == ID2) {
            cout << "No puede seleccionar el mismo Pokemon para el combate. Inténtelo de nuevo." << endl;
        } else if (!findPokemonByID(ID2, pokemon2)) {
            cout << "El Pokemon con ID " << ID2 << " no está registrado. Inténtelo de nuevo." << endl;
        }
    } while (ID1 == ID2 || !findPokemonByID(ID2, pokemon2));

    // Mostrar estadísticas de los Pokémon
    cout << "\nEstadísticas del combate:\n\n";
    cout << "Pokemon 1: " << pokemon1.name << " (ID: " << pokemon1.id << ")\n";
    cout << "Tipo: " << pokemon1.type << "\n";
    cout << "Vida: " << pokemon1.hp << "\n";
    cout << "Ataque: " << pokemon1.attack << "\n";
    cout << "Defensa: " << pokemon1.defense << "\n";
    cout << "Ataque Especial: " << pokemon1.specialAttack << "\n";
    cout << "Defensa Especial: " << pokemon1.specialDefense << "\n";
    cout << "Velocidad: " << pokemon1.speed << "\n";
    cout << "Descripción: " << pokemon1.description << "\n";
    cout << "---------------------------------------------\n";
    cout << "Pokemon 2: " << pokemon2.name << " (ID: " << pokemon2.id << ")\n";
    cout << "Tipo: " << pokemon2.type << "\n";
    cout << "Vida: " << pokemon2.hp << "\n";
    cout << "Ataque: " << pokemon2.attack << "\n";
    cout << "Defensa: " << pokemon2.defense << "\n";
    cout << "Ataque Especial: " << pokemon2.specialAttack << "\n";
    cout << "Defensa Especial: " << pokemon2.specialDefense << "\n";
    cout << "Velocidad: " << pokemon2.speed << "\n";
    cout << "Descripción: " << pokemon2.description << "\n";
    cout << "---------------------------------------------\n";

    // Comparar estadísticas
    if (pokemon1.hp > pokemon2.hp) score1++; else if (pokemon1.hp < pokemon2.hp) score2++;
    if (pokemon1.attack > pokemon2.attack) score1++; else if (pokemon1.attack < pokemon2.attack) score2++;
    if (pokemon1.defense > pokemon2.defense) score1++; else if (pokemon1.defense < pokemon2.defense) score2++;
    if (pokemon1.specialAttack > pokemon2.specialAttack) score1++; else if (pokemon1.specialAttack < pokemon2.specialAttack) score2++;
    if (pokemon1.specialDefense > pokemon2.specialDefense) score1++; else if (pokemon1.specialDefense < pokemon2.specialDefense) score2++;
    if (pokemon1.speed > pokemon2.speed) score1++; else if (pokemon1.speed < pokemon2.speed) score2++;

    // Determinar el ganador
    cout << "\nResultado del combate:\n";
    cout << "Pokemon 1: " << pokemon1.name << " (ID: " << pokemon1.id << ") - Puntuación: " << score1 << endl;
    cout << "Pokemon 2: " << pokemon2.name << " (ID: " << pokemon2.id << ") - Puntuación: " << score2 << endl;

    if (score1 > score2) {
        cout << "\nEl ganador es: " << pokemon1.name << "!" << endl;
    } else if (score2 > score1) {
        cout << "\nEl ganador es: " << pokemon2.name << "!" << endl;
    } else {
        cout << "\nEl combate terminó en empate!" << endl;
    }

    cout << "\nPresione Enter para continuar...";
    cin.ignore();
    cin.get();

    // Detener la música de combate y volver a la música del menú principal
    stopMusic();
    playMusic("assets/audio/Pokemon_menu.mp3");
}


int main() {
    setlocale(LC_ALL, "es_ES.UTF-8");
    playMusic("assets/audio/Pokemon_menu.mp3"); // Reproducir música de fondo
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
            case 5: sortPokemon(); break; 
            case 6: deletePokemon(); break;
            case 7: filterPokemon(); break;
            case 8: combat(); break;
            case 9: exit = 1; break; 
        }
    } while (!exit);

    stopMusic(); // Detener la música antes de salir
    return 0;
}


