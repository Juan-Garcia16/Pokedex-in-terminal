--------------\n";
            }

            if (op >= 1 && op <= 8) {
                // Crear un archivo temporal para almacenar los registros ordenados
                FILE *tempFile = fopen("temp.bin", "wb");
                if (tempFile == NULL) {
                    cout << "Error al crear el archivo temporal";
                    delete[] currentPokemon;
                    return;
                }

                // Escribir los registros ordenados en el a