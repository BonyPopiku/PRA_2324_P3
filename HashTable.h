#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "../PRACTICA_1/ListLinked.h" 

using namespace std;

template <typename V>
class HashTable: public Dict<V> {

    private:
        int n;						//Numero de espacios ocupados
        int max;					//Numero de espacios en la tabla
        ListLinked<TableEntry<V>>* table;		//Tabla de cubetas
        
        int h(string key) {				//Calcula el valor ASCII y le asigna una posicion en la tabla
    		int sum = 0;
    		for (size_t i = 0; i < key.size(); i++) {	//Suma todos los valores ASCII de la palabra
        		sum += int(key.at(i)); 			// key.at(i) obtiene el carácter en la posición i, e int(e) obtiene su valor ASCII
    		}
    		return sum % max;				//Calcula donde ponerlo en la tabla
	}


    public:
    	HashTable(int size){				//Metodo constructor
    		n = 0;
    		max = size;
    		table = new ListLinked<TableEntry<V>>[max];
    	}
    	
    	~HashTable(){					//Metodo destructor
    		delete[] table;
    	}
    	
    	int capacity(){					//Numero total de cubetas de la tabla
    		return max;
    	}
    	
    	friend ostream& operator<<(ostream &out, const HashTable<V>& th){
    		out << "{\n";
    		
    		for(int i = 0; i < th.max; i++){
    			out << "[" << i << "]";
    			if(th.table[i].empty()){
    				out << "NULL\n";
    			}else{
    				out << th.table[i] << "\n";
    			}
    			
    		}
    		out << "}";
    		return out;
    	}
    	
    	V operator[](string key){			//Devuelve el valor que tiene asociado el string
    		int pos = h(key);
    		for(int i = 0; i < table[pos].size(); i++){
    			if (table[pos][i].key == key){		// Si encuentra el objeto con la clave
    				return table[pos][i].value;	// Devuelve el valor asociado
    			}
    		}
    		throw runtime_error("Clave no encontrada");
    	}
    	
        void insert(string key, V value) override{	// Inserta un valor asociado a una clave
        	int pos = h(key);
        	TableEntry<V> entrada(key, value);
        	for(int i = 0; i < table[pos].size(); i++){
        		if(table[pos][i].key == key){
        			throw runtime_error("Llave ya utilizada");
        		}
        	}
        	table[pos].insert(0, entrada);
        	n++;
        }
        
        V search(string key) override{			// Busca un valor asociado a una clave
        	int pos = h(key);
        	for(int i = 0; i < table[pos].size(); i++){
        		if (table[pos][i].key == key){
        			return table[pos][i].value;
        		}
        	}
        	throw runtime_error("Clave no encontrada");
        }
        
       	V remove(string key) override{
       		int pos = h(key);
       		for(int i = 0; i < table[pos].size(); i++){
       			if(table[pos][i].key == key){
       				V value = table[pos][i].value;
       				table[pos].remove(i);
       				n--;
       				return value;
       			}
       		}
       		throw runtime_error("Clave no encontrada");
       	}
       	
        int entries() override{			// Número de entradas en la tabla
        	return n;
        }
        
};

#endif
