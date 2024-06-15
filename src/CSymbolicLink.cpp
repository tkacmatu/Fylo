/**
 * @author Matus Tkac <tkacmatu@fit.cvut.cz>
 * @date 29/05/2023
 */

#include "CSymbolicLink.h"

CSymbolicLink::CSymbolicLink(const std::string & name, const fs::path & filePath)
        : CFile(name, filePath) {}

std::shared_ptr<CFile> CSymbolicLink::Clone() const {
    return std::make_shared<CSymbolicLink>(*this);
}

void CSymbolicLink::PerformOperation(const std::shared_ptr<COperation> &operation,
                                     std::vector<std::shared_ptr<CFile>> &files, std::string &folderPath) {
    operation->SymbolicLink(files, m_Name, folderPath);
}

