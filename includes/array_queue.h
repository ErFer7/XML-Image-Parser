// Copyright [2021] <Eric Fernandes Evaristo>
#ifndef STRUCTURES_ARRAY_QUEUE_H
#define STRUCTURES_ARRAY_QUEUE_H

#include <cstdint>    // std::size_t
#include <stdexcept>  // C++ Exceptions

namespace structures {

template <typename T>
//! classe ArrayQueue
class ArrayQueue {
   public:
    //! construtor padrao
    ArrayQueue();
    //! construtor com parametro
    explicit ArrayQueue(std::size_t max);
    //! destrutor padrao
    ~ArrayQueue();
    //! metodo enfileirar
    void enqueue(const T& data);
    //! metodo desenfileirar
    T dequeue();
    //! metodo retorna o ultimo
    T& back();
    //! metodo limpa a fila
    void clear();
    //! metodo retorna tamanho atual
    std::size_t size();
    //! metodo retorna tamanho maximo
    std::size_t max_size();
    //! metodo verifica se vazio
    bool empty();
    //! metodo verifica se esta cheio
    bool full();

   private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;
    int begin_;  // indice do inicio (para fila circular)
    int end_;    // indice do fim (para fila circular)
    static const auto DEFAULT_SIZE = 10u;
};

}  // namespace structures

template <typename T>
structures::ArrayQueue<T>::ArrayQueue() {
    max_size_ = DEFAULT_SIZE;     // Inicializa o tamanho com o tamanho padrão
    contents = new T[max_size_];  // Inicializa a array de conteúdo
    size_ = 0;                    // Inicializa o tamanho
    begin_ = 0;                   // Inicializa o início da fila
    end_ = -1;                    // Inicializa o final da fila
}

template <typename T>
structures::ArrayQueue<T>::ArrayQueue(std::size_t max) {
    max_size_ = max;              // Inicializa o tamanho com o parâmetro
    contents = new T[max_size_];  // Inicializa a array de conteúdo
    size_ = size_t(0);            // Inicializa o tamanho
    begin_ = 0;                   // Inicializa o início da fila
    end_ = -1;                    // Inicializa o final da fila
}

template <typename T>
structures::ArrayQueue<T>::~ArrayQueue() {
    delete[] contents;  // Apaga a array de conteúdo
}

template <typename T>
void structures::ArrayQueue<T>::enqueue(const T& data) {
    if (!full()) {                // Quando a fila não está cheia
        contents[++end_] = data;  // Enfileira os dados
        size_++;                  // Incrementa o tamanho

        // Caso o final tenha passado do tamanho máximo redefine ele para -1
        if (end_ == static_cast<int>(max_size())) {
            end_ = -1;
        }
    } else {
        throw std::out_of_range("fila cheia");  // Erro de fila cheia
    }
}

template <typename T>
T structures::ArrayQueue<T>::dequeue() {
    if (!empty()) {                   // Quando a fila não está vazia
        T data = contents[begin_++];  // desenfileira os dados
        size_--;                      // Decrementa o tamanho

        // Caso o início tenha passado do tamanho máximo redefine ele para 0
        if (begin_ == static_cast<int>(max_size())) {
            begin_ = 0;
        }

        return data;
    } else {
        throw std::out_of_range("fila vazia");  // Erro de fila vazia
    }
}

template <typename T>
T& structures::ArrayQueue<T>::back() {
    if (!empty()) {
        return contents[end_];  // Retorna o último elemento da fila
    } else {
        throw std::out_of_range("fila vazia");  // Erro de fila vazia
    }
}

template <typename T>
void structures::ArrayQueue<T>::clear() {
    size_ = 0;  // Redefine o tamanho para 0
}

template <typename T>
std::size_t structures::ArrayQueue<T>::size() {
    return size_;  // Retorna o tamanho
}

template <typename T>
std::size_t structures::ArrayQueue<T>::max_size() {
    return max_size_;  // Retorna o tamanho máximo
}

template <typename T>
bool structures::ArrayQueue<T>::empty() {
    return size_ == 0;  // Retorna verdadeiro quando o tamanho for 0
}

template <typename T>
bool structures::ArrayQueue<T>::full() {
    // Retorna verdadeiro quando o tamanho for igual ao máximo
    return size_ == max_size();
}

#endif
