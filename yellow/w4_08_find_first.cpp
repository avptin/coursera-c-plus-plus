// https://www.coursera.org/learn/c-plus-plus-yellow/programming/y7l7D/poisk-blizhaishiegho-eliemienta

#include <algorithm>
#include <iostream>
#include <set>

using namespace std;

set<int>::const_iterator FindNearestElement(const set<int> &numbers,
                                            int border) {
  set<int>::const_iterator lb;
  set<int>::const_iterator ub;

  // Greater or equla to:  ____[X<-____
  // 1 3 4
  // 0
  lb = numbers.lower_bound(border);
  ub = numbers.upper_bound(border);

  if (lb == ub){
    if (lb == end(numbers)){
      if (numbers.size() == 0){
        return end(numbers);
      }
      else {
        return prev(end(numbers));
      }
    }
    else{
      if (abs(*prev(lb) - border) > abs(*lb - border)){
        return lb;
      }
      else
      {
        return prev(lb);
      }

    }
  }

  if (lb != end(numbers)){
    return lb;
  }
}

int main() {
  set<int> numbers = {1, 4, 6};
  cout << *FindNearestElement(numbers, 0) << " "
       << *FindNearestElement(numbers, 3) << " "
       << *FindNearestElement(numbers, 5) << " "
       << *FindNearestElement(numbers, 6) << " "
       << *FindNearestElement(numbers, 100) << endl;

  set<int> empty_set;

  cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;
  return 0;
}
