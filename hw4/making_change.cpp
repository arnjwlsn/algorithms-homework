#include <iostream>
#include <vector>

int main() {
   int change = 0;
   std::vector<int> denom;
   denom.reserve(4);
   denom.push_back(25);
   denom.push_back(10);
   denom.push_back(5);
   denom.push_back(1);

   std::cout << "Make change for: ";
   std::cin >> change;

   std::vector<int> coins_used;
   coins_used.reserve(denom.size());
   int i = 0;
   while (i < denom.size()) {
      coins_used.push_back(change / denom[i]);
      change -= denom[i] * coins_used[i]; 
      ++i;
   }

   for(int i = 0; i < coins_used.size(); ++i) {
      switch(i) {
         case 0:
            std::cout << "Quarter(s): " << coins_used[i] << std::endl;
            break;
         case 1:
            std::cout << "Dime(s): " << coins_used[i] << std::endl;
            break;
         case 2: 
            std::cout << "Nickel(s): " << coins_used[i] << std::endl;
            break;
         case 3: 
            std::cout << "Penny(ies): " << coins_used[i] << std::endl;
            break;
         default:
            break;
      }
   }

   return 0;
}
