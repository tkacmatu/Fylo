/**
 * @author Matus Tkac <tkacmatu@fit.cvut.cz>
 * @date 29/05/2023
 */

#include "CFile.h"

CFile::CFile(const std::string &name, const fs::path &filePath)
        : m_Name(name), m_FilePath(filePath) {}

std::string CFile::GetName() const {
    return m_Name;
}

std::string CFile::GetPath() const {
    return m_FilePath;
}

std::string CFile::getFileTypeIcon(const fs::path &filePath) {
    if (fs::is_directory(filePath)) {
        return "\U0001F4C1"; // Folder icon
    } else if (fs::is_symlink(filePath)) {
        return "\U0001F517"; // Symbolic Link icon
    } else if (fs::is_regular_file(filePath)) {
        return "\U0001F4C4"; // Regular file icon
    } else {
        return "?"; // Unknown file type
    }
}

std::string CFile::getFileTypeColor(const fs::path &filePath) {
    if (fs::is_directory(filePath)) {
        return "\033[32m"; // Green color for directories
    } else if (fs::is_symlink(filePath)) {
        return "\033[31m"; // Red color for symbolic links
    } else if (fs::is_regular_file(filePath)) {
        return "\033[0m"; // Default color for regular files
    } else {
        return "\033[0m"; // Default color for unknown file types
    }
}
