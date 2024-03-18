#include "predictor.h"
#include <string.h>

uint8_t *global_bht;
uint64_t global_history;
uint8_t *local_bht;
uint32_t *local_predictor;
uint8_t *choice_predictor;

int global_history_bits; 
int local_history_bits; 
int pc_index_bits;

uint32_t bht_size;
uint32_t local_bht_size;
uint32_t local_predictor_size;
uint32_t choice_predictor_size;

uint32_t pht_cutoff, local_cutoff, global_cutoff;

uint8_t local_outcome, global_outcome;

void init_global_bht(){
    printf("GHB: %d\n", global_history_bits);
    bht_size = 1 << global_history_bits;
    global_bht = malloc((bht_size * sizeof(uint8_t)));
    memset(global_bht, WEAK_NOTTAKEN, (bht_size * sizeof(uint8_t)));
    global_history = 0;
}

void init_local_predictor(){
    printf("PIB: %d\n", pc_index_bits);
    local_predictor_size = 1 << pc_index_bits;
    local_predictor =  malloc(local_predictor_size * sizeof(uint32_t));
    memset(local_predictor, 0, (local_predictor_size * sizeof(uint32_t)));
}

void init_local_bht(){
    printf("LHB: %d\n", local_history_bits);
    local_bht_size = 1 << local_history_bits;
    local_bht = malloc(local_bht_size * sizeof(uint8_t));
    memset(local_bht, WEAK_NOTTAKEN, (local_bht_size * sizeof(uint8_t)));
}

void init_choice_predictor(){
    choice_predictor_size = 1 << global_history_bits;
    choice_predictor =  malloc(choice_predictor_size * sizeof(uint8_t));
    memset(choice_predictor, WEAK_NOTTAKEN, (choice_predictor_size * sizeof(uint8_t)));
}

uint8_t get_local_prediction(uint32_t pc) {
    uint32_t local_idx = pc & pht_cutoff;
    uint8_t local_predicton =  local_bht[local_predictor[local_idx]];
    uint8_t local_outcome = TAKEN;
    if (local_predicton == WEAK_NOTTAKEN || local_predicton == STRONG_NOTTAKEN){
        local_outcome = NOTTAKEN;
    }
    return local_outcome;
}

uint8_t get_global_prediction() {
    uint32_t global_idx = global_history & global_cutoff;
    uint8_t global_prediction = global_bht[global_idx];
    uint8_t global_outcome = TAKEN;
    if (global_prediction == WEAK_NOTTAKEN || global_prediction == STRONG_NOTTAKEN){
        global_outcome = NOTTAKEN;
    }
    return global_outcome;
}

uint8_t get_choice_prediction(uint8_t lp, uint8_t gp) {
    uint32_t global_idx = global_history & global_cutoff;
    uint8_t choice_prediction = choice_predictor[global_idx];
    if (choice_prediction == WEAK_NOTTAKEN || choice_prediction == STRONG_NOTTAKEN){
        return gp;
    }
    return lp;
}

void update_bht(uint8_t *bht, uint32_t index, uint8_t outcome){
    if (outcome == TAKEN) {
        if (bht[index] != STRONG_TAKEN) bht[index]++;
    } else {
        if (bht[index] != STRONG_NOTTAKEN) bht[index]--;
    }
}

void update_global_history(uint8_t outcome){
    global_history = ((global_history << 1) & global_cutoff) | outcome;
}

void update_local_predictor(uint32_t pc, uint8_t outcome){
    uint32_t local_idx = pc & pht_cutoff;
    local_predictor[local_idx] = ((local_predictor[local_idx] << 1) & local_cutoff) | outcome;
}

void init_tournament(){
    init_global_bht();
    init_local_predictor();
    init_local_bht();
    init_choice_predictor();

    pht_cutoff = (1 << pc_index_bits) - 1;
    local_cutoff = (1 << local_history_bits) - 1;
    global_cutoff = (1 << global_history_bits) - 1;
}

uint8_t get_tournament_prediction(uint32_t pc){

    local_outcome = get_local_prediction(pc);
    global_outcome = get_global_prediction();
    return get_choice_prediction(local_outcome, global_outcome);
}


void train_tournament(uint32_t pc, uint8_t outcome){
    uint32_t local_idx = pc & pht_cutoff;
    uint32_t global_idx = global_history & global_cutoff;

    update_bht(global_bht, global_idx, outcome);
    update_bht(local_bht, local_predictor[local_idx], outcome);
    if(global_outcome != local_outcome){
        update_bht(choice_predictor, global_idx,  (local_outcome == outcome) ? TAKEN : NOTTAKEN);
    }
    
    update_global_history(outcome);
    update_local_predictor(pc, outcome);
}
