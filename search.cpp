#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <vector>
#include <string>

const int MAX_RAND_VALUE = 100000;
const int INCREMENT_SIZE = 5000;
const int TRIALS_PER_TEST = 10;
const std::string TIME_UNIT = "1*10^-6s";
const int DIVIDE_TIME = 1000000;
int _size = 5000;

// Fill the array with random values that range from 0 - 100,000
void fill_array(int *list) {
   for(int i = 0; i < _size; ++i) {
      list[i] = rand() % (MAX_RAND_VALUE + 1);
   }
}

// Sort the array in ascending order
void sort_array(int *list) {
   for(int i = 0; i < _size - 1; ++i) {
      for(int j = i; j < _size; ++j) {
         if(list[i] > list[j]) {
            int tmp = 0;
            tmp = list[i];
            list[i] = list[j];
            list[j] = tmp;
         }
      }
   }
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

int linear_search(int *list, int key) {
   for(int i = 0; i < _size; ++i) {
      if(list[i] == key) return i;
   }
   return -1;
}

double average(std::vector<double> vec) {
   double average = 0;
   for(std::vector<double>::iterator it = vec.begin(); it != vec.end(); ++it) {
      average += *it;
   }
   return average/(double)vec.size();
}

std::ostream& operator<<(std::ostream& out, const int *list) {
   for(int i = 0; i < _size; ++i) {
      out << list[i] << std::endl;   
   }
   return out;
}

double clock_time(clock_t start, clock_t end) {
   double per_micros = (CLOCKS_PER_SEC/DIVIDE_TIME);
   return ((double)end - (double)start) / per_micros;
}

void display(int key, int location, clock_t start, clock_t end) {
   std::cout << "Key: " << key << std::endl;
   std::cout << "Location: " << location << std::endl;
   std::cout << "Time: " << clock_time(start, end) << " " << TIME_UNIT  << std::endl;
}

int main() {
   clock_t start, end;
   int key = 0, location = 0, counter = 0;
   std::vector<double> tern, bin, lin;
   srand(time(NULL));
   
   std::ofstream myfile;
   myfile.open("results.csv");
   myfile << "No. of Element in Array,"
          << "Ternary Search Time (" << TIME_UNIT << ")," 
          << "Binary Search Time (" << TIME_UNIT << ")" 
          << std::endl;

   while(_size <= 100000) {
      int list[_size];
      
      fill_array(list);
      sort_array(list);
      myfile << _size << ",";

      std::cout << _size << "..." << std::endl;
   
      while(counter < TRIALS_PER_TEST) {
         key = rand() % (MAX_RAND_VALUE + 1);

         // Ternary Search
         start = clock();
         location = ternary_search(list, key);
         end = clock();
         tern.push_back(clock_time(start, end));

         // Binary Search
         start = clock();
         location = binary_search(list, key);
         end = clock();
         bin.push_back(clock_time(start, end));

         /*/ Linear Search
         start = clock();
         location = linear_search(list, key);
         end = clock();
         lin.push_back(clock_time(start, end));*/

         //increment the counter
         counter++;
      }
      
      myfile << average(tern) << ","
             << average(bin) <<  std::endl;

      //clear vectors
      tern.clear();
      bin.clear();
      //lin.clear();

      //reset counter
      counter = 0;

      //increment the array size
      _size += INCREMENT_SIZE;
   }   

   myfile.close();
   return 0;
}
