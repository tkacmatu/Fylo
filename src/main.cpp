//
// @author Matus Tkac <tkacmatu@fit.cvut.cz>
// @date 03/06/2023

#include "CApplication.h"
#include "CCommand.h"
#include <iostream>

/**
 * @brief Main function
 * @return 0 if successful
 */
int main() {

    CApplication app;
    // Register commands (Beware you wont be able to execute the command unless you add it to the map as well)
    app.RegisterCommand(CCommand("list", "Prints the current directory"))
        .RegisterCommand(CCommand("create", "Creates a new file"))
        .RegisterCommand(CCommand("cd", "Changes the current directory"))
        .RegisterCommand(CCommand("move", "Moves a file"))
        .RegisterCommand(CCommand("copy", "Copies a file"))
        .RegisterCommand(CCommand("concat", "Merges two files"))
        .RegisterCommand(CCommand("dedup", "Removes duplicate files"))
        .RegisterCommand(CCommand("help", "Prints help"))
        .RegisterCommand(CCommand("exit", "Exits the program"))
        .RegisterCommand(CCommand("delete", "Deletes a file"))
        .RegisterCommand(CCommand("textfind", "Searches for files by the text they contain"))
        .RegisterCommand(CCommand("namefind", "Searches for files by their name"))
        .RegisterCommand(CCommand("regex", "Provides Move/Copy/Delete functionality with over regular expressions"));

    app.run();

    return EXIT_SUCCESS;
}
