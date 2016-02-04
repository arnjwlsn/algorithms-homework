#include <iostream>
#include <stdlib.h>
#include <time.h>

const int MAX_RAND_VALUE = 100000;
int _size = 5000;

// Fill the array with random values that range from 0 - 100,000
void fill_array(size_t *list) {
   for(int i = 0; i < _size; ++i) {
      list[i] = rand() % (MAX_RAND_VALUE + 1);
   }
}

// Sort the array in ascending order
void sort_array(size_t *list) {
   for(int i = 0; i < _size - 1; ++i) {
      for(int j = i; j < _size; ++j) {
         if(list[i] > list[j]) {
            size_t tmp = 0;
            tmp = list[i];
            list[i] = list[j];
            list[j] = tmp;
         }
      }
   }
}

void binary_search(size_t *list, size_t find) {
   // TODO: Implement binary search   
}

std::ostream& operator<<(std::ostream& out, const size_t *list) {
   for(int i = 0; i < _size; ++i) {
      out << list[i] << std::endl;   
   }
   return out;
} 

int main() {
   size_t list[_size];
   clock_t start, end;
   size_t find = 0;

   srand(time(NULL));

   fill_array(list);
   sort_array(list);
   //std::cout << list;
   
   find = rand() % (MAX_RAND_VALUE + 1);

   start = clock();
   binary_search(list, find);
   end = clock();

   return 0;
}
