// Francisco Leudes Bezerra Neto, 552478
// Bianca Almeida Baia, 553659

#ifndef QUEUE_H
#define QUEUE_H
#include "Node.h" // usada pois essa fila é formada por nós
#include <stdexcept> // usada para lançar exceções em caso de erro
#include <initializer_list> // usada para fazer o uso da lista inicializadora
#include <iostream> // usada para fazer o uso do "cout"

template <typename Type> 
class Queue{ // classe que implementa fila com a lógica First In, First Out (FIFO)
private:
    unsigned int m_size {};  // tamanho da fila
    Node<Type>* m_first {}; // ponteiro para o primeiro nó da fila
    Node<Type>* m_last {}; // ponteiro para o último nó da fila

public:
    // construtor que cria uma fila vazia
    Queue(){}
    // construtor que cria uma fila com a lista dos valores passados
    Queue(std::initializer_list<Type> list){
        for(Type t : list){
            push(t);
        }
    }
    // função que testa se a fila está vazia
    bool empty() const{
        return m_size == 0;
    }
    // função que retorna o tamanho atual da fila
    unsigned size() const{
        return m_size;
    }
    // função que acessa o valor do primeiro elemento da fila(somente se m_size > 0)
    Type& front(){
        if(m_size == 0){
            throw std::runtime_error("A fila esta vazia.");
        }
        return m_first->value;
    }
    // versão const: função que acessa o valor do primeiro elemento da fila(somente se m_size > 0)
    const Type& front() const{
        if(m_size == 0){
            throw std::runtime_error("A fila esta vazia.");
        }
        return m_first->value;
    }
    // função que acessa o valor do ultimo elemento inserido na fila(somente se m_size > 0)
    Type& back(){
        if(m_size == 0){
            throw std::runtime_error("A fila esta vazia.");
        }
        return m_last->value;
    }
    // versão const: função que acessa o valor do ultimo elemento inserido na fila(somente se m_size > 0)
    const Type& back() const{
        if(m_size == 0){
            throw std::runtime_error("A fila esta vazia.");
        }
        return m_last->value;
    }
    // função que insere o elemento passado como parâmetro no final da fila
    void push(const Type& val){
        if(m_size == 0){
            m_first = m_last = new Node<Type>(val, nullptr);
        }
        else{
            m_last = m_last->next = new Node<Type>(val, nullptr);
        }
        m_size += 1;
    }
    // função que remove o primeiro elemento da fila(somente se m_size > 0)
    void pop(){
        if(m_size == 0){
            throw std::runtime_error("A fila esta vazia.");
        }
        Node<Type>* aux = m_first;
        m_first = m_first->next;
        aux->next = nullptr;
        delete aux;
        m_size -= 1;
        if(m_size == 0){
            m_last = nullptr;
        }
    }
    // função que troca o conteúdo de duas filas
    void swap(Queue<Type>& fila){
        Node<Type>* aux = m_first;
        m_first = fila.m_first;
        fila.m_first = aux;
        aux = m_last;
        m_last = fila.m_last;
        fila.m_last = aux;
        unsigned int aux2 = m_size;
        m_size = fila.m_size;
        fila.m_size = aux2;
    }
    // função que imprime a fila
    void print(){
        if(m_size == 0){
            throw std::runtime_error("A fila esta vazia.");
        }
        Node<Type>* aux = m_first;
        while(aux != nullptr){
            std::cout << aux->value << " ";
            aux = aux->next;
        }
        std::cout << '\n';
    }
    //função que remove o elemento a partir do seu indice na fila
    void remove(unsigned int n){
        if(m_size == 0){
            throw std::runtime_error("A fila esta vazia.");
        }
        if(n >= m_size || n < 0){
            throw std::runtime_error("Indice invalido.");
        }
        Node<Type>* aux = m_first;
        if(n == 0){
            m_first = aux->next;
            aux->next = nullptr;
            delete aux;
        }else{
            for(int i = 0; i < n-1; i++){
            aux = aux->next;
            }
            Node<Type>* aux2 = aux->next;
            aux->next = aux->next->next;
            aux2->next = nullptr;
            delete aux2;
        }
        m_size--;
        if(m_size == 0){
            m_last = nullptr;
        }
    }
    //sobrecarga do operador colchetes para acessar um elemento a partir do indice
    Type& operator[](unsigned int n){
        if(m_size == 0){
            throw std::runtime_error("A fila esta vazia.");
        }
        if(n >= m_size || n < 0){
            throw std::runtime_error("Indice invalido.");
        }
        Node<Type>* aux = m_first;
        for(int i = 0; i < n; i++){
            aux = aux->next;
        }
        return aux->value;
    }
    // destrutor que desaloca a mémoria da fila
    ~Queue(){
        delete m_first;
    }
};

#endif