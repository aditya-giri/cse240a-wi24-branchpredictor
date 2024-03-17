
#include <stdio.h>
#include "predictor.h"
#include "gshare.c"
#include "tournament.c"
#include "perceptron.c"

const char *studentName1 = "Shyam Renjith";
const char *studentID1   = "A59020323";
const char *email1       = "srenjith@ucsd.edu";

const char *studentName2 = "Aditya Giridharan";
const char *studentID2   = "A59012233";
const char *email2       = "agiridharan@ucsd.edu";

//------------------------------------//
//      Predictor Configuration       //
//------------------------------------//

// Handy Global for use in output routines
const char *predictorNames[4] = { "Static", "Gshare",
                          "Tournament", "Custom" };

//------------------------------------//
//        Predictor Functions         //
//------------------------------------//

// Initialize the predictor
//
int global_history_bits;
int local_history_bits;
int pc_index_bits;
int predictor_type;       // Branch Prediction Type
int verbosity;


void
initializePredictor()
{
  // Call init based on prediction algorithm
  switch (predictor_type) {
    case STATIC: break;
    case GSHARE: init_gshare(); break;
    case TOURNAMENT: init_tournament(); break;
    case CUSTOM: init_perceptron(); break;
    default:
      break;
  }
}

// Make a prediction for conditional branch instruction at PC 'pc'
// Returning TAKEN indicates a prediction of taken; returning NOTTAKEN
// indicates a prediction of not taken
//
uint8_t
makePrediction(uint32_t pc)
{
  // Make a prediction based on the bpType
  switch (predictor_type) {
    case STATIC:
      return TAKEN; break;
    case GSHARE: 
      return get_gshare_pred(pc); break;
    case TOURNAMENT: 
      return get_tournament_pred(pc); break;
    case CUSTOM: 
      return get_perceptron_pred(pc); break;
    default:
      break;
  }

  // If there is not a compatable bpType then return NOTTAKEN
  return NOTTAKEN;
}

// Train the predictor the last executed branch at PC 'pc' and with
// outcome 'outcome' (true indicates that the branch was taken, false
// indicates that the branch was not taken)
//
void
trainPredictor(uint32_t pc, uint8_t outcome)
{
  // Call trainer based on prediction algorithm
  switch (predictor_type) {
    case STATIC: break;
    case GSHARE: train_gshare(pc, outcome); break;
    case TOURNAMENT: train_tournament(pc, outcome); break;
    case CUSTOM: train_perceptron(pc, outcome); break;
    default:
      break;
  }
}