// Francisco Leudes Bezerra Neto, 552478
// Bianca Almeida Baia, 553659

#ifndef ORDERED_LIST_H
#define ORDERED_LIST_H
#include "Node.h" // usada pois essa fila é formada por nós
#include <stdexcept> // usada para lançar exceções em caso de erro
#include <initializer_list> // usada para fazer o uso da lista inicializad
#include <iostream> // usada para fazer o uso do "cout"

template <typename Type> 
class OrderedList{ // classe que implementa lista com a lógica Shortest Job First (SJF)
private:
    unsigned int m_size {}; // tamanho da lista
    Node<Type>* m_first ; // ponteiro para o primeiro nó da lista
    Node<Type>* m_last; // ponteiro para o último nó da lista

public:
    // construtor que cria uma lista vazia com nó sentinela
    OrderedList(){
        Type temp;
        m_last = m_first = new Node<Type>(temp, nullptr);
        m_size = 0;
    }
    // construtor que cria uma lista com os valores passados
    OrderedList(std::initializer_list<Type> list){
        Type temp;
        m_last = m_first = new Node<Type>(temp, nullptr);
        m_size = 0;
        for(Type t: list){
            push(t);
        }
    }
    // função que insere um elemento na lista, mantendo a ordem crescente
    void push(const Type& val){
        int f = 0;
        Node<Type>* aux = m_first;
        while(aux->next != nullptr){
            if(aux->next->value > val){
                aux->next = new Node<Type>(val, aux->next);
                f = 1;
                break;
            }
            aux = aux->next;
        }
        if(f == 0){
            m_last = aux->next = new Node<Type>(val, nullptr);
        }
        m_size += 1;
    }
    // função que remove o primeiro elemento da lista(somente se m_size > 0)
    void pop(){
        if(m_size == 0){
            throw std::runtime_error("A lista ordenada esta vazia.");
        }
        Node<Type>* aux = m_first->next;
        m_first->next = aux->next;
        aux->next = nullptr;
        delete aux;
        m_size -= 1;
        if(m_size == 0){
            m_last = nullptr;
        }
    }
    // função que testa se a lista está vazia
    bool empty() const{
        return m_size == 0;
    }
    // função que retorna o tamanho atual da lista
    unsigned size() const{
        return m_size;
    }
    // função que acessa o valor do primeiro elemento da lista(somente se m_size > 0)
    Type& front(){
        if(m_size == 0){
            throw std::runtime_error("A lista ordenada esta vazia.");
        }
        return m_first->next->value;
    }
    // versão const: função que acessa o valor do primeiro elemento da lista(somente se m_size > 0)
    const Type& front() const{
        if(m_size == 0){
            throw std::runtime_error("A lista ordenada esta vazia.");
        }
        return m_first->next->value;
    }
    // função que acessa o valor do último elemento da lista(somente se m_size > 0)
    Type& back(){
        if(m_size == 0){
            throw std::runtime_error("A lista ordenada esta vazia.");
        }
        return m_last->value;
    }
    // versão const: função que acessa o valor do último elemento da fila(somente se m_size > 0)
    const Type& back() const{
        if(m_size == 0){
            throw std::runtime_error("A lista ordenada esta vazia.");
        }
        return m_last->value;
    }
    // função que imprime a lista ordenada
    void print(){
        if(m_size == 0){
            throw std::runtime_error("A lista ordenada esta vazia.");
        }
        Node<Type>* aux = m_first;
        while(aux->next != nullptr){
            std::cout << aux->next->value << " ";
            aux = aux->next;
        }
        std::cout << '\n';
    }
    // função que troca o conteúdo de duas listas
    void swap(OrderedList<Type>& list){
        Node<Type>* aux = m_first;
        m_first = list.m_first;
        list.m_first = aux;
        aux = m_last;
        m_last = list.m_last;
        list.m_last = aux;
        unsigned int aux2 = m_size;
        m_size = list.m_size;
        list.m_size = aux2;
    }
    //função que remove o elemento a partir do seu indice na lista
    void remove(unsigned int n){
        if(m_size == 0){
            throw std::runtime_error("A lista esta vazia.");
        }
        if(n >= m_size || n < 0){
            throw std::runtime_error("Indice invalido.");
        }
        Node<Type>* aux = m_first;
        for(int i = 0; i < n; i++){
            aux = aux->next;
        }
        Node<Type>* aux2 = aux->next;
        aux->next = aux2->next;
        aux2->next = nullptr;
        delete aux2;
        m_size--;
        if(m_size == 0){
            m_last = m_first;
        }
    }
    //sobrecarga do operador colchetes para acessar um elemento a partir do indice
    Type& operator[](unsigned int n){
        if(m_size == 0){
            throw std::runtime_error("A lista esta vazia.");
        }
        if(n >= m_size || n < 0){
            throw std::runtime_error("Indice invalido.");
        }
        Node<Type>* aux = m_first->next;
        for(int i = 0; i < n; i++){
            aux = aux->next;
        }
        return aux->value;
    }
    // destrutor que desaloca a mémoria da lista
    ~OrderedList(){
        delete m_first->next;
    }
};

#endif