# CSE 240A Winter 2024 Branch Predictor Project

A Comparative analysis project undertaken as part of the CSE 240A course at UCSD in Winter '2024, evaluating performance of ``Gshare:13``, ``Tournament:9:10:10`` and a custom Perceptron predictor implemented based on the paper [Dynamic Branch Prediction with Perceptrons](https://www.cs.utexas.edu/~lin/papers/hpca01.pdf). Results show the prediction superiority of the implemented custom perceptron predictor over the baselines across all test traces while not excedding the specified memory limits. 

# Overview:

# Project Structure: 

* The project is organized into two main directories: The ``src`` directory contains all the source code and makefiles for all 3 predictors and corresponding execution scripts are provided. The ``report`` directory contains the consolidated raw results from the executed trials and also the ``report/visualizations`` folder contains an interactive Jupyter notebook to generate visualizations and HPO plots for all the experiments mentioned in the Report. Corresponding image files are also present. 

* The ``traces`` directory contains the 6 traces (Integer, Floating point and Memory) across which we evaluate all the 3 implemented predictors to benchmark performance. 

# How to Run:

# Ackonwledgements:

## Team: 

[Shyam Renjith](mailto:srenjith@ucsd.edu)
[Aditya Giridharan](mailto:agiridharan@ucsd.edu)