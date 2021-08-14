// Copyright [2021] <Eric Fernandes Evaristo>
#ifndef STRUCTURES_CHAR_IMAGE_H
#define STRUCTURES_CHAR_IMAGE_H

#include <matrix.h>

#include <cstdint>
#include <stdexcept>

using structures::Matrix;

namespace structures {

class CharImage : Matrix<char> {
   public:
    CharImage(std::string name, int width, int height) : Matrix<char>(width, height) {
        _name = name;
    };
    ~CharImage();
    void set_image(const std::string &image);
    void set_char(std::size_t i, const char &c);
    char get_char(int x, int y);
    std::string name();
    int width();
    int height();
    unsigned int length();

   private:
    std::string _name;
};

}  // namespace structures

structures::CharImage::~CharImage() {}

void structures::CharImage::set_image(const std::string &image) {
    if (image.length() == length()) {
        for (std::size_t i = 0; i < image.length(); ++i) {
            set_data(i, image[i]);
        }
    } else {
        throw std::out_of_range("Invalid image size");
    }
}

void structures::CharImage::set_char(std::size_t i, const char &c) { set_data(i, c); }

char structures::CharImage::get_char(int x, int y) { return get_data(x, y); }

std::string structures::CharImage::name() { return _name; }

int structures::CharImage::width() { return Matrix<char>::width(); }

int structures::CharImage::height() { return Matrix<char>::height(); }

unsigned int structures::CharImage::length() {
    return (unsigned int)(Matrix<char>::width() * Matrix<char>::height());
}

#endif
