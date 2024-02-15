// Francisco Leudes Bezerra Neto, 552478
// Bianca Almeida Baia, 553659

#ifndef NODE_H
#define NODE_H
template <typename Type> class Queue; // declaração da classe Queue como uma classe com template
template <typename Type> class OrderedList; // declaração da classe OrderedList como uma classe com template

template <typename Type> 
class Node{ // classe que implementa um nó
friend class Queue<Type>; // usado para que a classe Queue tenha acesso aos atributos de Node
friend class OrderedList<Type>; // usado para que o classe OrderedList tenha acesso aos atributos de Node
    Type value; // valor armazenado no nó
    Node<Type>* next; // ponteiro para o proximo nó

public:
    // construtor que cria um nó sem valor e seu "next" aponta para nulo
    Node(){}
    // construtor que cria um nó conforme os parâmetros passados
    Node(Type val, Node<Type>* ptr){
        value = val;
        next = ptr;
    } 
    // destrutor que deleta o proximo nó
    ~Node(){ 
        delete next;
    }
};

#endif