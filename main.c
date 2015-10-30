#include <stdio.h>
#include <stdlib.h>
#define SIZE 1000

//1. name of process
//2. average CPU time
//3. average burst time
//4. average interarrival time
//5. average time required to se

//struct for process type
struct ProcessType {
    char *process;
    
    int cpuTime, burstTime, interArrTime, IOTime;
};

//main method
int main(int argc, char **argv) {
    
    
//    int counter = 0;
//
//    FILE *fp = fopen(argv[1], "r");
//    
//    char buff[1000];
//    //buff = malloc(sizeof(char*) * counter);
//    
//    
//    
//    fscanf(fp, buff);
//
//    printf("%s\n", &buff[2]);
//
//
//    fclose(fp);
    
    //read hardcoded string
    char buf[] = "2 interactive 20 10 80 5 batch 500 250 1000 10";
    int i;
    char *p;
    char *array[100];
    i = 0;
    p = strtok (buf," ");
    while (p != NULL)
    {
        array[i++] = p;
        p = strtok (NULL, " ");
    }
    for (i=0;i<15; ++i)
        printf("%s\n", array[i]);
    

    //type in commands in the command line separated by space 
    //read file and save the values from the file and the command line to variables
    //add the variables 
    //create process: event move to ready queue
    //round robin scheduling 

}



//initialize event queue
//while loop, until sim over, tke next event from pq
//take command line input (use getlong function)
//evet Q: PQ, time stamp:
//ready queue: queue depends on algorithm
//