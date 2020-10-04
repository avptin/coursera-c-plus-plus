
// https://www.coursera.org/learn/c-plus-plus-yellow/programming/pg1Vd/massa-blokov

#include <iostream>
#include <vector>

using namespace std;

int main() {
  uint64_t sum = 0;
  unsigned n, r;
  cin >> n >> r;

  for (unsigned i = 0; i < n; ++i) {
    uint64_t w, h, d;
    cin >> w >> h >> d;
    sum += w * h * d;
  }

  cout << sum * r;

  return 0;
}
