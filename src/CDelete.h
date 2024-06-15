/**
 * @author Matus Tkac <tkacmatu@fit.cvut.cz>
 * @date 29/05/2023
 */

#ifndef TKACMATU_CDELETE_H
#define TKACMATU_CDELETE_H

#include "COperation.h"
#include "CFile.h"

/**
 * @brief Class for deleting files
 */
class CDelete : public COperation {
    /**
     * @brief Clone this operation
     * @return Pointer to the cloned operation
     */
    std::shared_ptr<COperation> Clone() const override;

public:
    /**
     * @brief Destructor
     */
    virtual ~CDelete() = default;

    /**
     * @brief Delete regular file
     * @param files Vector of files
     * @param name Name of the file
     * @param folderPath Path to the folder
     */
    void RegularFile(std::vector<std::shared_ptr<CFile>> &files, std::string &name, std::string &folderPath) override;

    /**
     * @brief Delete folder
     * @param files Vector of files
     * @param name Name of the folder
     * @param folderPath Path to the folder
     */
    void Folder(std::vector<std::shared_ptr<CFile>> &files, std::string &name, std::string &folderPath) override;

    /**
     * @brief Delete symbolic link
     * @param files Vector of files
     * @param name Name of the symbolic link
     * @param folderPath Path to the folder
     */
    void SymbolicLink(std::vector<std::shared_ptr<CFile>> &files, std::string &name, std::string &folderPath) override;

};

#endif //TKACMATU_CDELETE_H
