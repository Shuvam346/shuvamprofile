#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*-----------------------------------------
   Structure Definition
------------------------------------------*/
struct Student {
    int roll;          // Student roll number
    char name[50];     // Student name
    float gpa;         // Student GPA
};

/*-----------------------------------------
   Function Declarations
------------------------------------------*/
void addStudent();
void displayStudents();
void searchStudent();
void deleteStudent();
void updateStudent();

/*-----------------------------------------
   Main Function - Program Starts Here
------------------------------------------*/
int main() {

    int choice;   // To store user's menu choice

    // Infinite loop for menu
    while (1) {

        printf("\n=====================================\n");
        printf("      STUDENT MANAGEMENT SYSTEM      \n");
        printf("=====================================\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Delete Student\n");
        printf("5. Update Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);

        // Switch case for menu options
        switch (choice) {

            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                deleteStudent();
                break;

            case 5:
                updateStudent();
                break;

            case 6:
                printf("Exiting Program...\n");
                exit(0);

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

/*-----------------------------------------
   Function 1: Add Student
------------------------------------------*/
void addStudent() {

    struct Student s;       // Create structure variable
    FILE *fp;               // File pointer

    fp = fopen("student.txt", "a");   // Open file in append mode

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\nEnter Roll Number: ");
    scanf("%d", &s.roll);

    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter GPA: ");
    scanf("%f", &s.gpa);

    // Write structure data into file
    fwrite(&s, sizeof(s), 1, fp);

    fclose(fp);   // Close file

    printf("Student record added successfully!\n");
}

/*-----------------------------------------
   Function 2: Display All Students
------------------------------------------*/
void displayStudents() {

    struct Student s;
    FILE *fp;

    fp = fopen("student.txt", "r");   // Open file in read mode

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("\n--------- Student Records ---------\n");

    // Read file until end
    while (fread(&s, sizeof(s), 1, fp)) {

        printf("Roll : %d\n", s.roll);
        printf("Name : %s\n", s.name);
        printf("GPA  : %.2f\n", s.gpa);
        printf("-----------------------------------\n");
    }

    fclose(fp);
}

/*-----------------------------------------
   Function 3: Search Student
------------------------------------------*/
void searchStudent() {

    struct Student s;
    int roll;
    int found = 0;
    FILE *fp;

    fp = fopen("student.txt", "r");

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("Enter Roll Number to search: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fp)) {

        if (s.roll == roll) {

            printf("\nStudent Found!\n");
            printf("Name : %s\n", s.name);
            printf("GPA  : %.2f\n", s.gpa);

            found = 1;
            break;
        }
    }

    if (found == 0) {
        printf("Student not found!\n");
    }

    fclose(fp);
}

/*-----------------------------------------
   Function 4: Delete Student
------------------------------------------*/
void deleteStudent() {

    struct Student s;
    int roll;
    int found = 0;

    FILE *fp;
    FILE *temp;

    fp = fopen("student.txt", "r");
    temp = fopen("temp.txt", "w");

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("Enter Roll Number to delete: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fp)) {

        if (s.roll != roll) {
            fwrite(&s, sizeof(s), 1, temp);
        }
        else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("student.txt");          // Delete old file
    rename("temp.txt", "student.txt");   // Rename temp file

    if (found == 1)
        printf("Student record deleted successfully!\n");
    else
        printf("Student not found!\n");
}

/*-----------------------------------------
   Function 5: Update Student
------------------------------------------*/
void updateStudent() {

    struct Student s;
    int roll;
    int found = 0;

    FILE *fp;

    fp = fopen("student.txt", "r+");   // Read and write mode

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("Enter Roll Number to update: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fp)) {

        if (s.roll == roll) {

            printf("Enter New Name: ");
            scanf(" %[^\n]", s.name);

            printf("Enter New GPA: ");
            scanf("%f", &s.gpa);

            fseek(fp, -sizeof(s), SEEK_CUR);  // Move pointer back
            fwrite(&s, sizeof(s), 1, fp);

            printf("Record updated successfully!\n");

            found = 1;
            break;
        }
    }

    if (found == 0) {
        printf("Student not found!\n");
    }

    fclose(fp);
}