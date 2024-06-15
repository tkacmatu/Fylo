/**
 * @author Matus Tkac <tkacmatu@fit.cvut.cz>
 * @date 29/05/2023
 */

#ifndef TKACMATU_CMOVE_H
#define TKACMATU_CMOVE_H

#include "COperation.h"
#include "CFile.h"

/**
 * @brief Class for moving files
 */
class CMove : public COperation {
    /**
     * @brief Clone this operation
     * @return Pointer to the cloned operation
     */
    std::shared_ptr<COperation> Clone() const override;

public:
    /**
     * @brief Destructor
     */
    virtual ~CMove() = default;

    /**
     * @brief Move regular file
     * @param files Vector of files
     * @param name Name of the file
     * @param folderPath Path to the folder
     */
    void RegularFile(std::vector<std::shared_ptr<CFile>> &files, std::string &name, std::string &folderPath) override;

    /**
     * @brief Move folder
     * @param files Vector of files
     * @param name Name of the folder
     * @param folderPath Path to the folder
     */
    void Folder(std::vector<std::shared_ptr<CFile>> &files, std::string &name, std::string &folderPath) override;

    /**
     * @brief Move symbolic link
     * @param files Vector of files
     * @param name Name of the symbolic link
     * @param folderPath Path to the folder
     */
    void SymbolicLink(std::vector<std::shared_ptr<CFile>> &files, std::string &name, std::string &folderPath) override;
};


#endif //TKACMATU_CMOVE_H
