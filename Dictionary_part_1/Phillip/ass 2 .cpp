#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream> // for stringstream

struct Word {
    std::string name, type, definition;
};

// Function to parse the dictionary file and load words into the vector
void parseDictionary(const std::string& filename, std::vector<Word>& dictionary) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << ". Falling back to default dictionary." << std::endl;
        file.open("dictionary_2024S1.txt"); // Fall back to default dictionary if file not found
        if (!file.is_open()) {
            std::cerr << "Default dictionary file not found. Exiting." << std::endl;
            return;
        }
    }

    std::string line;
    std::string type, definition, word;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string tag;
        iss >> tag;

        if (tag == "Type:") {
            iss >> type;
        }
        else if (tag == "Definition:") {
            std::getline(iss, definition);
            definition = definition.substr(1); // Trim leading space
        }
        else if (tag == "Word:") {
            iss >> word;
            dictionary.push_back({ word, type, definition });
        }
    }

    file.close();
}

// Function to search for a word in the dictionary
void searchWord(const std::vector<Word>& dictionary, const std::string& word) {
    std::string lowercaseWord = word;
    std::transform(lowercaseWord.begin(), lowercaseWord.end(), lowercaseWord.begin(), [](unsigned char c) {
        return std::tolower(c);
        });

    auto it = std::find_if(dictionary.begin(), dictionary.end(), [&](const Word& w) {
        std::string lowercaseDictWord = w.name;
        std::transform(lowercaseDictWord.begin(), lowercaseDictWord.end(), lowercaseDictWord.begin(), [](unsigned char c) {
            return std::tolower(c);
            });
        return lowercaseDictWord == lowercaseWord;
        });

    if (it != dictionary.end()) {
        std::cout << "Word: " << it->name << "\nType: " << it->type << "\nDefinition: " << it->definition << std::endl;
    }
    else {
        std::cout << "Word not found." << std::endl;
    }
}

int main() {
    std::vector<Word> dictionary;
    parseDictionary("dictionary_2024S1.txt", dictionary);

    std::string inputWord;
    while (true) {
        std::cout << "Enter a word to search (or 'exit' to quit): ";
        std::getline(std::cin, inputWord);

        if (inputWord == "exit")
            break;

        searchWord(dictionary, inputWord);
    }

    return 0;
}
