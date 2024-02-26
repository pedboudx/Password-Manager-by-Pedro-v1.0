#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h> // Assuming you're on Windows for console color
#include <cstdio>    // For std::remove

const std::string MASTER_KEY_FILE = "master.txt";
const int SHIFT = 3; // Example shift for Caesar Cipher

void masterEncrypt(const std::string& input) {
    std::ofstream outputFile(MASTER_KEY_FILE);
    if (!outputFile.is_open()) {
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h, 4);
        std::cerr << "Error opening file: " << MASTER_KEY_FILE << " for writing." << std::endl;
        SetConsoleTextAttribute(h, 15);
        return;
    }

    // Caesar Cipher encryption
    for (char ch : input) {
        if (std::isalpha(ch)) {
            ch = std::isupper(ch) ? 'A' + (ch - 'A' + SHIFT) % 26 : 'a' + (ch - 'a' + SHIFT) % 26;
        }
        outputFile << ch;
    }

    outputFile.close();
    std::cout << "Encryption completed successfully. Encrypted text saved as: " << MASTER_KEY_FILE << std::endl;
}

std::string masterDecrypt() {
    std::ifstream inputFile(MASTER_KEY_FILE);
    if (!inputFile.is_open()) {
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h, 4);
        std::cerr << "Error opening file: " << MASTER_KEY_FILE << " for reading." << std::endl;
        SetConsoleTextAttribute(h, 15);
        return "";
    }

    std::string decryptedText;
    char ch;
    while (inputFile.get(ch)) {
        if (std::isalpha(ch)) {
            ch = std::isupper(ch) ? 'A' + (ch - 'A' - SHIFT + 26) % 26 : 'a' + (ch - 'a' - SHIFT + 26) % 26;
        }
        decryptedText += ch;
    }

    inputFile.close();
    return decryptedText;
}


