/**
 * @author Matus Tkac <tkacmatu@fit.cvut.cz>
 * @date 29/05/2023
 */

#include "CDelete.h"

namespace fs = std::filesystem;

std::shared_ptr<COperation> CDelete::Clone() const {
    return std::make_shared<CDelete>(*this);
}

void CDelete::RegularFile(std::vector<std::shared_ptr<CFile>> & files, std::string &name, std::string &folderPath) {
    for (auto it = files.begin(); it != files.end(); ++it) {
        if ((*it)->GetName() == name) {
            fs::path filePath = folderPath + "/" + name;
            fs::remove(filePath);
            files.erase(it);
            break;
        }
    }
}

void CDelete::Folder(std::vector<std::shared_ptr<CFile>> & files, std::string &name, std::string &folderPath) {
    for (auto it = files.begin(); it != files.end(); ++it) {
        if ((*it)->GetName() == name) {
            fs::path folderPathToDelete = folderPath + "/" + name;
            fs::remove_all(folderPathToDelete);
            files.erase(it);
            break;
        }
    }
}

void CDelete::SymbolicLink(std::vector<std::shared_ptr<CFile>> & files, std::string &name, std::string &folderPath) {
    for (auto it = files.begin(); it != files.end(); ++it) {
        if ((*it)->GetName() == name) {
            fs::path symbolicLinkPath = folderPath + "/" + name;
            fs::remove(symbolicLinkPath);
            files.erase(it);
            break;
        }
    }
}