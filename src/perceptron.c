#include <stdio.h>
#include <string.h>
#include <math.h>

#define HEIGHT 32
#define LEN_SATURATE 8
#define PC_SIZE 256

#define PC_MASK(x) ((x * 19) % PC_SIZE)

int32_t theta;
uint8_t train_required = 0;
uint8_t recent_pred = NOTTAKEN;

int16_t gHistory_table[HEIGHT];
int16_t weights_table[PC_SIZE][HEIGHT];


void perceptron_shift(int16_t* saturation, uint8_t flag){
  if(flag){
    if(*saturation != ((1 << (LEN_SATURATE - 1)) - 1)){
      (*saturation)++;
    }
  }else{
    if(*saturation != -(1 << (LEN_SATURATE - 1 ) )){
      (*saturation)--;
    }
  }
}

void init_perceptron(){
  theta = perceptron_theta == DEFAULT_PERCEPTRON_THETA ? (int32_t)(1.93 * HEIGHT + 14): perceptron_theta;
  memset(weights_table, 0, sizeof(int16_t) * PC_SIZE * (HEIGHT));
  memset(gHistory_table, 0, sizeof(uint16_t) * HEIGHT);
}



uint8_t get_perceptron_pred(uint32_t pc){
  uint32_t index = PC_MASK(pc);
  int16_t out = weights_table[index][0];

  for(int i = 1 ; i <= HEIGHT ; i++){
    out += gHistory_table[i-1] ? weights_table[index][i] : -weights_table[index][i];
  }

  recent_pred = (out >= 0) ? TAKEN : NOTTAKEN;
  train_required = (out < theta && out > -theta) ? 1 : 0;

  return recent_pred;
}

void train_perceptron(uint32_t pc, uint8_t outcome){

  uint32_t index = PC_MASK(pc);

  if((recent_pred != outcome) || train_required){
    perceptron_shift(&(weights_table[index][0]), outcome);
    for(int i = 1 ; i <= HEIGHT ; i++){
      uint8_t prediction = gHistory_table[i-1];
      perceptron_shift(&(weights_table[index][i]), (outcome == prediction));
    }

  }

  for(int i = HEIGHT - 1; i > 0 ; i--){
    gHistory_table[i] = gHistory_table[i-1];
  }
  gHistory_table[0] = outcome;

}
