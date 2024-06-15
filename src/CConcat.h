/**
 * @author Matus Tkac <tkacmatu@fit.cvut.cz>
 * @date 29/05/2023
 */

#ifndef TKACMATU_CCONCAT_H
#define TKACMATU_CCONCAT_H

#include "COperation.h"
#include "CFolder.h"

/**
 * @brief Class for concatenating two files
 */
class CConcat : public COperation {
    /**
     * @brief Clones this operation
     * @return Pointer to the cloned operation
     */
    std::shared_ptr<COperation> Clone() const override;

public:
    /**
     * @brief Destructor
     */
    virtual ~CConcat() = default;
    /**
     * @brief Concatenates two files
     * @param files Vector of files
     * @param name Name of the file
     * @param folderPath Path to the folder
     */
    void RegularFile(std::vector<std::shared_ptr<CFile>> & files, std::string &name, std::string &folderPath) override;

    /**
     * @brief Concatenates two folders
     * @param files Vector of files
     * @param name Name of the folder
     * @param folderPath Path to the folder
     */
    void Folder(std::vector<std::shared_ptr<CFile>> & files, std::string &name, std::string &folderPath) override;

    /**
     * @brief Concatenates two symbolic links
     * @param files Vector of files
     * @param name Name of the symbolic link
     * @param folderPath Path to the folder
     */
    void SymbolicLink(std::vector<std::shared_ptr<CFile>> & files, std::string &name, std::string &folderPath) override;
};


#endif //TKACMATU_CCONCAT_H
