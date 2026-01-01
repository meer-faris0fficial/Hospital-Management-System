#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HOSPITAL_FILE "hospitals.txt"
#define PATIENT_FILE "patients.txt"
#define USER_FILE "users.txt"
#define NAME_SIZE 50
#define CITY_SIZE 30
#define DISEASE_SIZE 50
#define LINE_SIZE 256
#define USERNAME_SIZE 30
#define PASSWORD_SIZE 30

// ---------------------- Structures ----------------------
typedef struct
{
    int hospitalID;
    char hospitalName[NAME_SIZE];
    char city[CITY_SIZE];
    int availableBeds;
    float bedPrice;
    float rating;
    int reviews;
} Hospital;

typedef struct
{
    int patientID;
    char patientName[NAME_SIZE];
    int age;
    char disease[DISEASE_SIZE];
    int hospitalID;
} Patient;

typedef struct
{
    char username[USERNAME_SIZE];
    char password[PASSWORD_SIZE];
} User;

// ---------------------- Function Prototypes ----------------------
void clearInputBuffer();
void clearScreen();
void printWelcomeBanner();
int countRecords(const char *filename);
void loadHospitals(Hospital *hospitals, int *n);
void loadPatients(Patient *patients, int *n);
char *getHospitalNameByID(int hospitalID);

void signup();
int login();

void addHospital();
void displayHospitals();
void displayHospitalsByCity();
void sortHospitalsByBedPrice();
void sortHospitalsByAvailableBeds();
void sortHospitalsByName();
void sortHospitalsByRatingAndReviews();

void addPatient();
void displayPatients();

// ---------------------- Main Program ----------------------
int main()
{
    int choice;

    clearScreen();
    printWelcomeBanner();

    // Authentication
    int auth = 0;
    while (!auth)
    {
        printf("\n1. Login\n2. Sign Up\n3. Exit\nEnter choice: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input!\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (choice)
        {
        case 1:
            auth = login();
            break;
        case 2:
            signup();
            break;
        case 3:
            exit(0);
        default:
            printf("Invalid choice! Try again.\n");
        }
    }

    // Main menu
    while (1)
    {
        clearScreen();
        printWelcomeBanner();
        printf("\n--- Main Menu ---\n");
        printf("1. Add Hospital Data\n");
        printf("2. Display Hospital Data\n");
        printf("3. Display Hospitals by City\n");
        printf("4. Sort Hospitals by Bed Price\n");
        printf("5. Sort Hospitals by Available Beds\n");
        printf("6. Sort Hospitals by Name\n");
        printf("7. Sort Hospitals by Rating and Reviews\n");
        printf("8. Add Patient Data\n");
        printf("9. Display Patient Data\n");
        printf("10. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input!\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        clearScreen();
        printWelcomeBanner();

        switch (choice)
        {
        case 1:
            addHospital();
            break;
        case 2:
            displayHospitals();
            break;
        case 3:
            displayHospitalsByCity();
            break;
        case 4:
            sortHospitalsByBedPrice();
            break;
        case 5:
            sortHospitalsByAvailableBeds();
            break;
        case 6:
            sortHospitalsByName();
            break;
        case 7:
            sortHospitalsByRatingAndReviews();
            break;
        case 8:
            addPatient();
            break;
        case 9:
            displayPatients();
            break;
        case 10:
            exit(0);
        default:
            printf("Invalid choice! Try again.\n");
        }

        printf("\nPress Enter to continue...");
        getchar();
    }

    return 0;
}

// ---------------------- Utility Functions ----------------------
void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void printWelcomeBanner()
{
    printf("=============================================\n");
    printf("     WELCOME TO HOSPITAL MANAGEMENT SYSTEM  \n");
    printf("=============================================\n");
}

int countRecords(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
        return 0;
    int count = 0;
    char line[LINE_SIZE];
    while (fgets(line, LINE_SIZE, fp))
        count++;
    fclose(fp);
    return count;
}

void loadHospitals(Hospital *hospitals, int *n)
{
    FILE *fp = fopen(HOSPITAL_FILE, "r");
    if (!fp)
    {
        *n = 0;
        return;
    }
    int i = 0;
    char line[LINE_SIZE];
    while (fgets(line, LINE_SIZE, fp))
    {
        sscanf(line, "%d|%[^|]|%[^|]|%d|%f|%f|%d",
               &hospitals[i].hospitalID, hospitals[i].hospitalName, hospitals[i].city,
               &hospitals[i].availableBeds, &hospitals[i].bedPrice,
               &hospitals[i].rating, &hospitals[i].reviews);
        i++;
    }
    *n = i;
    fclose(fp);
}

void loadPatients(Patient *patients, int *n)
{
    FILE *fp = fopen(PATIENT_FILE, "r");
    if (!fp)
    {
        *n = 0;
        return;
    }
    int i = 0;
    char line[LINE_SIZE];
    while (fgets(line, LINE_SIZE, fp))
    {
        sscanf(line, "%d|%[^|]|%d|%[^|]|%d",
               &patients[i].patientID, patients[i].patientName, &patients[i].age,
               patients[i].disease, &patients[i].hospitalID);
        i++;
    }
    *n = i;
    fclose(fp);
}

char *getHospitalNameByID(int hospitalID)
{
    static char name[NAME_SIZE];
    FILE *fp = fopen(HOSPITAL_FILE, "r");
    if (!fp)
    {
        strcpy(name, "Unknown");
        return name;
    }
    char line[LINE_SIZE];
    while (fgets(line, LINE_SIZE, fp))
    {
        Hospital h;
        sscanf(line, "%d|%[^|]|%[^|]|%d|%f|%f|%d",
               &h.hospitalID, h.hospitalName, h.city,
               &h.availableBeds, &h.bedPrice, &h.rating, &h.reviews);
        if (h.hospitalID == hospitalID)
        {
            strcpy(name, h.hospitalName);
            fclose(fp);
            return name;
        }
    }
    fclose(fp);
    strcpy(name, "Unknown");
    return name;
}

// ---------------------- Login System ----------------------
void signup()
{
    User u;
    FILE *fp = fopen(USER_FILE, "a+");
    if (!fp)
    {
        perror("Error opening users file");
        return;
    }

    printf("Enter username: ");
    fgets(u.username, USERNAME_SIZE, stdin);
    u.username[strcspn(u.username, "\n")] = 0;

    // Check existing username
    char line[LINE_SIZE];
    while (fgets(line, LINE_SIZE, fp))
    {
        char existingUser[USERNAME_SIZE];
        sscanf(line, "%[^|]|%*s", existingUser);
        if (strcmp(existingUser, u.username) == 0)
        {
            printf("Username already exists!\n");
            fclose(fp);
            return;
        }
    }

    printf("Enter password: ");
    fgets(u.password, PASSWORD_SIZE, stdin);
    u.password[strcspn(u.password, "\n")] = 0;

    fprintf(fp, "%s|%s\n", u.username, u.password);
    fclose(fp);
    printf("Sign-up successful! You can now login.\n");
}

int login()
{
    char username[USERNAME_SIZE], password[PASSWORD_SIZE];
    FILE *fp = fopen(USER_FILE, "r");
    if (!fp)
    {
        perror("Error opening users file");
        return 0;
    }

    printf("Enter username: ");
    fgets(username, USERNAME_SIZE, stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Enter password: ");
    fgets(password, PASSWORD_SIZE, stdin);
    password[strcspn(password, "\n")] = 0;

    char line[LINE_SIZE];
    while (fgets(line, LINE_SIZE, fp))
    {
        char fileUser[USERNAME_SIZE], filePass[PASSWORD_SIZE];
        sscanf(line, "%[^|]|%s", fileUser, filePass);
        if (strcmp(fileUser, username) == 0 && strcmp(filePass, password) == 0)
        {
            fclose(fp);
            printf("Login successful!\n");
            return 1;
        }
    }

    fclose(fp);
    printf("Invalid username or password!\n");
    return 0;
}

// ---------------------- Hospital Management ----------------------
void addHospital()
{
    Hospital h;
    FILE *fp = fopen(HOSPITAL_FILE, "a");
    if (!fp)
    {
        perror("Error opening hospital file");
        return;
    }

    printf("Enter Hospital ID: ");
    if (scanf("%d", &h.hospitalID) != 1)
    {
        printf("Invalid input!\n");
        clearInputBuffer();
        fclose(fp);
        return;
    }
    clearInputBuffer();

    printf("Enter Hospital Name: ");
    fgets(h.hospitalName, NAME_SIZE, stdin);
    h.hospitalName[strcspn(h.hospitalName, "\n")] = 0;

    printf("Enter City: ");
    fgets(h.city, CITY_SIZE, stdin);
    h.city[strcspn(h.city, "\n")] = 0;

    printf("Enter Number of Available Beds: ");
    if (scanf("%d", &h.availableBeds) != 1)
    {
        printf("Invalid input!\n");
        clearInputBuffer();
        fclose(fp);
        return;
    }
    clearInputBuffer();

    printf("Enter Bed Price per Day: ");
    if (scanf("%f", &h.bedPrice) != 1)
    {
        printf("Invalid input!\n");
        clearInputBuffer();
        fclose(fp);
        return;
    }
    clearInputBuffer();

    printf("Enter Hospital Rating (0-5): ");
    if (scanf("%f", &h.rating) != 1)
    {
        printf("Invalid input!\n");
        clearInputBuffer();
        fclose(fp);
        return;
    }
    clearInputBuffer();

    printf("Enter Number of Reviews: ");
    if (scanf("%d", &h.reviews) != 1)
    {
        printf("Invalid input!\n");
        clearInputBuffer();
        fclose(fp);
        return;
    }
    clearInputBuffer();

    fprintf(fp, "%d|%s|%s|%d|%.2f|%.1f|%d\n",
            h.hospitalID, h.hospitalName, h.city, h.availableBeds, h.bedPrice, h.rating, h.reviews);
    fclose(fp);
    printf("Hospital added successfully!\n");
}

// Display Hospitals
void displayHospitals()
{
    FILE *fp = fopen(HOSPITAL_FILE, "r");
    if (!fp)
    {
        perror("Error opening hospital file");
        return;
    }

    char line[LINE_SIZE];
    printf("\n--- Hospital Records ---\n");
    while (fgets(line, LINE_SIZE, fp))
    {
        Hospital h;
        sscanf(line, "%d|%[^|]|%[^|]|%d|%f|%f|%d", &h.hospitalID, h.hospitalName, h.city,
               &h.availableBeds, &h.bedPrice, &h.rating, &h.reviews);
        printf("ID: %d | Name: %s | City: %s | Beds: %d | Price: %.2f | Rating: %.1f | Reviews: %d\n",
               h.hospitalID, h.hospitalName, h.city, h.availableBeds, h.bedPrice, h.rating, h.reviews);
    }
    fclose(fp);
}

// ... Similarly add displayHospitalsByCity, sortHospitalsByBedPrice, sortHospitalsByAvailableBeds, sortHospitalsByName, sortHospitalsByRatingAndReviews

// ---------------------- Patient Management ----------------------
void addPatient()
{
    Patient p;
    FILE *fp = fopen(PATIENT_FILE, "a");
    if (!fp)
    {
        perror("Error opening patient file");
        return;
    }

    printf("Enter Patient ID: ");
    if (scanf("%d", &p.patientID) != 1)
    {
        printf("Invalid input!\n");
        clearInputBuffer();
        fclose(fp);
        return;
    }
    clearInputBuffer();

    printf("Enter Patient Name: ");
    fgets(p.patientName, NAME_SIZE, stdin);
    p.patientName[strcspn(p.patientName, "\n")] = 0;

    printf("Enter Patient Age: ");
    if (scanf("%d", &p.age) != 1)
    {
        printf("Invalid input!\n");
        clearInputBuffer();
        fclose(fp);
        return;
    }
    clearInputBuffer();

    printf("Enter Disease/Condition: ");
    fgets(p.disease, DISEASE_SIZE, stdin);
    p.disease[strcspn(p.disease, "\n")] = 0;

    printf("Enter Hospital ID (where patient is admitted): ");
    if (scanf("%d", &p.hospitalID) != 1)
    {
        printf("Invalid input!\n");
        clearInputBuffer();
        fclose(fp);
        return;
    }
    clearInputBuffer();

    fprintf(fp, "%d|%s|%d|%s|%d\n", p.patientID, p.patientName, p.age, p.disease, p.hospitalID);
    fclose(fp);
    printf("Patient added successfully!\n");
}

void displayPatients()
{
    FILE *fp = fopen(PATIENT_FILE, "r");
    if (!fp)
    {
        perror("Error opening patient file");
        return;
    }

    char line[LINE_SIZE];
    printf("\n--- Patient Records ---\n");
    while (fgets(line, LINE_SIZE, fp))
    {
        Patient p;
        sscanf(line, "%d|%[^|]|%d|%[^|]|%d",
               &p.patientID, p.patientName, &p.age, p.disease, &p.hospitalID);
        char *hname = getHospitalNameByID(p.hospitalID);
        printf("ID: %d | Name: %s | Age: %d | Disease: %s | Hospital: %s\n",
               p.patientID, p.patientName, p.age, p.disease, hname);
    }
    fclose(fp);
}

// ---------------------- Hospital Filter & Sort ----------------------

// Display hospitals by city
void displayHospitalsByCity()
{
    char city[CITY_SIZE];
    printf("Enter City Name: ");
    fgets(city, CITY_SIZE, stdin);
    city[strcspn(city, "\n")] = 0;

    int n = countRecords(HOSPITAL_FILE);
    if (n == 0)
    {
        printf("No hospitals found!\n");
        return;
    }

    Hospital *hospitals = (Hospital *)malloc(n * sizeof(Hospital));
    loadHospitals(hospitals, &n);

    int found = 0;
    printf("\n--- Hospitals in %s ---\n", city);
    for (int i = 0; i < n; i++)
    {
        if (strcmp(hospitals[i].city, city) == 0)
        {
            Hospital h = hospitals[i];
            printf("ID: %d | Name: %s | Beds: %d | Price: %.2f | Rating: %.1f | Reviews: %d\n",
                   h.hospitalID, h.hospitalName, h.availableBeds, h.bedPrice, h.rating, h.reviews);
            found = 1;
        }
    }

    if (!found)
        printf("No hospitals found in this city.\n");
    free(hospitals);
}

// Sort hospitals by bed price descending
void sortHospitalsByBedPrice()
{
    int n = countRecords(HOSPITAL_FILE);
    if (n == 0)
    {
        printf("No hospitals found!\n");
        return;
    }

    Hospital *h = (Hospital *)malloc(n * sizeof(Hospital));
    loadHospitals(h, &n);

    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (h[i].bedPrice < h[j].bedPrice)
            {
                Hospital temp = h[i];
                h[i] = h[j];
                h[j] = temp;
            }

    printf("\n--- Hospitals Sorted by Bed Price ---\n");
    for (int i = 0; i < n; i++)
    {
        Hospital x = h[i];
        printf("ID: %d | Name: %s | City: %s | Beds: %d | Price: %.2f | Rating: %.1f | Reviews: %d\n",
               x.hospitalID, x.hospitalName, x.city, x.availableBeds, x.bedPrice, x.rating, x.reviews);
    }
    free(h);
}

// Sort hospitals by available beds descending
void sortHospitalsByAvailableBeds()
{
    int n = countRecords(HOSPITAL_FILE);
    if (n == 0)
    {
        printf("No hospitals found!\n");
        return;
    }

    Hospital *h = (Hospital *)malloc(n * sizeof(Hospital));
    loadHospitals(h, &n);

    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (h[i].availableBeds < h[j].availableBeds)
            {
                Hospital temp = h[i];
                h[i] = h[j];
                h[j] = temp;
            }

    printf("\n--- Hospitals Sorted by Available Beds ---\n");
    for (int i = 0; i < n; i++)
    {
        Hospital x = h[i];
        printf("ID: %d | Name: %s | City: %s | Beds: %d | Price: %.2f | Rating: %.1f | Reviews: %d\n",
               x.hospitalID, x.hospitalName, x.city, x.availableBeds, x.bedPrice, x.rating, x.reviews);
    }
    free(h);
}

// Sort hospitals by name alphabetically
void sortHospitalsByName()
{
    int n = countRecords(HOSPITAL_FILE);
    if (n == 0)
    {
        printf("No hospitals found!\n");
        return;
    }

    Hospital *h = (Hospital *)malloc(n * sizeof(Hospital));
    loadHospitals(h, &n);

    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (strcmp(h[i].hospitalName, h[j].hospitalName) > 0)
            {
                Hospital temp = h[i];
                h[i] = h[j];
                h[j] = temp;
            }

    printf("\n--- Hospitals Sorted by Name ---\n");
    for (int i = 0; i < n; i++)
    {
        Hospital x = h[i];
        printf("ID: %d | Name: %s | City: %s | Beds: %d | Price: %.2f | Rating: %.1f | Reviews: %d\n",
               x.hospitalID, x.hospitalName, x.city, x.availableBeds, x.bedPrice, x.rating, x.reviews);
    }
    free(h);
}

// Sort hospitals by rating descending, then reviews descending
void sortHospitalsByRatingAndReviews()
{
    int n = countRecords(HOSPITAL_FILE);
    if (n == 0)
    {
        printf("No hospitals found!\n");
        return;
    }

    Hospital *h = (Hospital *)malloc(n * sizeof(Hospital));
    loadHospitals(h, &n);

    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (h[i].rating < h[j].rating ||
                (h[i].rating == h[j].rating && h[i].reviews < h[j].reviews))
            {
                Hospital temp = h[i];
                h[i] = h[j];
                h[j] = temp;
            }

    printf("\n--- Hospitals Sorted by Rating & Reviews ---\n");
    for (int i = 0; i < n; i++)
    {
        Hospital x = h[i];
        printf("ID: %d | Name: %s | City: %s | Beds: %d | Price: %.2f | Rating: %.1f | Reviews: %d\n",
               x.hospitalID, x.hospitalName, x.city, x.availableBeds, x.bedPrice, x.rating, x.reviews);
    }
    free(h);
}
