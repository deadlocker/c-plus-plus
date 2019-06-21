/**
 * Programmer               :       Rajesh Mani Poudel
 * Class                    :       Operating  Systems
 * Program Number           :       4     
 * Purpose                  :       This program will write a discrete event simulation to analyze different 
 *                                  CPU scheduling algorithms.  The process data will be read in from the 
 *                                  random number generator. It will implement the First-Come First-Served (FCFS), 
 *                                  Shortest Job First (SJF), Priority, and Round-Robin (RR) algorithms. It will create
 *                                  average runs of all the scheduling tasks
 * Due Date                 :       November 21, 2017
 **/
 
/**
 * C header libraries
 * */
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <time.h>  
#include <stdbool.h>
#define  size 4 //maximum process total, can be changed
#define  runTime 100 //runtime for priocess, can be changed
/**
 * structure Process
 * @data types int
 **/
struct Process {
    int brustTime;
    int waitTime;
    int turnAroundTime;
    int pid;
    int priority;
};

/**
 * function prototypes
 * @datatype int
 * @datatype array
 **/
void firstComeFirstServeScheduling(struct Process testArray[], float *awtFCFS, float *attFCFS);
void shortestJobFirstScheduling(struct Process testArray[], float *awtSJF, float *attSJF);
void priorityScheduling(struct Process testArray[], float *awtPS, float *attPS);
void roudRobinScheduling(struct Process testArray[], int, float *, float *);

/**
 * first come first serve scheduling function 
 * @datatype int, float
 * @datatype array
 * @return time
 **/
void firstComeFirstServeScheduling(struct Process testArray[], float *awtFCFS, float *attFCFS) {
    int i;
    float totalWaitTime = 0.0, totalTurnAroundTime = 0.0;
    testArray[0].waitTime = 0;
    
    for ( i = 1; i < size; i++ ) {
        testArray[i].waitTime = testArray[i].brustTime + testArray[i-1].waitTime;
    }
    
    for(i = 0; i < size; i++) {
        testArray[i].turnAroundTime = testArray[i].brustTime + testArray[i].waitTime;
    }
    
    for( i = 0; i < size; i++) {
        totalWaitTime += testArray[i].waitTime;
        totalTurnAroundTime += testArray[i].turnAroundTime;
    }
    
    *awtFCFS = totalWaitTime / size;
    *attFCFS = totalTurnAroundTime / size;
    printf("FCFS\t\t");
    printf("\t%f", totalWaitTime / size);
    printf("\t\t%f", totalTurnAroundTime / size);
    printf("\n");
}
/**
 * sorting brust time function 
 * @datatype int
 * @datatype array
 * @return sorted array
 **/
int compareBrustTime(const void *first, const void *second) {
    return (((struct Process*)first)->brustTime - ((struct Process*)second)->brustTime);
}
/**
 * shortest job first scheduling function 
 * @datatype int, float
 * @datatype array
 * @return time
 **/
void shortestJobFirstScheduling(struct Process testArray[], float *awtSJF, float *attSJF) {
    int i; 
    float totalWaitTime = 0.0, totalTurnAroundTime = 0.0;
    testArray[0].waitTime = 0;
    
    for ( i = 1; i < size; i++ ) {
        testArray[i].waitTime = testArray[i-1].brustTime + testArray[i-1].waitTime;
    }
    
    for(i = 0; i < size; i++) {
        testArray[i].turnAroundTime = testArray[i].brustTime + testArray[i].waitTime;
    }
    
    for( i = 0; i < size; i++) {
        totalWaitTime += testArray[i].waitTime;
        totalTurnAroundTime += testArray[i].turnAroundTime;
    }
    
    *awtSJF = totalWaitTime / size;
    *attSJF = totalTurnAroundTime / size;
    printf("SJF\t\t");
    printf("\t%f", totalWaitTime / size);
    printf("\t\t%f", totalTurnAroundTime / size);
    printf("\n");
}
/**
 * sorting priority function 
 * @datatype int
 * @datatype array
 * @return sorted array
 **/
int comparePriority(const void *first, const void *second) {
    return (((struct Process*)first)->priority < ((struct Process*)second)->priority);
}
/**
 * priority scheduling function 
 * @datatype int, float
 * @datatype array
 * @return time
 **/
void priorityScheduling(struct Process testArray[], float *awtPS, float *attPS) {
    int i, j; 
    float totalWaitTime = 0.0, totalTurnAroundTime = 0.0;
    testArray[0].waitTime = 0;
    
    for ( i = 1; i < size; i++ ) {
        for ( j = 0; j < i; j++ ) { 
            testArray[i].waitTime = testArray[i].brustTime + testArray[i].waitTime;
        }
    }
    
    for(i = 0; i < size; i++) {
        testArray[i].turnAroundTime = testArray[i].brustTime + testArray[i].waitTime;
    }
    
    for( i = 0; i < size; i++) {
        totalWaitTime += testArray[i].waitTime;
        totalTurnAroundTime += testArray[i].turnAroundTime;
    }
    
    *awtPS = totalWaitTime / size;
    *attPS = totalTurnAroundTime / size;
    
    printf("Priority\t");
    printf("\t%f", totalWaitTime / size);
    printf("\t\t%f", totalTurnAroundTime / size);
    printf("\n");
}
/**
 * round robin scheduling function 
 * @datatype int, float
 * @datatype array
 * @return time
 **/
void roudRobinScheduling(struct Process testArray[], int quantum, float *awtRR, float *attRR) {
    int i, currentTime = 0;
    float totalWaitTime = 0.0, totalTurnAroundTime = 0.0;
    struct Process copyBrustTime[size];
    
    for( i = 0; i < size; i++ ) {
        copyBrustTime[i].brustTime = testArray[i].brustTime;
    }
    
    copyBrustTime[0].waitTime = 0;
    for ( ;; ) {
        bool done = true;
        for ( i = 0; i < size; i++ ) {
            if ( copyBrustTime[i].brustTime > 0 ) {
                done = false;
                if ( copyBrustTime[i].brustTime > quantum ) {
                    currentTime += quantum;
                    copyBrustTime[i].brustTime -= quantum;
                } else {
                    currentTime += copyBrustTime[i].brustTime;
                    testArray[i].waitTime = currentTime - testArray[i].brustTime;
                    copyBrustTime[i].brustTime = 0;
                }
            }
        }
        if ( done == true ) 
            break;
    }
    
    for(i = 0; i < size; i++) {
        testArray[i].turnAroundTime = testArray[i].brustTime + testArray[i].waitTime;
    }
    
    for( i = 0; i < size; i++) {
        totalWaitTime += testArray[i].waitTime;
        totalTurnAroundTime += testArray[i].turnAroundTime;
    }
    
    *awtRR = totalWaitTime / size;
    *attRR = totalTurnAroundTime / size;
    printf("\t%f", totalWaitTime / size);
    printf("\t\t%f", totalTurnAroundTime / size);
    printf("\n");
}
/**
 * main function 
 * @datatype int, float
 * @datatype array
 * @return scheduling tasks
 **/
int main() {
    srand (time(NULL));
    struct Process testArray[size];
    struct Process tempArray[size];
    float awtFCFS = 0.0, awtSJF = 0.0, awtPS = 0.0, awtRR1 = 0.0, awtRR2 = 0.0;
    float attFCFS = 0.0, attSJF = 0.0, attPS = 0.0, attRR1 = 0.0, attRR2 = 0.0;
    float totalAwtFCFS = 0.0, totalAwtSJF = 0.0, totalAwtPS = 0.0, totalAwtRR1 = 0.0,  totalAttRR1 = 0.0;
    float totalAttFCFS = 0.0, totalAttSJF = 0.0, totalAttPS = 0.0, totalAwtRR2 = 0.0,  totalAttRR2 = 0.0;
    int i, j, quantum1 = 4, quantum2 = 8;

    for ( j = 0; j < runTime; j++) {
        for (i = 0; i < size; i++){
            testArray[i].brustTime = 1.0 + rand()%20;
            testArray[i].pid = i;
            testArray[i].priority = 0 +  rand()%7;
            testArray[i].turnAroundTime = 0 + rand()%20;
        }
        memcpy(&tempArray, &testArray, sizeof(testArray)); 
        printf("\t\t\t\tRun # %d\n", j);
        printf("\t\t\tAWt in seconds\t\tATT in seconds\n");
        firstComeFirstServeScheduling(tempArray, &awtFCFS, &attFCFS);
        totalAwtFCFS += awtFCFS / runTime;
        totalAttFCFS += attFCFS / runTime;
        qsort(tempArray, size, sizeof(int), compareBrustTime);
        shortestJobFirstScheduling(tempArray, &awtSJF, &attSJF);
        totalAwtSJF += awtSJF / runTime;
        totalAttSJF += attSJF / runTime;
        qsort(tempArray,size, sizeof(int), comparePriority);
        priorityScheduling(tempArray, &awtPS, &attPS);
        totalAwtPS += awtPS / runTime;
        totalAttPS += attPS / runTime;
        printf("RR q = 4\t");
        roudRobinScheduling(tempArray, quantum1, &awtRR1, &attRR1);
        totalAwtRR1 += awtRR1 / runTime;
        totalAttRR1 += attRR1 / runTime;
        printf("RR q = 8\t");
        roudRobinScheduling(tempArray, quantum2, &awtRR2, &attRR2);
        totalAwtRR2 += awtRR2 / runTime;
        totalAttRR2 += attRR2 / runTime;
    }
    printf("\n");
    printf("\t\t\tSummary of the %d runs with %d process\n", runTime, size);
    printf("\t\t\tAverage AWt in seconds\t\tAverage ATT in seconds\n");
    printf("FCFS\t\t\t");
    printf("%f\t\t\t", totalAwtFCFS);
    printf("%f\n", totalAttFCFS);
    printf("SJF\t\t\t");
    printf("%f\t\t\t", totalAwtSJF);
    printf("%f\n", totalAttSJF);
    printf("PS\t\t\t");
    printf("%f\t\t\t", totalAwtPS);
    printf("%f\n", totalAttPS);
    printf("RR q = %d\t\t", quantum1);
    printf("%f\t\t\t", totalAwtRR1);
    printf("%f\n", totalAttRR1);
    printf("RR q = %d\t\t", quantum2);
    printf("%f\t\t\t", totalAwtRR2);
    printf("%f\n", totalAttRR2);
    return 0;
}
