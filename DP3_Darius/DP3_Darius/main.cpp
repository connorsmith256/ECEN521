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

void printInput() {
    printf("Diagonalized Matrix\n");
    printf("  ");
    for (int i = 0; i < numCities; i++) {
        printf(" %c ", 'A'+i);
    }
    printf("\n");
    for (int i = 0; i < numCities; i++) {
        printf("%c ", 'A'+i);
        for (int k = 0; k < numCities; k++) {
            int num = inputArray[i][k];
            if (num >= 0) {
                printf(" %d ", num);
            }
            else {
                printf(" - ");
            }
        }
        printf("\n");
    }
}

void printResults(std::pair<std::vector<int>, int> results) {
    for (int i = 0; i < results.first.size()-1; i++) {
        int city1 = results.first.at(i);
        int city2 = results.first.at(i+1);
        std::vector<int> path = getPath(city1, city2);
        for (int i = 0; i < path.size()-1; i++) {
            printf("%c ", 'A'+path.at(i));
        }
        if (i == results.first.size()-2) {
            printf("%c ", 'A'+path.at(path.size()-1));
        }
    }
    printf("(%d)\n", results.second);
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

    double start, end;
    if (verbose) {
        printInput();
    }

    start = get_current_time();
    floyd(numCities, inputArray);
    std::pair<std::vector<int>, int> results = darius();
    end = get_current_time();
    printResults(results);
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
