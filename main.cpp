// Copyright [2021] <Eric Fernandes Evaristo>
// Versão: 1.0.1

#include <array_stack.h>
#include <image.h>
#include <linked_queue.h>
#include <matrix.h>

#include <fstream>
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using structures::ArrayStack;
using structures::CharImage;
using structures::LinkedQueue;
using structures::Matrix;

#define STACK_SIZE 10  // Define o tamanho da stack de tags, 10 é o suficiente para o trabalho

int main() {
    char xmlFileName[100];  // Vetor de chars para o nome do arquivo

    std::ifstream xmlFile;  // Arquivo que será lido

    ArrayStack<string> tags(STACK_SIZE);  // Pilha para as tags
    LinkedQueue<CharImage*> charImages;   // Fila de ponteiros para as imagens

    bool dataIsValid = true;  // Variável para a validade do arquivo

    std::cin >> xmlFileName;  // entrada

    xmlFile.open(xmlFileName);  // Tenta abrir o arquivo

    // Caso o arquivo esteja aberto faz a leitura, caso contrário define o arquivo como inválido
    if (xmlFile.is_open()) {
        string tag;      // String para a tag atual
        string data;     // String para o dado atual
        string imgName;  // String para o nome da imagem atual
        string imgData;  // String para os dados da imagem atual

        int imgWidth;   // Inteiro para a largura da imagem atual
        int imgHeight;  // Inteiro para a altura da imagem atual

        // Inteiro para contar a quantidade de dados já obtidos sobre uma imagem
        int obtainedData = 0;

        bool readingTag = false;  // Variável que define o estado de leitura da tag
        bool openingTag = false;  // Variável que define se a tag lida é de abertura

        char c;  // Char para a leitura de cada caractere do arquivo

        // Enquanto o arquivo não acaba lê cada caractere e armazena no 'c'
        while (xmlFile.get(c)) {
            switch (c) {
                case '<':               // Caso o caractere '<' tenha sido encontrado
                    readingTag = true;  // Define que a tag está sendo lida
                    openingTag = true;  // Define que é uma tag de abertura

                    /**
                     * As operações abaixo são realizadas caso já exista alguma tag na pilha.
                     * Quando há uma tag, os dados serão armazenados para a criação da imagem.
                     */

                    // Caso a pilha de tags esteja vazia sai do caso
                    if (tags.empty()) {
                        break;
                    }

                    if (tags.top() == "name") {          // Quando o dado lido é o nome
                        imgName = data;                  // Armazena o nome da imagem
                    } else if (tags.top() == "width") {  // Quando o dado lido é a largura
                        // Tenta ler a largura e a armazena caso consiga, caso contrário marca o
                        // arquivo como inválido
                        try {
                            imgWidth = std::stoi(data);
                        } catch (const std::invalid_argument& e) {
                            dataIsValid = false;
                            break;
                        }
                    } else if (tags.top() == "height") {  // Quando o dado lido é a altura
                        // Tenta ler a altura e a armazena caso consiga, caso contrário marca o
                        // arquivo como inválido
                        try {
                            imgHeight = std::stoi(data);
                        } catch (const std::invalid_argument& e) {
                            dataIsValid = false;
                            break;
                        }
                    } else if (tags.top() == "data") {  // Quando o dado lido é a imagem
                        imgData = data;                 // Armazena os dados da imagem
                    } else {                            // Quando o dado lido é outro
                        break;                          // Sai do caso
                    }

                    // Incrementa os dados obtidos até obter 4 dados. Com 4 dados é possível criar
                    // uma imagem
                    if (++obtainedData == 4) {
                        CharImage* charImage;  // Ponteiro para uma imagem
                        // Cria uma imagem com os dados iniciais
                        charImage = new structures::CharImage(imgName, imgWidth, imgHeight);
                        charImage->set_image(imgData);  // Armazena os dados da imagem em si

                        charImages.enqueue(charImage);  // Enfilera a imagem

                        obtainedData = 0;  // Zera os dados obtidos
                    }
                    data.clear();  // Limpa o dado
                    break;
                case '>':                // Caso o caractere '>' tenha sido encontrado
                    if (openingTag) {    // Caso a tag lida seja de abertura
                        tags.push(tag);  // Empilha a tag
                    } else {             // Caso a tag seja de fechamento
                        // Caso a tag no topo da pilha seja igual a tag atual ela é desempilhada.
                        // Caso contrário o arquivo é marcadado como inválido
                        if (tags.top() == tag) {
                            tags.pop();
                        } else {
                            dataIsValid = false;
                        }
                    }

                    readingTag = false;  // Define que a tag não está sendo lida
                    openingTag = false;  // Define que a tag é de fechamento
                    tag.clear();         // Limpa a tag atual
                    break;
                case '/':                // Caso o caractere '/' tenha sido encontrado
                    openingTag = false;  // Define que a tag é de fechamento
                    break;
                default:                        // Caso padrão
                    if (c != '\n') {            // Caso o caractere não seja uma nova linha
                        if (readingTag) {       // Caso esteja lendo uma tag
                            tag.push_back(c);   // Anexa o caractere no fim da tag
                        } else {                // Caso esteja lendo dados da imagem
                            data.push_back(c);  // Anexa o caractere no fim dos dados
                        }
                        break;
                    }
            }
        }
    } else {
        dataIsValid = false;
    }

    // Caso a pilha de tags não esteja vazia o arquivo é inválido
    if (!tags.empty()) {
        dataIsValid = false;
    }

    // Caso o arquivo seja válido a análise será feita, caso contrário exibe "error" no console
    if (dataIsValid) {
        while (charImages.size() > 0) {  // Enquando há imagens para analisar

            // O algoritmo abaixo é o que está descrito no moodle

            CharImage* charImage = charImages.dequeue();                  // Desenfilera uma imagem
            int label = 0;                                                // Rótulo
            Matrix<int> matrix(charImage->width(), charImage->height());  // Matriz de rótulos
            LinkedQueue<int*> queue;  // Fila de ponteiros (no caso vetores) de inteiros

            // Preenche a matriz de rótulos com '0'
            for (int j = 0; j < charImage->height(); ++j) {
                for (int k = 0; k < charImage->width(); ++k) {
                    matrix.set_data(k, j, 0);
                }
            }

            // Itera pelos caracteres da imagem
            for (int j = 0; j < charImage->height(); ++j) {
                for (int k = 0; k < charImage->width(); ++k) {
                    // Caso o caractere seja '0' na matriz e seja '1' na imagem
                    if (matrix.get_data(k, j) == 0 && charImage->get_char(k, j) == '1') {
                        int* position = new int[2];  // Cria um novo vetor para a coordenada
                        // Armazena a coordenada do caractere
                        position[0] = k;
                        position[1] = j;
                        queue.enqueue(position);         // Enfilera a coordenada
                        matrix.set_data(k, j, ++label);  // Define o rótulo na matriz
                    }

                    while (!queue.empty()) {  // Enquanto a fila de coordenadas não está vazia
                        int* position = queue.dequeue();  // Desenfilera a coordenada

                        // Esquerda
                        // É feita a verificação se o caractere na matriz está no limite a esquerda,
                        // se na imagem esse caractere é '1' e se na matriz esse caractere é '0'
                        if (position[0] - 1 >= 0) {
                            if (charImage->get_char(position[0] - 1, position[1]) == '1' &&
                                matrix.get_data(position[0] - 1, position[1]) == 0) {
                                int* left = new int[2];  // Cria a coordenada
                                // Armazena a coordenada a esquerda
                                left[0] = position[0] - 1;
                                left[1] = position[1];

                                queue.enqueue(left);  // Enfilera a coordenada
                                // Define o rótulo na matriz
                                matrix.set_data(position[0] - 1, position[1], label);
                            }
                        }

                        // Direita
                        // É feita a verificação se o caractere na matriz está no limite a direita,
                        // se na imagem esse caractere é '1' e se na matriz esse caractere é '0'
                        if (position[0] + 1 < charImage->width()) {
                            if (charImage->get_char(position[0] + 1, position[1]) == '1' &&
                                matrix.get_data(position[0] + 1, position[1]) == 0) {
                                int* right = new int[2];  // Cria a coordenada
                                // Armazena a coordenada a direita
                                right[0] = position[0] + 1;
                                right[1] = position[1];

                                queue.enqueue(right);  // Enfilera a coordenada
                                // Define o rótulo na matriz
                                matrix.set_data(position[0] + 1, position[1], label);
                            }
                        }

                        // Acima
                        // É feita a verificação se o caractere na matriz está no limite acima,
                        // se na imagem esse caractere é '1' e se na matriz esse caractere é '0'
                        if (position[1] - 1 >= 0) {
                            if (charImage->get_char(position[0], position[1] - 1) == '1' &&
                                matrix.get_data(position[0], position[1] - 1) == 0) {
                                int* up = new int[2];  // Cria a coordenada
                                // Armazena a coordenada acima
                                up[0] = position[0];
                                up[1] = position[1] - 1;

                                queue.enqueue(up);  // Enfilera a coordenada
                                // Define o rótulo na matriz
                                matrix.set_data(position[0], position[1] - 1, label);
                            }
                        }

                        // Abaixo
                        // É feita a verificação se o caractere na matriz está no limite abaixo,
                        // se na imagem esse caractere é '1' e se na matriz esse caractere é '0'
                        if (position[1] + 1 < charImage->height()) {
                            if (charImage->get_char(position[0], position[1] + 1) == '1' &&
                                matrix.get_data(position[0], position[1] + 1) == 0) {
                                int* down = new int[2];  // Cria a coordenada
                                // Armazena a coordenada abaixo
                                down[0] = position[0];
                                down[1] = position[1] + 1;

                                queue.enqueue(down);  // Enfilera a coordenada
                                // Define o rótulo na matriz
                                matrix.set_data(position[0], position[1] + 1, label);
                            }
                        }

                        delete position;  // Deleta a coordenada
                    }
                }
            }

            cout << charImage->name() << " " << label << endl;  // Exibe o resultado no console
            delete charImage;                                   // Deleta a imagem
        }
    } else {
        cout << "error" << endl;
    }

    return 0;
}
