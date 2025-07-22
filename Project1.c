#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student
{
    int roll;
    char name[50];
    float marks;
};

// Function declarations
void addStudent();
void viewStudents();
void searchStudent();
void deleteStudent();

int main()
{
    int choice;

    while (1)
    {
        printf("\n--- Student Record System ---\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Search Student\n");
        printf("4. Delete Student\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addStudent();
            break;
        case 2:
            viewStudents();
            break;
        case 3:
            searchStudent();
            break;
        case 4:
            deleteStudent();
            break;
        case 5:
            exit(0);
        default:
            printf("Invalid choice!\n");
        }
    }

    return 0;
}

void addStudent()
{
    struct Student s;
    FILE *fp = fopen("students.dat", "ab"); // append binary
    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter roll number: ");
    scanf("%d", &s.roll);
    printf("Enter name: ");
    scanf(" %[^\n]", s.name); // space before % to read full line
    printf("Enter marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);
    printf("Student added successfully!\n");
}

void viewStudents()
{
    struct Student s;
    FILE *fp = fopen("students.dat", "rb"); // read binary
    if (fp == NULL)
    {
        printf("No records found.\n");
        return;
    }

    printf("\n--- All Students ---\n");
    while (fread(&s, sizeof(s), 1, fp))
    {
        printf("Roll: %d | Name: %s | Marks: %.2f\n", s.roll, s.name, s.marks);
    }
    fclose(fp);
}

void searchStudent()
{
    int roll;
    int found = 0;
    struct Student s;
    FILE *fp = fopen("students.dat", "rb");
    if (fp == NULL)
    {
        printf("No records found.\n");
        return;
    }

    printf("Enter roll number to search: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fp))
    {
        if (s.roll == roll)
        {
            printf("Record found!\n");
            printf("Roll: %d | Name: %s | Marks: %.2f\n", s.roll, s.name, s.marks);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Student not found.\n");
    }

    fclose(fp);
}

void deleteStudent()
{
    int roll;
    struct Student s;
    FILE *fp, *temp;

    printf("Enter roll number to delete: ");
    scanf("%d", &roll);

    fp = fopen("students.dat", "rb");
    temp = fopen("temp.dat", "wb");

    if (fp == NULL || temp == NULL)
    {
        printf("File error.\n");
        return;
    }

    int found = 0;
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

    if (found)
        printf("Student deleted successfully.\n");
    else
        printf("Student not found.\n");
}
