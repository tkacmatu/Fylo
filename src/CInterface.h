/**
 * @author Matus Tkac <tkacmatu@fit.cvut.cz>
 * @date 29/05/2023
 */


#ifndef TKACMATU_CINTERFACE_H
#define TKACMATU_CINTERFACE_H

#include "CCommand.h"
#include "CRegularFile.h"
#include "CFolder.h"
#include "CSymbolicLink.h"
#include <iostream>
#include <filesystem>

// ANSI escape codes for text colors
#define RED_TEXT "\033[31m"
#define GREEN_TEXT "\033[32m"
#define YELLOW_TEXT "\033[33m"
#define RESET_TEXT "\033[0m"

namespace fs = std::filesystem;

/**
 * @brief Class for handling user input and output
 */
class CInterface {
private:
    std::istream & m_Input;
    std::ostream & m_Output;
    std::vector<CCommand> m_Commands;

public:
    /**
     * @brief Constructor
     * @param commands vector of commands
     */
    CInterface(std::vector<CCommand> commands);
    /**
     * @brief Destructor
     */
    ~CInterface();

    /**
     * @brief Validates user input
     * @param input user input
     * @return true if input is valid, false otherwise
     */
    bool ValidateInput(std::string & input);

    /**
     * @brief Clears user input
     */
    void ClearInput();

    /**
     * @brief Prompts user for command
     * @return user input
     */
    std::string PromptCommand();

    /**
     * @brief Prompts user for filename
     * @param files vector of files
     * @return shared pointer to file
     */
    std::shared_ptr<CFile> PromptFilename(std::vector<std::shared_ptr<CFile>> & files);

    /**
     * @brief Gets content of directory
     * @param files vector of files
     * @param path path to directory
     */
    void GetDirectoryContent(std::vector<std::shared_ptr<CFile>> & files, std::string & path);
};


#endif //TKACMATU_CINTERFACE_H
