#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

using namespace std;

template <typename T> 
class BSTree {
    private:
        int nelem = 0;                  // Número de elementos almacenados en ABB
        BSNode<T>* root = nullptr;      // Nodo raíz del ABB
        
        // Método recursivo para la búsqueda en ABB
        BSNode<T>* search(BSNode<T>* n, T e) const {  
            if (n == nullptr) {
                throw runtime_error("Elemento no encontrado");
            } else if (n->elem < e) {
                return search(n->right, e);
            } else if (n->elem > e) {
                return search(n->left, e);
            } else {
                return n;
            }
        }
        
        // Método recursivo para la inserción ordenada
        BSNode<T>* insert(BSNode<T>* n, T e) {  
            if (n == nullptr) {
                nelem++;
                return new BSNode<T>(e);
            } else if (n->elem == e) {
                throw runtime_error("Elemento duplicado");
            } else if (n->elem < e) {
                n->right = insert(n->right, e);
            } else {
                n->left = insert(n->left, e);
            }
            return n;
        }

        // Recorrido inorder del árbol
        void print_inorder(ostream& out, BSNode<T>* n) const {
            if (n != nullptr) {
                print_inorder(out, n->left);
                out << n->elem << " ";
                print_inorder(out, n->right);
            }
        }
        
        // Método recursivo para la eliminación de un nodo
        BSNode<T>* remove(BSNode<T>* n, T e) {  
            if (n == nullptr) {
                throw runtime_error("Elemento no encontrado");
            } else if (n->elem < e) {
                n->right = remove(n->right, e);
            } else if (n->elem > e) {
                n->left = remove(n->left, e);
            } else {
                if (n->left != nullptr && n->right != nullptr) {
                    // Si el nodo tiene dos hijos, se reemplaza por el máximo de la subárbol izquierdo
                    n->elem = max(n->left);
                    n->left = remove_max(n->left);  // Elimina el máximo de la subárbol izquierdo
                    nelem--;
                } else {
                    // Si el nodo tiene uno o ningún hijo, se ajusta la referencia
                    BSNode<T>* temp = n;
                    n = (n->left != nullptr) ? n->left : n->right;  // Sube el hijo (si existe)
                    delete temp;  // Libera la memoria del nodo eliminado
                    nelem--;
                }
            }
            return n;
        }
        
        // Método recursivo para obtener el elemento máximo de un subárbol
        T max(BSNode<T>* n) const {  
            if (n == nullptr) {
                throw runtime_error("Elemento no encontrado");
            } else if (n->right != nullptr) {
                return max(n->right);
            } else {
                return n->elem;
            }
        }
        
        // Método recursivo que elimina el nodo con el valor máximo de un subárbol
        BSNode<T>* remove_max(BSNode<T>* n) {  
            if (n->right == nullptr) {
                BSNode<T>* temp = n;
                n = n->left;  // Sube el hijo izquierdo (si existe)
                delete temp;  // Libera la memoria del nodo eliminado
                return n;
            } else {
                n->right = remove_max(n->right);
                return n;
            }
        }
        
        // Elimina recursivamente todos los nodos del árbol
        void delete_cascade(BSNode<T>* n) {
            if (n != nullptr) {
                delete_cascade(n->left);
                delete_cascade(n->right);
                delete n;
            }
        }

    public:
        BSTree(): nelem(0), root(nullptr) {}  // Constructor del árbol
        
        // Devuelve el número de elementos en el árbol
        int size() const {  
            return nelem;
        }
        
        // Busca y devuelve el elemento e
        T search(T e) const {  
            return search(root, e)->elem;
        }
        
        // Sobrecarga del operador [] para búsqueda
        T operator[](T e) const {  
            return search(root, e)->elem;
        }
        
        // Inserta el elemento e de manera ordenada
        void insert(T e) {  
            root = insert(root, e);
        }
        
        // Recorrido inorder del árbol
        friend std::ostream& operator<<(std::ostream& out, const BSTree<T>& bst) {  
            bst.print_inorder(out, bst.root);
            return out;
        }
        
        // Elimina el elemento e
        void remove(T e) {  
            root = remove(root, e);
        }
        
        // Destructor que libera la memoria ocupada por el árbol
        ~BSTree() {  
            delete_cascade(root);
        }
};

#endif
