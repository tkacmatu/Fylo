/**
 * @author Matus Tkac <tkacmatu@fit.cvut.cz>
 * @date 29/05/2023
 */

#include "CCreate.h"

namespace fs = std::filesystem;

std::shared_ptr<COperation> CCreate::Clone() const {
    return std::make_shared<CCreate>(*this);
}

void CCreate::RegularFile(std::vector<std::shared_ptr<CFile>>& files, std::string &name, std::string &folderPath) {
    fs::path itemPath = fs::path(folderPath) / name;
    std::ofstream file(itemPath);
    if (file) {
        std::cout << "Folder created successfully." << std::endl;
    } else {
        std::cout << "Failed to create the folder." << std::endl;
    }
}

void CCreate::Folder(std::vector<std::shared_ptr<CFile>>& files, std::string &name, std::string &folderPath) {
    fs::path itemPath = fs::path(folderPath) / name;
    if (fs::create_directory(itemPath)) {
        std::cout << "Folder created successfully." << std::endl;
    } else {
        std::cout << "Failed to create the folder." << std::endl;
    }
}

void CCreate::SymbolicLink(std::vector<std::shared_ptr<CFile>>& files, std::string &name, std::string &folderPath) {
    fs::path itemPath = fs::path(folderPath) / name;

    std::cout << "Enter the target path for the symbolic link: ";
    std::string target;
    std::cin >> target;
    // Check if the target path exists
    if (!fs::exists(target)) {
        std::cout << "The target path does not exist." << std::endl;
        return;
    }

    std::error_code ec;
    fs::create_symlink(fs::path(target), itemPath, ec);

    if (!ec) {
        std::cout << "Symbolic link created successfully." << std::endl;
    } else {
        std::cout << "Failed to create the symbolic link. Error: " << ec.message() << std::endl;
    }
}

