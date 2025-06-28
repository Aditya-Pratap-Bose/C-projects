#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h> // for getch()

// Structure to store student info
struct Student
{
    int roll;
    char name[50];
    float marks;
};

// Function declarations
void addStudent(FILE *fp);
void displayStudents(FILE *fp);
void searchStudent(FILE *fp);
void deleteStudent(FILE *fp);
void updateStudent(FILE *fp);
void pause();

// Main function with login and menu
int main()
{
    FILE *fp;
    char password[20], ch;
    int choice;

    // Login section (simple password protection)
    printf("Enter Admin Password: ");
    int i = 0;
    while (1)
    {
        ch = getch();

        if (ch == 13)
        { // Enter key ASCII
            password[i] = '\0';
            break;
        }
        else if (ch == 8 && i > 0)
        { // Backspace handling
            i--;
            printf("\b \b");
        }
        else
        {
            password[i++] = ch;
            printf("*");
        }
    }

    if (strcmp(password, "admin123") != 0)
    {
        printf("\nWrong password. Access denied.\n");
        return 0;
    }

    // File open in read+write mode, binary
    fp = fopen("students.dat", "rb+");
    if (fp == NULL)
    {
        fp = fopen("students.dat", "wb+"); // create if not exists
        if (fp == NULL)
        {
            printf("Cannot open file.\n");
            return 1;
        }
    }

    // Menu loop
    do
    {
        system("cls");
        printf("====== Student Management System ======\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student by Roll No\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        fflush(stdin);

        switch (choice)
        {
        case 1:
            addStudent(fp);
            break;
        case 2:
            displayStudents(fp);
            break;
        case 3:
            searchStudent(fp);
            break;
        case 4:
            updateStudent(fp);
            break;
        case 5:
            deleteStudent(fp);
            break;
        case 6:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice!\n");
            pause();
        }
    } while (choice != 6);

    fclose(fp);
    return 0;
}

// Utility to pause after action
void pause()
{
    printf("\nPress any key to continue...");
    getch();
}

// Add student
void addStudent(FILE *fp)
{
    struct Student s;
    fseek(fp, 0, SEEK_END); // go to end
    printf("Enter Roll No: ");
    scanf("%d", &s.roll);
    printf("Enter Name: ");
    fflush(stdin);
    gets(s.name);
    printf("Enter Marks: ");
    scanf("%f", &s.marks);
    fwrite(&s, sizeof(s), 1, fp);
    printf("Student added successfully.\n");
    pause();
}

// Display all students
void displayStudents(FILE *fp)
{
    struct Student s;
    rewind(fp); // go to start
    printf("\n%-10s %-30s %-10s\n", "Roll", "Name", "Marks");
    printf("-------------------------------------------------\n");
    while (fread(&s, sizeof(s), 1, fp))
    {
        printf("%-10d %-30s %-10.2f\n", s.roll, s.name, s.marks);
    }
    pause();
}

// Search by roll
void searchStudent(FILE *fp)
{
    struct Student s;
    int roll, found = 0;
    printf("Enter Roll No to search: ");
    scanf("%d", &roll);
    rewind(fp);
    while (fread(&s, sizeof(s), 1, fp))
    {
        if (s.roll == roll)
        {
            printf("Record Found: %d - %s - %.2f\n", s.roll, s.name, s.marks);
            found = 1;
            break;
        }
    }
    if (!found)
        printf("Record not found.\n");
    pause();
}

// Update student record
void updateStudent(FILE *fp)
{
    struct Student s;
    int roll, found = 0;
    printf("Enter Roll No to update: ");
    scanf("%d", &roll);
    rewind(fp);
    while (fread(&s, sizeof(s), 1, fp))
    {
        if (s.roll == roll)
        {
            printf("Enter new Name: ");
            fflush(stdin);
            gets(s.name);
            printf("Enter new Marks: ");
            scanf("%f", &s.marks);
            fseek(fp, -sizeof(s), SEEK_CUR); // go back one record
            fwrite(&s, sizeof(s), 1, fp);
            printf("Record updated.\n");
            found = 1;
            break;
        }
    }
    if (!found)
        printf("Record not found.\n");
    pause();
}

// Delete student
void deleteStudent(FILE *fp)
{
    struct Student s;
    FILE *temp = fopen("temp.dat", "wb");
    int roll, found = 0;
    printf("Enter Roll No to delete: ");
    scanf("%d", &roll);
    rewind(fp);
    while (fread(&s, sizeof(s), 1, fp))
    {
        if (s.roll != roll)
        {
            fwrite(&s, sizeof(s), 1, temp);
        }
        else
        {
            found = 1;
        }
    }
    fclose(fp);
    fclose(temp);
    remove("students.dat");
    rename("temp.dat", "students.dat");
    fp = fopen("students.dat", "rb+");
    if (found)
        printf("Record deleted.\n");
    else
        printf("Record not found.\n");
    pause();
}
