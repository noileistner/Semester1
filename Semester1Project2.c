/***********************************************
*
* @Purpose: Project 2 of semester 1
* @Author: Elvar Nói Leistner
* @Creation date: 17/12/2024
* @Date of last modification: 
*
************************************************/

#include <stdio.h>
#include <string.h>

#define DASHES 65
#define MAX_DOCTORS 30
#define MAX_INPUT_LENGTH 100
#define MAX_HOSPITAL_VISITS 50


struct Doctor {
    int doctor_id;
    int vacation_month;
};

struct Visit {
    char name[100];
    int doctor_id;
    char month[20];
    int num_of_visits;
    int day;
};

int charToInt(char character[]) {
    int i=0;
    int result=0;

    while (character[i] != '\0') {
        result = (result*10) + (character[i] - '0');
        i++;
    }

    return result;
}

int extractIdFromInput(char input[]) {
    int id_length = 6;
    char id[id_length];
    strncpy(id, input, id_length);
    return charToInt(id);
}

void welcomeMessage() {
    int i;

    for (i=1; i<DASHES; i++) {
        printf("-");
    }

    printf("\n\t\tWELCOME TO LSHEALTH MANAGER\n");

    for (i=1; i<DASHES; i++) {
        printf("-");
    }
    printf("\n");
}

int validateDoctorCodeFormat(char id_month[]) {
    int i=0, valid = 1;
    int dash_count=0, id_digits=0;

    while (id_month[i] != '\0') {
        if (id_month[i] == '-') {
            dash_count++;
        }
        if (id_month[i] != '-' && dash_count == 0) {
            id_digits++;
        }
        i++;
    }

    if (id_digits != 6 && dash_count == 1) {
        printf("ERROR: ID must have 6 digits.\n");
        valid = 0;
    }

    if (strlen(id_month) != 9 || dash_count != 1 || id_month[6] != '-') {
        valid = 0;
    }

    if (id_month[0] == '0') {
        printf("ERROR: ID cannot begin with 0.\n");
        valid = 0;
    } else {
        if (id_month[i-1] == '-') {
            printf("ERROR: Wrong format. Should be <ID>-<month>.\n");
        } else {
            if ((id_month[7] == '\0' || id_month[8] == '\0' || id_month[9] != '\0') && dash_count == 1 && id_digits == 6) {
                printf("ERROR: Wrong month format. Please use two digits.\n");
                valid = 0;
            }
        }
    }

    for (i = 0; i < 6; i++) {
        if (id_month[i] < '0' || id_month[i] > '9') {
            valid = 0;
        }
    }

    if (!valid && dash_count != 1) {
        printf("ERROR: Wrong format. Should be <ID>-<month>.\n");
    }
    return valid;
}

int addDoctor(struct Doctor doctors[], int num_doctors) {
    int i=0, is_valid_input=0;
    int month_digits[2];
    int month=0;
    int length=0;
    int dash_count=0, id_digits=0;
    int repeated_id=0;

    char id_month[100];
    char doctor_id[7];


    while (!is_valid_input) {
        printf("Enter ID and vacation month (ex. 123456-06) : ");
        
        if (fgets(id_month, 100, stdin)) {
            length = strlen(id_month);

            if (length > 0 && id_month[length - 1] == '\n') {
                id_month[length - 1] = '\0';
            }
            
            is_valid_input = validateDoctorCodeFormat(id_month);

            if (is_valid_input) {
                strncpy(doctor_id, id_month, 6);
                doctor_id[6] = '\0';

                month = (id_month[7] - '0') * 10 + (id_month[8] - '0');

                if (month < 1 || month > 12) {
                    printf("ERROR: Wrong month value. It must be between 01 and 12.\n");
                    is_valid_input = 0;
                }
                else {
                    repeated_id=0;
                    for (i=0; i<num_doctors; i++) {
                        if (strcmp(doctors[i].doctor_id, doctor_id) == 0) {
                            repeated_id=1;
                        }
                    }

                    if (repeated_id) {
                        printf("Failed to add doctor: Doctor already exists.\n");
                    }
                    else {
                        strcpy(doctors[num_doctors].doctor_id, doctor_id);
                        doctors[num_doctors].vacation_month = month;
                        num_doctors++;
                        printf("Doctor added successfully.\n");
                    }
                }
            }
        }
    }
    return num_doctors;
}

void listDoctors(struct Doctor doctors[], int num_doctors) {
    int i;
    char month[20];

    if (num_doctors == 0) {
        printf("No doctors exist in the system yet.\n");
    }
    else {
        printf("Doctors List (total of %d):\n", num_doctors);
        for (i=0; i < num_doctors; i++) {
            struct Doctor doctor = doctors[i];

            switch (doctor.vacation_month) {
                case 1:
                    strcpy(month, "January");
                    break;
                case 2:
                    strcpy(month, "February");
                    break;
                case 3:
                    strcpy(month, "March");
                    break;
                case 4:
                    strcpy(month, "April");
                    break;
                case 5:
                    strcpy(month, "May");
                    break;
                case 6:
                    strcpy(month, "June");
                    break;
                case 7:
                    strcpy(month, "July");
                    break;
                case 8:
                    strcpy(month, "August");
                    break;
                case 9:
                    strcpy(month, "September");
                    break;
                case 10:
                    strcpy(month, "October");
                    break;
                case 11:
                    strcpy(month, "November");
                    break;
                case 12:
                    strcpy(month, "December");
                    break;
                default:
                    strcpy(month, "Invalid Month");
                    break;
            }
            printf("\t%d) Doctor ID: %s, Vacation Month: %s\n", i+1, doctor.doctor_id, month);
        }
    }
}

int validateDoctorIDFormat(char doctor_id[]) {
    int i=0, valid = 1;
    int id_digits=0;

    while (doctor_id[i] != '\0') {
        if (doctor_id[i] == '-') {
            valid=0;
        }
        if (doctor_id[i] != '-') {
            id_digits++;
        }
        i++;
    }

    if (id_digits != 6) {
        printf("ERROR: ID must have 6 digits.\n");
        valid = 0;
    }

    if (doctor_id[0] == '0') {
        printf("ERROR: ID cannot begin with 0.\n");
        valid = 0;
    } else {
        if (doctor_id[i-1] == '-') {
            valid=0;
        }
    }

    for (i = 0; i < 6; i++) {
        if (doctor_id[i] < '0' || doctor_id[i] > '9') {
            valid = 0;
        }
    }
    return valid;
}

int promptDoctorId(int num_doctors) {
    int i=0;
    int is_valid_id=0, length=0;
    int id=0;

    char doctor_id[8];

    if (num_doctors == 0) {
        printf("No doctors exist in the system yet.\n");
    }
    else {
        while (!is_valid_id) {
            printf("Enter the ID of the doctor to remove: ");
            if (fgets(doctor_id, 8, stdin)) {
                length = strlen(doctor_id);

                if (length > 0 && doctor_id[length - 1] == '\n') {
                    doctor_id[length - 1] = '\0';
                }
                
                is_valid_id = validateDoctorIDFormat(doctor_id);
            }
        }
    }

    while (doctor_id[i] != '\0') {
        id = (id * 10) + (doctor_id[i] - '0');
        i++;
    }

    return id;
}

int removeDoctor(struct Doctor doctors[], int num_doctors, int doctor_id) {
    int i, j, k=0;
    
    int removed_doctor=0;

    for (i=0; i<num_doctors; i++) {

        if (doctors[i].doctor_id == doctor_id) {
            for (j = i; j < num_doctors - 1; j++) {
                doctors[j] = doctors[j + 1];
            }
            num_doctors--;
            printf("Doctor removed successfully.\n");
            removed_doctor=1;
        }
    }
    if (!removed_doctor) {
        printf("Failed to remove doctor: Doctor does not exist.\n");
    }
    return num_doctors;
}

int removeVisitsForDoctor(int doctor_id, struct Visit visits[], int num_visits) {
    int i=0, k=0, j;

    while (k < num_visits) {
        if (visits[i].doctor_id == doctor_id) {
            for (j = k; j < num_visits - 1; j++) {
                visits[j] = visits[j + 1];
            }
            num_visits--;
        }
        else {
            k++;
        }
    }
    return num_visits;
}

int validateVisitNameFormat(char name[]) {
    int valid=1, valid_characters=1;
    int i=0;

    if (name[0] == '\n' || name[0] == '\0') {
        printf("ERROR: Name cannot be empty.\n");
        valid=0;
    }

    while (name[i] != '\0') {
        if (!((name[i] >= 'a' && name[i] <= 'z') || (name[i] >= 'A' && name[i] <= 'Z'))) {
            valid_characters=0;
            valid=0;
        }
        i++;
    }

    if (!valid_characters) {
        printf("ERROR: Name can only contain letters.\n");
    }

    return valid;
}

int validateVisitCodeFormat(char id_month_day[]) {
    int i=0, valid=1;
    int dash_count=0, id_digits=0;

    while (id_month_day[i] != '\0') {
        if (id_month_day[i] == '-') {
            dash_count++;
        }
        if (id_month_day[i] != '-' && dash_count == 0) {
            id_digits++;
        }
        i++;
    }

    if (dash_count != 2 || id_month_day[6] != '-' || id_month_day[9] != '-') {
        valid=0;
    }

    if (id_month_day[0] == '0') {
        printf("ERROR: ID cannot begin with 0.\n");
        valid=0;
    } else {
        if (id_month_day[i-1] == '-') {
            printf("ERROR: Wrong format. Should be <ID>-<month>-<day>.\n");
        } else {
            if ((id_month_day[7] < '0' || id_month_day[7] > '9' || id_month_day[8] < '0' || id_month_day[8] > '9') && dash_count == 2 && id_digits == 6) {
                printf("ERROR: Wrong month format. Please use two digits.\n");
                valid=0;
            } else {
                if ((id_month_day[10] == '\0' || id_month_day[11] == '\0' || id_month_day[12] != '\0') && dash_count == 2 && id_digits == 6 && !(id_month_day[7] == '0' && id_month_day[8] == '0')) {
                    printf("ERROR: Wrong day format. Please use two digits.\n");
                    valid = 0;
                }
            }
        }
    }

    if (id_digits != 6 && dash_count == 2) {
        printf("ERROR: ID must have 6 digits.\n");
        valid = 0;
    }

    if (!valid && dash_count != 2) {
        printf("ERROR: Wrong format. Should be <ID>-<month>-<day>.\n");
    }

    return valid;
}

int addVisit(struct Visit visits[], struct Doctor doctors[], int num_visits, int num_doctors) {
    int i;
    int is_valid_name=0, is_valid_code=0;
    int length_name=0, length_code=0;
    int month=0, day=0;
    int repeated_id=0;
    int visit_added=0;

    char visit_name[100];
    char id_month_day[100];
    int doctor_id;
    char month_in_str[30];

    while (!is_valid_name) {
        printf("Enter your name: ");

        if (fgets(visit_name, 100, stdin)) {
            length_name = strlen(visit_name);

            if (length_name > 0 && visit_name[length_name - 1] == '\n') {
                visit_name[length_name - 1] = '\0';
            }

            is_valid_name = validateVisitNameFormat(visit_name);
        }

        while (is_valid_name && !is_valid_code) {
            printf("Enter doctor ID, month and day of visit (ex. 123456-06-27): ");

            if (fgets(id_month_day, 100, stdin)) {
                length_code = strlen(id_month_day);

                if (length_code > 0 && id_month_day[length_code - 1] == '\n') {
                    id_month_day[length_code - 1] = '\0';
                }

                is_valid_code = validateVisitCodeFormat(id_month_day);

                if (is_valid_code) {
                    doctor_id = extractIdFromInput(id_month_day);

                    month = (id_month_day[7] - '0') * 10 + (id_month_day[8] - '0');
                    day = (id_month_day[10] - '0') * 10 + (id_month_day[11] - '0');

                    if (month < 1 || month > 12) {
                        printf("ERROR: Wrong month value. It must be between 01 and 12.\n");
                        is_valid_code = 0;
                    }
                    else {
                        if ((day < 0 || day > 30) && !(id_month_day[7] == '0' && id_month_day[8] == '0')) {
                            printf("ERROR: Wrong day value. It must be between 01 and 30.\n");
                            is_valid_code = 0;
                        }
                    }
                }
            }
        }
    }

    switch (month) {
        case 1:
            strcpy(month_in_str, "January");
            break;
        case 2:
            strcpy(month_in_str, "February");
            break;
        case 3:
            strcpy(month_in_str, "March");
            break;
        case 4:
            strcpy(month_in_str, "April");
            break;
        case 5:
            strcpy(month_in_str, "May");
            break;
        case 6:
            strcpy(month_in_str, "June");
            break;
        case 7:
            strcpy(month_in_str, "July");
            break;
        case 8:
            strcpy(month_in_str, "August");
            break;
        case 9:
            strcpy(month_in_str, "September");
            break;
        case 10:
            strcpy(month_in_str, "October");
            break;
        case 11:
            strcpy(month_in_str, "November");
            break;
        case 12:
            strcpy(month_in_str, "December");
            break;
        default:
            strcpy(month_in_str, "Invalid Month");
            break;
    }

    visit_added=0;
    for (i=0; i<num_doctors && !visit_added; i++) {
        if (doctors[i].doctor_id == doctor_id) {
            printf("Doctor %s not found.\n", doctor_id);
        }
        else {
            if (strcmp(doctors[i].doctor_id, doctor_id) == 0) {
                if (doctors[i].vacation_month == month) {
                    printf("Doctor is on vacation in %s.\n", month_in_str);
                }
                else {
                    strcpy(visits[num_visits].name, visit_name);
                    strcpy(visits[num_visits].doctor_id, doctor_id);
                    strcpy(visits[num_visits].month, month_in_str);
                    visits[num_visits].day = day;
                    visits[num_visits].num_of_visits++;
                    num_visits++;
                    printf("Visit added successfully.\n");
                    visit_added=1;
                }
            }
        }
    }

    return num_visits;
}

void listVisits(struct Visit visits[], struct Doctor doctors[], int num_visits) {
    int i, j=0;
    int is_valid_name=0;
    int length_name=0;

    char visit_name[100];

    while (!is_valid_name) {
        printf("Enter your name: ");

        if (fgets(visit_name, 100, stdin)) {
            length_name = strlen(visit_name);

            if (length_name > 0 && visit_name[length_name - 1] == '\n') {
                visit_name[length_name - 1] = '\0';
            }

            is_valid_name = validateVisitNameFormat(visit_name);
        }
    }

    if (is_valid_name) {
        for (i=0; i<num_visits; i++) {
            if (strcmp(visits[i].name, visit_name) == 0) {
                j++;
                printf("\t%d. Doctor ID: %s --- Date: %d of %s\n", j, visits[i].doctor_id, visits[i].day, visits[i].month);
            }
        }

        if (j==0) {
            printf("No visits have been found for patient %s.\n", visit_name);
        }
    }
}

int cancelVisit(struct Visit visits[], struct Doctor doctors[], int num_visits, int num_doctors) {
    int i, j=0;
    int is_valid_name=0;
    int length=0;
    int visit_indices[num_visits];
    int choice=0;
    int index_to_remove=0;
    int is_valid_number=0;

    char visit_name[100];
    char visit_to_cancel[100];

    while (!is_valid_name) {
        printf("Enter your name: ");

        if (fgets(visit_name, 100, stdin)) {
            length = strlen(visit_name);

            if (length > 0 && visit_name[length - 1] == '\n') {
                visit_name[length - 1] = '\0';
            }

            is_valid_name = validateVisitNameFormat(visit_name);
        }
    }

    if (is_valid_name) {
        for (i=0; i<num_visits; i++) {
            if (strcmp(visits[i].name, visit_name) == 0) {
                j++;
                visit_indices[j - 1] = i;
                printf("\t%d. Doctor ID: %s --- Date: %d of %s\n", j, visits[i].doctor_id, visits[i].day, visits[i].month);
            }
        }

        if (j==0) {
            printf("No visits have been found for patient %s.\n", visit_name);
        }
        else {
            j++;
            printf("\t%d. Back\n\n", j);

            while (!is_valid_number) {
                printf("Enter the number of the visit to cancel: ");
                if (fgets(visit_to_cancel, 100, stdin)) {
                    length = strlen(visit_to_cancel);

                    if (length > 0 && visit_to_cancel[length - 1] == '\n') {
                        visit_to_cancel[length - 1] = '\0';
                    }
                    
                    choice = (visit_to_cancel[0] - '0');

                    if (choice == j) {
                        is_valid_number=1;
                    }
                    else {
                        if (choice > 0 && choice < j) {
                            index_to_remove = visit_indices[choice - 1];

                            for (i = index_to_remove; i < num_visits - 1; i++) {
                                visits[i] = visits[i + 1];
                            }
                            num_visits--;
                            printf("Visit cancelled successfully.\n");
                            is_valid_number=1;
                        }
                        else {
                            printf("ERROR: Invalid visit number.\n");
                            is_valid_number=0;
                        }
                    }
                }
            }
        }
    }

    return num_visits;
}

int main() {
    char command[100];
    int is_valid_input=1;
    int command_length=0;
    int num_doctors=0, num_visits=0;
    int doctor_id=0;

    struct Doctor doctors[MAX_DOCTORS];
    struct Visit visits[MAX_HOSPITAL_VISITS];

    welcomeMessage();

    while (is_valid_input) {
        printf("admin@LSHealth> ");
        fgets(command, 100, stdin);

        command_length = strlen(command);

        if (command_length > 0 && command[command_length - 1] == '\n') {
            command[command_length - 1] = '\0';
        }

        if (strcmp(command, "add doctor") == 0) {
            if (num_doctors < MAX_DOCTORS) {
                num_doctors = addDoctor(doctors, num_doctors);
            }
            else {
                printf("Maximum number of doctors reached.\n");
            }
        }
        else {
            if (strcmp(command, "list doctors") == 0) {
                listDoctors(doctors, num_doctors);
            }
            else {
                if (strcmp(command, "remove doctor") == 0) {
                    doctor_id = promptDoctorId(num_doctors);
                    num_doctors = removeDoctor(doctors, num_doctors, doctor_id);
                    num_visits = removeVisitsForDoctor(doctor_id, visits, num_visits);
                } 
                else {
                    if (strcmp(command, "add visit") == 0) {
                        if (num_visits < MAX_HOSPITAL_VISITS) {
                            if (num_doctors == 0) {
                                printf("No doctors exist in the system yet.\n");
                            } else {
                                num_visits = addVisit(visits, doctors, num_visits, num_doctors);
                            }
                        }
                        else {
                            printf("Maximum number of visits reached.\n");
                        }
                    } 
                    else {
                        if (strcmp(command, "list visits") == 0) {
                            if (num_visits == 0) {
                                printf("No visits exist in the system yet.\n");
                            }
                            else {
                                listVisits(visits, doctors, num_visits);
                            }
                        } 
                        else {
                            if (strcmp(command, "cancel visit") == 0) {
                                num_visits = cancelVisit(visits, doctors, num_visits, num_doctors);
                            } 
                            else {
                                if (strcmp(command, "exit") == 0) {
                                    is_valid_input = 1;
                                } 
                                else {
                                    is_valid_input = 0;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}