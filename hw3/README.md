# CS 4720 Homework Assignment 3

## 1. Small Statistic Problem or the Selection Problem
Given an unsorted list of n numbers, find the kth smallest element.

### Usage
Compile with: `g++ selection.cpp -o selection -std=c++11`

Then run with: `./selection`

The program generates a .csv file will the time taken for given values of n.

## 2. Counting Inversion Problem
Given a sequence of numbers, count the number of inversions that would have to take place in order to make the sequence ascending.

### Usage
Compile with: `g++ counting_inversions.cc -o inversions -std=c++11`  
  
Then run with: `./inversions`  

The program will generate a .csv file that contains the information for the time taken given array sizes n.  

## 3. Convex Hull
Given an a group of points on a 2-D plain, find the convex hull using a divide and conquer algorithm.

### Usage
Compile with: `g++ convex_hull.cpp -o hull -std=c++11`

Then run with 1 parameter: `./hull 0`

The single parameter will determine (0) if you want to get the time taken for increasing point array sizes from 5,000 - 100,000 with increments of 5,000 or (1) if you want to run the program once for a point array of size 10. The (0) option will generate a .csv file for the increasing values of n and the time taken for each value n. The (1) option generates two .csv files: hull.csv and points.csv where the hull file contains only the points from a set of points in the points file that make up the convex hull.
