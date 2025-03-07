//  Phillip_Mwanguku_1061972
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

struct Word {
    std::string name, type, definition;
};

void parseDictionary(const std::string& filename, std::vector<Word>& dictionary) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }

    std::string line;
    std::string type, definition, word;
    while (std::getline(file, line)) {
        if (line.find("Type:") == 0) {
            type = line.substr(6);
        }
        else if (line.find("Definition:") == 0) {
            definition = line.substr(11);
        }
        else if (line.find("Word:") == 0) {
            word = line.substr(6);
            dictionary.push_back({ word, type, definition });
        }
    }

    file.close();
}

void searchWord(const std::vector<Word>& dictionary, const std::string& word) {
    // Convert the input word to lowercase
    std::string lowercaseWord = word;
    std::transform(lowercaseWord.begin(), lowercaseWord.end(), lowercaseWord.begin(),
        [](unsigned char c) { return std::tolower(c); });

    auto it = std::find_if(dictionary.begin(), dictionary.end(), [&](const Word& w) {
        // Convert the dictionary word to lowercase before comparing
        std::string lowercaseDictWord = w.name;
        std::transform(lowercaseDictWord.begin(), lowercaseDictWord.end(), lowercaseDictWord.begin(),
            [](unsigned char c) { return std::tolower(c); });
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
    std::string filename, inputWord;
    std::cout << "Enter full path of the file to open (or leave blank for default 'dictionary_2024S1.txt'): ";
    std::getline(std::cin, filename);

    if (filename.empty())
        filename = "dictionary_2024S1.txt";

    std::vector<Word> dictionary;
    parseDictionary(filename, dictionary);

    while (true) {
        std::cout << "Enter a word to search (or 'exit' to quit): ";
        std::getline(std::cin, inputWord);

        if (inputWord == "exit")
            break;

        searchWord(dictionary, inputWord);
    }

    return 0;
}


