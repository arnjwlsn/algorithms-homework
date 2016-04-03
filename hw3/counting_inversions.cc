#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <random>
#include <vector>

/* Brute force method runs in O(n^2) where n is the number of elements in
 *  * the collection.
 *   * 
 *    * The method itself checks to see that for every element in the collection:
 *     * how many values less than the current index exist. If a value is less than
 *      * the current index, then you know that a swap must occur between those numbers
 *       * which would be an inversion
 *        */
uint32_t find_brute_inversion_count(const std::vector<uint32_t> data, const bool verbose = false) {
     size_t inversions = 0;

       if (verbose) {
              printf("Data:\n{ ");
                  for (auto &it : data) {
                           printf("%u ", it);
                               }
                      printf("}\n");
                        }

         for (size_t i = 0; i < data.size() - 1; ++i) {
                for (size_t j = i + 1; j < data.size() ; ++j) {
                         if (verbose) {
                                    printf("Comparing data[i] = %u and data[j] = %u\n", data[i], data[j]);
                                          }
                               if (data[i] > data[j]) {
                                          if (verbose) {
                                                       printf("data[i] = %u is greater than data[j] = %u which will require 1 inversion\n");
                                                               }
                                                  ++inversions;
                                                        }
                                   }
                  }
           return inversions;
}

/*
 *  * Merge the two halves of an unsorted vector into a sorted vector
 *   */
uint32_t merge(std::vector<uint32_t> &data, const uint32_t left, const uint32_t middle, const uint32_t right, const bool verbose = false) {
     int i = left;
       int j = middle;
         int k = left;
           int inversions = 0;
             std::vector<uint32_t> copy;
               copy.reserve(data.size());

                 if (verbose) {
                        printf("Merging [ ");
                            for (size_t i = left; i < middle; ++i) {
                                     printf("%u ", data[i]);
                                         }
                                printf("] and [ ");
                                    for (size_t i = middle; i <= right; ++i) {
                                             printf("%u ", data[i]);
                                                 }
                                        printf("]\n");
                                          }

                   // i < middle is copying from the first array
                   //   // j <= right is copying from the second array
                   //     // This loop will copy the smaller value of the either array until it has
                   //       // copied everything from one array
                   //         while ((i < middle) && (j <= right)) {
                   //             if (verbose) {
                   //                   printf("Comparing data[i] = %u and data[j] = %u\n", data[i], data[j]);
                   //                       }
                   //                           if (data[i] <= data[j]) {
                   //                                 copy[k++] = data[i++];
                   //                                       if (verbose) {
                   //                                               printf("data[i] = %u is less than or equal to data[j] = %u which means no inverting is required\n", data[i - 1], data[j]);
                   //                                                     }
                   //                                                         } else {
                   //                                                               copy[k++] = data[j++];
                   //
                   //                                                                     // The below equation works due to the merging process
                   //                                                                           // If an element from the left array is larger than an element from the right array
                   //                                                                                 // then it is guaranteed that all remaining elements in the left array will be bigger
                   //                                                                                       // than the elements in the right array. Which means all the remaining elements from the left array
                   //                                                                                             // will also need to be inverted.
                   //                                                                                                   inversions += middle - i;
                   //                                                                                                         if (verbose) {
                   //                                                                                                                 printf("data[i] = %u is greater than data[j] = %u which requires %u inversion(s)\n", data[i], data[(j - 1)], middle - i);
                   //                                                                                                                       }
                   //                                                                                                                           }
                   //                                                                                                                             }
                   //
                   //                                                                                                                               // The following two while loops copy the remaining elements from the left or right array
                   //                                                                                                                                 // depending on which one ran out of elements first in the above loop
                   //                                                                                                                                   while (i < middle) {
                   //                                                                                                                                       copy[k++] = data[i++];
                   //                                                                                                                                         }
                   //                                                                                                                                           while (j <= right) {
                   //                                                                                                                                               copy[k++] = data[j++];
                   //                                                                                                                                                 }
                   //
                   //                                                                                                                                                   // Reorder elements for proper display
                   //                                                                                                                                                     for (size_t n = left; n <= right; ++n) {
                   //                                                                                                                                                         data[n] = copy[n];
                   //                                                                                                                                                           }
                   //
                   //                                                                                                                                                             if (verbose) {
                   //
                   //                                                                                                                                                                 printf("Merged: [ ");
                   //                                                                                                                                                                     for (size_t n = left; n <= right; ++n) {
                   //                                                                                                                                                                           printf("%u ", copy[n]);
                   //                                                                                                                                                                               }
                   //                                                                                                                                                                                   printf("]\n");
                   //                                                                                                                                                                                     }
                   //                                                                                                                                                                                       return inversions;
                   //                                                                                                                                                                                       }
                   //
                   //                                                                                                                                                                                       uint32_t merge_sort_r(std::vector<uint32_t> &data, const uint32_t left, const uint32_t right, const bool verbose = false) {
                   //                                                                                                                                                                                         // Impossible paramaters. The left index should never be greater than or equal
                   //                                                                                                                                                                                           // to the right index. If it is, then there are 0 inversions possible
                   //                                                                                                                                                                                             if (left >= right) return 0;
                   //
                   //                                                                                                                                                                                               // Integer division truncates the decimal
                   //                                                                                                                                                                                                 int middle = (right + left) / 2;
                   //
                   //                                                                                                                                                                                                   if (verbose) {
                   //                                                                                                                                                                                                       printf("Splitting [ ");
                   //                                                                                                                                                                                                           for (size_t i = left; i <= right; ++i) {
                   //                                                                                                                                                                                                                 printf("%u ", data[i]);
                   //                                                                                                                                                                                                                     }
                   //                                                                                                                                                                                                                         printf("] into [ ");
                   //                                                                                                                                                                                                                             for (size_t i = left; i <= middle; ++i) {
                   //                                                                                                                                                                                                                                   printf("%u ", data[i]);
                   //                                                                                                                                                                                                                                       }
                   //                                                                                                                                                                                                                                           printf("] and [ ");
                   //                                                                                                                                                                                                                                               for (size_t i = middle + 1; i <= right; ++i) {
                   //                                                                                                                                                                                                                                                     printf("%u ", data[i]);
                   //                                                                                                                                                                                                                                                         }
                   //                                                                                                                                                                                                                                                             printf("]\n");
                   //                                                                                                                                                                                                                                                               }
                   //
                   //                                                                                                                                                                                                                                                                 // Return the sum of inversions in the left array and right array
                   //                                                                                                                                                                                                                                                                   return merge_sort_r(data, left, middle, verbose) + 
                   //                                                                                                                                                                                                                                                                            merge_sort_r(data, middle + 1, right, verbose) + 
                   //                                                                                                                                                                                                                                                                                     merge(data, left, middle + 1, right, verbose);
                   //                                                                                                                                                                                                                                                                                     }
                   //
                   //                                                                                                                                                                                                                                                                                     uint32_t find_recursive_inversion_count(std::vector<uint32_t> &data, const bool verbose = false) {
                   //                                                                                                                                                                                                                                                                                       return merge_sort_r(data, 0, data.size() - 1, verbose);
                   //                                                                                                                                                                                                                                                                                       }
                   //
                   //
                   //                                                                                                                                                                                                                                                                                       int32_t main(int32_t argc, char **argv) { 
                   //                                                                                                                                                                                                                                                                                         if (argc < 4) {
                   //                                                                                                                                                                                                                                                                                             printf("Incorrect number of parameters\n");
                   //                                                                                                                                                                                                                                                                                                 return -1;
                   //                                                                                                                                                                                                                                                                                                   }
                   //
                   //                                                                                                                                                                                                                                                                                                     const size_t vector_length = std::atoi(argv[1]);
                   //                                                                                                                                                                                                                                                                                                       std::vector<uint32_t> data;
                   //                                                                                                                                                                                                                                                                                                         data.reserve(vector_length);
                   //
                   //                                                                                                                                                                                                                                                                                                           std::mt19937 mersenne_twister(std::chrono::system_clock::now().time_since_epoch().count());
                   //                                                                                                                                                                                                                                                                                                             std::uniform_int_distribution<size_t> distribution(0, 20);
                   //                                                                                                                                                                                                                                                                                                               for (size_t i = 0; i < vector_length; ++i) {
                   //                                                                                                                                                                                                                                                                                                                   data.push_back(distribution(mersenne_twister));
                   //                                                                                                                                                                                                                                                                                                                     }
                   //
                   //                                                                                                                                                                                                                                                                                                                       auto start_time = std::chrono::high_resolution_clock::now();
                   //
                   //                                                                                                                                                                                                                                                                                                                         size_t inversions = 0;
                   //                                                                                                                                                                                                                                                                                                                           
                   //                                                                                                                                                                                                                                                                                                                             if (!std::atoi(argv[2]) && !std::atoi(argv[3])) {
                   //                                                                                                                                                                                                                                                                                                                                 inversions = find_brute_inversion_count(data);
                   //                                                                                                                                                                                                                                                                                                                                     printf("Brute force, no logging\n");
                   //                                                                                                                                                                                                                                                                                                                                       } else if (!std::atoi(argv[2]) && std::atoi(argv[3])) {
                   //                                                                                                                                                                                                                                                                                                                                           inversions = find_brute_inversion_count(data, true);
                   //                                                                                                                                                                                                                                                                                                                                               printf("Brute force, with logging\n");
                   //                                                                                                                                                                                                                                                                                                                                                 } else if (std::atoi(argv[2]) && !std::atoi(argv[3])) {
                   //                                                                                                                                                                                                                                                                                                                                                     inversions = find_recursive_inversion_count(data);
                   //                                                                                                                                                                                                                                                                                                                                                         printf("Divide and conquer, no logging\n");
                   //                                                                                                                                                                                                                                                                                                                                                           } else {
                   //                                                                                                                                                                                                                                                                                                                                                               inversions = find_recursive_inversion_count(data, true);
                   //                                                                                                                                                                                                                                                                                                                                                                   printf("Divide and conquer, with logging\n");
                   //                                                                                                                                                                                                                                                                                                                                                                     }
                   //
                   //                                                                                                                                                                                                                                                                                                                                                                       auto end_time = std::chrono::high_resolution_clock::now();
                   //                                                                                                                                                                                                                                                                                                                                                                         auto time_difference = end_time - start_time;
                   //                                                                                                                                                                                                                                                                                                                                                                           uint32_t microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
                   //
                   //                                                                                                                                                                                                                                                                                                                                                                             printf("%zu inversions in %f milliseconds\n", inversions, (float)microseconds * 0.001);
                   //                                                                                                                                                                                                                                                                                                                                                                               return 0;
                   //                                                                                                                                                                                                                                                                                                                                                                               }
                   //                                                                                                                                                                                                                                                                                                                                                                               ZZ
