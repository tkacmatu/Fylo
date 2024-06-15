/**
 * @author Matus Tkac <tkacmatu@fit.cvut.cz>
 * @date 29/05/2023
 */

#include "CCopy.h"


namespace fs = std::filesystem;

std::shared_ptr<COperation> CCopy::Clone() const {
    return std::make_shared<CCopy>(*this);
}

void CCopy::RegularFile(std::vector<std::shared_ptr<CFile>> &files, std::string &name, std::string &folderPath) {
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

    // Check if the file already exists in the destination folder
    if (fs::exists(destinationFile)) {
        // Generate a new filename with an appended number
        std::string newFilename = name;
        std::string extension = destinationFile.extension().string();
        std::string baseFilename = destinationFile.stem().string();
        int count = 1;

        while (fs::exists(destinationPath / newFilename)) {
            newFilename = baseFilename + std::to_string(count) + extension;
            count++;
        }

        destinationFile = destinationPath / newFilename;
    }

    try {
        fs::copy(sourcePath, destinationFile);
        std::cout << "File '" << name << "' copied to '" << destinationFile.filename() << "'." << std::endl;

        // If the file was copied within the same folder, add it to the files vector
        if (destinationPath == folderPath) {
            files.push_back(std::make_shared<CRegularFile>(destinationFile.filename().string(), folderPath));
        }
    } catch (const fs::filesystem_error &e) {
        std::cout << "Failed to copy file '" << name << "': " << e.what() << std::endl;
    }
}

void CCopy::Folder(std::vector<std::shared_ptr<CFile>> &files, std::string &name, std::string &folderPath) {
    // Prompt user for destination
    std::string destination;
    std::cout << "Enter destination folder (Enter '.' for current folder): ";
    std::cin >> destination;

    if (destination == ".") {
        destination = folderPath; // Set the current folder as the destination
    }

    std::filesystem::path destinationPath(destination);

    if (!std::filesystem::is_directory(destinationPath)) {
        std::cout << "Destination folder '" << destination << "' does not exist." << std::endl;
        return;
    }

    std::filesystem::path sourcePath = folderPath + "/" + name;
    std::filesystem::path destinationFolder = destinationPath / name;

    // Check if the folder already exists in the destination folder
    if (std::filesystem::exists(destinationFolder)) {
        // Generate a new folder name with an appended number
        std::string newFolderName = name;
        int count = 1;

        while (std::filesystem::exists(destinationPath / newFolderName)) {
            newFolderName = name + std::to_string(count);
            count++;
        }

        destinationFolder = destinationPath / newFolderName;
    }

    try {
        std::filesystem::copy(sourcePath, destinationFolder);
        std::cout << "Folder '" << name << "' copied to '" << destinationFolder.filename() << "'." << std::endl;

        // If the folder was copied within the same folder, add it to the files vector
        if (destinationPath == folderPath) {
            files.push_back(std::make_shared<CFolder>(destinationFolder.filename().string(), folderPath));
        }
    } catch (const std::filesystem::filesystem_error &e) {
        std::cout << "Failed to copy folder '" << name << "': " << e.what() << std::endl;
    }
}

void CCopy::SymbolicLink(std::vector<std::shared_ptr<CFile>> &files, std::string &name, std::string &folderPath) {
    // Prompt user for destination
    std::string destination;
    std::cout << "Enter destination folder (Enter '.' for current folder): ";
    std::cin >> destination;

    if (destination == ".") {
        destination = folderPath; // Set the current folder as the destination
    }

    std::filesystem::path destinationPath(destination);

    if (!std::filesystem::is_directory(destinationPath)) {
        std::cout << "Destination folder '" << destination << "' does not exist." << std::endl;
        return;
    }

    std::filesystem::path sourcePath = folderPath + "/" + name;
    std::filesystem::path destinationLink = destinationPath / name;

    // Check if the symbolic link already exists in the destination folder
    if (std::filesystem::exists(destinationLink)) {
        // Generate a new link name with an appended number
        std::string newLinkName = name;
        int count = 1;

        while (std::filesystem::exists(destinationPath / newLinkName)) {
            newLinkName = name + std::to_string(count);
            count++;
        }

        destinationLink = destinationPath / newLinkName;
    }

    try {
        std::filesystem::create_symlink(sourcePath, destinationLink);
        std::cout << "Symbolic link '" << name << "' copied to '" << destinationLink.filename() << "'." << std::endl;

        // If the symbolic link was copied within the same folder, add it to the files vector
        if (destinationPath == folderPath) {
            files.push_back(std::make_shared<CSymbolicLink>(destinationLink.filename().string(), folderPath));
        }
    } catch (const std::filesystem::filesystem_error &e) {
        std::cout << "Failed to copy symbolic link '" << name << "': " << e.what() << std::endl;
    }
}
