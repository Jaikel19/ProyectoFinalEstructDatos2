#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include "AVLTree.h"
#include "Artista.h"

bool esNumero(const std::string& str) {
    return std::all_of(str.begin(), str.end(), ::isdigit);
}

bool esEmailValido(const std::string& email) {
    const std::regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    return std::regex_match(email, pattern);
}

void cargarArtistasDesdeArchivo(AVLTree& tree, const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo " << nombreArchivo << "\n";
        return;
    }

    std::string linea;
    while (getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string cedula, apellido, nombre, telefono, email, provincia, canton, barrio;

        // Leer y separar cada campo de la línea
        getline(ss, cedula, ',');
        getline(ss, apellido, ',');
        getline(ss, nombre, ',');
        getline(ss, telefono, ',');
        getline(ss, email, ',');
        getline(ss, provincia, ',');
        getline(ss, canton, ',');
        getline(ss, barrio, ',');

        // Validaciones básicas
        if (cedula.empty() || apellido.empty() || nombre.empty() || telefono.empty() ||
            email.empty() || provincia.empty() || canton.empty() || barrio.empty()) {
            std::cerr << "Línea con datos incompletos: " << linea << "\n";
            continue;
        }

        if (!esNumero(cedula) || !esNumero(telefono)) {
            std::cerr << "Error en formato de cédula o teléfono en: " << linea << "\n";
            continue;
        }

        if (!esEmailValido(email)) {
            std::cerr << "Email inválido en: " << linea << "\n";
            continue;
        }

        // Crear objeto Artista e insertarlo en el árbol
        Artista artista(cedula, apellido, nombre, telefono, email, provincia, canton, barrio);
        tree.insert(artista);
    }

    archivo.close();
    std::cout << "Artistas cargados exitosamente desde " << nombreArchivo << "\n";
}

int main() {
    AVLTree tree;
    int choice;
    std::string archivoNombre, cedula, apellido, nombre, telefono, email, provincia, canton, barrio;

    do {
        std::cout << "\n1. Insertar Artista\n";
        std::cout << "2. Eliminar Artista\n";
        std::cout << "3. Buscar Artista\n";
        std::cout << "4. Mostrar Artistas Ascendente\n";
        std::cout << "5. Mostrar Artistas Descendente\n";
        std::cout << "6. Cargar Artistas desde Archivo\n";
        std::cout << "7. Salir\n";
        std::cout << "Elige una opcion: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Cedula: "; std::cin >> cedula;
            while (!esNumero(cedula)) {
                std::cout << "Cedula inválida. Debe ser un número: ";
                std::cin >> cedula;
            }

            std::cout << "Apellido: "; std::cin >> apellido;
            while (apellido.empty()) {
                std::cout << "Apellido no puede estar vacío. Intenta de nuevo: ";
                std::cin >> apellido;
            }

            std::cout << "Nombre: "; std::cin >> nombre;
            while (nombre.empty()) {
                std::cout << "Nombre no puede estar vacío. Intenta de nuevo: ";
                std::cin >> nombre;
            }

            std::cout << "Telefono: "; std::cin >> telefono;
            while (!esNumero(telefono)) {
                std::cout << "Telefono inválido. Debe ser un número: ";
                std::cin >> telefono;
            }

            std::cout << "Email: "; std::cin >> email;
            while (!esEmailValido(email)) {
                std::cout << "Email inválido. Intenta de nuevo: ";
                std::cin >> email;
            }

            std::cout << "Provincia: "; std::cin >> provincia;
            std::cout << "Canton: "; std::cin >> canton;
            std::cout << "Barrio: "; std::cin >> barrio;

            tree.insert(Artista(cedula, apellido, nombre, telefono, email, provincia, canton, barrio));
            break;

        case 2:
            std::cout << "Cedula del artista a eliminar: ";
            std::cin >> cedula;
            tree.deleteNode(cedula);
            break;

        case 3:
            std::cout << "Cedula del artista a buscar: ";
            std::cin >> cedula;
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
            std::cout << "Nombre del archivo: ";
            std::cin >> archivoNombre;
            cargarArtistasDesdeArchivo(tree, archivoNombre);
            break;

        case 7:
            std::cout << "Saliendo...\n";
            break;

        default:
            std::cout << "Opción inválida. Intenta de nuevo.\n";
        }
    } while (choice != 7);

    return 0;
}
