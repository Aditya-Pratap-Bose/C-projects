# Student Management System (C with File I/O)

A simple, menu-driven Student Management System built in C using binary file handling and struct to store and manage student records efficiently.

## Features

* Add new student record
* Display all students in tabular format
* Search student by roll number
* Update existing student details
* Delete student record
* Admin login (with hidden password using `getch()`)

## Core Concepts Used

* `struct` for student data model
* `fopen()`, `fread()`, `fwrite()`, `fseek()`, `rewind()`, `remove()`, `rename()`
* File modes: `"rb+"`, `"wb+"`, `"ab+"`
* `getch()` for password input
* `system("cls")` to clear console (Windows)
* Dynamic terminal layout with `printf()` formatting

## File Structure

```
student_file.c          → Main source code (file-based)
students.dat            → Auto-created binary file to store student records
README.md               → This documentation
```

## Compilation & Run

### Compile:

```bash
gcc student_file.c -o student.exe
```

### Run:

```bash
./student.exe
```

Admin Password: `admin123`

## Notes

* Output formatted with `%-10d %-30s %-10.2f` for clean display
* File stored in binary `.dat` format
* Password is hardcoded
* Uses `fflush(stdin)` and `gets()` (not recommended in modern C)
* Windows-specific: replace `system("cls")` & `getch()` for Linux compatibility

## Learning Outcomes

* Real-life use of C structs + file handling
* Handling file pointers and dynamic navigation
* Logic for deletion using temp file copying
* Foundation for building DB-style CLI apps


---

> _📌 Trying to learn DSA, so will try shifting this to dynamic structures later. If you have ideas or suggestions, feel free to share!_
