#ifndef DICT_H
#define DICT_H
#include <string>

template <typename V>
class Dict {
	public:
    		// Inserta un par clave->valor
    		// Lanza std::runtime_error si la clave ya existe
		virtual void insert(std::string key, V value) = 0;

    		// Busca el valor asociado a la clave
    		// Devuelve el valor si existe, lanza std::runtime_error si no
		virtual V search(std::string key) = 0;
	
		// Elimina el par clave->valor
		// Devuelve el valor eliminado si existe, lanza std::runtime_error si no
		virtual V remove(std::string key) = 0;

		// Devuelve el número de elementos en el diccionario
		virtual int entries() = 0;

		// Destructor virtual para asegurar liberación correcta en clases derivadas
		virtual ~Dict() {}
};

#endif

