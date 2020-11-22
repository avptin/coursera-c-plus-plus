// https://www.coursera.org/learn/c-plus-plus-yellow/programming/AhGVS/gruppirovka-strok-po-priefiksu

#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

template <typename RandomIt>
pair<RandomIt, RandomIt>
FindStartsWith(RandomIt range_begin, RandomIt range_end, const string &prefix) {
  auto f = lower_bound(
      range_begin, range_end, prefix,
      [prefix](const string &lhs, const string &rhs) {
          int size = min(prefix.size(), lhs.size(), 10);
          string ltmp = lhs;
          string rtmp = rhs;

          return rtmp.resize(size) > ltmp.resize(size);
        });
  auto s = upper_bound(
      range_begin, range_end, prefix,
      [](const string &lhs, const string &rhs) { return rhs[0] > lhs[0]; });

  return make_pair(f, s);
}

int main() {
  const vector<string> sorted_strings = {"moscow", "motovilikha", "murmansk"};

  const auto mo_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
  for (auto it = mo_result.first; it != mo_result.second; ++it) {
    cout << *it << " ";
  }
  cout << endl;

  const auto mt_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
  cout << (mt_result.first - begin(sorted_strings)) << " "
       << (mt_result.second - begin(sorted_strings)) << endl;

  const auto na_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
  cout << (na_result.first - begin(sorted_strings)) << " "
       << (na_result.second - begin(sorted_strings)) << endl;

  return 0;
}
