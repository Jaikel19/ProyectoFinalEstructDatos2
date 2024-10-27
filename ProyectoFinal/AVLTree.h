#ifndef AVLTREE_H
#define AVLTREE_H

#include "NodoAVL.h"
#include <string>

class AVLTree {
private:
    NodoAVL* root;

    // Métodos privados para la lógica del árbol AVL
    int height(NodoAVL* node);
    int balanceFactor(NodoAVL* node);
    NodoAVL* rotateRight(NodoAVL* y);
    NodoAVL* rotateLeft(NodoAVL* x);
    NodoAVL* insert(NodoAVL* node, Artista artista);
    NodoAVL* deleteNode(NodoAVL* node, const std::string& cedula);
    NodoAVL* minValueNode(NodoAVL* node);
    NodoAVL* searchNode(NodoAVL* node, const std::string& cedula);
    void inOrder(NodoAVL* node);
    void inOrderDesc(NodoAVL* node);

public:
    AVLTree();
    void insert(Artista artista);
    void deleteNode(const std::string& cedula);
    void search(const std::string& cedula);
    void displayAscending();
    void displayDescending();
};

#endif
