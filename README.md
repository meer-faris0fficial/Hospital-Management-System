# Hospital Management System (C)

A simple console-based Hospital Management System written in C.  
Features include user signup/login, hospital records (add, list, filter, sort), and patient records (add, list). Data is saved to plain text files.

> NOTE: This program uses Windows console headers (`windows.h`, `conio.h`) and ANSI escape sequences for colored output. It is intended to build and run on Windows (MinGW or MSVC). See the "Build & Run" section for platform notes and tips.

---

## Features
- User authentication: signup and login (credentials stored in plain text).
- Hospital management:
  - Add hospital records (ID, name, city, beds, price, rating, reviews)
  - Display all hospitals
  - Display hospitals by city (alphabetically sorted)
  - Sorting utilities:
    - Sort by bed price (descending)
    - Sort by available beds (descending)
    - Sort by name (A→Z)
    - Sort by rating (then reviews)
- Patient management:
  - Add patient records (ID, name, age, disease, hospital ID)
  - Display patients (shows hospital name via hospital ID lookup)
- Simple, file-based storage (no external DB).

---

## Files Used by the Program
- `hospitals.txt` — stores hospital records; one record per line in pipe-separated format:
  id|name|city|available_beds|bed_price|rating|reviews
  Example:
  101|City General Hospital|Springfield|50|75.00|4.3|128
- `patients.txt` — stores patient records; one record per line:
  id|name|age|disease|hospital_id
  Example:
  201|John Doe|45|Pneumonia|101
- `users.txt` — stores user credentials in plain text:
  username|password
  Example:
  alice|password123

---

## Build & Run

### Requirements
- Windows (recommended), or adapt the source for POSIX systems.
- C compiler:
  - MinGW (gcc) or Microsoft Visual C++ (cl).

### Compile (MinGW / msys)
Open a terminal in the folder containing the .c file and run:
```
gcc -o hms.exe main.c
```
(Replace `main.c` with your source filename.)

### Compile (MSVC)
Open Visual Studio Developer Command Prompt:
```
cl /Fe:hms.exe main.c
```

### Run
From the console:
```
hms.exe
```

### Platform notes
- The program includes `windows.h`, `conio.h`, and uses `Sleep()`. It is written primarily for Windows.
- The program also prints ANSI color escape sequences. On modern Windows 10/11 consoles these are usually supported; otherwise run the program inside a terminal that supports ANSI (e.g., Windows Terminal, Git Bash, or enable Virtual Terminal Processing).
- To build on Linux/macOS you must:
  - Remove or ifdef out `windows.h`, `conio.h`, and `Sleep()` (replace with `unistd.h`/`sleep()`), and either remove colors or adapt them.
  - Replace `getch()` with a portable alternative (e.g., getchar()/termios).

---

## Usage Overview
1. Start the program.
2. Signup (first-time) or Login with existing credentials.
3. Use the Main Menu to select:
   - Hospital Management: add hospitals, display all, or filter by city.
   - Patient Management: add patients, display all patients (with hospital names).
   - Sorting Features: sort hospitals by price, beds, name, or rating & reviews.
4. Data is appended to the corresponding text files.

---

## Security & Limitations (Important)
- Credentials are stored in `users.txt` in plain text. This is insecure for production use.
- No input sanitization beyond basic checks; malformed input may cause unexpected behavior.
- No concurrency control — simultaneous writers may corrupt files.
- No validation that hospital IDs are unique or that a patient’s hospital ID exists (except basic display lookup which will show "Unknown" if missing).
- No encryption, no password hashing, and no secure password handling.

---

## Suggested Improvements
- Hash and salt passwords (e.g., use bcrypt/Argon2 externally or a secure library).
- Use a binary file format or a database (SQLite) to store records safely.
- Add validation for unique IDs and referential integrity (ensure patient hospital IDs exist).
- Replace bubble sort with more efficient sorting (qsort).
- Add edit/delete hospital & patient features.
- Add input size checks and stronger input validation.
- Implement cross-platform compatibility (POSIX wrappers).
- Improve the UI (menu navigation, search features, filtering).

---

## Contributing
This project is lightweight and file-based. Contributions are welcome — you can:
- Submit improvements to build scripts or platform compatibility.
- Harden security (password hashing, secure storage).
- Add tests and sample datasets.

If you want me to suggest or create patches (e.g., password hashing, POSIX port), tell me what you'd like next and I can propose changes.

---

## License
This project is released into the public domain using the CC0 1.0 Universal (CC0 1.0) Public Domain Dedication. See the included `LICENSE` file for full text.

---

## Author / Contact
Original code provided by the user. For further edits, testing, or packaging, I can help convert this into a cross-platform CLI, add a Makefile, or prepare a GitHub repository structure.
