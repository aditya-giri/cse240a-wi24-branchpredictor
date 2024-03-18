#include <stdio.h>
#include <string.h>
#include <math.h>

// Data for perceptron predictor

#define p_PCSIZE 256
#define p_HEIGHT 32
#define p_SATUATELEN 8

#define p_MASK_PC(x) ((x * 19) % p_PCSIZE)

int16_t p_W[p_PCSIZE][p_HEIGHT];
int16_t p_gHistory[p_HEIGHT];
int32_t p_train_theta;
uint8_t p_recent_prediction = NOTTAKEN;
uint8_t p_need_train = 0;


void perceptron_shift(int16_t* satuate, uint8_t same){
  if(same){
    if(*satuate != ((1 << (p_SATUATELEN - 1)) - 1)){
      (*satuate)++;
    }
  }else{
    if(*satuate != -(1 << (p_SATUATELEN - 1 ) )){
      (*satuate)--;
    }
  }
}

void init_perceptron(){
  p_train_theta = perceptron_theta == DEFAULT_PERCEPTRON_THETA ? (int32_t)(1.93 * p_HEIGHT + 14): perceptron_theta;
  memset(p_W, 0, sizeof(int16_t) * p_PCSIZE * (p_HEIGHT));
  memset(p_gHistory, 0, sizeof(uint16_t) * p_HEIGHT);
}



uint8_t get_perceptron_pred(uint32_t pc){
  uint32_t index = p_MASK_PC(pc);
  int16_t out = p_W[index][0];

  for(int i = 1 ; i <= p_HEIGHT ; i++){
    out += p_gHistory[i-1] ? p_W[index][i] : -p_W[index][i];
  }

  p_recent_prediction = (out >= 0) ? TAKEN : NOTTAKEN;
  p_need_train = (out < p_train_theta && out > -p_train_theta) ? 1 : 0;

  return p_recent_prediction;
}

void train_perceptron(uint32_t pc, uint8_t outcome){

  uint32_t index = p_MASK_PC(pc);

  if((p_recent_prediction != outcome) || p_need_train){
    perceptron_shift(&(p_W[index][0]), outcome);
    for(int i = 1 ; i <= p_HEIGHT ; i++){
      uint8_t predict = p_gHistory[i-1];
      perceptron_shift(&(p_W[index][i]), (outcome == predict));
    }

  }

  for(int i = p_HEIGHT - 1; i > 0 ; i--){
    p_gHistory[i] = p_gHistory[i-1];
  }
  p_gHistory[0] = outcome;

}
