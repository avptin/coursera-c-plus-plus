#include "sum_reverse_sort.h"

using namespace std;

int Sum(int x, int y) { return x + y; }
string Reverse(string s) {
  string result;
  for (auto rit = s.rbegin(); rit != s.rend(); ++rit) {
    result.push_back(*rit);
  }
  return result;
};
void Sort(vector<int>& nums) { return sort(nums.begin(), nums.end()); }

int main() { return 0; }