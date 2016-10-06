/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: TylerShipman
 *
 * Created on September 22, 2016, 10:08 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

double mean(int values[], int size);        //Finds the mean of the input file
int findMax(int values[], int size);        //Finds the max of the input file

/*
 * 
 */
int main(int argc, char** argv) {
    int userChoice;                         //stores the number associated with the input file to save other files appropriately
                 
    FILE* fp_r;                             //points to input     
    FILE* fp_w;
    FILE* fp_Stats;                         //points to new file stats
    FILE* fp_Centered;                      //points to new file centered
    FILE* fp_Normalized;                    //points to new file normalized
    FILE* fp_Scaled;                        //points to new file scaled
    FILE* fp_Offset;                        //points to new file offset
     
    //All file names based on above variables
    char inputFileName[80];                 
    char outputFileName[80];
    char outputStatsFile[80];
    char outputCentered[80];
    char outputNormalized[80];
    char outputScaled[80];
    char outputOffset[80];
    char rename[80];
    int i = 0;
    int sizeOfFile;
    int maxValue;
    double meanValue;
    int fileMax = 0;
    double scaleFactor;
    double offsetFactor;
    int counter;


    int fileValues[sizeOfFile];             //Saves input file values
    

    //Goes through all args to see if -r exists
    for(counter = 1; counter < argc; counter++){
     if (strcmp(argv[counter], "-r") == 0) {

            
            sprintf(rename, "%s", argv[counter + 1]);
            
            

        }   
    }

    
    //goes through each arg again to create necessary files
    for (counter = 1; counter < argc; counter++) {

        if (strcmp(argv[counter], "-n") == 0) {

            userChoice = atoi(argv[counter + 1]);


            if (userChoice < 10) {
                sprintf(inputFileName, "Raw_data_0%d.txt", userChoice);

            } else {
                sprintf(inputFileName, "Raw_data_%d.txt", userChoice);
            }
            fp_r = fopen(inputFileName, "r");
            if (!fp_r) {
                printf("Error opening input file.");
                return 0;
            }
            fscanf(fp_r, "%d %d", &sizeOfFile, &maxValue);

            for (i = 0; i < sizeOfFile; i++) {

                fscanf(fp_r, "%d", &fileValues[i]);

            }

            for (i = 0; i < sizeOfFile; i++) {

                printf("%d\n", fileValues[i]);

            }
            meanValue = mean(fileValues, sizeOfFile);
            fileMax = findMax(fileValues, sizeOfFile);

            fclose(fp_r);
            
            
        }

        else if (strcmp(argv[counter], "-o") == 0) {
            if (userChoice < 10) {
                sprintf(outputOffset, "%s_Offset_0%d.txt", rename, userChoice);

            } else {
                sprintf(outputOffset, "%s_Offset_%d.txt", rename, userChoice);
            }
            fp_Offset = fopen(outputOffset, "ab+");

            if (!fp_Offset) {
                printf("Error creating Offset file.");
                return 0;
            }
            offsetFactor = strtod(argv[counter + 1], NULL);

            for (i = 0; i < sizeOfFile; i++) {

                fprintf(fp_Offset, "%lf\n", ((double) fileValues[i] + offsetFactor));
                printf("%lf\n", ((double) fileValues[i] + offsetFactor));
            }

            fclose(fp_Offset);

        }
        else if (strcmp(argv[counter], "-s") == 0) {
            if (userChoice < 10) {
                sprintf(outputScaled, "%s_Scaled_0%d.txt", rename, userChoice);

            } else {
                sprintf(outputScaled, "%s_Scaled_%d.txt",rename, userChoice);
            }

            fp_Scaled = fopen(outputScaled, "ab+");

            if (!fp_Scaled) {
                printf("Error creating Scaled file.");
                return 0;
            }

            scaleFactor = strtod(argv[counter + 1], NULL);

            for (i = 0; i < sizeOfFile; i++) {

                fprintf(fp_Scaled, "%lf\n", ((double) fileValues[i] * scaleFactor));
                printf("%lf\n", ((double) fileValues[i] * scaleFactor));
            }
            fclose(fp_Scaled);

        }
        else if (strcmp(argv[counter], "-S") == 0) {

            if (userChoice < 10) {
                sprintf(outputStatsFile, "%s_Statistics_0%d.txt", rename, userChoice);

            } else {
                sprintf(outputStatsFile, "%s_Statistics_%d.txt",rename, userChoice);
            }


            fp_Stats = fopen(outputStatsFile, "ab+");

            if (!fp_Stats) {
                printf("Error creating Stats file.");
                return 0;
            }

            fprintf(fp_Stats, "%d %lf", fileMax, meanValue);

            fclose(fp_Stats);

        }
        else if (strcmp(argv[counter], "-C") == 0) {

            if (userChoice < 10) {

                sprintf(outputCentered, "%s_Centered_0%d.txt", rename, userChoice);

            } else {

                sprintf(outputCentered, "%s_Centered_%d.txt", rename, userChoice);

            }
            fp_Centered = fopen(outputCentered, "ab+");
            if (!fp_Centered) {
                printf("Error creating Centered file.");
                return 0;
            }

            for (i = 0; i < sizeOfFile; i++) {

                fprintf(fp_Centered, "%lf\n", ((double) fileValues[i] - meanValue));
                printf("%lf\n", ((double) fileValues[i] - meanValue));
            }
            fclose(fp_Centered);
        }
        else if (strcmp(argv[counter], "-N") == 0) {
            if (userChoice < 10) {

                sprintf(outputNormalized, "%s_Normalized_0%d.txt", rename, userChoice);

            } else {

                sprintf(outputNormalized, "%s_Normalized_%d.txt", rename, userChoice);

            }

            fp_Normalized = fopen(outputNormalized, "ab+");
            if (!fp_Normalized) {
                printf("Error creating Normalized file.");
                return 0;
            }
            for (i = 0; i < sizeOfFile; i++) {

                fprintf(fp_Normalized, "%lf\n", ((double) fileValues[i] / (double) maxValue));
                printf("%lf\n", ((double) fileValues[i] / (double) maxValue));
            }
            fclose(fp_Normalized);

        }
        
        else if (strcmp(argv[counter], "-h") == 0) {

            printf("\n\nHELP MENU\n\nTo indicate which file to open, enter '-n' followed by a space and a number from 1 to 11.\n");
            printf("To indicate an offset value, enter '-o' followed by a space and a number to offset the data by.\n");
            printf("To indicate a scale factor, enter '-s' followed by a space and a number to scale the data by.\n");
            printf("To print the data statistics, enter '-S'.\n");
            printf("To center the data, enter '-C'.\n");
            printf("To normalize the data, enter '-N'.\n");
            printf("To rename the data file, enter '-r' followed by a space and the name you would like to rename it to (Name must NOT contain spaces).\n");
            printf("To return to the help menu, enter '-h'.\n\n");

            return 0;

        }
        //else if(!isdigit(arg))
           


    }

    return (EXIT_SUCCESS);

}

double mean(int values[], int size) {
    int i = 0;
    double sum = 0;
    double average = 0;
    for (i = 0; i < size; i++) {

        sum += (double) values[i];

    }

    average = sum / (double) size;

    return average;

}

int findMax(int values[], int size) {

    int maximum = values[0];
    int i = 0;
    for (i = 1; i < size; i++) {

        if (maximum < values[i]) {
            maximum = values[i];
        }
    }

    return maximum;


}