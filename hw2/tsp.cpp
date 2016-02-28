#include <vector>
#include <time.h>
#include <iostream>
#include <stdlib.h>
#include <cstdio>

const int SIZE = 3;
const int MAX = 20;

void generate(std::vector<int>&, std::vector<std::vector<int> >&);

int main() {
   srand(time(NULL));

   std::vector<int> cities;
   std::vector<std::vector<int> > distances;

   generate(cities, distances);

   for(int i = 0; i < distances.size(); ++i) {
      for(int j = 0; j < distances.size(); ++j) {
         printf("%3d", distances[i][j]);
      }
      std::cout << std::endl;
   }

   return 0;
}

void generate(std::vector<int>& cities, std::vector<std::vector<int> >& distances) {
   for(int i = 0; i < SIZE; ++i) {
      cities.push_back(i+1);
      std::vector<int> vec;
      for(int j = 0; j < SIZE; ++j) vec.push_back(rand() % MAX + 1); 
      distances.push_back(vec);
   }
} 
