#include <stdio.h>
#include <sys/time.h>
#include <string.h>

#include "darius.h"

int inputLine;
bool verbose;
int inputArray[MAX_SIZE][MAX_SIZE];
int numCities;

void ReadFile(FILE* f);
void ReadLine(char* line);

double get_current_time() {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return ((double) tp.tv_sec + (double) tp.tv_usec * 1e-6);
}

int main(int argc, const char* argv[]) {
    verbose = false;
    if (argc < 2) {
        printf("Error: no input file specified.\n");
        return 1;
    }

    if (argc >= 3) {
        for(int i = 1; i < argc; i++) {
            printf("%s\n",argv[i]);
            if (strcmp(argv[i],"-v")) {
                printf("Verbose mode active!\n");
                verbose = true;
            }
        }
    }

    FILE* f = fopen(argv[1], "r");
    if (f == NULL) {
        printf("Unable to open file!\n");
        return 1;
    }

    inputLine = 0;
    for(int i = 0; i < MAX_SIZE; i++) {
        for(int k = 0; k < MAX_SIZE; k++) {
            inputArray[i][k] = 0;
        }
    }

    ReadFile(f);
    fclose(f);

    for(int i = 0; i < numCities; i++) {
        for(int k = 0; k < numCities; k++) {
            printf("%d ",inputArray[i][k]);
        }
        printf("\n");
    }

    double start = 0.0,end;
    if (verbose) {
        start = get_current_time();
    }
    darius();
    if (verbose) {
        end = get_current_time();
        printf("Time: %lf\n",end-start);
    }
    return 0;
}

void ReadFile(FILE* f) {
    const int LINE_SIZE = 4096;
    char line[LINE_SIZE];
    while (fgets(line, LINE_SIZE, f) != NULL) {
        ReadLine(line);
    }
}

void ReadLine(char* line) {
    char input[256];
    int temp;

    if (inputLine == 0) {
        sscanf(line,"%d", &numCities);
    }
    else if (inputLine == 1) {
        sscanf(line,"%s",input);
    }
    else {
        for(int i = 0; i < inputLine - 1; i++) {
            if(i == inputLine - 2) {
                sscanf(&line[i+2],"%s", input);
            }
            else {
                sscanf(&line[i+2],"%s ", input);
            }
            temp = atoi(input);
            printf("%d\n",temp);
            inputArray[inputLine - 2][i-2] = temp;
            inputArray[i-2][inputLine-2] = temp;
        }
    }
    inputLine++;
}
