#include <iostream>
#include <fstream>
#include <array_stack.h>
#include <array_list.h>
#include <image.h>

// v0.2

int main() {

    char xmlFileName[100];

    std::ifstream xmlFileStream;

    structures::ArrayStack<std::string> tags;
    structures::ArrayList<structures::CharImage*> charImages;

    bool dataIsValid = true;

    std::cin >> xmlFileName;  // entrada
    xmlFileStream.open(xmlFileName);

    if (xmlFileStream.is_open()) {

        std::string xmlFile;
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
        bool readingData = false;

        while (getline(xmlFileStream, line)) {
            xmlFile.append(line);
        }

        for (std::size_t i = 0; i < xmlFile.length(); ++i) {
            if (readingData) {
                if (xmlFile[i + 1] != '<') {
                    data.push_back(xmlFile[i]);
                } else {
                    readingData = false;
                }
            } else {
                switch (xmlFile[i])
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
                        readingData = true;
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
                        tag.push_back(xmlFile[i]);
                    }
                    break;
                }
            }

            std::cout << xmlFile[i] << ", " << openingTag << ", " << dataIsValid << std::endl;
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

    } else {
        std::cout << "error" << std::endl;
    }

    return 0;
}
