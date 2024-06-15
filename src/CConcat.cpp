/**
 * @author Matus Tkac <tkacmatu@fit.cvut.cz>
 * @date 29/05/2023
 */

#include "CConcat.h"

std::shared_ptr<COperation> CConcat::Clone() const {
    return std::make_shared<CConcat>(*this);
}

void CConcat::RegularFile(std::vector<std::shared_ptr<CFile>> &files, std::string &name, std::string &folderPath) {
    // Try to open the first file
    std::ifstream file1(folderPath + "/" + name);

    // Check if the first file exists and can be opened
    if (!file1) {
        std::cout << "Failed to open file '" << name << "'." << std::endl;
        return;
    }

    // Prompt for the second file
    std::string secondFileName;
    std::cout << "Enter the name of the second file: ";
    std::cin >> secondFileName;

    // Check if the second file exists and is a regular file
    std::filesystem::path secondFilePath = folderPath + "/" + secondFileName;
    if (!std::filesystem::is_regular_file(secondFilePath)) {
        std::cout << "File '" << secondFileName << "' does not exist or is not a regular file." << std::endl;
        return;
    }

    // Try to open the second file
    std::ifstream file2(secondFilePath);

    // Check if the second file can be opened
    if (!file2) {
        std::cout << "Failed to open file '" << secondFileName << "'." << std::endl;
        return;
    }

    // Prompt for the name of the merged file
    std::string mergedFileName;
    std::cout << "Enter the name of the merged file: ";
    std::cin >> mergedFileName;

    // Check for reserved characters
    std::string reservedChars = "/\\:*?\"<>|";
    for (char c: mergedFileName) {
        if (reservedChars.find(c) != std::string::npos) {
            std::cout << "Invalid file name" << std::endl;
            return;
        }
    }
    // Check for forbidden names or keywords
    std::vector<std::string> forbiddenNames = {"CON", "PRN", "AUX", "COM1", "LPT1"};  // Add more if needed
    for (const std::string &forbiddenName: forbiddenNames) {
        if (mergedFileName == forbiddenName) {
            std::cout << "Invalid file name" << std::endl;
            return;
        }
    }

    // Check if the merged file already exists
    if (std::filesystem::exists(folderPath + "/" + mergedFileName)) {
        std::cout << "File '" << mergedFileName << "' already exists." << std::endl;
        return;
    }

    // Create the merged file
    std::ofstream mergedFile(folderPath + "/" + mergedFileName);

    // Check if the merged file was created successfully
    if (!mergedFile) {
        std::cout << "Failed to create merged file '" << mergedFileName << "'." << std::endl;
        return;
    }

    // Add to the list of files
    files.push_back(std::make_shared<CFolder>(mergedFileName, folderPath));

    // Read and write the contents of the first file to the merged file
    mergedFile << file1.rdbuf();

    // Read and write the contents of the second file to the merged file
    mergedFile << file2.rdbuf();

    // Close all three files
    file1.close();
    file2.close();
    mergedFile.close();

    std::cout << "Files '" << name << "' and '" << secondFileName << "' have been merged into '" << mergedFileName
              << "'." << std::endl;
}

void CConcat::Folder(std::vector<std::shared_ptr<CFile>> &files, std::string &name, std::string &folderPath) {
    std::cout << RED_TEXT << "Error: You are trying to use Concat opeartion on Folder" << RESET_TEXT << std::endl;
}

void CConcat::SymbolicLink(std::vector<std::shared_ptr<CFile>> &files, std::string &name, std::string &folderPath) {
    std::cout << RED_TEXT << "Error: You are trying to use Concat opeartion on SymbolicLink" << RESET_TEXT << std::endl;
}