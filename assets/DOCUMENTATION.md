# Fylo

Fylo is a file manager that allows you to perform various file operations. Below are the available commands:

- `create [filename][filetype]`: Creates a new empty file with the given `filename`.
- `copy [filename] [destination]`: Copies the file `filename` to the `destination` directory.
- `move [filename] [destination]`: Moves the file `filename` to the `destination` directory.
- `delete [filename]`: Deletes the file `filename`.
- `concat [filename1] [filename2] [destination]`: Concatenates files `filename1` and `filename2` into the file `destination`.
- `namefind [filename]`: Finds the file `filename` in a specific directory.
- `textfind [string]`: Finds a file that contains the `string`.
- `dedup [filename]`: Finds duplicates of the file `filename` in the current directory.
- `regex [expression][command]`: Executes the `command` on all files in the current directory that match the regular expression.
- `cd [destination]`: Changes the current directory to `destination`.
- `list`: Lists the contents of the current directory.
- `help`: Displays help.
- `exit`: Quits the program.

Feel free to explore and use these commands to manage your files with Fylo!
