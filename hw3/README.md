# CS 4720 Homework Assignment 3

## 1. Small Statistic Problem or the Selection Problem
Given an unsorted list of n numbers, find the kth smallest element.

### Usage
Compile with:
`g++ selection.cpp -o selection -std=c++11`

Then run without parameters:
`./selection`

The program generates a .csv file will the time taken for given values of n.

## 2. Counting Inversion Problem
Given a sequence of numbers, count the number of inversions that would have to take place in order to make the sequence ascending.

### Usage
Compile with:  
`g++ -o inversions -std=c++11 main.cc`  
  
Then run with 3 parameters:  
`./inversions 100 0 0`  

The first parameter is the size of the vector you want to generate.  
The second paramater (0/1) will determine if you use brute force or divide and conquer.  
The third parameter (0/1) will determine if you get verbose console output or not.  
