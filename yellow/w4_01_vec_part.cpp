#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

void PrintVectorPart(const vector<int>& numbers);

int main() {
  PrintVectorPart({6, 1, 8, -5, 4});
  cout << endl;
  PrintVectorPart({-6, 1, 8, -5, 4});  // ничего не выведется
  cout << endl;
  PrintVectorPart({6, 1, 8, 5, 4});
  cout << endl;
  PrintVectorPart({});
  cout << endl;
  PrintVectorPart({-1});
  cout << endl;
  return 0;
}

void PrintVectorPart(const vector<int>& numbers) {
  auto it =
      find_if(begin(numbers), end(numbers), [](const int& e) { return e < 0; });

  bool first = true;
  if (it != begin(numbers)) {
    for (--it; it >= begin(numbers); --it) {
      if (!first) {
        cout << " ";
      }
      cout << *it;
      first = false;
    }
  }
}
