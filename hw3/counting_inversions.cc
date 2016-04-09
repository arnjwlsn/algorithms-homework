/* Aaron Wilson
 * Dr. Kalita
 * CS4720 - Design and Analys of Algorithms
 * April 11, 2015
 * Email: awilson8@uccs.edu
 *
 * Problem 2: Counting Inversion Problem
 */

#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <random>
#include <vector>
#include <iostream>
#include <fstream>
#include <time.h>

const int FINAL_SIZE = 100000;
const int DIVIDE_TIME = 1000;
const std::string TIME_UNIT = "ms";
const int INCREMENT = 5000;
const int INITIAL_SIZE = 5000;
int array_size = INITIAL_SIZE;

uint32_t merge(const std::vector<uint32_t> &data, const uint32_t left, const uint32_t middle, const uint32_t right);
uint32_t merge_sort_r(const std::vector<uint32_t> &data, const uint32_t left, const uint32_t right);
uint32_t find_recursive_inversion_count(const std::vector<uint32_t> &data);
double clock_time(clock_t start, clock_t end);

int main() {
   std::ofstream my_file;
   my_file.open("counting_inversions_results.csv");
   my_file << "No. of Elements, Time (" << TIME_UNIT << "), No. of Inversions" << std::endl;

   // Time of algorithm
   srand(time(NULL));
   clock_t start, end;

   std::cout << "Generating... " << std::endl;

   while(array_size <= FINAL_SIZE) {
      std::cout << "  " << array_size << std::endl;

      std::vector<uint32_t> data;
      data.reserve(array_size);

      std::mt19937 mersenne_twister;
      std::uniform_int_distribution<size_t> distribution(0, (uint32_t)-1);
      for (size_t i = 0; i < array_size; ++i) {
         data.push_back(distribution(mersenne_twister));
      }

      start = clock();
      uint32_t inversions = find_recursive_inversion_count(data);
      end = clock();
      
      my_file << array_size << "," << clock_time(start,end) << "," << inversions << std::endl;

      //std::cout << "Inversions: " << inversions << std::endl;
      //std::cout << "Time Taken(" << array_size << "): " << clock_time(start,end) << TIME_UNIT << std::endl;

      array_size += INCREMENT;
   }
   
   my_file.close();   
   return 0;
}

uint32_t merge(const std::vector<uint32_t> &data, const uint32_t left, const uint32_t middle, const uint32_t right) {
   int i = left;
   int j = middle;
   int k = left;
   int inversions = 0;

   while ((i < middle) && (j <= right)) {
      if (data[i] <= data[j]) 
         ++i; 
      else {
         ++j;
         inversions += middle - i;
      }
      ++k;
   }
   return inversions;
}

uint32_t merge_sort_r(const std::vector<uint32_t> &data, const uint32_t left, const uint32_t right) {
   if (left >= right) return 0;

   // Integer division truncates the decimal
   int middle = (right + left) / 2;

   // Return the sum of inversions in the left array and right array
   return merge_sort_r(data, left, middle) + merge_sort_r(data, middle + 1, right) + merge(data, left, middle + 1, right);
}

uint32_t find_recursive_inversion_count(const std::vector<uint32_t> &data) {
    return merge_sort_r(data, 0, data.size() - 1);
}

double clock_time(clock_t start, clock_t end) {
   double per_sec = (CLOCKS_PER_SEC/DIVIDE_TIME);
      return ((double)end - (double)start) / per_sec;
}
