/**
 * @author Matus Tkac <tkacmatu@fit.cvut.cz>
 * @date 29/05/2023
 */

#include "CRegularFile.h"

CRegularFile::CRegularFile(const std::string & name, const fs::path & filePath)
        : CFile(name, filePath) {}

std::shared_ptr<CFile> CRegularFile::Clone() const {
    return std::make_shared<CRegularFile>(*this);
}

void CRegularFile::PerformOperation(const std::shared_ptr<COperation> &operation, std::vector<std::shared_ptr<CFile>> & files, std::string &folderPath) {
    operation->RegularFile(files, m_Name, folderPath);
}