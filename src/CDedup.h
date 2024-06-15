/**
 * @author Matus Tkac <tkacmatu@fit.cvut.cz>
 * @date 29/05/2023
 */

#ifndef TKACMATU_CDEDUP_H
#define TKACMATU_CDEDUP_H

#include "COperation.h"
#include "CSymbolicLink.h"

/**
 * @brief Class for deduplication operation
 */
class CDedup : public COperation {
    /**
     * @brief Clone this operation
     * @return Pointer to cloned operation
     */
    std::shared_ptr<COperation> Clone() const override;

public:
    /**
     * @brief Constructor
     */
    virtual ~CDedup() = default;
    /**
     * @brief Deduplicate regular file
     * @param files Vector of files
     * @param name Name of file
     * @param folderPath Path to folder
     */
    void RegularFile(std::vector<std::shared_ptr<CFile>> & files, std::string &name, std::string &folderPath) override;

    /**
     * @brief Deduplicate folder
     * @param files Vector of files
     * @param name Name of folder
     * @param folderPath Path to folder
     */
    void Folder(std::vector<std::shared_ptr<CFile>> & files, std::string &name, std::string &folderPath) override;

    /**
     * @brief Deduplicate symbolic link
     * @param files Vector of files
     * @param name Name of symbolic link
     * @param folderPath Path to folder
     */
    void SymbolicLink(std::vector<std::shared_ptr<CFile>> & files, std::string &name, std::string &folderPath) override;

};

#endif //TKACMATU_CDEDUP_H
