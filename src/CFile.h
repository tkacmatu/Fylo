/**
 * @author Matus Tkac <tkacmatu@fit.cvut.cz>
 * @date 29/05/2023
 */

#ifndef TKACMATU_CFILE_H
#define TKACMATU_CFILE_H

#include "COperation.h"
#include <iostream>
#include <memory>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

/**
 * @brief Abstract class representing file
 */
class CFile {
public:

    /**
     * @brief Constructor
     * @param name Name of the file
     * @param filePath Path to the file
     */
    CFile(const std::string &name, const fs::path &filePath);

    /**
     * @brief Destructor
     */
    virtual ~CFile() = default;

    /**
     * @brief Clone method
     * @return Shared pointer to the clone of the file
     */
    virtual std::shared_ptr<CFile> Clone() const = 0;

    /**
     * @brief Perform operation on the file
     * @param operation Operation to be performed
     * @param files Vector of files
     * @param folderPath Path to the folder
     */
    virtual void
    PerformOperation(const std::shared_ptr<COperation> &operation, std::vector<std::shared_ptr<CFile>> &files,
                     std::string &folderPath) = 0;

    /**
     * @brief Get name of the file
     * @return Name of the file
     */
    std::string GetName() const;

    /**
     * @brief Get path to the file
     * @return Path to the file
     */
    std::string GetPath() const;

    /**
     * @brief Get file type icon
     * @param filePath Path to the file
     * @return File type icon
     */
    static std::string getFileTypeIcon(const fs::path &filePath);

    /**
     * @brief Get file type color
     * @param filePath Path to the file
     * @return File type color
     */
    static std::string getFileTypeColor(const fs::path &filePath);

protected:
    std::string m_Name; /**< Name of the file */
    std::string m_FilePath; /**< Path to the file */
};

#endif //TKACMATU_CFILE_H
