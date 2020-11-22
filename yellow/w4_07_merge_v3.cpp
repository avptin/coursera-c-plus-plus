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

  int onethird = (range_end - range_begin) / 3;
  vector<typename RandomIt::value_type> tv1 (range_begin, range_begin + onethird);
  vector<typename RandomIt::value_type> tv2 (range_begin + onethird, range_end - onethird);
  vector<typename RandomIt::value_type> tv3 (range_begin + 2 * onethird, range_end);


  MergeSort(begin(tv1), end(tv1));
  MergeSort(begin(tv2), end(tv2));
  MergeSort(begin(tv3), end(tv3));

  /*
  cout << "tv1 = { ";
  for (int x : tv1) {
    cout << x << " ";
  }
  cout << "}.  tv2 = { ";
  for (int x : tv2) {
    cout << x << " ";
  }
  cout << "}.  tv3 = { ";
  for (int x : tv3) {
    cout << x << " ";
  }
  cout << "}." << endl;
  */

  vector<typename RandomIt::value_type> tv;

  merge(begin(tv1), end(tv1), begin(tv2), end(tv2), back_inserter(tv));
  merge(begin(tv), end(tv), begin(tv3), end(tv3), range_begin);
}

int main() {
  vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};
  MergeSort(begin(v), end(v));
  for (int x : v) {
    cout << x << " ";
  }
  cout << endl;
  return 0;
}