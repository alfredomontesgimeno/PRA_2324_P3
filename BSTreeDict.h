
#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict: public Dict<V> {

    private:
        // ABB con elementos de tipo TableEntry<V> para gestionar el diccionario.
        BSTree<TableEntry<V>>* tree;

        // (Opcional) ayudante para crear una entrada solo con clave
        // Se usa V{} como valor por defecto cuando no es relevante (búsqueda/eliminación).
        static TableEntry<V> make_entry(const std::string& key, const V& value = V{}) {
            return TableEntry<V>(key, value);
        }

    public:
        // Constructor: crea un ABB vacío con memoria dinámica.
        BSTreeDict();

        // Destructor: libera la memoria ocupada por el ABB.
        ~BSTreeDict() {
            delete tree;
            tree = nullptr;
        }

        // --- Métodos de la interfaz Dict<V> (implementación esperada) ---

        // Inserta (key, value) en el diccionario; lanza si la clave ya existe.
        void insert(std::string key, V value) override {
            tree->insert(make_entry(key, value));
        }

        // Elimina la entrada con la clave dada; lanza si no existe.
        void remove(std::string key) override {
            tree->remove(make_entry(key));
        }

        // Busca y devuelve el valor asociado a la clave; lanza si no existe.
        V search(std::string key) const override {
            TableEntry<V> te = tree->search(make_entry(key));
            return te.value; // ajusta si tu TableEntry usa otro nombre (p.ej., te.val o te.getValue())
        }

        // Devuelve el número de elementos del diccionario.
        int size() const override {
            return tree->size();
        }

        // --- Métodos propios solicitados ---

        // Sobrecarga del operador << para imprimir el contenido del diccionario.
        friend std::ostream& operator<<(std::ostream& out, const BSTreeDict<V>& bs) {
            if (bs.tree) {
                out << *(bs.tree); // delega en el operator<< de BSTree (recorrido inorden)
            }
            return out;
        }

        // Sobrecarga del operador[]: interfaz a search(key).
        V operator[](std::string key) {
            return this->search(key);
        }
};

#endif
