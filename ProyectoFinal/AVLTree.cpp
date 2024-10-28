#include "AVLTree.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

// Constructor
AVLTree::AVLTree() : root(nullptr) {}

// Calcular altura del nodo
int AVLTree::height(NodoAVL* node) {
    return node ? node->height : 0;
}

// Calcular factor de balanceo
int AVLTree::balanceFactor(NodoAVL* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

// Rotación derecha
NodoAVL* AVLTree::rotateRight(NodoAVL* y) {
    NodoAVL* x = y->left;
    NodoAVL* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;

    return x;
}

// Rotación izquierda
NodoAVL* AVLTree::rotateLeft(NodoAVL* x) {
    NodoAVL* y = x->right;
    NodoAVL* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;

    return y;
}

// Insertar un nodo en el árbol
NodoAVL* AVLTree::insert(NodoAVL* node, Artista artista) {
    if (!node) return new NodoAVL(artista);

    if (artista.cedula < node->data.cedula)
        node->left = insert(node->left, artista);
    else if (artista.cedula > node->data.cedula)
        node->right = insert(node->right, artista);
    else
        return node; // cedula duplicada

    node->height = 1 + std::max(height(node->left), height(node->right));
    int balance = balanceFactor(node);

    // Rotaciones para balancear
    if (balance > 1 && artista.cedula < node->left->data.cedula)
        return rotateRight(node);
    if (balance < -1 && artista.cedula > node->right->data.cedula)
        return rotateLeft(node);
    if (balance > 1 && artista.cedula > node->left->data.cedula) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && artista.cedula < node->right->data.cedula) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Insertar público
void AVLTree::insert(Artista artista) {
    root = insert(root, artista);
}

// Eliminar un nodo en el árbol
NodoAVL* AVLTree::deleteNode(NodoAVL* node, const std::string& cedula) {
    if (!node) return node;

    if (cedula < node->data.cedula)
        node->left = deleteNode(node->left, cedula);
    else if (cedula > node->data.cedula)
        node->right = deleteNode(node->right, cedula);
    else {
        if (!node->left || !node->right) {
            NodoAVL* temp = node->left ? node->left : node->right;
            if (!temp) {
                delete node; // Liberar memoria
                return nullptr;
            }
            *node = *temp; // copia el contenido del nodo
            delete temp; // Liberar memoria
        }
        else {
            NodoAVL* temp = minValueNode(node->right);
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data.cedula);
        }
    }

    if (!node) return node; // Si el nodo ha sido eliminado

    node->height = 1 + std::max(height(node->left), height(node->right));
    int balance = balanceFactor(node);

    // Rotaciones para balancear
    if (balance > 1 && balanceFactor(node->left) >= 0)
        return rotateRight(node);
    if (balance < -1 && balanceFactor(node->right) <= 0)
        return rotateLeft(node);
    if (balance > 1 && balanceFactor(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && balanceFactor(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Eliminar público
void AVLTree::deleteNode(const std::string& cedula) {
    root = deleteNode(root, cedula);
}

// Mínimo valor nodo
NodoAVL* AVLTree::minValueNode(NodoAVL* node) {
    NodoAVL* current = node;
    while (current && current->left)
        current = current->left;
    return current;
}

// Búsqueda de un nodo
NodoAVL* AVLTree::searchNode(NodoAVL* node, const std::string& cedula) {
    if (!node || node->data.cedula == cedula)
        return node;

    if (cedula < node->data.cedula)
        return searchNode(node->left, cedula);
    return searchNode(node->right, cedula);
}

void AVLTree::search(const std::string& cedula) {
    NodoAVL* result = searchNode(root, cedula);
    if (result)
        result->data.display();
    else
        std::cout << "Artista no encontrado\n";
}

// Recorrido ascendente
void AVLTree::displayAscending() {
    inOrder(root);
}

// Recorrido descendente
void AVLTree::displayDescending() {
    inOrderDesc(root);
}

void AVLTree::cargarDatos(const std::string& nombreArchivo)
{
    std::ifstream archivo(nombreArchivo);
    std::string linea;

    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string dato;
        std::vector < std::string > datos;

        while (std::getline(ss, dato, ',')) {
            datos.push_back(dato);
        }

        if (datos.size() == 8) {
            Artista artista(
                datos[0], // cedula
                datos[1], // nombre
                datos[2], // apellido
                datos[3], // telefono
                datos[4], // email
                datos[5], // provincia
                datos[6], // canton
                datos[7]  // barrio
            );

            insert(artista);
        }
    }
    archivo.close();
}

void AVLTree::guardarDatos(const std::string& nombreArchivo)
{
    std::ofstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        guardarEnArchivo(root, archivo);
        archivo.close();
    }
}

void AVLTree::guardarEnArchivo(NodoAVL* nodo, std::ofstream& archivo) {
    if (nodo != nullptr) {
        guardarEnArchivo(nodo->left, archivo);
        archivo << nodo->data.toString() << std::endl;
        guardarEnArchivo(nodo->right, archivo);
    }
}

void AVLTree::inOrder(NodoAVL* node) {
    if (node) {
        inOrder(node->left);
        node->data.display();
        inOrder(node->right);
    }
}

void AVLTree::inOrderDesc(NodoAVL* node) {
    if (node) {
        inOrderDesc(node->right);
        node->data.display();
        inOrderDesc(node->left);
    }
}
