#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

// ===== COLOR CODES =====
// These ANSI escape codes are used to display colored text in the terminal
#define RESET "\033[0m"           // Resets text color to default
#define RED "\033[31m"            // Red text color
#define GREEN "\033[32m"          // Green text color
#define YELLOW "\033[33m"         // Yellow text color
#define BLUE "\033[34m"           // Blue text color
#define MAGENTA "\033[35m"        // Magenta/Purple text color
#define CYAN "\033[36m"           // Cyan/Light blue text color
#define WHITE "\033[37m"          // White text color
#define BOLD "\033[1m"            // Makes text bold/bright
#define BG_GREEN "\033[42m"       // Green background color
#define BG_BLUE "\033[44m"        // Blue background color

// ===== FILE DEFINITIONS =====
// These constants store the names of the data files where information is saved
#define HOSPITAL_FILE "hospitals.txt"  // File to store hospital records
#define PATIENT_FILE "patients.txt"    // File to store patient records
#define USER_FILE "users.txt"          // File to store user login credentials

// ===== SIZE CONSTANTS =====
// These constants define the maximum length of various text fields
#define NAME_SIZE 50               // Maximum characters for hospital/patient names
#define CITY_SIZE 30               // Maximum characters for city names
#define DISEASE_SIZE 50            // Maximum characters for disease descriptions
#define LINE_SIZE 256              // Maximum characters per line when reading files
#define USERNAME_SIZE 30           // Maximum characters for usernames
#define PASSWORD_SIZE 30           // Maximum characters for passwords

// ===== DATA STRUCTURES =====
// A struct (structure) is a collection of variables of different types grouped together

// Hospital structure: stores information about a single hospital
typedef struct
{
    int hospital_id;          // Unique identifier for the hospital
    char hospital_name[NAME_SIZE];      // Name of the hospital
    char city[CITY_SIZE];              // City where hospital is located
    int available_beds;       // Number of beds available for patients
    float bed_price;          // Cost per bed per day (uses decimal numbers)
    float rating;            // Hospital rating from 0-5 stars
    int reviews;             // Total number of reviews received
} Hospital;

// Patient structure: stores information about a single patient
typedef struct
{
    int patient_id;           // Unique identifier for the patient
    char patient_name[NAME_SIZE];       // Name of the patient
    int age;                 // Age of the patient
    char disease[DISEASE_SIZE];        // Disease or medical condition
    int hospital_id;          // ID of the hospital where patient is admitted
} Patient;

// User structure: stores login credentials for authentication
typedef struct
{
    char username[USERNAME_SIZE];      // Username for login
    char password[PASSWORD_SIZE];      // Password for login
} User;

// ===== FUNCTION PROTOTYPES =====
// These are declarations that tell the compiler about functions we'll define later
// Format: returnType functionName(parameters);

void clear_input_buffer();                    // Clears leftover characters from input
void clear_screen();                         // Clears the terminal/console screen
void print_welcome_banner();                  // Displays welcome message
int count_records(const char *filename);     // Counts total records in a file
void load_hospitals(Hospital *hospitals, int *n);  // Reads all hospitals from file into memory
void load_patients(Patient *patients, int *n);     // Reads all patients from file into memory
char *get_hospital_name_by_id(int hospital_id); // Finds hospital name using its ID
void signup();                              // Handles new user registration
int login();                                // Handles user login verification
void add_hospital();                         // Adds new hospital to file
void display_hospitals();                    // Shows all hospitals on screen
void display_hospitals_by_city();              // Filters and shows hospitals by city
void sort_hospitals_by_bed_price();             // Sorts hospitals by price
void sort_hospitals_by_available_beds();        // Sorts hospitals by available beds
void sort_hospitals_by_name();                 // Sorts hospitals alphabetically
void sort_hospitals_by_rating_and_reviews();     // Sorts hospitals by rating
void add_patient();                          // Adds new patient to file
void display_patients();                     // Shows all patients on screen
void press_any_key_to_continue(void);

// ===== MAIN PROGRAM =====
// The main() function is where the program starts executing
int main()
{
    int choice;  // Variable to store user's menu choice
    // Clear the screen and show welcome banner at program start
    clear_screen();
    print_welcome_banner();

    int auth = 0;  // Variable to track authentication choice (1=Signup, 2=Login, 3=Exit)
    
    // This loop continues until user successfully logs in or chooses to exit
    while (1) {
        // Display login/signup menu
        printf(CYAN "\nThe management system requires login so if you donot have any account please signup.\n" RESET);
        printf(YELLOW "\n1. Signup\n2. Login\n3. Exit\n" RESET);
        printf(BLUE "_________________________________________________________________________________________________________________________\n" RESET);
        printf(GREEN "Enter your choice: " RESET);
        
        // Read user's choice and check if input is valid (expecting an integer)
        while (scanf("%d", &auth) != 1) {
            printf(RED "Invalid input!\n" RESET);
            clear_input_buffer();  // Clear invalid input from buffer
            printf("Enter the valid option(1, 2, or 3): ");
        }
        clear_input_buffer();

        // Execute action based on user's choice
        if (auth == 1) {
            signup();  // Call signup function
        } else if (auth == 2) {
            // Call login function and check if login was successful
            if (login()) {
                 printf(BLUE "_________________________________________________________________________________________________________________________\n" RESET);
                printf(GREEN BOLD "\nYou can now proceed to the main program.\n" RESET);
                break;  // Exit authentication loop and go to main menu
            }
        } else if (auth == 3) {
            printf(YELLOW "Exiting...\n" RESET);
            printf(GREEN "Thank you for using the Hospital Management System!\n" RESET);
            exit(0);  // Terminate the program
            break;  // Exit program
        } else {
             printf(BLUE "_________________________________________________________________________________________________________________________\n" RESET);
            printf(RED "\nInvalid choice! Enter 1, 2, or 3.\n" RESET);
            printf(BLUE "_________________________________________________________________________________________________________________________\n" RESET);
            Sleep(1500);
            clear_screen();
            print_welcome_banner();
        }
    }

    press_any_key_to_continue();

    // Main menu loop - continues until user chooses to exit
    while (1)
    {
        // clear_input_buffer();
        clear_screen();
        print_welcome_banner();
        printf(MAGENTA BOLD "\n--- Main Menu ---\n" RESET);
        printf(BLUE "_________________________________________________________________________________________________________________________\n" RESET);
        printf(YELLOW "1. Hospital Management\n");
        printf("2. Patient Management\n");
        printf("3. Sorting Features\n");
        printf("4. Exit\n" RESET);
        printf(BLUE "_________________________________________________________________________________________________________________________\n" RESET);
        printf(GREEN "Enter your choice: " RESET);
        
        // Read main menu choice with error checking
        while (scanf("%d", &choice) != 1)
        {
            printf(RED "Invalid input!\n" RESET);
            clear_input_buffer();  // Clear invalid input
            printf("Enter the valid option(1, 2, 3, or 4): ");
        }
        clear_input_buffer();  // Clear newline from input buffer

        // Execute different sections based on choice using switch statement
        switch (choice)
        {
        case 1:  // Hospital Management submenu
        {
            int hospital_choice;  // Variable for hospital submenu choice
            clear_screen();
            print_welcome_banner();
            printf(MAGENTA BOLD "\n--- Hospital Management ---\n" RESET);
            printf(BLUE "_________________________________________________________________________________________________________________________\n" RESET);
            printf(YELLOW "1. Add Hospital Data\n");
            printf("2. Display Hospital Data\n");
            printf("3. Display Hospitals by City\n");
            printf("4. Return to the main menu\n" RESET);
             printf(BLUE "_________________________________________________________________________________________________________________________\n" RESET);
            printf(GREEN "Enter your choice: " RESET);
            
            // Read hospital submenu choice with error checking
            while (scanf("%d", &hospital_choice) != 1)
            {
                printf(RED "Invalid input!\n" RESET);
                clear_input_buffer();
                printf(GREEN "Enter the valid option(1, 2, 3 or 4): " RESET);
            }
            clear_input_buffer();
            
            clear_screen();
            print_welcome_banner();
            
            // Execute hospital operation based on submenu choice
            switch (hospital_choice)
            {
            case 1:
                add_hospital();  // Add new hospital
                break;
            case 2:
                display_hospitals();  // Show all hospitals
                break;
            case 3:
                display_hospitals_by_city();  // Show hospitals in specific city
                break;
            case 4:
                continue;
                break;
            default:
                printf(RED "Invalid choice! Try again.\n" RESET);
            }
            break;
        }
        case 2:  // Patient Management submenu
        {
            int patient_choice;  // Variable for patient submenu choice
            clear_screen();
            print_welcome_banner();
            printf(MAGENTA BOLD "\n--- Patient Management ---\n" RESET);
            printf(BLUE "_________________________________________________________________________________________________________________________\n" RESET);
            printf(YELLOW "1. Add Patient Data\n");
            printf("2. Display Patient Data\n");
            printf("3. Return to the main menu\n" RESET);
            printf(BLUE "_________________________________________________________________________________________________________________________\n" RESET);
            printf(GREEN "Enter your choice: " RESET);
            
            // Read patient submenu choice with error checking
            while (scanf("%d", &patient_choice) != 1)
            {
                printf(RED "Invalid input!\n" RESET);
                clear_input_buffer();
                printf("Enter the valid option(1, 2, or 3): ");
            }
            clear_input_buffer();
            
            clear_screen();
            print_welcome_banner();
            
            // Execute patient operation based on submenu choice
            switch (patient_choice)
            {
            case 1:
                add_patient();  // Add new patient
                break;
            case 2:
                display_patients();  // Show all patients
                break;
            case 3:
                continue;
                break;
            default:
                printf(RED "Invalid choice! Try again.\n" RESET);
            }
            break;
        }
        case 3:  // Sorting Features submenu
        {
            int sort_choice;  // Variable for sort submenu choice
            clear_screen();
            print_welcome_banner();
            printf(MAGENTA BOLD "\n--- Sorting Features ---\n" RESET);
            printf(BLUE "_________________________________________________________________________________________________________________________\n" RESET);
            printf(YELLOW "1. Sort by Bed Price\n");
            printf("2. Sort by Available Beds\n");
            printf("3. Sort by Hospital Name\n");
            printf("4. Sort by Rating and Reviews\n");
            printf("5. Return to the main menu\n" RESET);
            printf(BLUE "_________________________________________________________________________________________________________________________\n" RESET);
            printf(GREEN "Enter your choice: " RESET);
            
            // Read sort submenu choice with error checking
            while (scanf("%d", &sort_choice) != 1)
            {
                printf(RED "Invalid input!\n" RESET);
                clear_input_buffer();
                printf("Enter the valid option(1, 2, 3, or 4): ");
            }
            clear_input_buffer();
            
            clear_screen();
            print_welcome_banner();
            
            // Execute sorting operation based on submenu choice
            switch (sort_choice)
            {
            case 1:
                sort_hospitals_by_bed_price();  // Sort by price (highest to lowest)
                break;
            case 2:
                sort_hospitals_by_available_beds();  // Sort by beds (most to least)
                break;
            case 3:
                sort_hospitals_by_name();  // Sort alphabetically by name
                break;
            case 4:
                sort_hospitals_by_rating_and_reviews();  // Sort by rating and reviews
                break;
            case 5:
                continue;
                break;
            default:
                printf(RED "Invalid choice! Try again.\n" RESET);
            }
            break;
        }
        case 4:  // Exit option
            printf(GREEN "Thank you for using the Hospital Management System!\n" RESET);
            printf(BLUE "_________________________________________________________________________________________________________________________\n" RESET);
            printf(YELLOW "Exiting...\n" RESET);
            printf(BLUE "_________________________________________________________________________________________________________________________\n" RESET);
            exit(0);  // Terminate the program
        default:
            printf(RED "Invalid choice! Try again.\n" RESET);
        }
    
        // printf(GREEN "\nPress Enter to continue..." RESET);
        // getchar();  // Wait for user to press Enter
        press_any_key_to_continue();   
    }

    return 0;  // Program ends successfully
}

void press_any_key_to_continue(void)
{
    printf(GREEN "\nPress any key to continue..." RESET);
    getch();   // consumes exactly one key
}

// ===== AUTHENTICATION FUNCTIONS =====
// These functions handle user registration and login

// signup() - Allows new users to create an account
void signup()
{
    User u;  // Create a User variable to store signup information
    
    // Open the users file in "append" mode (a+) to add new users without deleting existing ones a+ means to open the file in both mode i.e read and write
    FILE *fp = fopen(USER_FILE, "a+");
    if (!fp)  // Check if file opened successfully
    {
        printf(RED "Error opening users file\n" RESET);
        return;  // Exit function if file can't be opened
    }

    // Ask user to enter a username
    printf(GREEN "Enter username: " RESET);
    fgets(u.username, USERNAME_SIZE, stdin);  // Read username from user input
    u.username[strcspn(u.username, "\n")] = 0;  // Remove newline character from end

    // Check if username already exists in file
    char line[LINE_SIZE];  // Buffer to store each line from file
    while (fgets(line, LINE_SIZE, fp))  // Loop through each line in file
    {
        char existing_user[USERNAME_SIZE];  // Buffer for existing username
        // %*s means Assignment suppression it means read the input but not store it anywhere
        sscanf(line, "%[^|]|%*s", existing_user);  // Extract username from line (before |)
        if (strcmp(existing_user, u.username) == 0)  // Compare with entered username
        {
            printf(RED "Username already exists!\n" RESET);
            printf(BLUE "_________________________________________________________________________________________________________________________\n" RESET);
            fclose(fp);  // Close file
            return;  // Exit function
        }
    }

    // Ask user to enter a password
    printf(GREEN "Enter password: " RESET);
    fgets(u.password, PASSWORD_SIZE, stdin);  // Read password from user input
    u.password[strcspn(u.password, "\n")] = 0;  // Remove newline character from end

    // Write the new username and password to file in format: username|password
    fprintf(fp, "%s|%s\n", u.username, u.password);
    fclose(fp);  // Close the file
    printf(GREEN BOLD "Sign-up successful! You can now login.\n" RESET);
    printf(BLUE "_________________________________________________________________________________________________________________________\n" RESET);
}

// login() - Allows existing users to verify their credentials
// Returns 1 if login successful, 0 if failed
int login()
{
    char username[USERNAME_SIZE], password[PASSWORD_SIZE];  // Variables to store entered credentials
    
    // Open the users file in read mode to check credentials
    FILE *fp = fopen(USER_FILE, "r");
    if (!fp)  // Check if file opened successfully
    {
        printf(RED "Error opening users file\n" RESET);
        printf(CYAN "\nNo users found! Please sign up first.\n" RESET);
        return 0;  // Return 0 (login failed)
    }

    // Ask user to enter username
    printf(GREEN "Enter username: " RESET);
    fgets(username, USERNAME_SIZE, stdin);  // Read username
    username[strcspn(username, "\n")] = 0;  // Remove newline character

    // Ask user to enter password
    printf(GREEN "Enter password: " RESET);
    fgets(password, PASSWORD_SIZE, stdin);  // Read password
    password[strcspn(password, "\n")] = 0;  // Remove newline character

    // Loop through each line in file to find matching credentials
    char line[LINE_SIZE];  // Buffer for each line from file
    while (fgets(line, LINE_SIZE, fp))  // Read line by line
    {
        char file_user[USERNAME_SIZE], file_pass[PASSWORD_SIZE];  // Variables to store file credentials
        // %[^|]| is called negated scanset
        sscanf(line, "%[^|]|%s", file_user, file_pass);  // Extract username and password from line
        
        // Check if entered credentials match file credentials
        if (strcmp(file_user, username) == 0 && strcmp(file_pass, password) == 0)
        {
            fclose(fp);  // Close file
            printf(GREEN BOLD "Login successful!\n" RESET);
            return 1;  // Return 1 (login successful)
        }
    }

    // If we reach here, no matching credentials were found
    fclose(fp);  // Close file
    printf(RED "Invalid username or password!\n" RESET);
    printf(BLUE "_________________________________________________________________________________________________________________________\n" RESET);
    return 0;  // Return 0 (login failed)
}

// ===== UTILITY FUNCTIONS =====
// These are helper functions used throughout the program

// clear_input_buffer() - Removes leftover characters from input buffer
// This is important when mixing scanf() and fgets() functions
void clear_input_buffer() 
{
    int c;  // Variable to store each character
    // Loop until newline or end of file is found
    while ((c = getchar()) != '\n' && c != EOF)
        ;  // Do nothing, just consume characters
}

// clear_screen() - Clears the terminal screen
// Uses different commands for Windows (cls) and Linux/Mac (clear)
void clear_screen()
{
#ifdef _WIN32  // Check if running on Windows
    system("cls");  // Windows command to clear screen
#else
    system("clear");  // Linux/Mac command to clear screen
#endif
}

// print_welcome_banner() - Displays a decorative welcome message at top of screen
void print_welcome_banner()
{
    printf(BG_BLUE BOLD "=========================================================================================================================\n");
    printf("****************************************   WELCOME TO HOSPITAL MANAGEMENT SYSTEM   **************************************\n");
    printf("=========================================================================================================================\n" RESET);
}

// ===== HOSPITAL MANAGEMENT FUNCTIONS =====
// These functions handle all hospital-related operations

// add_hospital() - Allows user to input and save a new hospital to file
void add_hospital()
{
    Hospital h;  // Create a Hospital variable to store new hospital data
    
    // Open hospital file in append mode (a) to add new data
    FILE *fp = fopen(HOSPITAL_FILE, "a");
    if (!fp)  // Check if file opened successfully
    {
        printf(RED "Error opening hospital file\n" RESET);
        return;  // Exit function if file can't be opened
    }

    printf("\n\nPlease enter the following details to add a new hospital:\n");
    printf(BLUE "_________________________________________________________________________________________________________________________\n" RESET);

    // Get Hospital ID from user
    printf(GREEN "Enter Hospital ID: " RESET);
    while (scanf("%d", &h.hospital_id) != 1)  // Check if valid integer was entered
    {
        printf(RED "Invalid input!\n" RESET);
        clear_input_buffer();  // Clear invalid input
        printf(GREEN "Enter Hospital ID: " RESET);
    }
    clear_input_buffer();  // Clear newline from buffer

    // Get Hospital Name from user
    printf(GREEN "Enter Hospital Name: " RESET);
    fgets(h.hospital_name, NAME_SIZE, stdin);  // Read hospital name
    h.hospital_name[strcspn(h.hospital_name, "\n")] = 0;  // Remove newline

    // Get City from user
    printf(GREEN "Enter City: " RESET);
    fgets(h.city, CITY_SIZE, stdin);  // Read city name
    h.city[strcspn(h.city, "\n")] = 0;  // Remove newline

    // Get Number of Available Beds from user
    printf(GREEN "Enter Number of Available Beds: " RESET);
    while (scanf("%d", &h.available_beds) != 1)  // Check if valid integer
    {
        printf(RED "Invalid input!\n" RESET);
        clear_input_buffer();
        printf(GREEN "Enter Number of Available Beds: " RESET);
    }
    clear_input_buffer();

    // Get Bed Price from user
    printf(GREEN "Enter Bed Price per Day: " RESET);
    while (scanf("%f", &h.bed_price) != 1)  // Check if valid decimal number
    {
        printf(RED "Invalid input!\n" RESET);
        clear_input_buffer();
        printf("Enter Bed Price per Day: ");
    }
    clear_input_buffer();

    // Get Hospital Rating from user
    printf(GREEN "Enter Hospital Rating (0-5): " RESET);
    while (scanf("%f", &h.rating) != 1)  // Check if valid decimal number
    {
        printf(RED "Invalid input!\n" RESET);
        clear_input_buffer();
        printf(GREEN "Enter Hospital Rating (0-5): " RESET);
    }
    clear_input_buffer();

    // Get Number of Reviews from user
    printf(GREEN "Enter Number of Reviews: " RESET);
    while (scanf("%d", &h.reviews) != 1)  // Check if valid integer
    {
        printf(RED "Invalid input!\n" RESET);
        clear_input_buffer();
        printf(GREEN "Enter Number of Reviews: " RESET);
    }
    clear_input_buffer();

    // Write hospital data to file in pipe-separated format: id|name|city|beds|price|rating|reviews
    fprintf(fp, "%d|%s|%s|%d|%.2f|%.1f|%d\n",
            h.hospital_id, h.hospital_name, h.city, h.available_beds, h.bed_price, h.rating, h.reviews);
    fclose(fp);  // Close file
    printf(BLUE "_________________________________________________________________________________________________________________________\n" RESET);
    printf(GREEN BOLD "\nHospital added successfully!\n" RESET);
}

// count_records() - Counts the number of lines (records) in a file
// Takes filename as parameter and returns the count
int count_records(const char *filename)
{
    FILE *fp = fopen(filename, "r");  // Open file in read mode
    if (!fp){  // If file doesn't exist or can't be opened
        return 0;  // Return 0 records
    }
    
    int count = 0;  // Counter for records
    char line[LINE_SIZE];  // Buffer to read each line
    
    // Loop through file and count each line
    while (fgets(line, LINE_SIZE, fp))
        count++;  // Increment counter for each line
    
    fclose(fp);  // Close file
    return count;  // Return total count
}

// load_hospitals() - Reads all hospital records from file into an array in memory
// Parameters: pointer to Hospital array, pointer to variable storing count
void load_hospitals(Hospital *hospitals, int *n)
{
    FILE *fp = fopen(HOSPITAL_FILE, "r");  // Open hospital file in read mode
    if (!fp)  // If file doesn't exist
    {
        *n = 0;  // Set count to 0
        return;  // Exit function
    }
    
    int i = 0;  // Index variable for array position
    char line[LINE_SIZE];  // Buffer to read each line
    
    // Loop through each line in file
    while (fgets(line, LINE_SIZE, fp))
    {
        // Extract data from pipe-separated line and store in array
        sscanf(line, "%d|%[^|]|%[^|]|%d|%f|%f|%d",
               &hospitals[i].hospital_id, hospitals[i].hospital_name, hospitals[i].city,
               &hospitals[i].available_beds, &hospitals[i].bed_price,
               &hospitals[i].rating, &hospitals[i].reviews);
        i++;  // Move to next array position
    }
    
    *n = i;  // Set count to number of records read
    fclose(fp);  // Close file
}

// get_hospital_name_by_id() - Searches for a hospital by ID and returns its name
// Parameter: hospital_id (integer ID to search for)
// Returns: pointer to string containing hospital name or "Unknown"
char *get_hospital_name_by_id(int hospital_id)
{
    static char name[NAME_SIZE];  // Static variable to store result (persists after function returns)
    
    FILE *fp = fopen(HOSPITAL_FILE, "r");  // Open hospital file in read mode
    if (!fp)  // If file can't be opened
    {
        strcpy(name, "Unknown");  // Copy "Unknown" to name
        return name;  // Return the name
    }
    
    char line[LINE_SIZE];  // Buffer to read each line
    
    // Loop through each line searching for matching ID
    while (fgets(line, LINE_SIZE, fp))
    {
        Hospital h;  // Temporary Hospital variable
        
        // Extract data from pipe-separated line
        sscanf(line, "%d|%[^|]|%[^|]|%d|%f|%f|%d",
               &h.hospital_id, h.hospital_name, h.city,
               &h.available_beds, &h.bed_price, &h.rating, &h.reviews);
        
        // Check if this is the hospital we're looking for
        if (h.hospital_id == hospital_id)
        {
            strcpy(name, h.hospital_name);  // Copy hospital name
            fclose(fp);  // Close file
            return name;  // Return the name
        }
    }
    
    // If hospital not found
    fclose(fp);  // Close file
    strcpy(name, "Unknown");  // Set name to "Unknown"
    return name;  // Return "Unknown"
}

// display_hospitals() - Reads and displays all hospitals from file
void display_hospitals()
{
    FILE *fp = fopen(HOSPITAL_FILE, "r");  // Open hospital file in read mode
    if (!fp)  // If file doesn't exist
    {
        printf(RED "Error opening hospital file, file not found.\n" RESET);
        return;  // Exit function
    }

    char line[LINE_SIZE];  // Buffer to read each line
    printf(MAGENTA BOLD "\n--- Hospital Records ---\n" RESET);  // Display header
    printf(BLUE "_________________________________________________________________________________________________________________________\n" RESET);
    printf("\n\n-------------------------------------------------------------------------------------------------------------------\n");
    // Loop through each line in file
    printf("%5s | %-50s | %-12s | %5s | %-10s | %7s | %7s\n", "ID", "Hospital Name", "City", "Beds", "Price", "Ratings", "Reviews");
    printf("-------------------------------------------------------------------------------------------------------------------\n");
    while (fgets(line, LINE_SIZE, fp))
    {
        Hospital h;  // Temporary Hospital variable
        
        // Extract data from pipe-separated line
        sscanf(line, "%d|%[^|]|%[^|]|%d|%f|%f|%d", &h.hospital_id, h.hospital_name, h.city,
               &h.available_beds, &h.bed_price, &h.rating, &h.reviews);
        
        // Display hospital information in formatted way
        printf(CYAN "%5d | %-50s | %-12s | %5d | %10.2f | %7.1f | %7d\n" RESET,
               h.hospital_id, h.hospital_name, h.city, h.available_beds, h.bed_price, h.rating, h.reviews);
    }
    fclose(fp);  // Close file
}

// load_patients() - Reads all patient records from file into an array in memory
void load_patients(Patient *patients, int *n)
{
    FILE *fp = fopen(PATIENT_FILE, "r");  // Open patient file in read mode
    if (!fp)  // If file doesn't exist
    {
        *n = 0;  // Set count to 0
        return;  // Exit function
    }
    
    int i = 0;  // Index variable for array position
    char line[LINE_SIZE];  // Buffer to read each line
    
    // Loop through each line in file
    while (fgets(line, LINE_SIZE, fp))
    {
        // Extract data from pipe-separated line and store in array
        sscanf(line, "%d|%[^|]|%d|%[^|]|%d",
               &patients[i].patient_id, patients[i].patient_name, &patients[i].age,
               patients[i].disease, &patients[i].hospital_id);
        i++;  // Move to next array position
    }
    
    *n = i;  // Set count to number of records read
    fclose(fp);  // Close file
}

// ===== PATIENT MANAGEMENT FUNCTIONS =====
// These functions handle all patient-related operations

// add_patient() - Allows user to input and save a new patient to file
void add_patient()
{
    Patient p;  // Create a Patient variable to store new patient data
    
    // Open patient file in append mode (a) to add new data
    FILE *fp = fopen(PATIENT_FILE, "a");
    if (!fp)  // Check if file opened successfully
    {
        printf(RED "Error opening patient file, file not found.\n" RESET);
        return;  // Exit function
    }

    printf(MAGENTA "\n\nPlease enter the following details to add a new patient:\n" RESET);
    printf(BLUE "_________________________________________________________________________________________________________________________\n" RESET);

    // Get Patient ID from user
    printf(GREEN "Enter Patient ID: " RESET);
    while (scanf("%d", &p.patient_id) != 1)  // Check if valid integer
    {
        printf(RED "Invalid input!\n" RESET);
        clear_input_buffer();  // Clear invalid input
        printf(GREEN "Enter Patient ID: " RESET);
    }
    clear_input_buffer();  // Clear newline from buffer

    // Get Patient Name from user
    printf(GREEN "Enter Patient Name: " RESET);
    fgets(p.patient_name, NAME_SIZE, stdin);  // Read patient name
    p.patient_name[strcspn(p.patient_name, "\n")] = 0;  // Remove newline

    // Get Patient Age from user
    printf(GREEN "Enter Patient Age: " RESET);
    while (scanf("%d", &p.age) != 1)  // Check if valid integer
    {
        printf(RED "Invalid input!\n" RESET);
        clear_input_buffer();
        printf(GREEN "Enter Patient Age: " RESET);
    }
    clear_input_buffer();

    // Get Disease/Condition from user
    printf(GREEN "Enter Disease/Condition: " RESET);
    fgets(p.disease, DISEASE_SIZE, stdin);  // Read disease
    p.disease[strcspn(p.disease, "\n")] = 0;  // Remove newline

    // Get Hospital ID where patient is admitted
    printf(GREEN "Enter Hospital ID (where patient is admitted): " RESET);
    while (scanf("%d", &p.hospital_id) != 1)  // Check if valid integer
    {
        printf(RED "Invalid input!\n" RESET);
        clear_input_buffer();
        printf(GREEN "Enter Hospital ID: " RESET);
    }
    clear_input_buffer();

    // Write patient data to file in pipe-separated format
    fprintf(fp, "%d|%s|%d|%s|%d\n", p.patient_id, p.patient_name, p.age, p.disease, p.hospital_id);
    fclose(fp);  // Close file
    printf(GREEN BOLD "Patient added successfully!\n" RESET);
}

// display_patients() - Reads and displays all patients from file
void display_patients()
{
    FILE *fp = fopen(PATIENT_FILE, "r");  // Open patient file in read mode
    if (!fp)  // If file doesn't exist
    {
        printf(RED "Error opening patient file, file not found.\n" RESET);
        return;  // Exit function
    }

    char line[LINE_SIZE];  // Buffer to read each line
    printf(MAGENTA BOLD "\n--- Patient Records ---\n" RESET);  // Display header
    printf(BLUE "_________________________________________________________________________________________________________________________\n" RESET);

    printf("\n\n-------------------------------------------------------------------------------------------------------------------\n");    
    printf(" %4s | %-20s | %-3s | %-25s | %-s\n", "ID", "Name", "Age", "Disease", "Hospital");
    printf("-------------------------------------------------------------------------------------------------------------------\n");
    // Loop through each line in file
    while (fgets(line, LINE_SIZE, fp))
    {
        Patient p;  // Temporary Patient variable
        
        // Extract data from pipe-separated line
        sscanf(line, "%d|%[^|]|%d|%[^|]|%d",
               &p.patient_id, p.patient_name, &p.age, p.disease, &p.hospital_id);
        
        // Get hospital name for this patient
        char *h_name = get_hospital_name_by_id(p.hospital_id);
        
        // Display patient information in formatted way
        printf(CYAN "%5d | %-20s | %-3d | %-25s | %-s\n" RESET,
               p.patient_id, p.patient_name, p.age, p.disease, h_name);
    }
    printf("\n\n-------------------------------------------------------------------------------------------------------------------\n");
    printf(BLUE "_________________________________________________________________________________________________________________________\n" RESET);
    printf("\n");
    fclose(fp);  // Close file
}

// ===== HOSPITAL FILTER & SORT FUNCTIONS =====
// These functions filter and sort hospitals based on different criteria

// display_hospitals_by_city() - Filters hospitals by city and displays them alphabetically
void display_hospitals_by_city()
{
    char city[CITY_SIZE];  // Variable to store city name user wants to search for
    
    // Ask user which city they want to see
    printf(BLUE "_________________________________________________________________________________________________________________________\n" RESET);
    printf(GREEN "Enter City Name: " RESET);
    fgets(city, CITY_SIZE, stdin);  // Read city name
    city[strcspn(city, "\n")] = 0;  // Remove newline

    // Count total number of hospital records
    int n = count_records(HOSPITAL_FILE);
    if (n == 0)  // If no hospitals exist
    {
        printf(RED "No hospitals found!\n" RESET);
        return;
    }

    // Allocate memory for array to store all hospitals
    Hospital *hospitals = (Hospital *)malloc(n * sizeof(Hospital));
    load_hospitals(hospitals, &n);  // Load all hospitals from file

    // Allocate memory for array to store hospitals matching the city
    Hospital *city_hospitals = (Hospital *)malloc(n * sizeof(Hospital));
    int city_count = 0;  // Counter for hospitals in selected city
    

    // Loop through all hospitals and copy matching ones to city_hospitals array
    for (int i = 0; i < n; i++)
    {
        if (strcmp(hospitals[i].city, city) == 0)  // If city matches
        {
            city_hospitals[city_count++] = hospitals[i];  // Copy to new array
        }
    }

    // If no hospitals found in this city
    if (city_count == 0)
    {
        printf(RED "No hospitals found in this city.\n" RESET);
        free(hospitals);  // Free allocated memory
        free(city_hospitals);
        return;
    }

    
    // Sort hospitals in the city alphabetically by name using Bubble Sort algorithm
    // Bubble Sort: repeatedly swap adjacent elements if they're in wrong order
    for (int i = 0; i < city_count - 1; i++)  // Outer loop
    {
        for (int j = 0; j < city_count - 1 - i; j++)  // Inner loop
        {
            // If current hospital name comes after next hospital name alphabetically
            if (strcmp(city_hospitals[j].hospital_name, city_hospitals[j + 1].hospital_name) > 0)
            {
                // Swap the two hospitals
                Hospital temp = city_hospitals[j];
                city_hospitals[j] = city_hospitals[j + 1];
                city_hospitals[j + 1] = temp;
            }
        }
    }

    // Display sorted hospitals
    printf(MAGENTA BOLD "\n--- Hospitals in %s (Alphabetically Sorted) ---\n" RESET, city);
    printf(BLUE "_________________________________________________________________________________________________________________________\n" RESET);

    printf("\n\n-------------------------------------------------------------------------------------------------------------------\n");
    printf("%5s | %-50s | %-12s | %5s | %-10s | %7s | %7s\n", "ID", "Hospital Name", "City", "Beds", "Price", "Ratings", "Reviews");
    printf("-------------------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < city_count; i++)
    {
        Hospital h = city_hospitals[i];
        printf(CYAN "%5d | %-50s | %-12s | %5d | %10.2f | %7.1f | %7d\n" RESET,
               h.hospital_id, h.hospital_name, h.city, h.available_beds, h.bed_price, h.rating, h.reviews);
    }
    printf("-------------------------------------------------------------------------------------------------------------------\n");
    // Free allocated memory to prevent memory leaks
    free(hospitals);
    free(city_hospitals);
}

// ===== BUBBLE SORT IMPLEMENTATIONS =====
// Bubble Sort is a simple sorting algorithm that repeatedly compares adjacent elements

// sort_hospitals_by_bed_price() - Sorts hospitals by bed price from highest to lowest
void sort_hospitals_by_bed_price()
{
    // Count total hospitals and check if any exist
    int n = count_records(HOSPITAL_FILE);
    if (n == 0)
    {
        printf(RED "No hospitals found!\n" RESET);
        return;
    }

    // Allocate memory for array to store all hospitals
    Hospital *h = (Hospital *)malloc(n * sizeof(Hospital));
    load_hospitals(h, &n);  // Load hospitals from file

    // Bubble Sort: sort by bed price in descending order (highest to lowest)
    for (int i = 0; i < n - 1; i++)  // Outer loop
    {
        for (int j = 0; j < n - 1 - i; j++)  // Inner loop
        {
            // If current price is less than next price, swap (to get descending order)
            if (h[j].bed_price < h[j + 1].bed_price)
            {
                Hospital temp = h[j];
                h[j] = h[j + 1];
                h[j + 1] = temp;
            }
        }
    }

    // Display sorted hospitals
    printf(MAGENTA BOLD "\n--- Hospitals Sorted by Bed Price (Highest to Lowest) ---\n" RESET);
    printf(BLUE "_________________________________________________________________________________________________________________________\n" RESET);

    printf("\n\n-------------------------------------------------------------------------------------------------------------------\n");
    printf("%5s | %-50s | %-12s | %5s | %-10s | %7s | %7s\n", "ID", "Hospital Name", "City", "Beds", "Price", "Ratings", "Reviews");
    printf("-------------------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++)
    {
        Hospital x = h[i];
        printf(CYAN "%5d | %-50s | %-12s | %5d | %10.2f | %7.1f | %7d\n" RESET,
               x.hospital_id, x.hospital_name, x.city, x.available_beds, x.bed_price, x.rating, x.reviews);
    }
    printf("-------------------------------------------------------------------------------------------------------------------\n");
    printf("\n\n");
    free(h);  // Free allocated memory
}

// sort_hospitals_by_available_beds() - Sorts hospitals by available beds from most to least
void sort_hospitals_by_available_beds()
{
    // Count total hospitals and check if any exist
    int n = count_records(HOSPITAL_FILE);
    if (n == 0)
    {
        printf(RED "No hospitals found!\n" RESET);
        return;
    }

    // Allocate memory for array to store all hospitals
    Hospital *h = (Hospital *)malloc(n * sizeof(Hospital));
    load_hospitals(h, &n);  // Load hospitals from file

    // Bubble Sort: sort by available beds in descending order (most to least)
    for (int i = 0; i < n - 1; i++)  // Outer loop
    {
        for (int j = 0; j < n - 1 - i; j++)  // Inner loop
        {
            // If current beds less than next beds, swap (to get descending order)
            if (h[j].available_beds < h[j + 1].available_beds)
            {
                Hospital temp = h[j];
                h[j] = h[j + 1];
                h[j + 1] = temp;
            }
        }
    }

    // Display sorted hospitals
    printf(MAGENTA BOLD "\n--- Hospitals Sorted by Available Beds (Highest to Lowest) ---\n" RESET);
    printf(BLUE "_________________________________________________________________________________________________________________________\n" RESET);
    printf("\n\n-------------------------------------------------------------------------------------------------------------------\n");
    printf("%5s | %-50s | %-12s | %5s | %-10s | %7s | %7s\n", "ID", "Hospital Name", "City", "Beds", "Price", "Ratings", "Reviews");
    printf("-------------------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++)
    {
        Hospital x = h[i];
        printf(CYAN "%5d | %-50s | %-12s | %5d | %10.2f | %7.1f | %7d\n" RESET,
               x.hospital_id, x.hospital_name, x.city, x.available_beds, x.bed_price, x.rating, x.reviews);
    }
    printf("-------------------------------------------------------------------------------------------------------------------\n");
    
    free(h);  // Free allocated memory
}

// sort_hospitals_by_name() - Sorts hospitals alphabetically by name (A to Z)
void sort_hospitals_by_name()
{
    // Count total hospitals and check if any exist
    int n = count_records(HOSPITAL_FILE);
    if (n == 0)
    {
        printf(RED "No hospitals found!\n" RESET);
        return;
    }

    // Allocate memory for array to store all hospitals
    Hospital *h = (Hospital *)malloc(n * sizeof(Hospital));
    load_hospitals(h, &n);  // Load hospitals from file

    // Bubble Sort: sort by hospital name alphabetically (A to Z)
    for (int i = 0; i < n - 1; i++)  // Outer loop
    {
        for (int j = 0; j < n - 1 - i; j++)  // Inner loop
        {
            // strcmp returns positive if first string comes after second alphabetically
            if (strcmp(h[j].hospital_name, h[j + 1].hospital_name) > 0)
            {
                Hospital temp = h[j];
                h[j] = h[j + 1];
                h[j + 1] = temp;
            }
        }
    }

    // Display sorted hospitals
    printf(MAGENTA BOLD "\n--- Hospitals Sorted by Name (A to Z) ---\n" RESET);
   printf(BLUE "_________________________________________________________________________________________________________________________\n" RESET);
   printf("\n\n-------------------------------------------------------------------------------------------------------------------\n");
    printf("%5s | %-50s | %-12s | %5s | %-10s | %7s | %7s\n", "ID", "Hospital Name", "City", "Beds", "Price", "Ratings", "Reviews");
    printf("-------------------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++)
    {
        Hospital x = h[i];
        printf(CYAN "%5d | %-50s | %-12s | %5d | %10.2f | %7.1f | %7d\n" RESET,
               x.hospital_id, x.hospital_name, x.city, x.available_beds, x.bed_price, x.rating, x.reviews);
    }
    printf("-------------------------------------------------------------------------------------------------------------------\n");
    free(h);  // Free allocated memory
}

// sort_hospitals_by_rating_and_reviews() - Sorts hospitals by rating, then by reviews
void sort_hospitals_by_rating_and_reviews()
{
    // Count total hospitals and check if any exist
    int n = count_records(HOSPITAL_FILE);
    if (n == 0)
    {
        printf(RED "No hospitals found!\n" RESET);
        return;
    }

    // Allocate memory for array to store all hospitals
    Hospital *h = (Hospital *)malloc(n * sizeof(Hospital));
    load_hospitals(h, &n);  // Load hospitals from file

    // Bubble Sort: sort by rating first, then by reviews if ratings are equal
    for (int i = 0; i < n - 1; i++)  // Outer loop
    {
        for (int j = 0; j < n - 1 - i; j++)  // Inner loop
        {
            // If current rating less than next, or ratings equal and current reviews less, swap
            if (h[j].rating < h[j + 1].rating ||
                (h[j].rating == h[j + 1].rating && h[j].reviews < h[j + 1].reviews))
            {
                Hospital temp = h[j];
                h[j] = h[j + 1];
                h[j + 1] = temp;
            }
        }
    }

    // Display sorted hospitals
    printf(MAGENTA BOLD "\n--- Hospitals Sorted by Rating & Reviews ---\n" RESET);
    printf(BLUE "_________________________________________________________________________________________________________________________\n" RESET);
    printf("\n\n-------------------------------------------------------------------------------------------------------------------\n");
    printf("%5s | %-50s | %-12s | %5s | %-10s | %7s | %7s\n", "ID", "Hospital Name", "City", "Beds", "Price", "Ratings", "Reviews");
    printf("-------------------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++)
    {
        Hospital x = h[i];
        printf(CYAN "%5d | %-50s | %-12s | %5d | %10.2f | %7.1f | %7d\n" RESET,
               x.hospital_id, x.hospital_name, x.city, x.available_beds, x.bed_price, x.rating, x.reviews);
    }
    printf("-------------------------------------------------------------------------------------------------------------------\n");
    
    free(h);  // Free allocated memory
}
