#pragma once

#include <iostream>
#include <vector>
#include "Password.hpp"
#include <fstream>
#include <Windows.h>

// DECRYPTOR, ENCRYPTOR, TEXTREADER AND TEXTWRITER
using namespace std;

namespace Boudoux
{
    // DECRYPTOR DOWN HERE

    void decrypt() {
        const std::string filename = "data.txt";
        const std::string tempFilename = "temp.txt";
        const int shift = 3; // Example shift for Caesar Cipher

        std::ifstream inputFile(filename);
        if (!inputFile.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        std::ofstream tempFile(tempFilename);
        if (!tempFile.is_open()) {
            std::cerr << "Error creating temp file." << std::endl;
            return;
        }

        char ch;
        while (inputFile.get(ch)) {
            if (std::isalpha(ch)) {
                ch = std::isupper(ch) ? 'A' + (ch - 'A' - shift + 26) % 26 : 'a' + (ch - 'a' - shift + 26) % 26;
            }
            tempFile << ch;
        }

        std::cout << "Decryption completed successfully. Decrypted text saved as: " << tempFilename << std::endl;
    }


    void retrieveFromTxt(std::vector <Boudoux::Password>& passwordList) {
        ifstream fileIn("temp.txt");

        if (!fileIn) {
            HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(h, 4);
            cerr << "Unable to open file for reading." << endl;
            SetConsoleTextAttribute(h, 15);
            return;
        }

        passwordList.clear(); // Clear the vector before populating

        string tempWebsite, tempUser, tempPassword;
        while (fileIn >> tempWebsite >> tempUser >> tempPassword) {
            Password password(tempWebsite, tempUser, tempPassword);
            passwordList.push_back(password);
        }

        fileIn.close();
        std::remove("temp.txt");

    }

    void writeToTxt(const std::vector <Boudoux::Password>& passwordList) {
        ofstream fileOut("temp.txt");

        if (!fileOut.is_open()) {
            HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(h, 4);
            cerr << "Unable to open file for writing." << endl;
            SetConsoleTextAttribute(h, 15);
            return;
        }

        for (size_t i = 0; i < passwordList.size(); ++i) {
            fileOut << passwordList[i].getWebsite() << " "
                << passwordList[i].getUser() << " "
                << passwordList[i].getPassword() << "\n";
        }

        fileOut.close();
    }

    void encrypt() {
        const std::string tempFilename = "temp.txt";
        const std::string encryptedFilename = "data.txt";
        const int shift = 3; // Example shift for Caesar Cipher

        std::ifstream inputFile(tempFilename);
        if (!inputFile.is_open()) {
            HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(h, 4);
            std::cerr << "Error opening file: " << tempFilename << " for reading." << std::endl;
            SetConsoleTextAttribute(h, 15);
            return;
        }

        std::ofstream outputFile(encryptedFilename);
        if (!outputFile.is_open()) {
            HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(h, 4);
            std::cerr << "Error opening file: " << encryptedFilename << " for writing." << std::endl;
            SetConsoleTextAttribute(h, 15);
            return;
        }

        char ch;
        while (inputFile.get(ch)) {
            if (std::isalpha(ch)) {
                ch = std::isupper(ch) ? 'A' + (ch - 'A' + shift) % 26 : 'a' + (ch - 'a' + shift) % 26;
            }
            outputFile << ch;
        }

        inputFile.close();
        outputFile.close();

        // Delete the temporary file
        std::remove(tempFilename.c_str());

        std::cout << "Encryption completed successfully. Encrypted text saved as: " << encryptedFilename << std::endl;
    }

}

