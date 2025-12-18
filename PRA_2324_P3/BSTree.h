
#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T> 
class BSTree {
    private:
        // miembros privados
        BSNode<T>* root = nullptr; // nodo raíz del ABB
        int nelem = 0;             // número de elementos del ABB

        // --- BÚSQUEDA (privado) ---
        BSNode<T>* search(BSNode<T>* n, T e) const {
            if (n == nullptr) {
                throw std::runtime_error("Elemento no encontrado");
            } else if (n->elem < e) {
                return search(n->right, e);
            } else if (n->elem > e) {
                return search(n->left, e);
            } else {
                return n;
            }
        }

        // --- INSERCIÓN (privado) ---
        BSNode<T>* insert(BSNode<T>* n, T e) {
            if (n == nullptr) {
                nelem++;
                return new BSNode<T>(e);
            } else if (n->elem == e) {
                throw std::runtime_error("Elemento duplicado");
            } else if (n->elem < e) {
                n->right = insert(n->right, e);
            } else {
                n->left = insert(n->left, e);
            }
            return n;
        }

        // --- RECORRIDO INORDEN / IMPRESIÓN (privado) ---
        void print_inorder(std::ostream &out, BSNode<T>* n) const {
            if (n != nullptr) {
                print_inorder(out, n->left);
                out << n->elem << ' ';
                print_inorder(out, n->right);
            }
        }

        // --- ELIMINACIÓN (privado) ---
        BSNode<T>* remove(BSNode<T>* n, T e) {
            if (n == nullptr) {
                throw std::runtime_error("Elemento no encontrado");
            } else if (n->elem < e) {
                n->right = remove(n->right, e);
            } else if (n->elem > e) {
                n->left = remove(n->left, e);
            } else {
                // encontrado: caso 2 descendientes
                if (n->left != nullptr && n->right != nullptr) {
                    n->elem = max(n->left);         // reemplazar por el máximo de la izquierda
                    n->left = remove_max(n->left);  // eliminar ese máximo
                    // nelem se decrementa dentro de remove_max
                } else {
                    // caso 1 ó 0 descendientes: sustituir por su único hijo (si existe) y borrar el nodo
                    BSNode<T>* hijo = (n->left != nullptr) ? n->left : n->right;
                    delete n;
                    nelem--;
                    return hijo;
                }
            }
            return n;
        }

        // --- AUXILIARES (privado) ---
        T max(BSNode<T>* n) const {
            if (n == nullptr) {
                throw std::runtime_error("Árbol vacío");
            } else if (n->right != nullptr) {
                return max(n->right);
            } else {
                return n->elem;
            }
        }

        BSNode<T>* remove_max(BSNode<T>* n) {
            // elimina el nodo con máximo valor del subárbol n (el más a la derecha)
            if (n == nullptr) {
                throw std::runtime_error("Árbol vacío");
            }
            if (n->right == nullptr) {
                // n es el máximo: borrarlo y devolver su hijo izquierdo
                BSNode<T>* izq = n->left;
                delete n;
                nelem--;
                return izq;
            } else {
                n->right = remove_max(n->right);
                return n;
            }
        }

        // --- DESTRUCCIÓN EN CASCADA (privado) ---
        void delete_cascade(BSNode<T>* n) {
            if (n != nullptr) {
                delete_cascade(n->left);
                delete_cascade(n->right);
                delete n;
            }
        }

    public:
        // miembros públicos

        // Constructor: ABB vacío
        BSTree() = default;

        // Número de elementos
        int size() const { return nelem; }

        // --- BÚSQUEDA (público) ---
        T search(T e) const {
            BSNode<T>* n = search(root, e);
            return n->elem;
        }

        // Operador [] como interfaz de búsqueda
        T operator[](T e) const {
            return search(e);
        }

        // --- INSERCIÓN (público) ---
        void insert(T e) {
            root = insert(root, e);
        }

        // --- ELIMINACIÓN (público) ---
        void remove(T e) {
            root = remove(root, e);
        }

        // --- IMPRESIÓN (público) ---
        friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst) {
            bst.print_inorder(out, bst.root);
            return out;
        }

        // --- DESTRUCTOR ---
        ~BSTree() {
            delete_cascade(root);
            root = nullptr;
            nelem = 0;
        }
};

#endif
