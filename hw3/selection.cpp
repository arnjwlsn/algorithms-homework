/* Aaron Wilson
 * Dr. Kalita
 * CS4720 - Design and Analys of Algorithms
 * April 11, 2016
 * Email: awilson8@uccs.edu
 *
 * Problem 1: Small Statistic Problem or the Selection Problem
 *
 */

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <algorithm>

const int MAX_RAND_VALUE = 1000000;
const int FINAL_SIZE = 100000;
const int INCREMENT = 5000;
const int DIVIDE_TIME = 1000;
const std::string TIME_UNIT = "ms";
const int INITIAL_SIZE = 5000;
int array_size = INITIAL_SIZE;

int partition(std::vector<int>, int, int);
int kth_smallest_element(std::vector<int>, int, int, int);

double clock_time(clock_t, clock_t);
void fill_array(std::vector<int>&);
int find_k(int);

int main() {
   int k;
   std::ofstream my_file;
   my_file.open("selection_results.csv");
   my_file << "No. of Elements,Time (" << TIME_UNIT << ")" << std::endl;

   srand(time(NULL));
   clock_t start, end;

   std::cout << "Generating:" << std::endl;

   while(array_size <= FINAL_SIZE) {
      std::vector<int> list;
      list.reserve(array_size);
      fill_array(list);
      k = find_k(array_size);
      
      std::cout << array_size << "..." << std::endl;

      int value = 0;
      start = clock();
      value = kth_smallest_element(list, 0, array_size-1, k);
      end = clock();

      my_file << array_size << "," << clock_time(start, end) << std::endl;
      array_size += INCREMENT;
   }

   return 0;
}

int kth_smallest_element(std::vector<int> list, int left, int right, int k) {
   // make sure k is less than list's size otherwise program will exit
   if((k > 0) && (k <= ((right - left) + 1))) {
      int index = partition(list, left, right);
      
      if(index - left == k - 1) return list[index];
      if(index - left > k - 1) return kth_smallest_element(list, left, index-1, k);
      return kth_smallest_element(list, index+1, right, k-index+left-1);
   }

   std::cout << "Invalid value for k. Program will exit." << std::endl;
   exit(EXIT_FAILURE);
}

int partition(std::vector<int> list, int left, int right) {
   int r_value = list[right];
   int pointer = left;

   for(int i = left; i < right; ++i) {
      if(list[i] <= r_value){
         // swap
         int tmp = list[i];
         list[i] = list[pointer];
         list[pointer] = tmp;
         
         pointer++;
      }
   }
   // swap back
   int tmp = list[pointer];
   list[pointer] = list[right];
   list[right] = tmp;

   return pointer;
}

double clock_time(clock_t start, clock_t end) {
   double per_sec = (CLOCKS_PER_SEC/DIVIDE_TIME);
      return ((double)end - (double)start) / per_sec;
}

void fill_array(std::vector<int> &list) {
   for(size_t i = 0; i < array_size; ++i) {
      list.push_back(i);
   }
   std::random_shuffle(list.begin(), list.end());
}

int find_k(int size) {
   return rand() % size;
}
