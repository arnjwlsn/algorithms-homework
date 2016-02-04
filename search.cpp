#include <iostream>
#include <stdlib.h>
#include <time.h>

const int MAX_RAND_VALUE = 100000;
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

std::ostream& operator<<(std::ostream& out, const int *list) {
   for(int i = 0; i < _size; ++i) {
      out << list[i] << std::endl;   
   }
   return out;
}

void display(int key, int location, clock_t start, clock_t end) {
   std::cout << "Key: " << key << std::endl;
   std::cout << "Location: " << location << std::endl;

   float per_ms = (CLOCKS_PER_SEC/1000);
   float run_time = ((float)end - (float)start) / per_ms;
   std::cout << "Time: " << run_time << " ms" << std::endl;
}

int main() {
   int list[_size];
   clock_t start, end;
   int key = 0, location = 0;

   srand(time(NULL));

   fill_array(list);
   sort_array(list);
   //std::cout << list;
   
   key = rand() % (MAX_RAND_VALUE + 1);

   std::cout << "-----------------------------\nTERNARY SEARCH: " << std::endl;
   start = clock();
   location = ternary_search(list, key);
   end = clock();
   display(key, location, start, end);

   std::cout << "-----------------------------\nBINARY SEARCH:" << std::endl; 
   start = clock();
   location = binary_search(list, key);
   end = clock();
   display(key, location, start, end);

   std::cout << "-----------------------------\nLINEAR SEARCH:" << std::endl; 
   start = clock();
   location = linear_search(list, key);
   end = clock();
   display(key, location, start, end);
   
   return 0;
}
