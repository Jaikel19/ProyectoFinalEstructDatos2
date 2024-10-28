#include <iostream>
#include <fstream>
#include <sstream>
#include "AVLTree.h"
#include "Artista.h"
#include <functional>
#include <regex>

bool validarCedula(const std::string& cedula) {
    return cedula.length() >= 9;
}

bool validarLongitudMinima(const std::string& entrada) {
    return entrada.length() >= 3;
}

bool validarTelefono(const std::string& telefono) {
    return telefono.length() >= 8;
}

bool validarCorreo(const std::string& correo) {
    const std::regex pattern(R"((\w+)(\.\w+)*@(\w+\.)+(\w+))");
    return std::regex_match(correo, pattern);
}

std::string validarEntrada(const std::string& mensaje, std::function<bool(const std::string&)> validador, const std::string& mensajeError) {
    std::string entrada;
    bool esValida;
    do {
        std::cout << mensaje;
        std::cin >> entrada;
        esValida = validador(entrada);
        if (!esValida) std::cout << mensajeError << std::endl;
    } while (!esValida);
    return entrada;
}

int main() {
    AVLTree tree;
    std::string nombreArchivo = "artistas.txt";
    std::string archivoNombre, cedula, apellido, nombre, telefono, email, provincia, canton, barrio;
    
    tree.cargarDatos(nombreArchivo);

    int opcion;
    do {
        std::cout << "\n1. Insertar Artista\n";
        std::cout << "2. Eliminar Artista\n";
        std::cout << "3. Buscar Artista\n";
        std::cout << "4. Mostrar Artistas Ascendente\n";
        std::cout << "5. Mostrar Artistas Descendente\n";
        std::cout << "6. Salir\n";
        std::cout << "Elige una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
        case 1:
            cedula = validarEntrada("Cedula: ", validarCedula, "La cedula debe tener al menos 9 caracteres.");
            nombre = validarEntrada("Nombre: ", validarLongitudMinima, "El nombre debe tener al menos 3 letras.");
            apellido = validarEntrada("Apellido: ", validarLongitudMinima, "El apellido debe tener al menos 3 letras.");
            telefono = validarEntrada("Telefono: ", validarTelefono, "El telefono debe tener al menos 8 caracteres.");
            email = validarEntrada("Email: ", validarCorreo, "El email ingresado no es valido.");
            provincia = validarEntrada("Provincia: ", validarLongitudMinima, "La provincia debe tener al menos 3 letras.");
            canton = validarEntrada("Canton: ", validarLongitudMinima, "El canton debe tener al menos 3 letras.");
            barrio = validarEntrada("Barrio: ", validarLongitudMinima, "El barrio debe tener al menos 3 letras.");

            tree.insert(Artista(cedula, apellido, nombre, telefono, email, provincia, canton, barrio));
            break;

        case 2:
            std::cout << "Cedula del artista a eliminar: ";
            cedula = validarEntrada("Cedula: ", validarCedula, "La cedula debe tener al menos 9 caracteres.");
            tree.deleteNode(cedula);
            break;

        case 3:
            std::cout << "Cedula del artista a buscar: ";
            cedula = validarEntrada("Cedula: ", validarCedula, "La cedula debe tener al menos 9 caracteres.");
            tree.search(cedula);
            break;

        case 4:
            std::cout << "Lista de Artistas Ascendente:\n";
            tree.displayAscending();
            break;

        case 5:
            std::cout << "Lista de Artistas Descendente:\n";
            tree.displayDescending();
            break;

        case 6:
            std::cout << "Guardando datos y saliendo del programa...\n";
            tree.guardarDatos(nombreArchivo);
            break;

        default:
            std::cout << "Opción inválida. Intenta de nuevo.\n";
        }
    } while (opcion != 6);

    return 0;
}
