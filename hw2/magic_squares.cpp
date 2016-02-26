#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <time.h>

const std::string TIME_UNIT = "sec";
const int DIVIDE_TIME = 1;

double clock_time(clock_t, clock_t);

int main() {
   std::vector<int> vec;
   clock_t start, end;

   srand(time(NULL));

   const size_t width = 3;
   const size_t size = width*width;
   const size_t magic_sum = width * ((width*width) + 1) / 2;
   
   // Initialize vector with values from 1-n^2
   for(size_t i = 0; i < size; i++) {
     vec.push_back(i+1); 
   }

   std::cout << "Magic Sum: " << magic_sum << std::endl;

   start = clock();
   do {
      int rows[width] = {0};
      int columns[width] = {0};
      int diagonal_pos = 0;
      int diagonal_neg = 0;
      int check_sums = 0;

      for(size_t i = 0; i < width; ++i) {
         for(size_t j = 0; j < width; ++j) {
            rows[i] += vec[(width*i) + j];
            columns[i] += vec[(width*j) + i];
         }
         diagonal_pos += vec[(width*i) + i];
         diagonal_neg += vec[(width*i) + (width-i) -1];
      }

      for(size_t i = 0; i < width; ++i) {
         if(rows[i] == magic_sum) ++check_sums;
         if(columns[i] == magic_sum) ++check_sums;
      }
      if(diagonal_pos == magic_sum) ++check_sums;
      if(diagonal_neg == magic_sum) ++check_sums;

      if(check_sums == (width*2) + 2) {
         std::cout << "----------" << std::endl;
         for(size_t i = 0; i < width; ++i) {
            for(size_t j = 0; j < width; ++j) {
               printf("%3d", vec[(width*i) + j]);
            }
            printf("\n");
         }
         printf("\n");
      }

   } while(std::next_permutation(vec.begin(), vec.end()));
   end = clock();

   std::cout << "Time Taken: " << clock_time(start, end) << " " << TIME_UNIT << std::endl;

   return 0;
}

double clock_time(clock_t start, clock_t end) {
   double per_sec = (CLOCKS_PER_SEC/DIVIDE_TIME);
      return ((double)end - (double)start) / per_sec;
}
