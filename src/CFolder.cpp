/**
 * @author Matus Tkac <tkacmatu@fit.cvut.cz>
 * @date 29/05/2023
 */


#include "CFolder.h"

CFolder::CFolder(const std::string & name, const fs::path & filePath)
        : CFile(name, filePath) {
}

std::shared_ptr<CFile> CFolder::Clone() const {
    return std::make_shared<CFolder>(*this);
}

void CFolder::PerformOperation(const std::shared_ptr<COperation> &operation, std::vector<std::shared_ptr<CFile>> & files, std::string &folderPath) {
    operation->Folder(files, m_Name, folderPath);
}