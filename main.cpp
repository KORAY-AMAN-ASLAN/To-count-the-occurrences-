#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <cctype>
#include <string>
#include <iomanip>

// Converts a string to lowercase for case-insensitive comparison
std::string toLower(const std::string& str) {
    std::string lowerStr = str;
    // Transform each character to lowercase
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return lowerStr;
}

// Counts the frequency of each word in a file
std::map<std::string, int> countWords(std::ifstream& file) {
    std::map<std::string, int> wordCount;
    std::string word;
    while (file >> word) {
        word = toLower(word);
        ++wordCount[word];
    }
    return wordCount;
}


// Function to sort and print the most frequent words
void printMostFrequent(const std::map<std::string, int>& wordCount, int n) {
    // Using multimap to sort by frequency in descending order
    std::multimap<int, std::string, std::greater<int>> sortedWords;

    // Insert words into multimap (sorted by frequency)
    for (const auto& pair : wordCount) {
        sortedWords.insert({pair.second, pair.first});
    }

    // Print a formatted header
    std::cout << std::left << std::setw(20) << "Word" << std::setw(10) << "Count" << std::endl;
    std::cout << std::string(30, '-') << std::endl;

    auto it = sortedWords.begin();
    for (int i = 0; i < n && it != sortedWords.end(); ++i, ++it) {
        std::cout << std::left << std::setw(20) << it->second << std::setw(10) << it->first << std::endl;
    }
}

int main() {

    std::string filename = "hitchhikersguide.txt";

    std::ifstream file(filename);

    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1;
    }

    std::cout << "Enter the number of most frequent words you want to see: ";
    int n;
    std::cin >> n;

    std::map<std::string, int> wordCount = countWords(file);
    printMostFrequent(wordCount, n);

    file.close();
    return 0;
}
