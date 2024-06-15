/**
 * @author Matus Tkac <tkacmatu@fit.cvut.cz>
 * @date 29/05/2023
 */

#include "CInterface.h"

CInterface::CInterface(std::vector<CCommand> commands)
        : m_Input(std::cin), m_Output(std::cout), m_Commands(commands) {
    m_Input.exceptions(std::ios::eofbit | std::ios::badbit);
    m_Output.exceptions(std::ios::failbit | std::ios::badbit | std::ios::eofbit);
}

CInterface::~CInterface() {
    m_Input.clear();
    m_Output.clear();
}

bool CInterface::ValidateInput(std::string &input) {
    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
    for (auto &c: m_Commands) {
        if (c.m_Name == input) {
            return true;
        }
    }
    return false;
}

void CInterface::ClearInput() {
    m_Input.clear();
    m_Input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string CInterface::PromptCommand() {
    std::string word;
    while (true) {
        m_Output << "Enter command or type help: " << std::endl;
        m_Input >> word;
        if (!ValidateInput(word)) {
            m_Output << RED_TEXT << "Error: Command not found" << RESET_TEXT << std::endl;
            ClearInput();
        } else {
            break;
        }
    }
    return word;
}

std::shared_ptr<CFile> CInterface::PromptFilename(std::vector<std::shared_ptr<CFile>> &files) {
    std::string word;
    while (true) {
        m_Output << "Enter the name of the file: " << std::endl;
        m_Input >> word;
        for (auto &file: files) {
            if (file->GetName() == word) {
                return file;
            }
        }
        m_Output << RED_TEXT << "Error: File not found" << RESET_TEXT << std::endl;
        ClearInput();
    }
}

void CInterface::GetDirectoryContent(std::vector<std::shared_ptr<CFile>> &files, std::string &path) {
    //Fetch all files in current directory
    for (const auto &item: fs::directory_iterator(path)) {
        if (item.is_directory()) {
            files.push_back(std::make_shared<CFolder>(item.path().filename().string(), item.path().string()));
        } else if (item.is_symlink()) {
            files.push_back(std::make_shared<CSymbolicLink>(item.path().filename().string(), item.path().string()));
        } else if (item.is_regular_file()) {
            files.push_back(std::make_shared<CRegularFile>(item.path().filename().string(), item.path().string()));
        }
    }

}
