#pragma once
#ifndef WC_H
#define WC_H

#include <string>


class WC {
private:
    std::string filename;
    int bytes;
    int lines;
    int words;
    int characters;

public:
    // Constructor
    WC(const std::string& file);

    // Method to calculate file statistics
    bool calculateStats();

    // Helper method to calculate UTF-8 continuation bytes
    int getUTF8Bytes(unsigned char c) const;

    // Method to print statistics based on user input
    void printStats(const std::string& choice) const;

    // Getter methods for testing purposes (optional)
    int getBytes() const { return bytes; }
    int getLines() const { return lines; }
    int getWords() const { return words; }
    int getCharacters() const { return characters; }
};

#endif
