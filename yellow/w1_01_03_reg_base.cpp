
// https://www.coursera.org/learn/c-plus-plus-yellow/programming/pg1Vd/massa-blokov

#include <iostream>
#include <map>
#include <memory>
#include <tuple>
#include <vector>

using namespace std;
/*
enum class Lang { DE, FR, IT };

struct Region {
  string std_name;
  string parent_std_name;
  map<Lang, string> names;
  int64_t population;
};
*/
auto RegionTuple(const Region &r) {
  return make_tuple(r.std_name, r.parent_std_name, r.names, r.population);
}

bool operator<(const Region &lhs, const Region &rhs) {
  return RegionTuple(lhs) < RegionTuple(rhs);
}

int FindMaxRepetitionCount(const vector<Region> &regions) {
  map<tuple<string, string, map<Lang, string>, int64_t>, int> regmap;

  for (auto item : regions) {
    auto t = RegionTuple(item);
    if (regmap.count(t) == 0) {
      regmap[t] = 0;
    } else {
      regmap[t]++;
    }
  }

  if (regmap.size() == 0) {
    return 0;
  }

  int max = 0;
  for (const auto &[k, v] : regmap) {
    if (v > max) {
      max = v;
    }
  }

  if (max == 0) {
    return 1;
  }

  return ++max;
}

int main() {
  cout
      << FindMaxRepetitionCount({
             {"Moscow",
              "Russia",
              {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
              89},
             {"Russia",
              "Eurasia",
              {{Lang::DE, "Russland"},
               {Lang::FR, "Russie"},
               {Lang::IT, "Russia"}},
              89},
             {"Moscow",
              "Russia",
              {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
              89},
             {"Moscow",
              "Russia",
              {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
              89},
             {"Russia",
              "Eurasia",
              {{Lang::DE, "Russland"},
               {Lang::FR, "Russie"},
               {Lang::IT, "Russia"}},
              89},
         })
      << endl;

  cout
      << FindMaxRepetitionCount({
             {"Moscow",
              "Russia",
              {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
              89},
             {"Russia",
              "Eurasia",
              {{Lang::DE, "Russland"},
               {Lang::FR, "Russie"},
               {Lang::IT, "Russia"}},
              89},
             {"Moscow",
              "Russia",
              {{Lang::DE, "Moskau"},
               {Lang::FR, "Moscou deux"},
               {Lang::IT, "Mosca"}},
              89},
             {"Moscow",
              "Toulouse",
              {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
              89},
             {"Moscow",
              "Russia",
              {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
              31},
         })
      << endl;

  return 0;
}
