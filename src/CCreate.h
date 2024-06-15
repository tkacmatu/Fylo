/**
 * @author Matus Tkac <tkacmatu@fit.cvut.cz>
 * @date 29/05/2023
 */

#ifndef TKACMATU_CCREATE_H
#define TKACMATU_CCREATE_H

#include "COperation.h"

/**
 * @brief Class for creating files
 */
class CCreate : public COperation {
    /**
     * @brief Clone this operation
     * @return Pointer to the cloned operation
     */
    std::shared_ptr<COperation> Clone() const override;

public:
    /**
     * @brief Destructor
     */
    virtual ~CCreate() = default;
    /**
     * @brief Create regular file
     * @param files Vector of files
     * @param name Name of the file
     * @param folderPath Path to the folder
     */
    void RegularFile(std::vector<std::shared_ptr<CFile>>& files, std::string &name, std::string &folderPath) override;

    /**
     * @brief Create folder
     * @param files Vector of files
     * @param name Name of the folder
     * @param folderPath Path to the folder
     */
    void Folder(std::vector<std::shared_ptr<CFile>>& files, std::string &name, std::string &folderPath) override;

    /**
     * @brief Create symbolic link
     * @param files Vector of files
     * @param name Name of the symbolic link
     * @param folderPath Path to the folder
     */
    void SymbolicLink(std::vector<std::shared_ptr<CFile>>& files, std::string &name, std::string &folderPath) override;
};


#endif //TKACMATU_CCREATE_H
