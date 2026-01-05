# Hospital Management System (C)

A simple console-based Hospital Management System written in C.  
This program lets users sign up / log in, add and view hospital and patient records, search hospitals by city, and sort hospitals by various criteria (price, available beds, name, rating & reviews). Data is stored in plain text files.

---

## Table of Contents

- [Project Overview](#project-overview)
- [Features](#features)
- [Files & Data Format](#files--data-format)
- [Build & Run](#build--run)
  - [Windows (recommended)](#windows-recommended)
  - [POSIX (Linux/macOS) — notes](#posix-linuxmacos---notes)
- [Usage Examples](#usage-examples)
- [Functions & Flow](#functions--flow)
- [Known Issues & Limitations](#known-issues--limitations)
- [Security & Improvements](#security--improvements)
- [Contributing](#contributing)
- [License](#license)
- [Contact](#contact)

---

## Project Overview

This project provides a minimal, file-based hospital management application. It demonstrates basic file I/O, simple authentication, structures, and command-line UI with color escape sequences.

It is intended as a learning/demo application and not for production use.

---

## Features

- Text-based sign-up and login system (username|password stored in `users.txt`)
- Add / display hospital records
- Add / display patient records (patients reference hospitals by ID)
- Display hospitals filtered by city (alphabetically sorted)
- Sorting features:
  - Sort by bed price (high → low)
  - Sort by available beds (high → low)
  - Sort by hospital name (A → Z)
  - Sort by rating (then reviews)
- ANSI color output for improved readability (may require terminal support)

---

## Files & Data Format

- Source file(s)
  - main C file (the code you provided)
- Data files (plain text, pipe-separated fields)
  - `hospitals.txt` — hospital records, one per line:
    Format:
    ```
    hospital_id|hospital_name|city|available_beds|bed_price|rating|reviews
    ```
    Example:
    ```
    101|Saint Mary Hospital|Springfield|120|250.00|4.5|150
    ```
  - `patients.txt` — patient records, one per line:
    Format:
    ```
    patient_id|patient_name|age|disease|hospital_id
    ```
    Example:
    ```
    501|John Doe|45|Pneumonia|101
    ```
  - `users.txt` — user credentials, one per line:
    Format:
    ```
    username|password
    ```
    Example:
    ```
    alice|password123
    ```

---

## Build & Run

The provided code includes Windows-specific headers (`<windows.h>` and `conio.h`) and uses `Sleep()` and `getch()`. Recommended platform: Windows (MinGW or Visual Studio). If you want to run on POSIX systems, see notes below.

No external libraries are required.

### Windows (recommended)

Using MinGW (gcc):

1. Open a Command Prompt or PowerShell with MinGW in PATH.
2. Compile:
   ```sh
   gcc -o hospital_management main.c
   ```
   - If your environment requires linking extra libs, default MinGW should work as-is.
3. Run:
   ```sh
   hospital_management.exe
   ```
Notes:
- If `getch()` isn't available, MinGW generally provides `getch()` in `conio.h`. If using MSVC, replace `getch()` with `_getch()` as appropriate.
- The ANSI color escape codes used may not render colors by default in legacy Windows cmd. Use Windows Terminal or enable ANSI processing:
  - Alternatively, modify the code to call Windows console APIs (SetConsoleMode with ENABLE_VIRTUAL_TERMINAL_PROCESSING).

### Visual Studio (cl)

1. Open "Developer Command Prompt for VS".
2. Compile:
   ```sh
   cl /Fe:hospital_management.exe main.c
   ```
3. Run:
   ```sh
   hospital_management.exe
   ```

### POSIX (Linux/macOS) — notes

The code uses Windows-only APIs (Sleep, windows.h, conio.h). To port:
- Replace `#include <windows.h>` and `Sleep(ms)` with `<unistd.h>` and `sleep(seconds)` or `usleep(microseconds)`.
- Replace `getch()` with `getchar()` or use termios to implement a non-buffered single-key input.
- Remove or guard Windows-specific headers with `#ifdef _WIN32` blocks and add POSIX equivalents.
- ANSI color escapes will work in POSIX terminals out of the box.

Example adjustments:
- Sleep(1500) → usleep(1500 * 1000) (remember to `#include <unistd.h>`).
- getch() → getchar() (but getchar waits for Enter).

---

## Usage Examples

- Start program → sign up or login.
- After login you can:
  - Add a hospital (enter ID, name, city, beds, price, rating, reviews).
  - Display all hospitals.
  - Filter hospitals by city (enter exact city name).
  - Add a patient (patient ID, name, age, disease, hospital ID).
  - Display patients (hospital name is looked up from hospital file).
  - Use sorting submenu to see different sorted views.

Sample workflow:
1. Sign up: `alice` / `alicepass`
2. Login as `alice`
3. Add hospital: `101 | St. John's | Gotham | 50 | 180.00 | 4.2 | 34`
4. Add patient: `201 | Bruce Wayne | 35 | Broken Arm | 101`
5. Display patients — shows hospital name for `101`.

---

## Functions & Flow (brief)

- Authentication:
  - `signup()` — append new user to `users.txt`.
  - `login()` — validate credentials against `users.txt`.
- Hospital management:
  - `add_hospital()` — append record to `hospitals.txt`.
  - `display_hospitals()` — show formatted list.
  - `display_hospitals_by_city()` — filter, sort alphabetically, and display.
  - `load_hospitals()` / `count_records()` — helpers for loading and counting.
- Patient management:
  - `add_patient()` — append record to `patients.txt`.
  - `display_patients()` — shows list with hospital name resolved by `get_hospital_name_by_id()`.
- Sorting helpers:
  - `sort_hospitals_by_bed_price()`, `sort_hospitals_by_available_beds()`, `sort_hospitals_by_name()`, `sort_hospitals_by_rating_and_reviews()` — in-memory bubble sort then display.

---

## Known Issues & Limitations

- Passwords are stored in plain text in `users.txt`. Never use this for real systems.
- No concurrency control or file locking — simultaneous writes may corrupt data.
- Minimal input validation (e.g., duplicate hospital/patient IDs not prevented).
- All I/O is synchronous and blocking — not suitable for large datasets.
- Uses Bubble Sort (O(n^2)) — acceptable for small data sets but not scalable.
- The code mixes scanf and fgets; code currently uses `clear_input_buffer()` to reduce input issues but edge cases remain.
- Color escape codes may not display in all terminals (Windows cmd may need special handling).

---

## Security & Recommended Improvements

Immediate improvements before any real use:
- Hash passwords (bcrypt / Argon2) rather than storing raw passwords.
- Use a proper database (SQLite) instead of plain files to ensure data integrity and concurrent access.
- Add input validation and unique ID checks.
- Implement file locking (flock/LockFile) if staying with file-based storage.
- Replace bubble sort with qsort() or more efficient algorithms for larger lists.
- Add logging and error handling enhancements.

---

## Contributing

- Fork the repository, make changes on a feature branch, and submit a pull request.
- Suggested first issues:
  - Port to POSIX-compatible build.
  - Replace plaintext passwords with hashed storage.
  - Add a CLI argument to set data file locations.
  - Add unit tests (for parsing/saving functions) and example data.

Please follow a consistent style and add comments for any non-trivial changes.

---

## License

Choose a license for your project. Example: MIT License — include a `LICENSE` file if you want to release it publicly.

---

## Contact

If you'd like, I can:
- Create a polished repository structure for you (with a Makefile, .gitignore, and sample data),
- Produce a Windows- and POSIX-compatible version,
- Or add improvements like password hashing and SQLite migration.

Tell me which you'd prefer and I will prepare the next set of files or instructions.
