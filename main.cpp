#include <iostream>
#include <fstream>
#include <array_stack.h>
#include <array_list.h>
#include <image.h>

// v0.3

int main() {

    char xmlFileName[100];

    std::ifstream xmlFile;

    structures::ArrayStack<std::string> tags;
    structures::ArrayList<structures::CharImage*> charImages;

    bool dataIsValid = true;

    std::cin >> xmlFileName;  // entrada
    xmlFile.open(xmlFileName);

    if (xmlFile.is_open()) {

        std::string line;
        std::string tag;
        std::string data;
        std::string imgName;
        std::string imgData;

        unsigned int imgWidth;
        unsigned int imgHeight;

        int obtainedData = 0;

        bool readingTag = false;
        bool openingTag = false;

        char c;

        while(xmlFile.get(c)) {
            switch (c)
            {
            case '<':
                readingTag = true;
                openingTag = true;

                if (tags.empty()) {
                    break;
                }

                if (tags.top() == "name") {
                    imgName = data;
                } else if (tags.top() == "width") {
                    imgWidth = std::stoi(data);
                } else if (tags.top() == "height") {
                    imgHeight = std::stoi(data);
                } else if (tags.top() == "data") {
                    imgData = data;
                } else {
                    break;
                }

                if (++obtainedData == 4) {
                    structures::CharImage* charImage;
                    charImage = new structures::CharImage(imgName,
                                                            imgWidth,
                                                            imgHeight);
                    charImage->set_image(imgData);

                    charImages.push_back(charImage);

                    obtainedData = 0;
                }
                data.clear();
                break;
            case '>':
                if (openingTag) {
                    tags.push(tag);
                } else {
                    if (tags.top() == tag) {
                        tags.pop();
                    } else {
                        dataIsValid = false;
                    }
                }

                readingTag = false;
                openingTag = false;
                tag.clear();
                break;
            case '/':
                openingTag = false;
                break;
            default:
                if (readingTag) {
                    tag.push_back(c);
                } else {
                    data.push_back(c);
                }
                break;
            }
        }
    } else {
        dataIsValid = false;
    }

    if (!tags.empty()) {
        dataIsValid = false;
    }

    if (dataIsValid) {

        // Fazer as outras operações
        std::cout << "ok" << std::endl;

        for (int i = 0; i < charImages.size(); ++i) {
            std::cout << charImages[i]->get_name() << std::endl;
            std::cout << charImages[i]->get_width() << std::endl;
            std::cout << charImages[i]->get_height() << std::endl;

            for (int j = 0; j < charImages[i]->get_height(); ++j) {
                for (int k = 0; k < charImages[i]->get_width(); ++k) {
                    std::cout << charImages[i]->get_pixel(k, j);
                }
                std::cout << std::endl;
            }
        }
    } else {
        std::cout << "error" << std::endl;
    }

    return 0;
}
