#ifndef ADMIN_H
#define ADMIN_H
#include "memory_management.h"
#include "data_management.h"
#include "file_acess.h"


/*
 * FILE: admin.h
 * AUTHOR: Yasmine Elmenofy
 * BRIEF: Header file for the module Module that
 *contain function prototypes
 * DATA: 8/05/2024
 */

void ADD_vChangeAdminPassword(const char *filename_password);
void ADD_vEditStudentRecords(const char *filename_studentrecord);
void ADD_vAddNewStudentRecord(const char *filename_studentrecord);
void ADD_vRemoveStudentRecord(const char *filename_studentrecord);
void ADD_vViewStudentRecord(const char *filename_studentrecord);
void ADD_vViewSpecificStudentRecord(const char *filename_studentrecord);



#endif /* ADMIN_H */
