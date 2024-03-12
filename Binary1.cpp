//Binary Files
//study and Research
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for a student record
struct Student {
    char name[50];
    int roll_number;
    float marks;
};

// Function to add a new student record
void addStudent(struct Student *students, int *num_students) {
    printf("Enter name: ");
    scanf("%s", students[*num_students].name);
    printf("Enter roll number: ");
    scanf("%d", &students[*num_students].roll_number);
    printf("Enter marks: ");
    scanf("%f", &students[*num_students].marks);
    (*num_students)++;
}

// Function to display all student records
void displayStudents(struct Student *students, int num_students) {
    printf("\nStudent Records:\n");
    printf("--------------------------------------------------\n");
    printf("Name\tRoll Number\tMarks\n");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < num_students; i++) {
        printf("%s\t%d\t\t%.2f\n", students[i].name, students[i].roll_number, students[i].marks);
    }
    printf("--------------------------------------------------\n");
}

// Function to save student records to a binary file
void saveRecords(struct Student *students, int num_students, const char *filename) {
    FILE *file = fopen(filename, "ab"); // "ab" mode for appending to binary file
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    fwrite(students, sizeof(struct Student), num_students, file);
    fclose(file);
    printf("Records saved successfully.\n");
}


// Function to load student records from a binary file
int loadRecords(struct Student *students, int *num_students, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 0;
    }
    fseek(file, 0, SEEK_END); // Move the file pointer to the end
    long file_size = ftell(file); // Get the current position, which is the file size
    rewind(file); // Reset the file pointer to the beginning
    *num_students = file_size / sizeof(struct Student); // Calculate the number of records
    fread(students, sizeof(struct Student), *num_students, file); // Read all records
    fclose(file);
    printf("Records loaded successfully.\n");
    return 1;
}


int main() {
    struct Student students[100];
    int num_students = 0;
    int choice;
	printf("-------------------------------------------Made by Prajjwal Maharjan-------------------------------------------------\n");
    while (1) {
        printf("\nStudent Record System\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Save Records\n");
        printf("4. Load Records\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent(students, &num_students);
                break;
            case 2:
                displayStudents(students, num_students);
                break;
            case 3:
                saveRecords(students, num_students, "student_records.bin");
                break;
            case 4:
                if (loadRecords(students, &num_students, "student_records.bin"))
                    displayStudents(students, num_students);
                break;
            case 5:
           		printf("Exited successfully!!");
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}

