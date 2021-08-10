#include <iostream>
#include <fstream>
#include <array_stack.h>

// v0.1

int main() {

    char xmlFileName[100];

    std::cin >> xmlFileName;  // entrada

    std::ifstream xmlFileStream;
    std::string xmlFile;
    std::string line;

    xmlFileStream.open(xmlFileName);
    
    while (getline(xmlFileStream, line)) {
        xmlFile.append(line);
    }

    std::string tag;
    structures::ArrayStack<std::string> tags;

    bool readingTag = false;
    bool openingTag = false;
    bool tagIsFree = true;
    bool valid = true;

    for (int i = 0; i < xmlFile.length(); ++i) {

        if (xmlFile[i] == '<') {
            readingTag = true;
            tagIsFree = false;

            if (xmlFile[i + 1] == '/') {
                openingTag = false;
                i += 2;
            } else {
                openingTag = true;
                ++i;
            }
        } else if (xmlFile[i] == '>') {
            readingTag = false;
        }

        if (readingTag) {
            tag.push_back(xmlFile[i]);
        } else if (!tagIsFree) {

            if (openingTag) {
                tags.push(tag);
            } else {
                if (tags.top() == tag) {
                    tags.pop();
                } else {
                    valid = false;
                    break;
                }
            }
            tag.clear();
            tagIsFree = true;
        }
    }

    if (!tags.empty()) {
        valid = false;
    }

    // for (int i = 0; i < tags.size(); ++i) {
    //     std::cout << tags.pop() << std::endl;
    // }

    if (valid) {
        std::cout << "ok" << std::endl;
    } else {
        std::cout << "error" << std::endl;
    }

    return 0;
}
