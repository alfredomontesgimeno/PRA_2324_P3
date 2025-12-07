#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include <string>
#include "Dict.h"
#include "TableEntry.h"
#include "../PRA_2324_P1/ListLinked.h"

template <typename V>
class HashTable : public Dict<V> {
private:
    int n;   // número de elementos almacenados
    int max; // número total de cubetas
    ListLinked<TableEntry<V>>* table; // array de listas enlazadas

    // Función hash: suma ASCII de caracteres % max
    int h(std::string key) {
        int sum = 0;
        for (size_t i = 0; i < key.size(); i++) {
            sum += static_cast<int>(key.at(i));
        }
        return sum % max;
    }

public:
    // Constructor
    HashTable(int size) {
        if (size <= 0) throw std::runtime_error("Tamaño inválido de la tabla hash");
        max = size;
        n = 0;
        table = new ListLinked<TableEntry<V>>[max];
    }

    // Destructor
    ~HashTable() {
        delete[] table;
    }

    // Devuelve capacidad total
    int capacity() {
        return max;
    }

    // Devuelve número de entradas
    int entries() override {
        return n;
    }

    // Inserta un par clave->valor
    void insert(std::string key, V value) override {
        int pos = h(key);
        TableEntry<V> entry(key, value);

        // Verificar si ya existe
        if (table[pos].search(entry) != -1) {
            throw std::runtime_error("Clave duplicada en la tabla hash");
        }

        table[pos].append(entry);
        n++;
    }

    // Busca un valor por clave
    V search(std::string key) override {
        int pos = h(key);
        TableEntry<V> entry(key);

        int idx = table[pos].search(entry);
        if (idx == -1) {
            throw std::runtime_error("Clave no encontrada en la tabla hash");
        }
        return table[pos].get(idx).value;
    }

    // Elimina un par clave->valor
    V remove(std::string key) override {
        int pos = h(key);
        TableEntry<V> entry(key);

        int idx = table[pos].search(entry);
        if (idx == -1) {
            throw std::runtime_error("Clave no encontrada en la tabla hash");
        }

        V val = table[pos].get(idx).value;
        table[pos].remove(idx);
        n--;
        return val;
    }

    // Sobrecarga del operador []
    V operator[](std::string key) {
        return search(key);
    }

    // Sobrecarga del operador <<
   friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th) {
    out << "HashTable [entries: " << th.n << ", capacity: " << th.max << "]\n";
    out << "==============\n\n";

    for (int i = 0; i < th.max; i++) {
        out << "== Cubeta " << i << " ==\n\n";
        out << "List => [";
        if (th.table[i].size() > 0) out << "\n";
        for (int j = 0; j < th.table[i].size(); j++) {
            out << "  " << th.table[i].get(j);
            if (j < th.table[i].size() - 1) out << "\n";
        }
        if (th.table[i].size() > 0) out << "\n";
        out << "]\n\n";
    }

    out << "==============\n";
    return out;
    }

};

#endif

