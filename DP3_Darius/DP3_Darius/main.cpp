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

    double start = 0.0,end;
    if (verbose) {
        printf("Diagonalized Matrix\n");
        for (int i = 0; i < numCities; i++) {
            for (int k = 0; k < numCities; k++) {
                int num = inputArray[i][k];
                printf(num >= 0 ? " %d " : "%d ", num);
            }
            printf("\n");
        }
    }
    start = get_current_time();
    std::pair<std::vector<int>, int> results = darius();
    for (int i = 0; i < results.first.size(); i++) {
        printf("%c ", 'A'+results.first.at(i));
    }
    printf("(%d)\n", results.second);
    end = get_current_time();
    printf("Time: %lf\n",end-start);
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
            sscanf(&line[2*i+1]," %s", input);
            temp = (input[0] == '-') ? SENTINEL : atoi(input);
            if (verbose) {
                printf(temp >= 0 ? " %d " : "%d ",temp);
            }
            inputArray[inputLine - 2][i] = temp;
            inputArray[i][inputLine-2] = temp;
        }
        if(verbose) {
            printf("\n");
        }
    }
    inputLine++;
}
