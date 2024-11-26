#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

using namespace std;

template <typename V>
class BSTreeDict: public Dict<V> {

    private:
        BSTree<TableEntry<V>>* tree;

    public:
       	BSTreeDict(): tree (new BSTree<TableEntry<V>>()) {}
       	
       	~BSTreeDict(){						//Destructor, libera memoria dinamica ocupada en ABB
       		delete tree;
       	};
       	
       	friend ostream& operator<<(ostream &out, const BSTreeDict<V> &bs){	//Imprime el contenido del diccionario por pantalla
       			out << *bs.tree;
			return out;
       	}
       	
       	V operator[] (string key){				//Interfaz al metodo de interfaz heredado
       		TableEntry<V> entry (key, V());
       		return tree->search(entry).value;
       	}
       	
       	void insert(string key, V value) override {	//Inserta el valor
       		TableEntry<V> entry(key, value);
       		tree->insert(entry);
       	}
       	
       	V search(string key) override { 		//Busca el valor al que le corresponde esa llave		
       		TableEntry<V> entry (key, V());
       		return tree->search(entry).value;
       	}
       	
  	V remove(string key) override {			//Elimina una entrada
  		TableEntry<V> entry (key, V());
  		V value = tree->search(entry).value;
  		tree->remove(entry);
  		return value;
  	}
  	
       	int entries() override{		//Tamaño del arbol
       		return tree->size();
       	}
        
};

#endif