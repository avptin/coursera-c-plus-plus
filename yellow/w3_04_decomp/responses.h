
#pragma once

#include <map>
#include <string>
#include <vector>

using namespace std;

struct BusesForStopResponse {
  string stop;
  map<string, vector<string>> s2b;
};

struct StopsForBusResponse {
  string bus;
  map<string, vector<string>> s2b;
  map<string, vector<string>> b2s;
};

struct AllBusesResponse {
  map<string, vector<string>> b2s;
  map<string, vector<string>> s2b;
};

ostream& operator<<(ostream& os, const BusesForStopResponse& r);
ostream& operator<<(ostream& os, const StopsForBusResponse& r);
ostream& operator<<(ostream& os, const AllBusesResponse& r);
