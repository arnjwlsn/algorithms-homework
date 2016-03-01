#include <vector>
#include <time.h>
#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include <algorithm>
#include <limits>
#include <fstream>

const std::string TIME_UNIT = "ms";
const int DIVIDE_TIME = 1000;

void display(std::vector< std::vector<int> >&);
double clock_time(clock_t, clock_t);
void read_file(std::vector<int>&, std::vector< std::vector<int> >&, std::string);

int main(int argc, char* argv[]) {
   srand(time(NULL));
   clock_t start, end;
   std::vector<int> cities;
   std::vector< std::vector<int> > distances;

   // Read input file distances
   std::string input = argv[1];
   read_file(cities, distances, input);

   int current_trip;                                     // Temp holder of current distance for permutation
   int shortest_trip = std::numeric_limits<int>::max();  // Contains the shortest distance so far
   std::vector<int> trip;                                // Contains the city permutation order for shortest trip

   // Begin exhaustive TSP
   start = clock();
   do {
      current_trip = 0;

      for(int i = 0; i < cities.size() - 1; ++i) {
         current_trip += distances[cities[i]-1][cities[i+1]-1];
      }

      if(current_trip < shortest_trip) {
         shortest_trip = current_trip;
         trip = cities;
      }

   } while(std::next_permutation(cities.begin(), cities.end()));
   end = clock();

   // Final Print
   std::cout << "Shortest Trip: " << shortest_trip << " units" << std::endl;
   std::cout << "Order of Cities: ";
   for(int i = 0; i < trip.size(); ++i) std::cout << trip[i] << " ";
   std::cout << std::endl;
   std::cout << "Time Taken: " << clock_time(start, end) << " " << TIME_UNIT << std::endl;

   return 0;
}

// For debugging - prints all elements in matrix distances
void display(std::vector< std::vector<int> >& vec) {
   for(int i = 0; i < vec.size(); ++i) {
      for(int j = 0; j < vec.size(); ++j) {
         printf("%3d", vec[i][j]);
      }
      std::cout << std::endl;
   }
}

double clock_time(clock_t start, clock_t end) {
   double per_sec = (CLOCKS_PER_SEC/DIVIDE_TIME);
      return ((double)end - (double)start) / per_sec;
}

void read_file(std::vector<int>& cities, std::vector<std::vector<int> >& distances, std::string filename) {
   std::fstream file;
   file.open(filename.c_str());
   int size = 0, dist = 0;
   if(file.is_open()) {
      if(!(file >> size)) std::cerr << "Error when reading file size.";      
      for(int i = 0; i < size; ++i) {
         cities.push_back(i+1);
         std::vector<int> vec;
         for(int j = 0; j < size; ++j) {
            if(!(file >> dist)) std::cerr << "Error when reading file distances." << std::endl;
            vec.push_back(dist); 
         }
         distances.push_back(vec);
      } 
   } 
} 
