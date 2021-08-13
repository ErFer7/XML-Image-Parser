// Copyright [2021] <Eric Fernandes Evaristo>
#ifndef STRUCTURES_MATRIX_H
#define STRUCTURES_MATRIX_H

#include <cstdint>    // std::size_t
#include <stdexcept>  // C++ exceptions

namespace structures {

template <typename T>
class Matrix {
   public:
    Matrix(int width, int height);
    ~Matrix();
    void set_data(std::size_t i, const T &data);
    void set_data(int x, int y, const T &data);
    T get_data(int x, int y);
    int width();
    int height();
    unsigned int length();

   private:
    int _width;
    int _height;
    T *_contents;
};

}  // namespace structures

template <typename T>
structures::Matrix<T>::Matrix(int width, int height) {
    _width = width;
    _height = height;
    _contents = new T[width * height];
}

template <typename T>
structures::Matrix<T>::~Matrix() { delete[] _contents; }

template <typename T>
void structures::Matrix<T>::set_data(std::size_t i, const T &data) {
    if ((i >= 0 && i < length())) {
        _contents[i] = data;
    } else {
        throw std::out_of_range("Invalid position");
    }
}

template <typename T>
void structures::Matrix<T>::set_data(int x, int y, const T &data) {
    if ((x >= 0 && x < width()) && (y >= 0 && y < height())) {
        _contents[y * width() + x] = data;
    } else {
        throw std::out_of_range("Invalid position");
    }
}

template <typename T>
T structures::Matrix<T>::get_data(int x, int y) {
    if ((x >= 0 && x < width()) && (y >= 0 && y < height())) {
        return _contents[y * width() + x];
    } else {
        throw std::out_of_range("Invalid position");
    }
}

template <typename T>
int structures::Matrix<T>::width() { return _width; }

template <typename T>
int structures::Matrix<T>::height() { return _height; }

template <typename T>
unsigned int structures::Matrix<T>::length() { return (unsigned int)(width() * height()); }

#endif
