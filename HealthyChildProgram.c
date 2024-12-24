/*
 @Purpose: Healthy Child Programming Task
 @Author: Elvar Noi Leistner
 @Creation date: 12/11/2024
 @Date of last modification: 14/11/2024
*/

#include <stdio.h>

int main() {
    // Variables
    int doctor_number;
    int child_data = 0, done_bmi = 0;   // Variables that make sure that data has been inserted and BMI calculated
    char selected_option;

    // Option a variables
    int child_age, child_height, child_weight;

    // Option b variables
    float child_weight_kg, child_height_meters, bmi;
    int next_consulting;
    float next_consulting_weight_kg, next_consulting_weight;

    // Option c variables
    float percentage_malnourished, percentage_normal, percentage_overweight;
    int number_malnourished = 0, number_normal = 0, number_overweight = 0, children_total = 0;

    // Ask user for their doctor number
    printf("Doctor number: ");
    scanf("%d", &doctor_number);

    // If statement to validate doctor number
    if (doctor_number > 100000 && doctor_number < 999999) {
        printf("Welcome to Healthy Child Program! (Dr. id: %d)\n\n", doctor_number);

        // Loop to validate the option chosen
        do {
            printf("a. Add child data | b. Calculate BMI | c. Statistics | d. Exit\n");
            printf("Select option: ");
            scanf(" %c", &selected_option);

            // Switch case for each case
            switch (selected_option) {
                // Case if user chose option a
                case 'a':
                case 'A':
                    // Loop asking for and making sure the age is between 0 and 18
                    do {
                        printf("Child's age: ");
                        scanf("%d", &child_age);

                        if (child_age >= 18 || child_age <= 0) {
                            printf("The patient is not a child. Enter the age again!\n");
                        }
                    } while (child_age >= 18 || child_age <= 0);

                    // Loop asking for and making sure the height is positive        
                    do {
                        printf("Enter height (cm): ");
                        scanf("%d", &child_height);

                        if (child_height <= 0) {
                            printf("The height must be a positive value!\n");
                        }
                    } while (child_height <= 0);

                    // Loop asking for and making sure the weight is positive
                    do {
                        printf("Enter weight (lb): ");
                        scanf("%d", &child_weight);

                        if (child_weight <= 0) {
                            printf("The weight must be a positive value!\n");
                        }
                    } while (child_weight <= 0);
                    printf("\n");

                    // Variable set to active to validate that data has been inserted
                    child_data = 1;
                    break;

                // Case if user chose option b
                case 'b':
                case 'B':
                    // If statement making sure that data was introduced previously
                    if (child_data == 1) {
                        // Calculation of weight in kg
                        child_weight_kg = child_weight / 2.2;
                        // Calculation of height in meters
                        child_height_meters = child_height / 100.0;
                        // Calculation of the BMI
                        bmi = child_weight_kg / (child_height_meters * child_height_meters);

                        // Variable confirming that BMI was calculated is set to active
                        done_bmi = 1;
                        printf("BMI: %.1f\n", bmi);

                        // If statement if the child is malnourished
                        if (bmi < 18.5) {
                            printf("This child must follow a nutrition plan!\n");

                            // Number of malnourished children is increased by one
                            number_malnourished++;
                            // Number of total children is increased by one
                            children_total++;

                            // Loop making sure the next consulting is in 20 weeks or less
                            do {
                                printf("Next consulting (weeks)? ");
                                scanf("%d", &next_consulting);

                                if (next_consulting < 0 || next_consulting > 20) {
                                    printf("ERROR! Must be less than 20 weeks.\n\n");
                                } else {
                                    // If statement separating the children above and below 7
                                    if (child_age < 7) {
                                        // Calculation of the weight the child (under 7yo) should have in the next consulting
                                        next_consulting_weight_kg = child_weight_kg + (next_consulting * (2.0 / 52));
                                    } else {
                                        // Calculation of the weight the child (over 7yo) should have in the next consulting
                                        next_consulting_weight_kg = child_weight_kg + (next_consulting * (2.4 / 52));
                                    }

                                    // Weight of the next consulting calculated in lbs
                                    next_consulting_weight = next_consulting_weight_kg * 2.2;
                                    printf("In %d weeks the child should weigh %.1f lb.\n\n", next_consulting, next_consulting_weight);
                                }
                            } while (next_consulting < 0 || next_consulting > 20);

                        // If statement if the child is normal
                        } else if (bmi >= 18.5 && bmi <= 24.9) {
                            printf("This child is at the right weight!\n\n");
                            // Number of normal children is increased by one
                            number_normal++;
                            // Number of total children is increased by one
                            children_total++;
                        // If statement if the child is overweight
                        } else {
                            printf("This child must perform a series of physical exercises!\n\n");
                            // Number of overweight children is increased by one
                            number_overweight++;
                            // Number of total children is increased by one
                            children_total++;
                        }
                    // Else condition if data hadn't been inserted previously
                    } else {
                        printf("BMI cannot be calculated until data is inserted.\n\n");
                    }
                    break;

                // Case if user chose c
                case 'c':
                case 'C':
                    // If statement making sure that data has been inserted and BMI calculated
                    if (child_data == 1 && done_bmi == 1) {
                        // Calculation of percentage of malnourished children
                        percentage_malnourished = (number_malnourished / children_total) * 100;
                        // Calculation of percentage of normal children
                        percentage_normal = (number_normal / children_total) * 100;
                        // Calculation of percentage of overweight children
                        percentage_overweight = (number_overweight / children_total) * 100;

                        printf("Child's statistics:\n");
                        printf("Malnourished => %d (%.0f%%)\n", number_malnourished, percentage_malnourished);
                        printf("Normal => %d (%.0f%%)\n", number_normal, percentage_normal);
                        printf("Overweight => %d (%.0f%%)\n", number_overweight, percentage_overweight);
                        printf("TOTAL ==== %d\n\n", children_total);
                    // Else display if the condition was not met
                    } else {
                        printf("Statistics cannot be displayed until BMI has been calculated.\n\n");
                    }
                    break;

                // Case if user chose d
                case 'd', 'D':
                    printf("See you in the next appointment!!\n");
                    break;

                //Default case
                default:
                    printf("Wrong option!\n");
            }
        } while (selected_option != 'd' && selected_option != 'D');
    // Else display if the condition was not met
    } else {
        printf("Invalid doctor number! (must have 6 digits)\n");
    }
    return 0;
}
