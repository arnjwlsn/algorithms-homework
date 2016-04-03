#include <iostream>
#include <stdlib.h>

int partition(int*, int, int);
int kth_smallest_element(int*, int, int, int);

int main() {
   int size = 10;
   int k = 5;

   std::cout << "Enter a value for k: ";
   std::cin >> k;

   int list[] = {2, 3, 1, 5, 4, 7, 8, 6, 9, 10};
   std::cout << "k'th smallest element: " << kth_smallest_element(list, 0, size-1, k) << std::endl;
   return 0;
}

int kth_smallest_element(int* list, int left, int right, int k) {
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

int partition(int* list, int left, int right) {
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
