# Hospital Management System

A comprehensive C-based Hospital Management System that allows users to manage hospital data, patient records, and user authentication. The system provides features for adding, displaying, filtering, and sorting hospital information along with patient management capabilities.

## Overview

This project is a command-line hospital management application built in C that demonstrates essential data structures, file I/O operations, and user authentication mechanisms. It enables administrators and staff to efficiently manage hospital records and patient admissions.

## Features

### Authentication System
- **User Sign-Up**: Create new user accounts with username and password
- **User Login**: Secure login mechanism with credential verification
- **User Management**: User data persisted in `users.txt` file

### Hospital Management
- **Add Hospital Data**: Create new hospital records with detailed information
- **Display All Hospitals**: View complete list of hospitals in the system
- **Filter by City**: Display hospitals available in a specific city
- **Sort by Bed Price**: Sort hospitals by daily bed cost (descending order)
- **Sort by Available Beds**: Sort hospitals by number of available beds (descending)
- **Sort by Name**: Alphabetical sorting of hospital names
- **Sort by Rating & Reviews**: Sort hospitals by rating and review count (both descending)

### Patient Management
- **Add Patient Records**: Register new patients with hospital assignment
- **Display All Patients**: View complete list of patient records
- **Hospital Association**: Each patient is linked to their admitted hospital

### Hospital Data Fields
- Hospital ID (unique identifier)
- Hospital Name
- City Location
- Available Beds
- Bed Price (per day)
- Rating (0-5 scale)
- Number of Reviews

### Patient Data Fields
- Patient ID (unique identifier)
- Patient Name
- Age
- Disease/Condition
- Hospital ID (admission hospital)

## Data Structures

### Hospital Structure
```c
typedef struct {
    int hospitalID;
    char hospitalName[NAME_SIZE];
    char city[CITY_SIZE];
    int availableBeds;
    float bedPrice;
    float rating;
    int reviews;
} Hospital;
```

### Patient Structure
```c
typedef struct {
    int patientID;
    char patientName[NAME_SIZE];
    int age;
    char disease[DISEASE_SIZE];
    int hospitalID;
} Patient;
```

### User Structure
```c
typedef struct {
    char username[USERNAME_SIZE];
    char password[PASSWORD_SIZE];
} User;
```

## Files Required

The program uses three data files (automatically created if missing):

1. **hospitals.txt** - Stores hospital records
   - Format: `ID|Name|City|Beds|Price|Rating|Reviews`
   - Example: `1|City Hospital|Karachi|50|5000.00|4.5|120`

2. **patients.txt** - Stores patient records
   - Format: `ID|Name|Age|Disease|HospitalID`
   - Example: `1|Ahmed Khan|35|Heart Disease|1`

3. **users.txt** - Stores user credentials
   - Format: `Username|Password`
   - Example: `admin|password123`

## Installation & Compilation

### Prerequisites
- GCC compiler or any C compiler
- Windows, Linux, or macOS operating system

### Compilation Steps

**Windows:**
```bash
gcc -o hospital_system protype3.c
hospital_system.exe
```

**Linux/macOS:**
```bash
gcc -o hospital_system protype3.c
./hospital_system
```

## Usage

### Starting the Program
1. Compile and run the executable
2. You will see the welcome banner
3. Choose to Login, Sign Up, or Exit

### First Time Users
1. Select "Sign Up" from the authentication menu
2. Create a username and password
3. Login with your credentials

### Main Menu Options

After successful login, you can access:
- **Option 1**: Add new hospital information
- **Option 2**: View all hospital records
- **Option 3**: Search hospitals by city
- **Option 4**: Sort hospitals by bed price
- **Option 5**: Sort hospitals by available beds
- **Option 6**: Sort hospitals alphabetically
- **Option 7**: Sort hospitals by rating and reviews
- **Option 8**: Add new patient record
- **Option 9**: View all patient records
- **Option 10**: Exit program

## Program Flow

```
Start
  ↓
Authentication (Login/Sign Up)
  ↓
Main Menu
  ├── Hospital Management
  │   ├── Add Hospital
  │   ├── Display Hospitals
  │   ├── Filter by City
  │   └── Sort Operations
  ├── Patient Management
  │   ├── Add Patient
  │   └── Display Patients
  └── Exit
```

## Key Functions

### Authentication Functions
- `signup()` - Register new user account
- `login()` - Authenticate existing user
- `clearInputBuffer()` - Clear input buffer after scanf

### Hospital Functions
- `addHospital()` - Add new hospital record
- `displayHospitals()` - Show all hospitals
- `displayHospitalsByCity()` - Filter hospitals by location
- `sortHospitalsByBedPrice()` - Sort by price (descending)
- `sortHospitalsByAvailableBeds()` - Sort by bed availability
- `sortHospitalsByName()` - Alphabetical sorting
- `sortHospitalsByRatingAndReviews()` - Sort by rating/reviews
- `loadHospitals()` - Load hospital data from file

### Patient Functions
- `addPatient()` - Register new patient
- `displayPatients()` - Show all patient records
- `loadPatients()` - Load patient data from file
- `getHospitalNameByID()` - Retrieve hospital name for display

### Utility Functions
- `clearScreen()` - Clear console screen (cross-platform)
- `printWelcomeBanner()` - Display welcome message
- `countRecords()` - Count total records in file

## Error Handling

The program includes error handling for:
- Invalid user input (non-numeric entries)
- File access errors
- Missing or corrupted data files
- Invalid credentials during login
- Duplicate usernames during signup

## Technical Details

### Constants
- `NAME_SIZE`: 50 characters (names, hospital names)
- `CITY_SIZE`: 30 characters (city names)
- `DISEASE_SIZE`: 50 characters (disease descriptions)
- `LINE_SIZE`: 256 characters (file line buffer)
- `USERNAME_SIZE`: 30 characters
- `PASSWORD_SIZE`: 30 characters

### Data Storage Format
All data is stored in pipe-delimited (|) text files for easy parsing and portability.

### Sorting Algorithm
The program uses Bubble Sort algorithm for sorting operations with O(n²) time complexity. The implementation compares adjacent elements and swaps them based on the sorting criteria.

### Memory Management
- Dynamic memory allocation using `malloc()` for arrays
- Proper `free()` calls after memory usage
- Stack-based allocation for local variables

## Limitations & Future Enhancements

### Current Limitations
- No data encryption for passwords
- Limited input validation
- Basic bubble sort (could use quicksort for better performance)
- No update/edit functionality for existing records
- No delete functionality for records
- Single-user active session per program run

### Suggested Enhancements
1. Add update and delete functionality for hospitals and patients
2. Implement password encryption
3. Add more advanced search filters (by rating range, price range, etc.)
4. Implement database connection (SQLite, MySQL)
5. Add appointment/booking system
6. Create doctor and staff management modules
7. Implement better input validation
8. Add data backup and recovery features
9. Multi-user concurrent access support
10. Generate reports (occupancy rates, revenue, etc.)

## Platform Compatibility

- **Windows**: Uses `system("cls")` for screen clearing
- **Linux/macOS**: Uses `system("clear")` for screen clearing
- The program automatically detects the platform using `#ifdef _WIN32`

## License

This project is provided as-is for educational purposes.

## Author

Created for educational purposes as part of a C programming course or assignment.

## Support

For issues or questions:
1. Check that all required files (hospitals.txt, patients.txt, users.txt) are in the same directory
2. Ensure proper compilation with a C compiler
3. Verify input format when adding records
4. Check file permissions for read/write access

## Version History

- **v1.0** (Current): Initial release with core features
  - User authentication (login/signup)
  - Hospital management (add, display, filter, sort)
  - Patient management (add, display)
  - Cross-platform compatibility

---

**Note**: This is a prototype application (protype3.c) suitable for learning C programming concepts including file I/O, data structures, dynamic memory allocation, and basic algorithms.
```

I've created a comprehensive README that covers:

- **Project overview** and purpose
- **All features** with detailed descriptions
- **Data structures** with code examples
- **Installation and compilation** instructions for both Windows and Linux/macOS
- **Usage instructions** with menu options
- **Program flow diagram**
- **All key functions** with brief descriptions
- **Error handling** information
- **Technical details** about constants and algorithms
- **Limitations and enhancement suggestions**
- **Platform compatibility** notes
- **Version history**

This README provides everything a user or developer needs to understand, compile, run, and modify the Hospital Management System. You can save this as `README.md` in your project directory.I've created a comprehensive README that covers:

- **Project overview** and purpose
- **All features** with detailed descriptions
- **Data structures** with code examples
- **Installation and compilation** instructions for both Windows and Linux/macOS
- **Usage instructions** with menu options
- **Program flow diagram**
- **All key functions** with brief descriptions
- **Error handling** information
- **Technical details** about constants and algorithms
- **Limitations and enhancement suggestions**
- **Platform compatibility** notes
- **Version history**

This README provides everything a user or developer needs to understand, compile, run, and modify the Hospital Management System. 
