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

// Funcion para validar la entrada de numeros positivos
int readInt() {
    int value;

    while (true) {
        cin >> value; // Recibe la entrada

        // Verifica si la entrada es válida y si es un número positivo
        if (cin.fail() || value <= 0) {
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
    cout << "1. Planta" << "     7. Normal" << "       13. Roca" << endl;
    cout << "2. Veneno" << "     8. Eléctrico" << "    14. Acero" << endl;
    cout << "3. Fuego" << "      9.  Tierra" << "      15. Hielo" << endl;
    cout << "4. Volador" << "    10. Hada" << "        16. Fantasma" << endl;
    cout << "5. Agua" << "       11. Lucha" << "       17. Dragón" << endl;
    cout << "6. Bicho" << "      12. Psíquico" << "    18. Siniestro" << endl;

    cout << "Su opcion: ";
    type = readInt();

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
        default:
            cout << "Opción no válida. Se asignará 'Desconocido'." << endl;
            strcpy(pokemon.type, "Desconocido"); break;
    }

    cout << "\t\t\tESTADÍSTICAS\n\n";
    cout << "Ingrese su vida: ";
    pokemon.hp = readInt();

    cout << "Ingrese su ataque: ";
    pokemon.attack = readInt();

    cout << "Ingrese su defensa: ";
    pokemon.defense = readInt();

    cout << "Ingrese su ataque especial: ";
    pokemon.specialAttack = readInt();

    cout << "Ingrese su defensa especial: ";
    pokemon.specialDefense = readInt();

    cout << "Ingrese su velocidad: ";
    pokemon.speed = readInt();

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

void modifyPokemon(){
    FILE *archi;
    int ID, pos, k, found = 0;
    Pokemon pokemon;
    char confirm;

    archi = fopen(archivo, "r+b");
    if (archi == NULL)
    {
        cout << "\n Error en la operacion de archivo";
    } else {
        do
        {
            rewind(archi);
            k = 0;
            cout << "Ingrese ID del Pokemon a modificar: ";
            ID = readInt();

            while (fread(&pokemon, sizeof(pokemon), 1, archi) && !found) 
            {
                if (ID == pokemon.id)
                {
                    found = 1;
                    pos = k;
                    break;
                }
                k++;
            }

            if (!found)
            {
                cout << "El Pokemon no existe";
                cout << "Presione Enter para continuar...";
                cin.get();
            } else {
                cout << "\n\t\t Datos actuales\n\n";
                cout << "Nombre: " << pokemon.name << "\n";
                cout << "Tipo: " << pokemon.type << "\n";
                cout << "Vida: " << pokemon.hp << "\n";
                cout << "Ataque: " << pokemon.attack << "\n";
                cout << "Defensa: " << pokemon.defense << "\n";
                cout << "Ataque Especial: " << pokemon.specialAttack << "\n";
                cout << "Defensa Especial: " << pokemon.specialDefense << "\n";
                cout << "Velocidad: " << pokemon.speed << "\n";
                cout << "Descripción: " << pokemon.description << "\n";

                pokemon.id = ID;
                cout << "\n------------------------------------------------------------\n";
                cout << "Nuevo nombre: ";
                cin.getline(pokemon.name, sizeof(pokemon.name));

                int type;  // Variable para capturar la opción ingresada por el usuario
                cout << "Nuevo tipo: \n";
                cout << "1. Planta" << "     7. Normal" << "       13. Roca" << endl;
                cout << "2. Veneno" << "     8. Eléctrico" << "    14. Acero" << endl;
                cout << "3. Fuego" << "      9.  Tierra" << "      15. Hielo" << endl;
                cout << "4. Volador" << "    10. Hada" << "        16. Fantasma" << endl;
                cout << "5. Agua" << "       11. Lucha" << "       17. Dragón" << endl;
                cout << "6. Bicho" << "      12. Psíquico" << "    18. Siniestro" << endl;

                type = readInt();

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
                    default:
                        cout << "Opción no válida. Se asignará 'Desconocido'." << endl;
                        strcpy(pokemon.type, "Desconocido"); break;
                }

                cout << "\t\t\tNUEVAS ESTADÍSTICAS\n\n";
                cout << "Ingrese su vida: ";
                pokemon.hp = readInt();

                cout << "Ingrese su ataque: ";
                pokemon.attack = readInt();

                cout << "Ingrese su defensa: ";
                pokemon.defense = readInt();

                cout << "Ingrese su ataque especial: ";
                pokemon.specialAttack = readInt();

                cout << "Ingrese su defensa especial: ";
                pokemon.specialDefense = readInt();

                cout << "Ingrese su velocidad: ";
                pokemon.speed = readInt();

                cin.ignore();

                cout << "Ingrese una breve descripcion del Pokemon: ";
                cin.getline(pokemon.description, sizeof(pokemon.description));

                fseek(archi, (long)pos * sizeof(pokemon), SEEK_SET);
                fwrite(&pokemon, sizeof(pokemon), 1, archi);
            }

            cout << "\n Desea modificar otro Pokemon S/N ";
            cin >> confirm;
            cin.ignore();

        } while (confirm == 's' || confirm == 'S');
        
        fclose(archi);
    }
    
}

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
        fclose(archi);
        cout << "\n Los datos han sido ordenados y guardados correctamente.\n";
    }
}

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
            cout << "\n El Pokemon con ID " << ID << " ha sido eliminado.";
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
        cout << "\n No se encontro un Pokemon con el ID especificado.";
        remove("temp.bin");  // eliminar el archivo temporal sin uso
    }

    cout << "\nPresione Enter para continuar...";
    cin.get(); 
}

void filterPokemon(){

}


int main() {
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