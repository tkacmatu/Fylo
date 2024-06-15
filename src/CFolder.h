/**
 * @author Matus Tkac <tkacmatu@fit.cvut.cz>
 * @date 29/05/2023
 */


#ifndef TKACMATU_CFOLDER_H
#define TKACMATU_CFOLDER_H

#include "CFile.h"

/**
 * @brief blass representing folder
 */
class CFolder : public CFile {
public:
    /**
     * Constructor
     * @param name name of the folder
     * @param filePath path to the folder
     */
    CFolder(const std::string &name, const fs::path &filePath);

    /**
     * Clones the folder
     * @return cloned folder
     */
    std::shared_ptr<CFile> Clone() const override;

    /**
     * Performs operation on the folder
     * @param operation operation to be performed
     * @param files vector of files
     * @param folderPath path to the folder
     */
    void PerformOperation(const std::shared_ptr<COperation> &operation, std::vector<std::shared_ptr<CFile>> &files,
                          std::string &folderPath) override;
};

#endif //TKACMATU_CFOLDER_H
