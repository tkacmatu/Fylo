/**
 * @author Matus Tkac <tkacmatu@fit.cvut.cz>
 * @date 29/05/2023
 */

#ifndef TKACMATU_CAPPLICATION_H
#define TKACMATU_CAPPLICATION_H

#include "CCommand.h"
#include "CInterface.h"
#include "CConcat.h"
#include "CCopy.h"
#include "CCreate.h"
#include "CDedup.h"
#include "CDelete.h"
#include "CMove.h"
#include <iostream>
#include <iostream>
#include <memory>
#include <vector>
#include <regex>

// ANSI escape codes for text colors
#define RED_TEXT "\033[31m"
#define RESET_TEXT "\033[0m"

/**
 * @brief Main application class
 */
class CApplication {
public:
    /**
     * @brief Default constructor
     */
    CApplication();

    /**
     * @brief Default destructor
     */
    ~CApplication();

    /**
     * @brief Registers command to the application
     * @param command Command to be registered
     * @return Reference to the application
     */
    CApplication &RegisterCommand(const CCommand &command);

    /**
     * @brief Runs the application
     */
    void run();

    /**
     * @brief Executes command
     * @param name Name of the command
     * @param interface Interface to be used
     * @return True if command was executed successfully, false otherwise
     */
    bool Execute(std::string &name, CInterface &interface);

    /**
     * @brief Creates new file
     * @param interface Interface to be used
     */
    void Create(CInterface &interface);

    /**
     * @brief Lists files in current directory
     * @param interface Interface to be used
     */
    void List(CInterface &interface);

    /**
     * @brief Changes current directory
     * @param interface Interface to be used
     */
    void CD(CInterface &interface);

    /**
     * @brief Exits the application
     * @param interface Interface to be used
     */
    void Exit(CInterface &interface);

    /**
     * @brief Prints help
     * @param interface Interface to be used
     */
    void Help(CInterface &interface);

    /**
     * @brief Finds files by name
     * @param interface Interface to be used
     */
    void NameFinder(CInterface &interface);

    /**
     * @brief Finds files by text
     * @param interface Interface to be used
     */
    void TextFinder(CInterface &interface);

    /**
     * @brief Finds files by regex
     * @param interface Interface to be used
     */
    void Regex(CInterface &interface);

    bool m_Running = true; /**< Flag indicating whether the application is running */
private:
    std::vector<std::shared_ptr<CFile>> m_Files; /**< Vector of files in current directory */

    std::string m_FolderPath; /**< Path to the current directory */

    std::vector<CCommand> m_Commands; /**< Vector of registered commands */

    std::unordered_map<std::string, std::shared_ptr<COperation>> m_CommandsMap{
            {"concat", std::make_shared<CConcat>()},
            {"copy",   std::make_shared<CCopy>()},
            {"create", std::make_shared<CCreate>()},
            {"dedup",  std::make_shared<CDedup>()},
            {"delete", std::make_shared<CDelete>()},
            {"move",   std::make_shared<CMove>()}
    }; /**< Map of registered commands (double-dispatch) */

    std::unordered_map<std::string, void (CApplication::*)(CInterface &)> actions{
            {"create",   &CApplication::Create},
            {"list",     &CApplication::List},
            {"cd",       &CApplication::CD},
            {"exit",     &CApplication::Exit},
            {"help",     &CApplication::Help},
            {"textfind", &CApplication::TextFinder},
            {"namefind", &CApplication::NameFinder},
            {"regex",    &CApplication::Regex}
    }; /**< Map of registered BasicCommands */
};

#endif //TKACMATU_CAPPLICATION_H
