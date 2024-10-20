#include "WC/WC.h"
#include <iostream>
#include <string>
#include <filesystem>

int main(int argc, char* argv[]) {
    std::string choice;
    std::string inputFile;

    // Get the input file name from the user
    std::cout << "Enter the file name (without extension): ";
    std::getline(std::cin, inputFile);
    inputFile += ".txt";  // Append .txt extension

    if (argc > 1) {
        inputFile = argv[1];
    }
    else {
        inputFile = "text.txt";  // Default filename
        std::cout << "No filename provided. Using default: " << inputFile << std::endl;
    }


    // Create a WC object for the specified file
    WC WC(inputFile);

    // Calculate statistics for the file, terminate if file cannot be opened
    if (!WC.calculateStats()) {
        return 1;
    }

    // Ask the user for their choice of statistics
    std::cout << "Enter a choice with hyphens (-c: bytes, -l: lines, -w: words, -m: characters), or press Enter for default (-c, -l, -w): ";
    std::getline(std::cin, choice);

    // If no input is provided, use default options
    if (choice.empty()) {
        choice = "-c-l-w";  // Default to showing bytes, lines, and words
    }

    // Print the statistics based on user input
    WC.printStats(choice);

    return 0;
}
