#include "responses.h"

#include <iostream>

ostream& operator<<(ostream& os, const BusesForStopResponse& r) {
  if (r.s2b.count(r.stop) == 0) {
    os << "No stop";
  } else {
    for (const string& bus : r.s2b.at(r.stop)) {
      os << bus << " ";
    }
  }

  return os;
}

ostream& operator<<(ostream& os, const StopsForBusResponse& r) {
  if (r.b2s.count(r.bus) == 0) {
    os << "No bus";
  } else {
    for (const string& stop : r.b2s.at(r.bus)) {
      os << "Stop " << stop << ": ";
      if (r.s2b.at(stop).size() == 1) {
        os << "no interchange";
      } else {
        for (const string& other_bus : r.s2b.at(stop)) {
          if (r.bus != other_bus) {
            os << other_bus << " ";
          }
        }
      }
      os << endl;
    }
  }
  return os;
}

ostream& operator<<(ostream& os, const AllBusesResponse& r) {
  if (r.b2s.empty()) {
    os << "No buses";
  } else {
    for (const auto& bus_item : r.b2s) {
      os << "Bus " << bus_item.first << ": ";
      for (const string& stop : bus_item.second) {
        os << stop << " ";
      }
      os << endl;
    }
  }
  return os;
}