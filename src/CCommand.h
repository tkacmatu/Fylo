/**
 * @author Matus Tkac <tkacmatu@fit.cvut.cz>
 * @date 29/05/2023
 */

#ifndef TKACMATU_CCOMMAND_H
#define TKACMATU_CCOMMAND_H

#include <iostream>

/**
 * @brief Class representing a command
 */
class CCommand {
public:
    std::string m_Name; /**< Name of the command */
    std::string m_Description; /**< Description of the command */

    /**
     * @brief Constructor
     * @param name Name of the command
     * @param description Description of the command
     */
    CCommand(const std::string name, const std::string description);
};


#endif //TKACMATU_CCOMMAND_H
