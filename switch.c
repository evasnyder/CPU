#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "run.h"

/** Program to calculate the area and perimeter of 
 * a rectangle using command line arguments
 */
void print_usage() {
    printf("Usage: rectangle [ap] -l num -b num\n");
}

int main(int argc, char *argv[]) {
    int opt= 0;
    int quantum;
    int stopTime;
    char *fileName;
    char *processType;
    int processTypeInt;
    int numCPU;
    int contextSwitch;
    //char* avgCPUTime;
    //int avgBurstTime;
    //int avgInterArrivalTime;
    //int avgIOTime;
    //int numProcesses;
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
                  
                 break;
             default: print_usage(); 
                 exit(EXIT_FAILURE);
        }
    }


     printf("Input file: %s\n",fileName); 
     printf("number of CPUs: %d\n",numCPU); 
     printf("Quantum: %d\n",quantum); 
     printf("Stop Time: %d\n",stopTime); 

     saveAvgValue(1, 500, 200, 1000, 10);

     runCPU(stopTime, numCPU, contextSwitch, quantum);

//      int i = 0;
//       const char *format = '%d';
//     fp = fopen(fileName, "r");
//      char  line[255];

    
//     while (fgets(line, sizeof(line), fp) != NULL)
//     {
//         //char val1[20] = strtok(line, ",");
//         const char* processType = strtok(line, " ");
//         const char* avgCPUTime = strtok(NULL, " ");
//         const char* avgBurstTime = strtok(NULL, " ");
//         const char* avgInterArrivalTime = strtok(NULL, " ");
//         const char* avgIOTime = strtok(NULL, " ");

//         printf("%s%s\n","Chosen process: ",processType  );
//         printf("%s%s\n","Chosen process cpu time: ",avgCPUTime );
//         printf("%s%s\n","Chosen process burst time:",avgBurstTime );
        
//     return 0;
// }
}