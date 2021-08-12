// Copyright [2021] <Eric Fernandes Evaristo>
#include <iostream>

namespace structures
{
    class CharImage
    {
    public:
        CharImage(std::string name, unsigned int width, unsigned int height);
        ~CharImage();
        void set_image(const std::string &image);
        // Avaliar se é realmente necessário
        void set_pixel(unsigned int x, unsigned int y, const char &pixel);
        char get_pixel(unsigned int x, unsigned int y);
        std::string get_name();
        unsigned int get_width();
        unsigned int get_height();

    private:
        std::string _name;
        unsigned int _width;
        unsigned int _height;
        char *_contents;
    };

} // namespace structures

structures::CharImage::CharImage(std::string name, unsigned int width, unsigned int height)
{
    _name = name;
    _width = width;
    _height = height;
    _contents = new char[width * height];
}

structures::CharImage::~CharImage()
{
    delete[] _contents;
}

void structures::CharImage::set_image(const std::string &image)
{
    if (image.length() == _width * _height) {
        for (std::size_t i = 0; i < image.length(); ++i) {
            _contents[i] = image[i];
        }
    } else {
        throw std::out_of_range("Invalid image size");
    }
}

void structures::CharImage::set_pixel(unsigned int x, unsigned int y, const char &pixel)
{
    if ((x >= 0 && x < _width) && (y >= 0 && y < _height)) {
        _contents[y * _width + x] = pixel;
    } else {
        throw std::out_of_range("Invalid pixel position");
    }
}

char structures::CharImage::get_pixel(unsigned int x, unsigned int y)
{
    if ((x >= 0 && x < _width) && (y >= 0 && y < _height)) {
        return _contents[y * _width + x];
    } else {
        throw std::out_of_range("Invalid pixel position");
    }
}

std::string structures::CharImage::get_name()
{
    return _name;
}

unsigned int structures::CharImage::get_width()
{
    return _width;
}

unsigned int structures::CharImage::get_height()
{
    return _height;
}
