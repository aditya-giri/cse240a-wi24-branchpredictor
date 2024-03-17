#include "predictor.h"
#include <string.h>

//Data Structures for perceptron
int8_t weight_limit_lower;
int8_t weight_limit_upper;
int16_t *perceptron_table; // stores weights - uses row-major ordering
uint64_t perceptron_global_history;

int perceptron_table_length; 
int perceptron_table_length_bits; 
int num_weights;
int num_weights_bits; 
int weight_bit_limit;
int perceptron_theta;

uint16_t get_power_of_2(int power){
  return 1 << power;
}

//Init Function for perceptron
void init_perceptron(){

  weight_limit_lower = -1 * get_power_of_2(weight_bit_limit);
  weight_limit_upper = get_power_of_2(weight_bit_limit) - 1;
  num_weights = get_power_of_2(num_weights_bits);
  perceptron_table_length = get_power_of_2(perceptron_table_length_bits);
    
  perceptron_table = (int16_t *) malloc(perceptron_table_length * num_weights * sizeof(int16_t)); // stores weights
  memset(perceptron_table, 0, (perceptron_table_length * num_weights * sizeof(int16_t)));
  
  perceptron_global_history = 0;
    
  //printf("weight_bit_limit=%d, weight_limit_lower=%d, weight_limit_upper=%d, num_weights=%d, perceptron_table_length=%d, perceptron_theta=%d\n", weight_bit_limit, weight_limit_lower, weight_limit_upper, num_weights, perceptron_table_length, perceptron_theta);
}

// get index into the table of perceptrons
uint8_t get_perceptron_table_index(uint32_t pc){
  return pc & ((1 << perceptron_table_length_bits) - 1);
}

// get perceptron weights from perceptron_table[perceptron_table_idx]
int8_t* get_perceptron_weights(uint8_t perceptron_table_idx){
  int8_t* perceptron_weights = malloc(sizeof(int8_t) * num_weights);
  
  for(uint8_t weight_idx = 0; weight_idx < num_weights; weight_idx++){
    perceptron_weights[weight_idx] = perceptron_table[perceptron_table_idx * num_weights + weight_idx]; // offset(i, j) = i * num_cols + j
  }
  
  return perceptron_weights;
}

// get predicted outcome based on weights and global history
int get_perceptron_sum(int8_t* perceptron_weights){
  int sum = 0;
  
  // adding the bias term first
  sum += perceptron_weights[0];
  for(uint8_t weight_idx = 1; weight_idx < num_weights; weight_idx++){
    if ((perceptron_global_history >> weight_idx) & 1){
      sum += perceptron_weights[weight_idx];
    } else {
      sum -= perceptron_weights[weight_idx];
    }
  } 
  
  return sum; 
}


// update weights of perceptron
void train_perceptron(uint32_t pc, uint8_t outcome){
  uint8_t perceptron_table_idx = get_perceptron_table_index(pc);
  int8_t* perceptron_weights = get_perceptron_weights(perceptron_table_idx);
  
  int sum = get_perceptron_sum(perceptron_weights);
  uint8_t perceptron_prediction = sum >= 0 ? TAKEN : NOTTAKEN;
  
  if((perceptron_prediction != outcome) || (abs(sum) <= perceptron_theta)){
    // update bias term
    perceptron_table[perceptron_table_idx * num_weights + 0] += (outcome == TAKEN) ? 1 : -1;
    if(perceptron_table[perceptron_table_idx * num_weights + 0] > weight_limit_upper){
        perceptron_table[perceptron_table_idx * num_weights + 0] = weight_limit_upper;
      } else if (perceptron_table[perceptron_table_idx * num_weights + 0] < weight_limit_lower){
        perceptron_table[perceptron_table_idx * num_weights + 0] = weight_limit_lower;
      } 
    // update other perceptron weights
    for(uint8_t weight_idx = 1; weight_idx < num_weights; weight_idx++){
      if(((perceptron_global_history >> weight_idx) & 1) == outcome){
        // when x_i and t are same then x_i * t = 1 -> so add 1
        perceptron_table[perceptron_table_idx * num_weights + weight_idx] += 1;
      } else {
        // else it is = -1, subtract 1
        perceptron_table[perceptron_table_idx * num_weights + weight_idx] += -1;
      }
      
      // keep weight within limits
      if(perceptron_table[perceptron_table_idx * num_weights + weight_idx] > weight_limit_upper){
        perceptron_table[perceptron_table_idx * num_weights + weight_idx] = weight_limit_upper;
      } else if (perceptron_table[perceptron_table_idx * num_weights + weight_idx] < weight_limit_lower){
        perceptron_table[perceptron_table_idx * num_weights + weight_idx] = weight_limit_lower;
      }  
    }
  }
  

  
  //Updating the global register
  perceptron_global_history = (perceptron_global_history << 1 | outcome) & ((1 << (num_weights-1)) - 1);
  
  return;
}

// get outcome for branch
uint8_t get_perceptron_pred(uint32_t pc){
    uint8_t perceptron_table_idx = get_perceptron_table_index(pc);
    int8_t* perceptron_weights = get_perceptron_weights(perceptron_table_idx);
    
    return get_perceptron_sum(perceptron_weights) >= 0 ? TAKEN : NOTTAKEN;
}