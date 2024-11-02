/*
Este programa se encarga de pasar los registros en un archivo de texto a un archivo
binario para facilidad en el proyecto
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main() {
    FILE *openText = fopen("pokemon_generacion1_espanol.txt", "r"); 
    FILE *openBin = fopen("pokedex1.bin", "wb");

    if (openText == NULL || openBin == NULL) {
        perror("Error al abrir los archivos");
        return EXIT_FAILURE;
    }

    struct Pokemon pokemon;

    //Se lee cada campo del registro para seguidamente guardarlos en el archivo binario
    while (fscanf(openText, "%d\n", &pokemon.id) == 1) { 
        fgets(pokemon.name, 20, openText); 
        pokemon.name[strcspn(pokemon.name, "\n")] = '\0';

        fgets(pokemon.type, 20, openText); 
        pokemon.type[strcspn(pokemon.type, "\n")] = '\0';

        fscanf(openText, "%i %i %i %i %i %i\n",
            &pokemon.hp, &pokemon.attack, &pokemon.defense,
            &pokemon.specialAttack, &pokemon.specialDefense, &pokemon.speed);

        fgets(pokemon.description, 200, openText); 
        pokemon.description[strcspn(pokemon.description, "\n")] = '\0';

        // escribe el registro en el archivo binario
        fwrite(&pokemon, sizeof(struct Pokemon), 1, openBin);
    }

    fclose(openText);
    fclose(openBin);

    printf("Datos de Pokemon guardados en formato binario.\n");
    return 0;
}


