#include <iostream>
#include <fstream>
#include <string>

class FileStats {
private:
    std::string filename;
    int bytes;
    int lines;
    int words;
    int characters;

public:
    // Constructor to initialize the filename and default stats
    FileStats(const std::string& file) : filename(file), bytes(0), lines(0), words(0), characters(0) {}

    // Method to count the statistics from the file
    bool calculateStats() {
        std::ifstream file(filename, std::ios::binary);  // Open the file in binary mode
        if (!file.is_open()) {
            std::cerr << "Failed to open the file." << std::endl;
            return false;
        }

        std::string line;
        unsigned char c;
        bool inWord = false;

        while (file.get(reinterpret_cast<char&>(c))) {
            bytes++;  // Count bytes

            // Handle UTF-8 multi-byte characters
            if ((c & 0x80) == 0) {
                // Single byte character (ASCII)
                characters++;
            } else {
                // Multi-byte character (start with a byte where the top bit is set)
                int count = 0;
                if ((c & 0xE0) == 0xC0) count = 1;       // 2-byte character
                else if ((c & 0xF0) == 0xE0) count = 2;  // 3-byte character
                else if ((c & 0xF8) == 0xF0) count = 3;  // 4-byte character

                characters++;  // Count the character (not each byte)

                // Skip continuation bytes (following bytes of the multi-byte character)
                for (int i = 0; i < count; i++) {
                    if (!file.get(reinterpret_cast<char&>(c))) break;
                    bytes++;  // Count each continuation byte
                }
            }

            if (c == '\n') {
                lines++;  // Count lines
            }

            if (std::isspace(c)) {
                inWord = false;
            } else if (!inWord) {
                words++;  // Count words
                inWord = true;
            }
        }

        // Handle case when file does not end with a newline
        if (!line.empty()) {
            lines++;
        }

        file.close();
        return true;
    }

    // Getter methods to access the stats
    int getBytes() const {
        return bytes;
    }

    int getLines() const {
        return lines;
    }

    int getWords() const {
        return words;
    }

    int getCharacters() const {
        return characters;
    }

    // Method to print the statistics based on the user's choice
     void printStats(const std::string& choice) const {
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

        // If none of the valid options are found, display an error message
        if (!validOption) {
            std::cerr << "Error: Invalid choice!" << std::endl;
        }
    }
};

int main() {
    std::string choice;
    std::string inputFile;

    // Create a FileStats object for the file "text.txt"
    std::cout << "Enter the file name: ";
    std::getline(std::cin,inputFile);
    inputFile += ".txt";
    FileStats fileStats(inputFile);

     // Calculate file statistics, terminate if file cannot be opened
    if (!fileStats.calculateStats()) {
        return 1;  // Exit the program if the file cannot be opened
    }

     std::cout << "Enter a choice with hyphens (-c: bytes, -l: lines, -w: words, -m: characters), or press Enter for default (-c, -l, -w): ";
    std::getline(std::cin, choice);

    if (choice.empty()) {
        choice = "-c-l-w";  // Default choice is to print -c, -l, and -w
    }



    // Print the statistics based on the user's choice
    fileStats.printStats(choice);

    return 0;
}
    