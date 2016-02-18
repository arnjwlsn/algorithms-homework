#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <vector>
#include <string>

const int FINAL_ARRAY_SIZE = 400000;
const int MAX_RAND_VALUE = 100000;
const int INCREMENT_SIZE = 5000;
const int INITIAL_SIZE = 5000;
const int TRIALS_PER_TEST = 100;
const std::string TIME_UNIT = "1*10^-6s";
const int DIVIDE_TIME = 1000000;
int _size = INITIAL_SIZE;

// Fill the array with random values that range from 0 - 100,000
void fill_array(int *list) {
   for(int i = 0; i < _size; ++i) {
      list[i] = rand() % (MAX_RAND_VALUE + 1);
   }
}

// Quick sort to sort array in ascending order
void quick_sort(int *list, int left, int right) {
   int i = left, j = right;
   int pivot = list[(left + right)/2];
   int tmp;

   while(i <= j) {
      while(list[i] < pivot)
         i++;
      while(list[j] > pivot)
         j--;
      if(i <= j) {
         tmp = list[i];
         list[i] = list[j];
         list[j] = tmp;
         i++;
         j--;
      }
   }

   if(left < j)
      quick_sort(list, left, j);
   if(i < right)
      quick_sort(list, i, right);
}

int binary_search(int *list, int key) {
   int start = 0, m = 0, end = _size - 1;

   while(start <= end) {
      m = (start + end)/2;
      if(key == list[m]) return m;
      else if(key < list[m]) end = m - 1;
      else start = m + 1; 
   }
   return -1;   
}

int ternary_search(int *list, int key) {
   int start = 0, end = _size - 1, m1 = 0, m2 = 0;
   
   while(start <= end) {
      m1 = start + (end-start)/3;
      m2 = start + (2*(end-start))/3;

      if(list[m1] == key) return m1;
      else if(list[m2] == key) return m2;
      else if(key < list[m1]) end = m1 - 1; // 1st third
      else if(key > list[m2]) start = m2 + 1; // 3rd third
      else { // Middle third
         start = m1;
         end = m2;
      }
   }
}

double average(std::vector<double> vec) {
   double average = 0;
   for(std::vector<double>::iterator it = vec.begin(); it != vec.end(); ++it) {
      average += *it;
   }
   return average/(double)vec.size();
}

double clock_time(clock_t start, clock_t end) {
   double per_micros = (CLOCKS_PER_SEC/DIVIDE_TIME);
   return ((double)end - (double)start) / per_micros;
}

std::ostream& operator << (std::ostream& out, const int *list) {
   for(int i = 0; i < _size; ++i) {
      out << list[i] << std::endl;
   }
   return out;
}

int main() {
   clock_t start, end;
   int key = 0, location = 0, counter = 0;
   std::vector<double> tern_avg, bin_avg;
   std::vector<int> time_res;
   std::vector<double> tern_res, bin_res;
   srand(time(NULL));

   std::ofstream myfile;
   myfile.open("results.csv");
   myfile << "No. of Element in Array,"
          << "Ternary Search Time (" << TIME_UNIT << ")," 
          << "Binary Search Time (" << TIME_UNIT << ")" 
          << std::endl;

   // Ternary Search Test
   std::cout << "-------------------\n" 
             << "| Ternary Search: |\n" 
             << "-------------------" << std::endl;
   while(_size <= FINAL_ARRAY_SIZE) {
      int list[_size];
      
      fill_array(list);
      quick_sort(list, 0, _size - 1);
      time_res.push_back(_size);

      std::cout << _size << "..." << std::endl;
   
      while(counter < TRIALS_PER_TEST) {
         key = rand() % (MAX_RAND_VALUE + 1);

         // Ternary Search
         start = clock();
         location = ternary_search(list, key);
         end = clock();
         tern_avg.push_back(clock_time(start, end));

         //increment the counter
         counter++;
      }

      tern_res.push_back(average(tern_avg));

      //clear vectors
      tern_avg.clear();

      //reset counter
      counter = 0;

      //increment the array size
      _size += INCREMENT_SIZE;
   }   

   _size = INITIAL_SIZE;

   // Binary Search Test
   std::cout << "------------------\n" 
             << "| Binary Search: |\n" 
             << "------------------" << std::endl;
   while(_size <= FINAL_ARRAY_SIZE) {
      int list[_size];
      
      fill_array(list);
      quick_sort(list, 0, _size - 1);

      std::cout << _size << "..." << std::endl;
   
      while(counter < TRIALS_PER_TEST) {
         key = rand() % (MAX_RAND_VALUE + 1);

         // Binary Search
         start = clock();
         location = binary_search(list, key);
         end = clock();
         bin_avg.push_back(clock_time(start, end));

         //increment the counter
         counter++;
      }

      bin_res.push_back(average(bin_avg));

      //clear vectors
      bin_avg.clear();

      //reset counter
      counter = 0;

      //increment the array size
      _size += INCREMENT_SIZE;
   }

   //write data values to file
   for(int i = 0; i < time_res.size(); ++i) {
      myfile << time_res[i] << "," << tern_res[i] << "," << bin_res[i] << std::endl;
   }

   myfile.close();
   return 0;
}
