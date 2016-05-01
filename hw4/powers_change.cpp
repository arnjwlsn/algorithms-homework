#include <iostream>
#include <algorithm>
#include <vector>

int main() {
   int change = 0;
   int power = 0;

   std::cout << "Power: ";
   std::cin >> power;
   std::cout << "Make change for: ";
   std::cin >> change;

   std::vector<int> denom;
   int next_value = power;
   denom.push_back(1);
   do {
      denom.push_back(next_value);
      next_value *= power;  
   } while (next_value < change);

   std::reverse(denom.begin(), denom.end());

   std::vector<int> coins_used;
   coins_used.reserve(denom.size());
   int i = 0;
   while (i < denom.size()) {
      coins_used.push_back(change / denom[i]);
      change -= denom[i] * coins_used[i];
      ++i;
   }

   for(int i = 0; i < coins_used.size(); ++i) {
      std::cout << "Value: " <<  denom[i] << " >> " << "Count: " << coins_used[i] << std::endl;
   }

   return 0;
}
