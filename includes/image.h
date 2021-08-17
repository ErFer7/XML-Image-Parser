// Copyright [2021] <Eric Fernandes Evaristo>
// Versão: 1.0

#ifndef STRUCTURES_CHAR_IMAGE_H
#define STRUCTURES_CHAR_IMAGE_H

#include <matrix.h>  // Para a herança

#include <cstdint>    // std::size_t
#include <stdexcept>  // C++ exceptions

using structures::Matrix;

namespace structures {

// Classe imagem (herda da classe Matriz)
class CharImage : Matrix<char> {
   public:
    // Construtor
    /**
     * Constrói um novo objeto Char Image com o tamanho width x height.
     *      Parâmetros:
     *          name: String que representa o nome da imagem.
     *          width: Largura da imagem.
     *          height: Altura da imagem.
     */
    CharImage(std::string name, int width, int height) : Matrix<char>(width, height) {
        _name = name;
    };
    ~CharImage();                              // Destrutor
    void set_image(const std::string &image);  // Define a imagem
    char get_char(int x, int y);               // Obtém um caractere
    std::string name();                        // Obtém o nome
    int width();                               // Obtém a largura
    int height();                              // Obtém a altura
    unsigned int length();                     // Obtém o tamanho da imagem

   private:
    std::string _name;  // Nome
};

}  // namespace structures

/**
 * Destrói o objeto structures::Char Image::Char Image.
 */
structures::CharImage::~CharImage() {}

/**
 * Define a imagem com base em um string, o string será usado para preencher a imagem.
 *      Parâmetros:
 *          Imagem: String que deve ter o mesmo tamanho da imagem.
 */
void structures::CharImage::set_image(const std::string &image) {
    if (image.length() == length()) {  // Compara se os tamanhos são iguais
        // Insere cada caractere em uma posição da imagem
        for (std::size_t i = 0; i < image.length(); ++i) {
            set_data(i, image[i]);
        }
    } else {
        throw std::out_of_range("Invalid image size!");
    }
}

/**
 * Obtém um caractere em uma posição específica.
 *      Parâmetros:
 *          x: inteiro que representa a posição horizontal na imagem.
 *          y: inteiro que representa a posição vertical na imagem.
 *
 *      Retorna um caractere (char).
 */
char structures::CharImage::get_char(int x, int y) { return get_data(x, y); }

/**
 * Retorna o nome da imagem.
 */
std::string structures::CharImage::name() { return _name; }

/**
 * Retorna a largura da imagem.
 */
int structures::CharImage::width() { return Matrix<char>::width(); }

/**
 * Retorna a altura da imagem.
 */
int structures::CharImage::height() { return Matrix<char>::height(); }

/**
 * Retorna o tamanho da imagem (largura x altura).
 */
unsigned int structures::CharImage::length() {
    return (unsigned int)(Matrix<char>::width() * Matrix<char>::height());
}

#endif
