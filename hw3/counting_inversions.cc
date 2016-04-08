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

uint32_t merge(const std::vector<uint32_t> &data, const uint32_t left, const uint32_t middle, const uint32_t right) {
  int i = left;
  int j = middle;
  int k = left;
  int inversions = 0;

  while ((i < middle) && (j <= right)) {
    if (data[i] <= data[j]) {
      ++i;
    } else {
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
  return merge_sort_r(data, left, middle) + 
         merge_sort_r(data, middle + 1, right) + 
         merge(data, left, middle + 1, right);
}

uint32_t find_recursive_inversion_count(const std::vector<uint32_t> &data) {
  return merge_sort_r(data, 0, data.size() - 1);
}


int32_t main(int32_t argc, char **argv) { 
  if (argc < 2) {
    printf("Incorrect number of parameters\n");
    return -1;
  }

  const size_t vector_length = std::atoi(argv[1]);
  std::vector<uint32_t> data;
  data.reserve(vector_length);

  std::mt19937 mersenne_twister;
  std::uniform_int_distribution<size_t> distribution(0, (uint32_t)-1);
  for (size_t i = 0; i < vector_length; ++i) {
    data.push_back(distribution(mersenne_twister));
  }

  auto start_time = std::chrono::high_resolution_clock::now();

  uint32_t inversions = find_recursive_inversion_count(data);

  auto end_time = std::chrono::high_resolution_clock::now();
  auto time_difference = end_time - start_time;
  uint32_t microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();

  printf("%u inversions in %f milliseconds\n", inversions, (float)microseconds * 0.001);
  return 0;
}
