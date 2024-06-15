# Fylo (File Manager Theme)
Author: Matúš Tkáč

## Assignment from Progtest

This semester project falls into the category of interactive applications. Your goal is to create an application that the user will interactively control (e.g., using commands on the standard input). Do not try to define any parameters directly in the code (not even using constants). Place them in configuration files (one or more) that your program will read.

Your task is to create a program for managing files and directories (similar to what the Midnight Commander program does).

Implement the following functionalities:

1. Allow working with files: regular files, directories, and symbolic links.

2. Basic operations: create, copy, move, delete.

3. The previous operations (except creation) should also be applicable to a set of files defined by a regular expression.

4. Advanced operations: file concatenation (concat), searching for files based on the text they contain, file deduplication (finding duplicate files and replacing them with symbolic links).

5. Create a user-friendly interface that enables at least the display of directories being worked on, visually distinguishing between files, directories, and symbolic links, and allows navigation between directories.

In this task, it is not possible to implement individual operations using system commands, for example, using the system command (with the exception of clearing the screen, e.g., system("clear")). You can implement individual operations using standard library tools (e.g., std::filesystem). If that is not enough, you can use system libraries like unistd.h, dirent.h, stat.h, and others. More complex operations need to be implemented manually.

Where can you use polymorphism? (recommended)

File types: regular file, directory, symbolic link, ...

Operations: create, copy, move, delete, ...

Finding duplicate files: exact, with whitespace ignoring, ...

User interface: console, ncurses, SDL, OpenGL (various variants), ...

Additional information:

https://midnight-commander.org/

In this task, you can also play with GUI and design a display for two columns.

## Fylo Application Assignment

We will create the CLI application Fylo, which will allow the user to manage files and directories. The user will be able to control the application through simple commands in the console. The user interface will be implemented using a command-line interface (CLI).

The application will have the following functionalities:

- It allows working with files:
    1. Regular files
    2. Directories
    3. Symbolic links

- Basic operations:
    1. Create
    2. Copy
    3. Move
    4. Delete

- The previous operations (except creation) need to be applicable to a set of files defined by a regular expression.

- Advanced operations:
    1. File concatenation (concat)
    2. File searching based on the text they contain (textfind)
    3. File deduplication (dedup)

Here are examples of commands that the application will be able to execute:
- create [filename][filetype]: creates a new empty file with the given [filename].
- copy [filename] [destination]: copies the file [filename] to the [destination] directory.
- move [filename] [destination]: moves the file [filename] to the [destination] directory.
- delete [filename]: deletes the file [filename].
- concat [filename1] [filename2] [destination]: concatenates files [filename1] and [filename2] into the file [destination].
- namefind [filename]: finds the file [filename] in a specific directory.
- textfind [string]: finds a file that contains the [string].
- dedup [filename]: finds duplicates of the file [filename] in the current directory.
- regex [coomand]: executes the [command] on all files in the current directory that match the regular expression.
- cd [destination]: changes the current directory to [destination].
- list: lists the contents of the current directory.
- help: displays help.
- exit: quits the program.

After each modification, the current state of directories and files will be displayed.

Application Sample:
```
Enter command or type (help):
$ create file1
file1 created successfully!
+-----------------+
| file1           |
+-----------------+
$ create dir dir1
dir1 created successfully!
+-----------------+
| file1           |
| dir1            |
+-----------------+
$ copy file1 dir1
file1 copied successfully!
+-----------------+
| file1           |
| +- dir1         |
|    file1        |
+-----------------+
$ cd dir1
$ ls 
+-----------------+
| file1           |
+-----------------+
```

### Polymorphism

My polymorphism works on the double-dispatch principle. I have a parent class CFile that has three derived classes: CRegularFile, CDirectory, and CSymbolicLink. Additionally, I have a CFileOperation class that includes the following operations: CCreate, CCopy, CMove, CDelete, CConcat, CNameFind, CTextFind, CDedup, and CRegex.

Each operation has its own implementation for each file type. For example, CCopy has CCopyRegularFile, CCopyDirectory, and CCopySymbolicLink. Similarly, every other operation has its own implementation for each file type.

When an operation is called, it invokes the operation on the file (based on the specific file type using polymorphism), and then the file polymorphically calls the operation on itself. This way, the operation is performed on the specific file type that is being operated on.