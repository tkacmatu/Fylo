/**
 * @author Matus Tkac <tkacmatu@fit.cvut.cz>
 * @date 29/05/2023
 */

#ifndef TKACMATU_CSYMBOLICLINK_H
#define TKACMATU_CSYMBOLICLINK_H

#include "CFile.h"

/**
 * @brief Class representing symbolic link
 */
class CSymbolicLink : public CFile {
public:
    /**
     * @brief Constructor
     * @param name Name of the file
     * @param filePath Path to the file
     */
    CSymbolicLink(const std::string &name, const fs::path &filePath);

    /**
     * @brief Clones the object
     * @return Shared pointer to the cloned object
     */
    std::shared_ptr<CFile> Clone() const override;

    /**
     * @brief Performs operation on the file
     * @param operation Operation to be performed
     * @param files Vector of files
     * @param folderPath Path to the folder
     */
    void PerformOperation(const std::shared_ptr<COperation> &operation, std::vector<std::shared_ptr<CFile>> &files,
                          std::string &folderPath) override;
};

#endif //TKACMATU_CSYMBOLICLINK_H
