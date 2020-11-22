#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <numeric>


using namespace std;


int main() {
  unsigned max;
  cin >> max;

  vector<int> v(max);
  iota(rbegin(v), rend(v), 1);

  do {
    for (const auto& i : v){
      cout << i << " ";
    }
    cout << endl;
  } while (prev_permutation(begin(v), end(v)));

  return 0;
}