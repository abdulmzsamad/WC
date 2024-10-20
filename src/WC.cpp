#include "WC/WC.h"
#include <iostream>
#include <fstream>
#include <cctype>

// Constructor to initialize the filename and default stats
WC::WC(const std::string& file) : filename("../../../Resources/" +  file), bytes(0), lines(0), words(0), characters(0) {}

// Method to calculate file statistics
bool WC::calculateStats() {

    std::ifstream file(filename, std::ios::binary);  // Open the file in binary mode
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file '" << filename << "'." << std::endl;
        return false;
    }

    unsigned char c;
    bool inWord = false;

    while (file.get(reinterpret_cast<char&>(c))) {
        bytes++;  // Count bytes

        // Handle UTF-8 multi-byte characters
        if ((c & 0x80) == 0) {
            characters++;  // Single-byte character (ASCII)
        }
        else {
            // Handle multi-byte characters (e.g., UTF-8)
            int continuationBytes = getUTF8Bytes(c);
            characters++;  // Count the character as one
            for (int i = 0; i < continuationBytes; ++i) {
                if (!file.get(reinterpret_cast<char&>(c))) break;
                bytes++;  // Count continuation bytes
            }
        }

        if (c == '\n') lines++;  // Count lines

        // Count words by detecting word boundaries
        if (std::isspace(c)) {
            inWord = false;
        }
        else if (!inWord) {
            words++;
            inWord = true;
        }
    }

    file.close();
    return true;
}

// Helper method to calculate UTF-8 continuation bytes
int WC::getUTF8Bytes(unsigned char c) const {
    if ((c & 0xE0) == 0xC0) return 1;  // 2-byte character
    if ((c & 0xF0) == 0xE0) return 2;  // 3-byte character
    if ((c & 0xF8) == 0xF0) return 3;  // 4-byte character
    return 0;  // Single-byte character (ASCII)
}

// Method to print statistics based on user input
void WC::printStats(const std::string& choice) const {
    bool validOption = false;

    if (choice.find("-c") != std::string::npos) {
        std::cout << "Bytes: " << bytes << std::endl;
        validOption = true;
    }
    if (choice.find("-l") != std::string::npos) {
        std::cout << "Lines: " << lines << std::endl;
        validOption = true;
    }
    if (choice.find("-w") != std::string::npos) {
        std::cout << "Words: " << words << std::endl;
        validOption = true;
    }
    if (choice.find("-m") != std::string::npos) {
        std::cout << "Characters (including non-ASCII): " << characters << std::endl;
        validOption = true;
    }

    // If no valid options were chosen
    if (!validOption) {
        std::cerr << "Error: Invalid choice. Please use -c, -l, -w, or -m." << std::endl;
    }
}
