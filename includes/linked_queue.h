// Copyright [2021] <Eric Fernandes Evaristo>
// Versão: 1.0

#ifndef STRUCTURES_LINKED_QUEUE_H
#define STRUCTURES_LINKED_QUEUE_H

#include <cstdint>    // std::size_t
#include <stdexcept>  // C++ exceptions

namespace structures {

template <typename T>
class LinkedQueue {
   public:
    LinkedQueue();                // Construtor
    ~LinkedQueue();               // Destrutor
    void clear();                 // Limpar
    void enqueue(const T& data);  // Enfilerar
    T dequeue();                  // Desenfilerar
    T& front() const;             // Primeiro dado
    T& back() const;              // Último dado
    bool empty() const;           // Fila vazia
    std::size_t size() const;     // Tamanho

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

/**
 * Constrói um novo objeto structures::Linked Queue<T>::Linked Queue
 */
template <typename T>
structures::LinkedQueue<T>::LinkedQueue() {
    // Inicializa os atributos
    head = nullptr;
    tail = nullptr;
    size_ = 0u;
}

/**
 * Destrói o objeto structures::Linked Queue<T>::Linked Queue
 */
template <typename T>
structures::LinkedQueue<T>::~LinkedQueue() {
    // Limpa a lista
    clear();
}

/**
 * Limpa a fila, removendo todos os dados.
 */
template <typename T>
void structures::LinkedQueue<T>::clear() {
    // Enquanto o tamanho não for 0 desenfilera
    while (size() > 0) {
        dequeue();
    }
}

/**
 * Enfileira os dados.
 *      Parâmetros:
 *          data: Dado do tipo generico T a ser enfileirado
 */
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

/**
 * Desenfileira dados retornando o dado removido da fila.
 */
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

/**
 * Retorna o dado do tipo T no início da fila.
 */
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

/**
 * Retorna o dado do tipo T no fim da fila.
 */
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

/**
 * Retorna verdadeiro caso o tamanho seja 0 e falso caso contrário.
 */
template <typename T>
bool structures::LinkedQueue<T>::empty() const {
    return size() == 0;
}

/**
 * Retorna o tamanho da fila com o tipo std::size_t.
 */
template <typename T>
std::size_t structures::LinkedQueue<T>::size() const {
    return size_;
}

#endif
