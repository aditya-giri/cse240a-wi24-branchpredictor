#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "predictor.h"

FILE *stream;
char *buf = NULL;
size_t len = 0;

void usage();
int handle_option(char *arg);
int read_branch(uint32_t *pc, uint8_t *outcome);

// Have to update
void usage() {
    printf("Usage: predictor <options> [<trace>]\n");
    printf("       bunzip -kc trace.bz2 | predictor <options>\n");
    printf(" Options:\n");
    printf(" --help       Print this message\n");
    printf(" --verbose    Print predictions on stdout\n");
    printf(" --<type>     Branch prediction scheme:\n");
    printf("    static\n"
           "    gshare:<# ghistory>\n"
           "    tournament:<# ghistory>:<# lhistory>:<# index>\n"
           "    custom\n");
}

int handle_option(char *arg) {

    if (!strcmp(arg,"--static")) {
        predictor_type= STATIC;
    } else if (!strncmp(arg,"--gshare:",9)) {
        predictor_type= GSHARE;
        sscanf(arg+9,"%d", &global_history_bits);
    } else if (!strncmp(arg,"--tournament:",13)) {
        predictor_type= TOURNAMENT;
        sscanf(arg+13,"%d:%d:%d", &global_history_bits, &local_history_bits, &pc_index_bits);
    } else if (!strncmp(arg,"--custom:", 9)) {
        predictor_type= CUSTOM;
        sscanf(arg+9,"%d:%d:%d:%d", &weight_bit_limit, &num_weights_bits, &perceptron_table_length_bits, &perceptron_theta);
    } else if (!strcmp(arg,"--verbose")) {
        verbosity = 1;
    } else {
        return 0;
    }

    return 1;
}

int read_branch(uint32_t *pc, uint8_t *outcome) {
    
    if (getline(&buf, &len, stream) == -1) {
        return 0;
    }

    uint32_t tmp;
    sscanf(buf,"0x%x %d\n",pc,&tmp);
    *outcome = tmp;

    return 1;
}

int main(int argc, char *argv[]) {
   // Set defaults
    stream = stdin;
    predictor_type = STATIC;
    verbosity = 0;

    // Process cmdline Arguments
    for (int i = 1; i < argc; ++i) {
        if (!strcmp(argv[i],"--help")) {
        usage();
        exit(0);
        } else if (!strncmp(argv[i],"--",2)) {
        if (!handle_option(argv[i])) {
            printf("Unrecognized option %s\n", argv[i]);
            usage();
            exit(1);
        }
        } else {
        // Use as input file
        stream = fopen(argv[i], "r");
        }
    }

    // Initialize the predictor
    initializePredictor();

    uint32_t num_branches = 0;
    uint32_t mispredictions = 0;
    uint32_t pc = 0;
    uint8_t outcome = NOTTAKEN;

    // Reach each branch from the trace
    while (read_branch(&pc, &outcome)) {
        num_branches++;

        // Make a prediction and compare with actual outcome
        uint8_t prediction = makePrediction(pc);
        if (prediction != outcome) {
        mispredictions++;
        }
        if (verbosity != 0) {
        printf ("%d\n", prediction);
        }

        // Train the predictor
        trainPredictor(pc, outcome);
    }

    // Print out the mispredict statistics
    printf("Branches:        %10d\n", num_branches);
    printf("Incorrect:       %10d\n", mispredictions);
    float mispredict_rate = 100*((float)mispredictions / (float)num_branches);
    printf("Misprediction Rate: %7.3f\n", mispredict_rate);

    // Cleanup
    fclose(stream);
    free(buf);

    return 0;
}
