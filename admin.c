#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "admin.h"
#include "data_management.h"
#include "file_acess.h"

/*
 * FILE: admin.c
 * AUTHOR: Yasmine Elmenofy
 * BRIEF: This section of the project deal with the admin mode and admin menu
 * DATA: 8/05/2024
 */

/*
* Use this function to change the admin password stored in the specified file.
* It asks the admin for current username and password  verifies them against stored records,
* and allows the admin to set a new password if authentication succeeds.
*/
void ADD_vChangeAdminPassword(const char *filename_password) {
    FILE *file = fopen(filename_password, "r+");
    if (file != NULL) {
        char current_username[50];
        char current_password[50];
        printf("Enter current admin username: ");
        scanf("%s", current_username);
        printf("Enter current admin password: ");
        scanf("%s", current_password);

        int found = 0;
        char line[100];
        while (fgets(line, sizeof(line), file)) {
            char *token = strtok(line, ",");
            if (strcmp(token, current_username) == 0) {
                token = strtok(NULL, ",");
                token[strcspn(token, "\n")] = '\0';
                if (strcmp(token, current_password) == 0) {
                    found = 1;
                    break;
                }
            }
        }

        if (found) {
            printf("Authentication successful. Enter new admin password: ");
            char new_password[50];
            scanf("%s", new_password);
            fseek(file, -strlen(current_password) - 1, SEEK_CUR);
            fprintf(file, "%s\n", new_password);
            printf("Admin password changed successfully.\n");
        } else {
            printf("Authentication failed. Unable to change admin password.\n");
        }

        fclose(file);
    } else {
        printf("Error: Unable to open admin passwords file %s\n", filename_password);
    }
}
/*
* Use this function to edit an existing student record in the specified file.
* It asks the admin for the ID of the record to be edited, displays the current
* information of the record, allows the admin to modify it, and updates the record
* in the file using DFF_vWriteStudentRecord.
*/

void ADD_vEditStudentRecords(const char *filename_studentrecord) {
    int targetId;
    printf("Enter the unique ID of the student record you want to edit: ");
    scanf("%d", &targetId);

    student_t student;
    if (DDM_nReadStudentRecord(filename_studentrecord, targetId, &student)) {
        printf("Current Information:\n");
        printf("Name: %s\n", student.cName);
        printf("Password: %s\n", student.cPassword);
        printf("ID: %d\n", student.nUnique_Id);
        printf("Grade: %.2f\n", student.fTotal_Grade);
        printf("Age: %d\n", student.nAge);
        printf("Gender: %s\n", student.cGender);

        printf("Enter new information:\n");
        printf("Name: ");
        scanf("%s", student.cName);
        printf("Password: ");
        scanf("%s", student.cPassword);
        printf("Grade: ");
        scanf("%f", &student.fTotal_Grade);
        printf("Age: ");
        scanf("%d", &student.nAge);
        printf("Gender: ");
        scanf("%s", student.cGender);

        FILE *file = fopen(filename_studentrecord, "r+");
        if (file != NULL) {
            fseek(file, -1 * (strlen(student.cName) + strlen(student.cPassword) + 15), SEEK_CUR); // Move pointer back to the beginning of the record
            fprintf(file, "%s,%s,%d,%.2f,%d,%s\n", student.cName, student.cPassword, student.nUnique_Id, student.fTotal_Grade, student.nAge, student.cGender);
            fclose(file);
            printf("Record updated successfully.\n");
        } else {
            printf("Error: Unable to open student records file %s\n", filename_studentrecord);
        }
    } else {
        printf("No student record found with the provided ID.\n");
    }
}


/*
*use this funtion to add new student record
*it ask admin to enter the information
*it use DFF_vWriteStudentRecord()to add them as new records to file
*/



void ADD_vAddNewStudentRecord(const char *filename_studentrecord) {
    printf("Adding a new student record...\n");
    student_t newStudent;
     newStudent.cPassword = (char *)malloc(50 * sizeof(char));
    if (newStudent.cPassword == NULL) {
        printf("Error: Memory allocation failed for password.\n");
        return;
    }

    printf("Enter student name: ");
    scanf("%s", newStudent.cName);
    printf("Enter student password: ");
    scanf(" %49[^\n]", newStudent.cPassword);
    printf("Enter student ID: ");
    scanf("%d", &newStudent.nUnique_Id);
    printf("Enter student GPA: ");
    scanf("%f", &newStudent.fTotal_Grade);
    printf("Enter student age: ");
    scanf("%d", &newStudent.nAge);
    printf("Enter student gender: ");
    scanf("%s", newStudent.cGender);

    DFF_vWriteStudentRecord(filename_studentrecord, &newStudent);
}
/*
*use this function to remove specific student record
*it ask the admin to enter the id then  it store it and use DDM_nReadStudentRecord() to read the record of that id
* id is correct , temp file will created and store all records except the record of that id
* after that the student file will deleted and temp file will take its name
*/

void ADD_vRemoveStudentRecord(const char *filename_studentrecord) {
    int targetId;
    printf("Enter the ID of the student record to remove: ");
    scanf("%d", &targetId);

    student_t student;
    if (!DDM_nReadStudentRecord(filename_studentrecord, targetId, &student)) {
        printf("Student record with ID %d not found\n", targetId);
        return;
    }

    FILE *file = fopen(filename_studentrecord, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error creating temporary file\n");
        fclose(file);
        return;
    }

    int recordFound = 0;
    while (fscanf(file, "%49[^,],%49[^,],%u,%f,%u,%9[^,\n]%*c", student.cName, student.cPassword, &student.nUnique_Id, &student.fTotal_Grade, &student.nAge, student.cGender) == 6) {
        if (student.nUnique_Id == targetId) {
            recordFound = 1;
        } else {
            fprintf(tempFile, "%s,%s,%u,%.2f,%u,%s\n", student.cName, student.cPassword, student.nUnique_Id, student.fTotal_Grade, student.nAge, student.cGender);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (!recordFound) {
        printf("Student record with ID %d not found\n", targetId);
        remove("temp.txt");
    } else {
        remove(filename_studentrecord);
        rename("temp.txt", filename_studentrecord);
        printf("Student record with ID %d removed successfully\n", targetId);
    }
}


/*
*use this function to view all student record in the file using DFF_vReadStudentRecords()
*/
void ADD_vViewStudentRecord(const char *filename_studentrecord) {
    printf("Viewing student records...\n");
    DFF_vReadStudentRecords(filename_studentrecord);
}
/*
* Use this function to view a specific student record based on the unique ID.
* It prompts the admin to enter the ID of the record to be viewed,
* then it retrieves and displays the information of that record.
*/
void ADD_vViewSpecificStudentRecord(const char *filename_studentrecord) {
    int targetId;
    printf("Enter the unique ID of the student record you want to view: ");
    scanf("%d", &targetId);

    student_t student;
    if (DDM_nReadStudentRecord(filename_studentrecord, targetId, &student)) {
        printf("Student Record:\n");
        printf("Name: %s\n", student.cName);
        printf("Password: %s\n", student.cPassword);
        printf("ID: %d\n", student.nUnique_Id);
        printf("Grade: %.2f\n", student.fTotal_Grade);
        printf("Age: %d\n", student.nAge);
        printf("Gender: %s\n", student.cGender);
    } else {
        printf("No student record found with the provided ID.\n");
    }
}
