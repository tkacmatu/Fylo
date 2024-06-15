/**
 * @author Matus Tkac <tkacmatu@fit.cvut.cz>
 * @date 29/05/2023
 */

#ifndef TKACMATU_CCOPY_H
#define TKACMATU_CCOPY_H

#include "COperation.h"
#include "CRegularFile.h"
#include "CFolder.h"
#include "CSymbolicLink.h"

/**
 * Class for copying files
 */
class CCopy : public COperation {
    /**
     * Clones this operation
     * @return cloned operation
     */
    std::shared_ptr<COperation> Clone() const override;
public:
    /**
     * @brief Destructor
     */
    virtual ~CCopy() = default;
    /**
     * Copies regular file
     * @param files vector of files
     * @param name name of file
     * @param folderPath path to folder
     */
    void RegularFile(std::vector<std::shared_ptr<CFile>> & files, std::string &name, std::string &folderPath) override;

    /**
     * Copies folder
     * @param files vector of files
     * @param name name of file
     * @param folderPath path to folder
     */
    void Folder(std::vector<std::shared_ptr<CFile>> & files, std::string &name, std::string &folderPath) override;

    /**
     * Copies symbolic link
     * @param files vector of files
     * @param name name of file
     * @param folderPath path to folder
     */
    void SymbolicLink(std::vector<std::shared_ptr<CFile>> & files, std::string &name, std::string &folderPath) override;
};

#endif //TKACMATU_CCOPY_H
