#ifndef TABLEENTRY_H
#define TABLEENTRY_H

#include <string>
#include <ostream>

using namespace std;

template <typename V> 
class TableEntry {
    public:
        string key;
        V value;
        
        TableEntry(string key, V value): key(key), value(value){}
        
        TableEntry(string key): key(key), value(V()){}
        
        TableEntry(): key(""), value(V()){}
        
        friend bool operator==(const TableEntry<V>& te1, const TableEntry<V>& te2) {
        	return te1.key == te2.key;
    	}
    	
    	friend bool operator!=(const TableEntry<V>& te1, const TableEntry<V>& te2) {
        	return te1.key != te2.key;
    	}

    
    	friend ostream& operator<<(ostream& out, const TableEntry<V>& te) {
        	out << te.key << " -> " << te.value;
        	return out;
        }
        
        friend bool operator<(const TableEntry<V> &te1, const TableEntry<V> &te2) {
            return te1.key < te2.key; 
    	}

        friend bool operator>(const TableEntry<V> &te1, const TableEntry<V> &te2) {
            return te1.key > te2.key;
        }
};

#endif