//! Copyright [2021] <Eric Fernandes Evaristo>
#ifndef STRUCTURES_LINKED_QUEUE_H
#define STRUCTURES_LINKED_QUEUE_H

#include <cstdint>
#include <stdexcept>

namespace structures {

template <typename T>
class LinkedQueue {
   public:
    LinkedQueue();

    ~LinkedQueue();

    void clear();  // limpar

    void enqueue(const T& data);  // enfilerar

    T dequeue();  // desenfilerar

    T& front() const;  // primeiro dado

    T& back() const;  // último dado

    bool empty() const;  // fila vazia

    std::size_t size() const;  // tamanho

   private:
    class Node {  // Elemento
       public:
        // Construtor usando apenas o dado.
        explicit Node(const T& data) : data_{data} {}

        // Construtor de um nodo completo.
        explicit Node(const T& data, Node* next) : data_{data}, next_{next} {}

        // Retorna o dado armazenado.
        T& data() { return data_; }

        // Retorna o dado armazenado.
        const T& data() const { return data_; }

        // Retorna ponteiro para próximo nodo.
        Node* next() {  // getter: próximo
            return next_;
        }

        // Retorna ponteiro para o o próximo node.
        const Node* next() const {  // getter const: próximo
            return next_;
        }

        // Altera o ponteiro para o próximo.
        void next(Node* node) {  // setter: próximo
            next_ = node;
        }

       private:
        T data_;               // data_
        Node* next_{nullptr};  // next_
    };

    Node* head;         // nodo-cabeça
    Node* tail;         // nodo-fim
    std::size_t size_;  // tamanho
};

}  // namespace structures

template <typename T>
structures::LinkedQueue<T>::LinkedQueue() {
    // Inicializa os atributos
    head = nullptr;
    tail = nullptr;
    size_ = 0u;
}

template <typename T>
structures::LinkedQueue<T>::~LinkedQueue() {
    // Limpa a lista
    clear();
}

template <typename T>
void structures::LinkedQueue<T>::clear() {
    // Enquanto o tamanho não for 0 desenfilera
    while (size() > 0) {
        dequeue();
    }
}

template <typename T>
void structures::LinkedQueue<T>::enqueue(const T& data) {
    // Cria um nó com o dado
    Node* newNode = new Node(data);

    // Checa se o nó foi alocado
    if (newNode != nullptr) {
        if (size() != 0) {  // Caso naõ seja o primeiro nó
            // O último nó apontará para o novo nó
            tail->next(newNode);
            // O novo nó passa a ser o último nó
            tail = newNode;
        } else {
            // Define o nó como primeiro e último
            head = newNode;
            tail = newNode;
        }
        // Incrementa o tamanho
        ++size_;
    } else {
        throw std::out_of_range("Full list!");
    }
}

template <typename T>
T structures::LinkedQueue<T>::dequeue() {
    // Variável para o dado
    T data;

    // Checa se a lista está vazia
    if (!empty()) {
        // Obtém o dado
        data = head->data();
        // Ponteiro para o nó a ser removido
        Node* dequeuedNode = head;
        // O próximo nó será o primeiro nó
        head = head->next();
        // Decrementa o tamanho
        --size_;
        delete dequeuedNode;
    } else {
        throw std::out_of_range("Empty list!");
    }

    // Retorna o dado
    return data;
}

template <typename T>
T& structures::LinkedQueue<T>::front() const {
    // Ponteiro para o dado
    T* data;

    // Checa se a lista está vazia
    if (!empty()) {
        // Aponta para o dado
        data = &head->data();
    } else {
        throw std::out_of_range("Empty list!");
    }

    // Retorna o dado
    return *data;
}

template <typename T>
T& structures::LinkedQueue<T>::back() const {
    // Ponteiro para o dado
    T* data;

    // Checa se a lista está vazia
    if (!empty()) {
        // Aponta para o dado
        data = &tail->data();
    } else {
        throw std::out_of_range("Empty list!");
    }

    // Retorna o dado
    return *data;
}

template <typename T>
bool structures::LinkedQueue<T>::empty() const {
    // Retorna verdadeiro caso o tamanho seja 0 e falso caso contrário
    return size() == 0;
}

template <typename T>
std::size_t structures::LinkedQueue<T>::size() const {
    // Retorna o tamanho
    return size_;
}

#endif
