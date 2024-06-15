/**
 * @author Matus Tkac <tkacmatu@fit.cvut.cz>
 * @date 03/06/2023
 */

#include "CApplication.h"

CApplication::CApplication() {
    std::cout << YELLOW_TEXT << "Hello, Welcome to Fylo!" << RESET_TEXT << std::endl;

    // Read the folder path from config.txt
    std::ifstream configFile("config.txt");
    if (configFile.is_open()) {
        std::getline(configFile, m_FolderPath);

        // Check if the folder path is valid
        if (!fs::exists(m_FolderPath)) {
            std::cerr << "Invalid folder path 22: " << m_FolderPath << std::endl;
            std::cerr << "Using the default folder path '.'" << std::endl;
            m_FolderPath = ".";
        }

        configFile.close();
    } else {
        std::cerr << "Error opening config.txt" << std::endl;

        // Set the default folder path
        m_FolderPath = ".";
    }
}

CApplication::~CApplication() {
    std::cout << RED_TEXT << "Terminating Fylo" << RESET_TEXT << std::endl;
}

CApplication &CApplication::RegisterCommand(const CCommand &command) {
    m_Commands.push_back(command);
    return *this;
}

bool CApplication::Execute(std::string &name, CInterface &interface) {
    auto it = actions.find(name);
    if (it != actions.end()) {
        (this->*(it->second))(interface); // This calls corresponding method
        return true;
    } else return false;
}

void CApplication::Create(CInterface &interface) {
    std::string NewFile;
    std::cout << "Type name of the file" << std::endl;
    std::cin >> NewFile;

    // Check for reserved characters
    std::string reservedChars = "/\\:*?\"<>|";
    for (char c: NewFile) {
        if (reservedChars.find(c) != std::string::npos) {
            std::cout << "Invalid file name" << std::endl;
            return;
        }
    }
    // Check for forbidden names or keywords
    std::vector<std::string> forbiddenNames = {"CON", "PRN", "AUX", "COM1", "LPT1"};  // Add more if needed
    for (const std::string &forbiddenName: forbiddenNames) {
        if (NewFile == forbiddenName) {
            std::cout << "Invalid file name" << std::endl;
            return;
        }
    }

    // Prompts user to choose file type
    std::string FileType;
    std::cout << "Type name of the file type [regular, folder, link]" << std::endl;
    std::cin >> FileType;
    fs::path path = m_FolderPath + "/" + NewFile;
    if (FileType == "folder") {
        m_Files.push_back(std::make_shared<CFolder>(NewFile, path));
    } else if (FileType == "link") {
        m_Files.push_back(std::make_shared<CSymbolicLink>(NewFile, path));
    } else if (FileType == "regular") {
        m_Files.push_back(std::make_shared<CRegularFile>(NewFile, path));
    } else {
        std::cout << "Invalid file type" << std::endl;
        return;
    }
    m_Files[m_Files.size() - 1]->PerformOperation(m_CommandsMap["create"], m_Files, m_FolderPath);
    List(interface);
}

void CApplication::List(CInterface &interface) {
    std::cout << "Folder:" << this->m_FolderPath << std::endl;
    for (const auto &item: fs::directory_iterator(this->m_FolderPath)) {
        const std::string &fileName = item.path().filename().string();
        const std::string &fileTypeIcon = CFile::getFileTypeIcon(item.path());
        const std::string &fileTypeColor = CFile::getFileTypeColor(item.path());

        std::cout << fileTypeIcon << fileTypeColor << fileName << " \033[0m" << std::endl;
    }
}

void CApplication::CD(CInterface &interface) {
    std::filesystem::path currentPath = this->m_FolderPath;
    std::string folderName;
    std::cout << "Type name of the folder or '..' for parent folder" << std::endl;
    std::cin >> folderName;
    if (folderName == "..") {
        // Handle navigation to the parent folder
        std::filesystem::path parentPath = currentPath.parent_path();

        if (parentPath.empty()) {
            std::cout << "Already at the root directory." << std::endl;
        } else {
            this->m_FolderPath = parentPath;
            m_Files.clear();
            interface.GetDirectoryContent(m_Files, this->m_FolderPath);
            List(interface);
        }
    } else {
        std::filesystem::path newPath = currentPath / folderName;

        if (!std::filesystem::is_directory(newPath)) {
            std::cout << "Directory '" << folderName << "' does not exist." << std::endl;
        } else {
            this->m_FolderPath = newPath;
            m_Files.clear();
            interface.GetDirectoryContent(m_Files, this->m_FolderPath);
            List(interface);
        }
    }
}

void CApplication::Exit(CInterface &interface) {
    m_Running = false;
}

void CApplication::Help(CInterface &interface) {
    for (auto &command: m_Commands) {
        std::string name = command.m_Name;
        std::transform(name.begin(), name.end(), name.begin(), ::toupper);
        std::cout << name << " - " << command.m_Description << std::endl;
    }
}

void CApplication::NameFinder(CInterface &interface) {
    std::cout << "Type name of the file" << std::endl;
    std::string name;
    std::cin >> name;

    for (const auto &item: fs::directory_iterator(this->m_FolderPath)) {
        const std::string &fileName = item.path().filename().string();
        if (fileName == name) {
            std::cout << GREEN_TEXT << "File found" << RESET_TEXT << std::endl;
            std::cout << "File path: " << item.path() << std::endl;
            return;
        }
    }
    std::cout << RED_TEXT << "File not found" << RESET_TEXT << std::endl;
}

void CApplication::TextFinder(CInterface &interface) {
    std::string searchText;
    interface.ClearInput();

    std::cout << "Enter the text to search for: ";
    std::getline(std::cin, searchText);

    std::cout << "Files containing the text \"" << searchText << "\":" << std::endl;

    // Iterate through the files in m_Files
    for (const auto &file: m_Files) {
        std::ifstream inputFile(file->GetPath());
        if (inputFile.is_open()) {
            std::string line;
            while (std::getline(inputFile, line)) {

                if (line.find(searchText) != std::string::npos) {
                    std::cout << file->GetName() << std::endl;
                    break;
                }
            }
            inputFile.close();
        }
    }
}

void CApplication::Regex(CInterface &interface) {
    // Prompt for operation
    std::cout << "Choose operation: [copy, move, delete]: ";
    std::string command;
    std::cin >> command;

    if ((command != "copy") && (command != "move") && (command != "delete")) {
        std::cout << RED_TEXT << "Invalid command" << RESET_TEXT << std::endl;
        return;
    }

    // Prompt for regular expression
    std::cout << "Enter regular expression: ";
    std::string regexPattern;
    std::cin >> regexPattern;

    try {
        // Validate the regular expression
        std::regex regex(regexPattern);
    } catch (const std::regex_error &e) {
        std::cout << "Invalid regular expression: " << e.what() << std::endl;
        return;
    }

    // Iterate through all files in m_Files
    std::vector<std::shared_ptr<CFile>> matchingFiles = m_Files;
    for (const auto &selectedFile: matchingFiles) {
        std::string fileName = selectedFile->GetName();

        // Check if the file name matches the regular expression
        if (std::regex_match(fileName, std::regex(regexPattern))) {
            // Perform the operation on the matching file
            auto it = m_CommandsMap.find(command);
            if (it != m_CommandsMap.end()) {
                selectedFile->PerformOperation(it->second, m_Files, m_FolderPath);
                List(interface);
            } else {
                std::cout << "Command not found" << std::endl;
            }
        }
    }
}

void CApplication::run() {
    // Run the application
    std::cout << GREEN_TEXT << "Application running" << RESET_TEXT << std::endl;

    // Creates an instance of the interface
    CInterface interface(m_Commands);

    // Now this will call GetDirectoryContent() on the folder
    interface.GetDirectoryContent(m_Files, m_FolderPath);

    // print m_Files
    List(interface);

    // Main loop
    try {
        while (m_Running) {
            std::string command = interface.PromptCommand();
            if (Execute(command, interface)) continue;
            std::shared_ptr<CFile> selectedFile = interface.PromptFilename(m_Files);
            std::cout << GREEN_TEXT << "Executing..." << RESET_TEXT << std::endl;

            auto it = m_CommandsMap.find(command);
            if (it != m_CommandsMap.end()) {
                selectedFile->PerformOperation(it->second, m_Files, m_FolderPath);
                List(interface);
            } else {
                std::cout << "Command not found" << std::endl;
            }
        }
    } catch (std::exception &e) {
        if (std::cin.eof()) {
            std::cout << "EOF" << std::endl;
            return;
        }
        std::cout << "Error: ";
        std::cout << e.what() << std::endl;
    }
}

