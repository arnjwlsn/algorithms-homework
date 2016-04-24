#include <iostream>
#include <vector>

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

int main() {
  const int amount = 6;
  std::vector<int> denom = { 1, 3, 4 };
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
  std::cout << "The used list is as follows:" << std::endl;
  std::cout << "[";
  for (int i = 0; i < coins_used.size() - 1; ++i) {
    std::cout << coins_used[i] << ", ";
  }
  std::cout << coins_used[coins_used.size() - 1] << "]" << std::endl;

  return 0;
}
