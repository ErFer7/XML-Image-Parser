#include <array_list.h>
#include <array_queue.h>
#include <array_stack.h>
#include <image.h>

#include <fstream>
#include <iostream>

// v0.4

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

        while (xmlFile.get(c)) {
            switch (c) {
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
                        charImage = new structures::CharImage(imgName, imgWidth, imgHeight);
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
                    if (c != '\n') {
                        if (readingTag) {
                            tag.push_back(c);
                        } else {
                            data.push_back(c);
                        }
                        break;
                    }
            }
        }
    } else {
        dataIsValid = false;
    }

    if (!tags.empty()) {
        dataIsValid = false;
    }

    if (dataIsValid) {
        for (std::size_t i = 0; i < charImages.size(); ++i) {
            int label = 0;
            int matrix[charImages[i]->height()][charImages[i]->width()];
            structures::ArrayQueue<unsigned int*> queue(charImages[i]->length());

            for (unsigned int j = 0; j < charImages[i]->height(); ++j) {
                for (unsigned int k = 0; k < charImages[i]->width(); ++k) {
                    matrix[j][k] = 0;
                }
            }

            for (unsigned int j = 0; j < charImages[i]->height(); ++j) {
                for (unsigned int k = 0; k < charImages[i]->width(); ++k) {
                    if (matrix[j][k] == 0 && charImages[i]->get_char(k, j) == '1') {
                        unsigned int* position = new unsigned int[2];
                        position[0] = j;
                        position[1] = k;
                        queue.enqueue(position);
                        matrix[j][k] = ++label;
                    }

                    while (!queue.empty()) {
                        unsigned int* position = queue.dequeue();

                        if (position[1] - 1 >= 0 &&
                            charImages[i]->get_char(position[1] - 1, position[0]) == '1' &&
                            matrix[position[0]][position[1] - 1] == 0) {
                            unsigned int* left = new unsigned int[2];
                            left[0] = position[0];
                            left[1] = position[1] - 1;

                            queue.enqueue(left);

                            matrix[position[0]][position[1] - 1] = label;
                        }

                        if (position[1] + 1 < charImages[i]->width() &&
                            charImages[i]->get_char(position[1] + 1, position[0]) == '1' &&
                            matrix[position[0]][position[1] + 1] == 0) {
                            unsigned int* right = new unsigned int[2];
                            right[0] = position[0];
                            right[1] = position[1] + 1;

                            queue.enqueue(right);

                            matrix[position[0]][position[1] + 1] = label;
                        }

                        if (position[0] - 1 >= 0 &&
                            charImages[i]->get_char(position[1], position[0] - 1) == '1' &&
                            matrix[position[0] - 1][position[1]] == 0) {
                            unsigned int* up = new unsigned int[2];
                            up[0] = position[0] - 1;
                            up[1] = position[1];

                            queue.enqueue(up);

                            matrix[position[0] - 1][position[1]] = label;
                        }

                        if (position[0] + 1 < charImages[i]->height() &&
                            charImages[i]->get_char(position[1], position[0] + 1) == '1' &&
                            matrix[position[0] + 1][position[1]] == 0) {
                            unsigned int* down = new unsigned int[2];
                            down[0] = position[0] + 1;
                            down[1] = position[1];

                            queue.enqueue(down);

                            matrix[position[0] + 1][position[1]] = label;
                        }

                        delete position;
                    }
                }
            }

            std::cout << charImages[i]->name() << " " << label << std::endl;
        }
    } else {
        std::cout << "error" << std::endl;
    }

    return 0;
}
