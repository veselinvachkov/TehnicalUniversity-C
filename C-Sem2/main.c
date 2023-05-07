#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    float grade;
} Student;

int num_students = 0;

// Function to report failed student names to a file
void report_failed_students(Student students[]) {
    FILE *failed_file = fopen("failed.txt", "w");
    if (failed_file != NULL) {
        for (int i = 0; i < num_students; i++) {
            if (students[i].grade < 3.0) {
                fprintf(failed_file, "%s\n", students[i].name);
            }
        }
        fclose(failed_file);
        printf("Report generated for failed students.\n");
    } else {
        printf("Error opening file for writing report.\n");
    }
}

// Function to add a new student
void add_student(Student students[]) {
    if (num_students >= 50) {
        printf("Maximum number of students reached.\n");
        return;
    }
    Student new_student;
    printf("Enter student ID: ");
    scanf("%d", &new_student.id);
    printf("Enter student name: ");
    scanf("%s", new_student.name);
    printf("Enter student grade: ");
    scanf("%f", &new_student.grade);
    students[num_students++] = new_student;
    printf("Student added successfully.\n");
}

// Function to delete a student at a given position
void delete_student(Student students[], int pos) {
    if (pos < 0 || pos >= num_students) {
        printf("Invalid position.\n");
        return;
    }
    for (int i = pos; i < num_students-1; i++) {
        students[i] = students[i+1];
    }
    num_students--;
    printf("Student deleted successfully.\n");
}

// Function to calculate the average GPA of all students
float calculate_average_grade(Student students[]) {
    float sum = 0.0;
    for (int i = 0; i < num_students; i++) {
        sum += students[i].grade;
    }
    return sum / num_students;
}

// Function to set the grade of a student at a given position
void set_grade(Student students[], int pos, float new_grade) {
    if (pos < 0 || pos >= num_students) {
        printf("Invalid position.\n");
        return;
    }
    students[pos].grade = new_grade;
    printf("Grade set successfully.\n");
}

// Function to give a bonus
void give_bonus(Student students[]) {
    for (int i = 0; i < num_students; i++) {
        if(students[i].grade <= 4){
           students[i].grade += 1;
        }
    }
    printf("Bonus given successfully.\n");
}

int main() {
    // Initialize data
    Student students[50] = {};

    int choice;

    do {
        printf("\n1. Read from binary file\n");
        printf("2. Write to binary file\n");
        printf("3. Print data\n");
        printf("4. Generate report for failed students\n");
        printf("5. Add a student\n");
        printf("6. Delete a student at position\n");
        printf("7. Calculate average GPA\n");
        printf("8. Set grade at position\n");
        printf("9. Give bonus to students\n");
        printf("10. Exit\n");

        printf("Enter your choice:\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                // Read from binary file
                FILE *fp = fopen("students.bin", "rb");
                if (fp != NULL) {
                    fread(&num_students, sizeof(int), 1, fp);
                    printf("count: %d\n", num_students);
                    fread(students, sizeof(Student), num_students, fp);
                    fclose(fp);
                    printf("Data read from binary file successfully.\n");
                } else {
                    printf("Error opening file for reading.\n");
                }
                break;
            }
            case 2: {
                // Write to binary file
                FILE *fp = fopen("students.bin", "wb");
                if (fp != NULL) {
                    fwrite(&num_students, sizeof(int), 1, fp);
                    fwrite(students, sizeof(Student), num_students, fp);
                    fclose(fp);
                    printf("Data written to binary file successfully.\n");
                } else {
                    printf("Error opening file for writing.\n");
                }
                break;
            }
            case 3: {
                // Print data
                printf("Student data:\n");
                printf("%-10s%-20s%s\n", "ID", "Name", "GPA");
                for (int i = 0; i < num_students; i++) {
                    printf("%-10d%-20s%.2f\n", students[i].id, students[i].name, students[i].grade);
                }
                break;
            }
            case 4: {
                // Generate report for failed students
                report_failed_students(students);
                break;
            }
            case 5: {
                // Add a student
                add_student(students);
                break;
            }
            case 6: {
                // Delete a student at position
                int pos;
                printf("Enter position of student to delete: ");
                scanf("%d", &pos);
                delete_student(students, pos);
                break;
            }
            case 7: {
                // Calculate average GPA
                float avg_grade = calculate_average_grade(students);
                printf("Average grade: %.2f\n", avg_grade);
                break;
            }
            case 8: {
                // Set grade at position
                int pos;
                float new_grade;
                printf("Enter position of student: ");
                scanf("%d", &pos);
                printf("Enter new grade: ");
                scanf("%f", &new_grade);
                set_grade(students, pos, new_grade);
                break;
            }
            case 9: {
                // Give bonus to students
                give_bonus(students);
                break;
            }
            case 10: {
                // Exit
                printf("Exiting...\n");
                break;
            }
            default: {
                printf("Invalid choice.\n");
            }
        }
    } while (choice != 10);

    return 0;
}

