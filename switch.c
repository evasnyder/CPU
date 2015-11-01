#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include "run.h"



//main method
int main(int argc, char *argv[]) {
    int opt= 0;
    int quantum;
    int stopTime;
    char *fileName;
    char *processType;
    int processTypeInt;
    int numCPU;
    int contextSwitch;
    enum { MAXLINES = 100 };
    int size = 100;
    char* avgCPUTime;
    int avgBurstTime;
    int avgInterArrivalTime;
    int avgIOTime;
    int numProcesses;
    FILE *fp;


    //Specifying the expected options
    //The two options l and b expect numbers as argument
    static struct option long_options[] = {
        {"fileName",    required_argument, 0,  'f' },
        {"numCPU",      required_argument, 0,  'c' },
        {"quantum", required_argument,       0,  'q' },
        {"simulationStopTime",   required_argument, 0,  't' },
        {"switchTime", required_argument,       0,  'w' },
        {"noIOFaults",   no_argument, 0,  'n' },
        {"verbose", no_argument,       0,  'v' },
        {"batch",   no_argument, 0,  'b' },
        {"help",   no_argument, 0,  'h' },
        {0,           0,                 0,  0   }
    };

    //switch statements for the different cases
    int long_index =0;
    while ((opt = getopt_long(argc, argv,"apf:b:c:q:t:w:n:v:b:h:",
                   long_options, &long_index )) != -1) {
        switch (opt) {
            case 'f' : fileName = optarg;
              printf("fileName: %s\n",optarg);
                 break;
             case 'c' : numCPU = atoi(optarg);
                 break;
             case 'q' : quantum = atoi(optarg);
                 break;
             case 't' : stopTime = atoi(optarg);
                 break;
              case 'w' : contextSwitch = atoi(optarg); //get context switch cost
                 break;
              case 'n' : //disable I/O faults
                 break;
              case 'v' : //enable verbose output
                 break;
              case 'b' : //display parsaeble batch output
                 break;
              case 'h' : //display help message
                printf("%s\n",  "f : enter input filen name\nc : enter number of CPUs\nq : enter quantum\nt : enter simulation stop time\nw : context switch cost\nn : disable I/O faults\nv : enable verbose output\nb : disable parseable batch output\nh : display help message");

                 break;

                 exit(EXIT_FAILURE);
        }
    }


    //read input file if an argument is given
     if (fileName != NULL){


     int i, j;
    fp = fopen(fileName, "r");
     char  line[255];
     char *eptr;
     long result;
     char value[10];
     int n1, n2, n3, n4;


     //array to store each line 
    char lines[MAXLINES][size];
     

    //save the contents of the file in an array
    while (i < MAXLINES && fgets(lines[i], sizeof(lines[0]), fp))
    {
        lines[i][strlen(lines[i])] = '\0';
        i = i + 1;
    }

    //close file after reading it
    fclose(fp);

    //srand(time(0));
    int k = (j+1) % i;
    int hello = i; 

    //total number of processes specified
    numProcesses = atoi(lines[0]);

    //go through all different types of processes and run the cpu scheduler
    for (int m = 1; m < i; ++m)
    {

    //tokenize
    processType = strtok(lines[m], " ");
    avgCPUTime = atoi(strtok(NULL, " "));
    avgBurstTime = atoi(strtok(NULL, " "));
    avgInterArrivalTime = atoi(strtok(NULL, " "));
    avgIOTime= atoi(strtok(NULL, " "));

    //set int representation of process type 
    if (strcmp(processType, "batch") == 0)
    {
        processTypeInt = 1;
    }

    else if (strcmp(processType, "interactive") == 0)
    {
        processTypeInt = 2;
    }


    //save the average values and then run the cpu scheduler
    saveAvgValue(processTypeInt, avgCPUTime, avgBurstTime, avgInterArrivalTime, avgIOTime);
    runCPU(stopTime, numCPU, contextSwitch, quantum); 
}


}


    return 0;
}
