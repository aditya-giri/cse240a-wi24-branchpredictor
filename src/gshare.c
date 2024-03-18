#include "predictor.h"

uint8_t *bht;
uint64_t global_history;
uint32_t bht_size;
int global_history_bits = 0;

void init_gshare(){
    printf("GHB: %d\n", global_history_bits);
    bht_size = 1 << global_history_bits;
    bht = (uint8_t *)malloc(bht_size * sizeof(uint8_t));
    global_history = 0;
    for (int i = 0; i < bht_size; i++) {
        bht[i] = WEAK_NOTTAKEN;
    }
}

void train_gshare(uint32_t pc, uint8_t outcome){
    uint32_t index = (pc ^ global_history) & (bht_size - 1);
    if (outcome == TAKEN) {
        if (bht[index] != STRONG_TAKEN) bht[index]++;
    } else {
        if (bht[index] != STRONG_NOTTAKEN) bht[index]--;
    }
    global_history = ((global_history << 1) & (bht_size - 1)) | outcome;
}

uint8_t get_gshare_prediction(uint32_t pc){
    uint32_t index = (pc ^ global_history) & (bht_size - 1);
    if (bht[index] == STRONG_TAKEN || bht[index] == WEAK_TAKEN) return TAKEN;
    return NOTTAKEN;
}