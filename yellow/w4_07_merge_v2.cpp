// https://www.coursera.org/learn/c-plus-plus-yellow/programming/wlbIg/sortirovka-sliianiiem

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
  if ((range_end - range_begin) < 2)
  {
    return;
  }

  vector<typename RandomIt::value_type> tv1 (range_begin, range_begin + (range_end - range_begin) / 2);
  vector<typename RandomIt::value_type> tv2 (range_begin + (range_end - range_begin) / 2, range_end);

  MergeSort(begin(tv1), end(tv1));
  MergeSort(begin(tv2), end(tv2));

  /*
  cout << "tv1 = { ";
  for (int x : tv1) {
    cout << x << " ";
  }
  cout << "}.  tv2 = { ";
  for (int x : tv2) {
    cout << x << " ";
  }
  cout << "}." << endl;
  */

  merge(begin(tv1), end(tv1), begin(tv2), end(tv2), range_begin);
}

int main() {
  vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
  MergeSort(begin(v), end(v));
  for (int x : v) {
    cout << x << " ";
  }
  cout << endl;
  return 0;
}
