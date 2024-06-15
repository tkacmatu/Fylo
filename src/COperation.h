/**
 * @author Matus Tkac <tkacmatu@fit.cvut.cz>
 * @date 29/05/2023
 */

#ifndef TKACMATU_COPERATION_H
#define TKACMATU_COPERATION_H

#include <memory>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>

// ANSI escape codes for text colors
#define RED_TEXT "\033[31m"
#define GREEN_TEXT "\033[32m"
#define RESET_TEXT "\033[0m"

class CFile;

/**
 * @brief Abstract class for operations
 */
class COperation {
public:
    /**
     * @brief Clone method for polymorphism
     */
    virtual std::shared_ptr<COperation> Clone() const = 0;

    /**
     * @brief Method for regular file operation
     * @param files vector of files
     * @param name name of file
     * @param folderPath path to folder
     */
    virtual void
    RegularFile(std::vector<std::shared_ptr<CFile>> &files, std::string &name, std::string &folderPath) = 0;

    /**
     * @brief Method for folder operation
     * @param files vector of files
     * @param name name of file
     * @param folderPath path to folder
     */
    virtual void Folder(std::vector<std::shared_ptr<CFile>> &files, std::string &name, std::string &folderPath) = 0;

    /**
     * @brief Method for symbolic link operation
     * @param files vector of files
     * @param name name of file
     * @param folderPath path to folder
     */
    virtual void
    SymbolicLink(std::vector<std::shared_ptr<CFile>> &files, std::string &name, std::string &folderPath) = 0;
};

#endif //TKACMATU_COPERATION_H
