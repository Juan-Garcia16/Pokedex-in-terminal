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