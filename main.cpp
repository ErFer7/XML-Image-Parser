#include <array_list.h>
#include <array_queue.h>
#include <array_stack.h>
#include <image.h>
#include <matrix.h>

#include <fstream>
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using structures::ArrayList;
using structures::ArrayQueue;
using structures::ArrayStack;
using structures::CharImage;
using structures::Matrix;

// v0.5

int main() {
    char xmlFileName[100];

    std::ifstream xmlFile;

    ArrayStack<string> tags;
    ArrayList<CharImage*> charImages(200);

    bool dataIsValid = true;

    std::cin >> xmlFileName;  // entrada
    xmlFile.open(xmlFileName);

    if (xmlFile.is_open()) {
        string line;
        string tag;
        string data;
        string imgName;
        string imgData;

        int imgWidth;
        int imgHeight;

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
                        try {
                            imgWidth = std::stoi(data);
                        } catch (const std::invalid_argument& e) {
                            dataIsValid = false;
                            break;
                        }
                    } else if (tags.top() == "height") {
                        try {
                            imgHeight = std::stoi(data);
                        } catch (const std::invalid_argument& e) {
                            dataIsValid = false;
                            break;
                        }
                    } else if (tags.top() == "data") {
                        imgData = data;
                    } else {
                        break;
                    }

                    if (++obtainedData == 4) {
                        CharImage* charImage;
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
            Matrix<int> matrix(charImages[i]->width(), charImages[i]->height());
            ArrayQueue<int*> queue(charImages[i]->length());

            for (int j = 0; j < charImages[i]->height(); ++j) {
                for (int k = 0; k < charImages[i]->width(); ++k) {
                    matrix.set_data(k, j, 0);
                }
            }

            for (int j = 0; j < charImages[i]->height(); ++j) {
                for (int k = 0; k < charImages[i]->width(); ++k) {
                    if (matrix.get_data(k, j) == 0 && charImages[i]->get_char(k, j) == '1') {
                        int* position = new int[2];
                        position[0] = j;
                        position[1] = k;
                        queue.enqueue(position);
                        matrix.set_data(k, j, ++label);
                    }

                    while (!queue.empty()) {
                        int* position = queue.dequeue();

                        if (position[1] - 1 >= 0) {
                            if (charImages[i]->get_char(position[1] - 1, position[0]) == '1' &&
                                matrix.get_data(position[1] - 1, position[0]) == 0) {
                                int* left = new int[2];
                                left[0] = position[0];
                                left[1] = position[1] - 1;

                                queue.enqueue(left);
                                matrix.set_data(position[1] - 1, position[0], label);
                            }
                        }

                        if (position[1] + 1 < charImages[i]->width()) {
                            if (charImages[i]->get_char(position[1] + 1, position[0]) == '1' &&
                                matrix.get_data(position[1] + 1, position[0]) == 0) {
                                int* right = new int[2];
                                right[0] = position[0];
                                right[1] = position[1] + 1;

                                queue.enqueue(right);
                                matrix.set_data(position[1] + 1, position[0], label);
                            }
                        }

                        if (position[0] - 1 >= 0) {
                            if (charImages[i]->get_char(position[1], position[0] - 1) == '1' &&
                                matrix.get_data(position[1], position[0] - 1) == 0) {
                                int* up = new int[2];
                                up[0] = position[0] - 1;
                                up[1] = position[1];

                                queue.enqueue(up);

                                matrix.set_data(position[1], position[0] - 1, label);
                            }
                        }

                        if (position[0] + 1 < charImages[i]->height()) {
                            if (charImages[i]->get_char(position[1], position[0] + 1) == '1' &&
                                matrix.get_data(position[1], position[0] + 1) == 0) {
                                int* down = new int[2];
                                down[0] = position[0] + 1;
                                down[1] = position[1];

                                queue.enqueue(down);

                                matrix.set_data(position[1], position[0] + 1, label);
                            }
                        }

                        delete position;
                    }
                }
            }

            cout << charImages[i]->name() << " " << label << endl;
        }
    } else {
        cout << "error" << endl;
    }

    return 0;
}
