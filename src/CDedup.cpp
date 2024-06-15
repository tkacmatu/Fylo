/**
 * @author Matus Tkac <tkacmatu@fit.cvut.cz>
 * @date 29/05/2023
 */

#include "CDedup.h"

namespace fs = std::filesystem;

std::shared_ptr<COperation> CDedup::Clone() const {
    return std::make_shared<CDedup>(*this);
}

void CDedup::RegularFile(std::vector<std::shared_ptr<CFile>> &files, std::string &name, std::string &folderPath) {
    // Compute the size of the file to compare with other files
    std::string filePath = folderPath + "/" + name;
    fs::path sourcePath(filePath);
    uintmax_t fileSize = fs::file_size(sourcePath);

    // Find duplicates based on matching file size and content comparison
    std::unordered_map<std::string, std::string> fileContentsMap;
    bool foundDuplicates = false;
    auto it = files.begin();

    // Iterate through all files in the folder and deal with duplicates
    while (it != files.end()) {
        if (fs::is_regular_file(folderPath + "/" + (*it)->GetName())) {
            std::string currentFilePath = folderPath + "/" + (*it)->GetName();
            fs::path currentPath(currentFilePath);
            uintmax_t currentFileSize = fs::file_size(currentPath);

            if (currentFileSize == fileSize && currentFilePath != filePath) {
                std::ifstream sourceFile(filePath, std::ios::binary);
                std::ifstream currentFile(currentFilePath, std::ios::binary);

                if (sourceFile && currentFile) {
                    if (std::equal(
                            std::istreambuf_iterator<char>(sourceFile.rdbuf()),
                            std::istreambuf_iterator<char>(),
                            std::istreambuf_iterator<char>(currentFile.rdbuf()))) {
                        if (!foundDuplicates) {
                            std::cout << "Duplicates found for file '" << name
                                      << "'. Do you want to delete them and replace with symbolic links? (Y/N): ";
                            char choice;
                            std::cin >> choice;
                            if (toupper(choice) != 'Y') {
                                return;
                            }
                            foundDuplicates = true;
                        }

                        fs::remove(currentFilePath);

                        std::string symbolicLinkName = (*it)->GetName();
                        std::string symbolicLinkPath = currentFilePath;
                        it = files.erase(it);
                        files.push_back(std::make_shared<CSymbolicLink>(symbolicLinkName, symbolicLinkPath));
                        continue;
                    }
                }
            }
        }
        ++it;
    }

    if (foundDuplicates) {
        std::cout << "Duplicate files for '" << name << "' have been replaced with symbolic links." << std::endl;
    } else {
        std::cout << "No duplicates found for file '" << name << "'." << std::endl;
    }
}

void CDedup::Folder(std::vector<std::shared_ptr<CFile>> &files, std::string &name, std::string &folderPath) {
    std::cout << RED_TEXT << "Error: Cannot perform CDedup operation on Folder." << RESET_TEXT << std::endl;
}

void CDedup::SymbolicLink(std::vector<std::shared_ptr<CFile>> &files, std::string &name, std::string &folderPath) {
    std::cout << RED_TEXT << "Error: Cannot perform CDedup operation on SymbolicLink." << RESET_TEXT << std::endl;
}