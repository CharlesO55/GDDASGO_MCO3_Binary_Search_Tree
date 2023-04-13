#pragma once

/*  
    Resets the csv record file: record.csv
*/
const void resetCSV(){
    FILE *fp = fopen("Results/record.csv", "w");
    fprintf(fp, "DATA SET SIZE, MODE, AVERAGE TIME IN MS, AVERAGE COUNT\n");
    fclose(fp);
}



/*
    Appends additional values into a new line in record.csv

    @param char str_AlgoName        Name of the algorithm used
    @param int n_Size               Data set size
    @param double d_AverageTime     Average time
    @param double d_AverageCount    Average count
*/
const void recordCSV(int n_Size, char str_AlgoName[20], double d_AverageTime, double d_AverageCount){
    FILE *fp = fopen("Results/record.csv", "a");

    if (fp == NULL){
        printf("[ERROR]: CSV NOT FOUND\n");
        return;
    }
    fprintf(fp, "%d, %s, %f, %f\n", n_Size, str_AlgoName, d_AverageTime, d_AverageCount);
    fclose(fp);
}