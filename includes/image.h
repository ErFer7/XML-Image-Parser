// Copyright [2021] <Eric Fernandes Evaristo>
#include <iostream>

namespace structures {
class CharImage {
   public:
    CharImage(std::string name, unsigned int width, unsigned int height);
    ~CharImage();
    void set_image(const std::string &image);
    // Avaliar se é realmente necessário
    void set_char(std::size_t i, const char &pixel);
    void set_char(unsigned int x, unsigned int y, const char &pixel);
    char get_char(unsigned int x, unsigned int y);
    std::string name();
    unsigned int width();
    unsigned int height();
    unsigned int length();

   private:
    std::string _name;
    unsigned int _width;
    unsigned int _height;
    char *_contents;
};

}  // namespace structures

structures::CharImage::CharImage(std::string name, unsigned int width, unsigned int height) {
    _name = name;
    _width = width;
    _height = height;
    _contents = new char[width * height];
}

structures::CharImage::~CharImage() { delete[] _contents; }

void structures::CharImage::set_image(const std::string &image) {
    if (image.length() == length()) {
        for (std::size_t i = 0; i < image.length(); ++i) {
            _contents[i] = image[i];
        }
    } else {
        throw std::out_of_range("Invalid image size");
    }
}

void structures::CharImage::set_char(std::size_t i, const char &pixel) {
    if ((i >= 0 && i < length())) {
        _contents[i] = pixel;
    } else {
        throw std::out_of_range("Invalid pixel position");
    }
}

void structures::CharImage::set_char(unsigned int x, unsigned int y, const char &pixel) {
    if ((x >= 0 && x < width()) && (y >= 0 && y < height())) {
        _contents[y * width() + x] = pixel;
    } else {
        throw std::out_of_range("Invalid pixel position");
    }
}

char structures::CharImage::get_char(unsigned int x, unsigned int y) {
    if ((x >= 0 && x < width()) && (y >= 0 && y < height())) {
        return _contents[y * width() + x];
    } else {
        throw std::out_of_range("Invalid pixel position");
    }
}

std::string structures::CharImage::name() { return _name; }

unsigned int structures::CharImage::width() { return _width; }

unsigned int structures::CharImage::height() { return _height; }

unsigned int structures::CharImage::length() { return width() * height(); }
