// Copyright [2021] <Eric Fernandes Evaristo>
// Versão: 1.0

#ifndef STRUCTURES_ARRAY_STACK_H
#define STRUCTURES_ARRAY_STACK_H

#include <cstdint>    // std::size_t
#include <stdexcept>  // C++ exceptions

namespace structures {

template <typename T>
// Classe Pilha
class ArrayStack {
   public:
    ArrayStack();                          // Construtor simples
    explicit ArrayStack(std::size_t max);  // Construtor com parâmetro tamanho
    ~ArrayStack();                         // Destrutor
    void push(const T &data);              // Método empilha
    T pop();                               // Método desempilha
    T &top();                              // Método retorna o topo
    void clear();                          // Método limpa pilha
    std::size_t size();                    // Método retorna tamanho
    std::size_t max_size();                // Método retorna capacidade máxima
    bool empty();                          // Verifica se está vazia
    bool full();                           // Verifica se está cheia

   private:
    T *contents;            // Conteúdo
    int top_;               // Topo
    std::size_t max_size_;  // Tamanho máximo

    static const auto DEFAULT_SIZE = 10u;  // Tamanho padrão
};

}  // namespace structures

/**
 * Constrói um novo objeto structures::Array Stack<T>::Array Stack.
 */
template <typename T>
structures::ArrayStack<T>::ArrayStack() {
    max_size_ = DEFAULT_SIZE;     // Inicializa o tamanho máximo
    contents = new T[max_size_];  // Aloca o vetor para os dados
    top_ = -1;                    // Inicializa o topo
}

/**
 * Constrói um novo objeto structures::Array Stack<T>::Array Stack com parâmetros.
 * Parâmetros:
 *      max: Tamanho máximo da pilha.
 */
template <typename T>
structures::ArrayStack<T>::ArrayStack(std::size_t max) {
    max_size_ = max;              // Inicializa o tamanho máximo
    contents = new T[max_size_];  // Aloca o vetor para os conteúdos
    top_ = -1;                    // Inicializa o topo
}

/**
 * Destrói o objeto structures::Array Stack<T>::Array Stack.
 */
template <typename T>
structures::ArrayStack<T>::~ArrayStack() {
    delete[] contents;  // Desaloca o vetor para os dados
}

/**
 * Empilha um novo dado na pilha.
 *
 * Parâmetros:
 *      data (tipo const T&): Dado a ser adicionado.
 */
template <typename T>
void structures::ArrayStack<T>::push(const T &data) {
    if (!full()) {                // Verifica se a pilha está cheia
        contents[++top_] = data;  // Empilha o dado
    } else {
        throw std::out_of_range("Full stack!");
    }
}

/**
 * Desempilha um dado da pilha, retornando-o com o tipo T.
 */
template <typename T>
T structures::ArrayStack<T>::pop() {
    if (!empty()) {               // Verifica se a pilha está cheia
        T temp;                   // Variável para retorno
        temp = contents[top_--];  // Obtém o dado
        return temp;              // Retorna o dado
    } else {
        throw std::out_of_range("Empty stack!");
    }
}

/**
 * Retorna o dado no topo da pilha com o tipo T&.
 */
template <typename T>
T &structures::ArrayStack<T>::top() {
    if (!empty()) {             // Verifica se a pilha está cheia
        return contents[top_];  // Retorna o dado
    } else {
        throw std::out_of_range("Empty stack!");
    }
}

/**
 * Limpa a pilha, eliminando todos os dados.
 */
template <typename T>
void structures::ArrayStack<T>::clear() {
    top_ = -1;  // Redefine o topo
}

/**
 * Retorna o tamanho com o tipo std::size_t.
 */
template <typename T>
std::size_t structures::ArrayStack<T>::size() {
    return top_ + 1;  // Retorna o tamanho
}

/**
 * Retorna o tamanho máximo com o tipo std::size_t.
 */
template <typename T>
std::size_t structures::ArrayStack<T>::max_size() {
    return max_size_;
}

/**
 * Retorna o valor verdadeiro (bool) caso a pilha esteja vazia e retorna falso caso contrário.
 */
template <typename T>
bool structures::ArrayStack<T>::empty() {
    return top_ == -1;  // A lista está vazia quando o topo é '-1'
}

/**
 * Retorna o valor verdadeiro (bool) caso a pilha esteja cheia e retorna falso caso contrário.
 */
template <typename T>
bool structures::ArrayStack<T>::full() {
    // A lista está cheia quando o topo é igual ao tamanho máximo
    return top_ == static_cast<int>(max_size() - 1);
}

#endif
