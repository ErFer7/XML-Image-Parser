// Copyright [2021] <Eric Fernandes Evaristo>
// Versão: 1.0

#ifndef STRUCTURES_MATRIX_H
#define STRUCTURES_MATRIX_H

#include <cstdint>    // std::size_t
#include <stdexcept>  // C++ exceptions

namespace structures {

// Classe Matriz
template <typename T>
class Matrix {
   public:
    Matrix(int width, int height);                // Construtor
    ~Matrix();                                    // Destrutor
    void set_data(std::size_t i, const T &data);  // Define o dado no índice 'i'
    void set_data(int x, int y, const T &data);   // Define o dado na posição (x, y)
    T get_data(int x, int y);                     // Retorna o dado na posição (x, y)
    int width();                                  // Retorna a largura
    int height();                                 // Retorna a altura
    unsigned int length();                        // Retorna o comprimento

   private:
    int _width;    // Largura
    int _height;   // Altura
    T *_contents;  // Conteúdo
};

}  // namespace structures

/**
 * Constrói um novo objeto structures::Matrix<T>::Matrix.
 *      Parâmetros:
 *          width: Largura da matriz.
 *          height: Altura da matriz.
 */
template <typename T>
structures::Matrix<T>::Matrix(int width, int height) {
    // Inicializa todos os atributos
    _width = width;
    _height = height;
    _contents = new T[width * height];
}

/**
 * Destrói o objeto structures::Matrix<T>::Matrix.
 */
template <typename T>
structures::Matrix<T>::~Matrix() {
    delete[] _contents;
}

/**
 * Define o dado de índice 'i' na matriz.
 *      Parâmetros:
 *          i: número do tipo std::size_t que deve ser positivo e menor que o tamanho da matriz.
 *          data: Dado do tipo T a ser inserido na matriz.
 */
template <typename T>
void structures::Matrix<T>::set_data(std::size_t i, const T &data) {
    if ((i >= 0 && i < length())) {  // Checa se o índice é válido
        _contents[i] = data;         // Define o dado
    } else {
        throw std::out_of_range("Invalid index!");
    }
}

/**
 * Define o dado da posição (x, y) na matriz.
 *      Parâmetros:
 *          x: inteiro que deve ser positivo e menor que a largura da matriz.
 *          y: inteiro que deve ser positivo e menor que a altura da matriz.
 *          data: Dado do tipo T a ser inserido na matriz.
 */
template <typename T>
void structures::Matrix<T>::set_data(int x, int y, const T &data) {
    if ((x >= 0 && x < width()) && (y >= 0 && y < height())) {  // Checa se x e y são válidos
        _contents[y * width() + x] = data;                      // Define o dado
    } else {
        throw std::out_of_range("Invalid position!");
    }
}

/**
 * Retorna o dado de tipo T na posição (x, y) da matriz.
 *      Parâmetros:
 *          x: inteiro que deve ser positivo e menor que a largura da matriz.
 *          y: inteiro que deve ser positivo e menor que a altura da matriz.
 *      Retorna:
 *          Dado de tipo T.
 */
template <typename T>
T structures::Matrix<T>::get_data(int x, int y) {
    if ((x >= 0 && x < width()) && (y >= 0 && y < height())) {  // Checa se x e y são válidos
        return _contents[y * width() + x];                      // Retorna o dado
    } else {
        throw std::out_of_range("Invalid position");
    }
}

/**
 * Retorna a largura da matriz com o tipo int.
 */
template <typename T>
int structures::Matrix<T>::width() {
    return _width;
}

/**
 * Retorna a altura da matriz com o tipo int.
 */
template <typename T>
int structures::Matrix<T>::height() {
    return _height;
}

/**
 * Retorna o tamanho da matriz com o tipo  unsigned int.
 */
template <typename T>
unsigned int structures::Matrix<T>::length() {
    return (unsigned int)(width() * height());
}

#endif
