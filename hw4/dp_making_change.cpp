/* Aaron Wilson
 * Dr. Kalita
 * CS 4720 - Design and Analys of Algorithms
 * May 4, 2016
 * Email: awilson8@uccs.edu
 *
 * Assignment 4, Problem 1: Making Change
 */

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

int make_change(const std::vector<int> &denom, const int &amount, std::vector<int> &coin_count, std::vector<int> &coins_used) {
  for (int i = 0; i < amount + 1; ++i) {
    int count = i;
    int new_coin = 1;
    std::vector<int> smaller_denom;

    for (const auto &it : denom) {
      if (it <= i) { smaller_denom.push_back(it); }
    }

    for (const auto &j : smaller_denom) {
      if (coin_count[i - j] + 1 < count) {
        count = coin_count[i - j] + 1;
        new_coin = j;
      }
    }

    coin_count[i] = count;
    coins_used[i] = new_coin;
  }

  return coin_count[amount];
}

void print_coins(const std::vector<int> &coins_used, const int &amount) {
  int coin = amount;
  while (coin > 0) {
    int current_coin = coins_used[coin];
    std::cout << current_coin << std::endl;
    coin -= current_coin;
  }
}

void print_list(const std::vector<int>& vec, bool used) {
  if(used) std::cout << "The used list is as follows:" << std::endl;
  else std::cout << "The count list is as follows:" << std::endl;
  
  std::cout << "[";
  for (int i = 0; i < vec.size() - 1; ++i) {
    std::cout << vec[i] << ", ";
  }
  std::cout << vec[vec.size() - 1] << "]" << std::endl;
}

int main() {
  std::ifstream myfile;
  myfile.open("denominations.inp");
  std::vector<int> denom;

  int new_coin = 0;
  while(myfile >> new_coin) {
    denom.push_back(new_coin);
  }

  std::sort(denom.begin(), denom.end());

  int amount = 0;
  std::cout << "Denomination:";
  for(int i = 0; i < denom.size(); ++i)
    std::cout << " " << denom[i];
  std::cout << std::endl;
  
  do{
    std::cout << "Make change for: ";
    std::cin >> amount;
  } while(amount < 1);

  std::vector<int> coin_count;
  std::vector<int> coins_used;
  coin_count.reserve(amount + 1);
  coins_used.reserve(amount + 1);
  for (int i = 0; i < amount + 1; ++i) {
    coin_count.push_back(0);
    coins_used.push_back(0);
  }

  std::cout << "Making change for " << amount << " requires" << std::endl;
  std::cout << make_change(denom, amount, coin_count, coins_used);
  std::cout << " coins" << std::endl;
  std::cout << "They are:" << std::endl;
  print_coins(coins_used, amount);
  print_list(coin_count, false);
  print_list(coins_used, true);

  return 0;
}
