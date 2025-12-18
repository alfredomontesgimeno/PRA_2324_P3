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
        // ABB con elementos de tipo TableEntry<V>
        BSTree<TableEntry<V>>* tree;

        // Crea una entrada a partir de la clave (valor por defecto V{} si no se usa)
        static TableEntry<V> make_entry(const std::string& key, const V& value = V{}) {
            return TableEntry<V>(key, value);
        }
*/
    public:
        // Crea un ABB vacío con memoria dinámica
        BSTreeDict() : tree(new BSTree<TableEntry<V>>()) {}

        // Libera la memoria del ABB
        ~BSTreeDict() {
            delete tree;
            tree = nullptr;
        }

        // --- Implementación de la interfaz Dict<V> ---

        // Inserta (key, value); lanza si la clave ya existe
        void insert(std::string key, V value) override {
            tree->insert(make_entry(key, value));
        }

        // Elimina la clave y devuelve su valor; lanza si no existe
        V remove(std::string key) override {
            // Primero obtenemos la entrada (si no existe, search lanzará)
            TableEntry<V> te = tree->search(make_entry(key));
            // Luego eliminamos por clave
            tree->remove(make_entry(key));
            // Devolvemos el valor eliminado
            return te.value; // ajusta si tu TableEntry usa otro nombre (p.ej., te.val)
        }

        // Busca y devuelve el valor; lanza si no existe
        V search(std::string key) override {
            TableEntry<V> te = tree->search(make_entry(key));
            return te.value; // ajusta si tu TableEntry usa otro nombre
        }

        // Número de entradas del diccionario
        int entries() override {
            return tree->size();
        }
*/
        // --- Métodos propios solicitados ---

        // Imprime el contenido del diccionario (delegando en el BSTree inorden)
        friend std::ostream& operator<<(std::ostream& out, const BSTreeDict<V>& bs) {
            if (bs.tree) {
                out << *(bs.tree);
            }
            return out;
        }

        // Operador[]: interfaz a search(key)
        V operator[](std::string key) {
            return this->search(key);
        }
};

#endif


