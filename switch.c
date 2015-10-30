#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

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
    int numCPU;
    FILE *fp;


    //Specifying the expected options
    //The two options l and b expect numbers as argument
    static struct option long_options[] = {
        {"fileName",    required_argument, 0,  'f' },
        {"numCPU",      required_argument, 0,  'c' },
        {"quantum", required_argument,       0,  'q' },
        {"simulationStopTime",   required_argument, 0,  't' },
        {"switchTime", no_argument,       0,  'q' },
        {"noIOFaults",   no_argument, 0,  't' },
        {"verbose", no_argument,       0,  'q' },
        {"batch",   no_argument, 0,  't' },
        {"help",   no_argument, 0,  't' },
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
              case 'w' : //get context switch cost
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


     printf("Area: %s\n",fileName); 
     printf("CPU: %d\n",numCPU); 
     printf("Quantum: %d\n",quantum); 
     printf("StopTime: %d\n",stopTime); 

    fp = fopen(fileName, "r");
     
    char s1[200],*p;
    while (fgets(s1, 200, fp))
    {

while (fgets(s1, 200, fp))
{

    p=strtok(s1, ";\n");

    do
    {
        printf ("%s\n",p);
    }
    while(p=strtok(NULL,";\n"));
}



    //call createNewProcess
    //
}



    // if (length == -1 || breadth ==-1) {
    //     print_usage();
    //     exit(EXIT_FAILURE);
    // }

    // // Calculate the area
    // if (area == 0) {
    //     area = length * breadth;
    //     printf("Area: %d\n",area);
    // }

    // // Calculate the perimeter
    // if (perimeter == 0) {
    //     perimeter = 2 * (length + breadth);
    //     printf("Perimeter: %d\n",perimeter);
    // }
    return 0;
}