// Header file

#ifndef PREDICTOR_H
#define PREDICTOR_H

#include <stdint.h>
#include <stdlib.h>

// Predictors
#define STATIC      0
#define GSHARE      1
#define TOURNAMENT  2
#define CUSTOM      3
#define DEFAULT_PERCEPTRON_THETA -99

extern const char *predictorNames[];

// Branch outcomes
#define NOTTAKEN  0
#define TAKEN     1

// 2-bit counters
#define STRONG_NOTTAKEN  0
#define WEAK_NOTTAKEN    1
#define WEAK_TAKEN       2
#define STRONG_TAKEN     3

// Predictor configs
extern int global_history_bits;
extern int local_history_bits;
extern int pc_index_bits;
extern int predictor_type;
extern int verbosity;

extern int perceptron_table_length_bits; 
extern int num_weights_bits; 
extern int weight_bit_limit;
extern int perceptron_theta;

void initializePredictor();
uint8_t makePrediction(uint32_t pc);
void trainPredictor(uint32_t pc, uint8_t outcome);

#endif