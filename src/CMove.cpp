/**
 * @author Matus Tkac <tkacmatu@fit.cvut.cz>
 * @date 29/05/2023
 */

#include "CMove.h"

namespace fs = std::filesystem;

std::shared_ptr<COperation> CMove::Clone() const {
    return std::make_shared<CMove>(*this);
}

void CMove::RegularFile(std::vector<std::shared_ptr<CFile>> &files, std::string &name, std::string &folderPath) {
    // Prompt user for destination
    std::string destination;
    std::cout << "Enter destination folder (Enter '.' for current folder): ";
    std::cin >> destination;

    if (destination == ".") {
        destination = folderPath; // Set the current folder as the destination
    }

    fs::path destinationPath(destination);

    if (!fs::is_directory(destinationPath)) {
        std::cout << "Destination folder '" << destination << "' does not exist." << std::endl;
        return;
    }

    fs::path sourcePath = folderPath + "/" + name;
    fs::path destinationFile = destinationPath / name;

    if (destinationPath == folderPath) {
        std::cout << "Source and destination folders are the same." << std::endl;
        return;
    }

    try {
        fs::rename(sourcePath, destinationFile);
        std::cout << "File '" << name << "' moved to '" << destinationFile << "'." << std::endl;

        // Remove the file from the files vector
        for (auto it = files.begin(); it != files.end(); ++it) {
            if ((*it)->GetName() == name) {
                files.erase(it);
                break;
            }
        }

    } catch (const fs::filesystem_error &e) {
        std::cout << "Failed to move file '" << name << "': " << e.what() << std::endl;
    }
}

void CMove::Folder(std::vector<std::shared_ptr<CFile>> &files, std::string &name, std::string &folderPath) {
    // Prompt user for destination
    std::string destination;
    std::cout << "Enter destination folder (Enter '.' for current folder): ";
    std::cin >> destination;

    if (destination == ".") {
        destination = folderPath; // Set the current folder as the destination
    }

    fs::path destinationPath(destination);

    if (!fs::is_directory(destinationPath)) {
        std::cout << "Destination folder '" << destination << "' does not exist." << std::endl;
        return;
    }

    fs::path sourcePath = folderPath + "/" + name;
    fs::path destinationFolder = destinationPath / name;

    if (destinationPath == folderPath) {
        std::cout << "Source and destination folders are the same." << std::endl;
        return;
    }

    try {
        fs::rename(sourcePath, destinationFolder);
        std::cout << "Folder '" << name << "' moved to '" << destinationFolder << "'." << std::endl;

        // Remove the file from the files vector
        for (auto it = files.begin(); it != files.end(); ++it) {
            if ((*it)->GetName() == name) {
                files.erase(it);
                break;
            }
        }
    } catch (const fs::filesystem_error &e) {
        std::cout << "Failed to move folder '" << name << "': " << e.what() << std::endl;
    }
}

void CMove::SymbolicLink(std::vector<std::shared_ptr<CFile>> &files, std::string &name, std::string &folderPath) {
    // Prompt user for destination
    std::string destination;
    std::cout << "Enter destination folder (Enter '.' for current folder): ";
    std::cin >> destination;

    if (destination == ".") {
        destination = folderPath; // Set the current folder as the destination
    }

    fs::path destinationPath(destination);

    if (!fs::is_directory(destinationPath)) {
        std::cout << "Destination folder '" << destination << "' does not exist." << std::endl;
        return;
    }

    fs::path sourcePath = folderPath + "/" + name;
    fs::path destinationLink = destinationPath / name;

    if (destinationPath == folderPath) {
        std::cout << "Source and destination folders are the same." << std::endl;
        return;
    }

    try {
        fs::rename(sourcePath, destinationLink);
        std::cout << "Symbolic link '" << name << "' moved to '" << destinationLink << "'." << std::endl;

        // Remove the file from the files vector
        for (auto it = files.begin(); it != files.end(); ++it) {
            if ((*it)->GetName() == name) {
                files.erase(it);
                break;
            }
        }
    } catch (const fs::filesystem_error &e) {
        std::cout << "Failed to move symbolic link '" << name << "': " << e.what() << std::endl;
    }
}