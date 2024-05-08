#include <stdio.h>
#include <stdlib.h>
#include "admin.h"
#include "memory_management.h"
#include "data_management.h"
#include "file_acess.h"


void adminMenu(const char *filename_studentrecord, const char *filename_password) {


    int choice;
    do {
        printf("\nAdmin Menu:\n");
        printf("1. Change Admin Password\n");
        printf("2. Edit Student Records\n");
        printf("3. Add New Student Record\n");
        printf("4. Remove Student Record\n");
        printf("5. View Student Records\n");
        printf("6. View Specific Student Record\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                ADD_vChangeAdminPassword(filename_password);
                break;
            case 2:
                ADD_vEditStudentRecords(filename_studentrecord);
                break;
            case 3:
                ADD_vAddNewStudentRecord(filename_studentrecord);
                break;
            case 4:
                ADD_vRemoveStudentRecord(filename_studentrecord);
                break;
            case 5:
                ADD_vViewStudentRecord(filename_studentrecord);
                break;
            case 6:
                ADD_vViewSpecificStudentRecord(filename_studentrecord);
                break;
                case 7:
                printf("Exiting Admin Menu...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 7);
}

int main() {
    const char *filename_studentrecord = "student_data.csv";
    const char *filename_password = "admin_password.csv";

    adminMenu(filename_studentrecord, filename_password);

    return 0;
}

