#include <cassert>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;
enum class QueryType { NewBus, BusesForStop, StopsForBus, AllBuses };

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

istream& operator>>(istream& is, Query& q) {
  string cmd;
  is >> cmd;

  if (cmd == "NEW_BUS") {
    int stop_count;
    q.type = QueryType::NewBus;

    is >> q.bus;
    is >> stop_count;

    q.stops.resize(stop_count);
    for (string& stop : q.stops) {
      is >> stop;
    }
  } else if (cmd == "BUSES_FOR_STOP") {
    q.type = QueryType::BusesForStop;
    is >> q.stop;
  } else if (cmd == "STOPS_FOR_BUS") {
    q.type = QueryType::StopsForBus;
    is >> q.bus;
  } else if (cmd == "ALL_BUSES") {
    q.type = QueryType::AllBuses;
  }

  return is;
}

struct BusesForStopResponse {
  string stop;
  map<string, vector<string>> s2b;
};

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

struct StopsForBusResponse {
  string bus;
  map<string, vector<string>> s2b;
  map<string, vector<string>> b2s;
};

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

struct AllBusesResponse {
  map<string, vector<string>> b2s;
  map<string, vector<string>> s2b;
};

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

class BusManager {
 public:
  void AddBus(const string& bus, const vector<string>& stops) {
    for (auto& stop : stops) {
      stops_to_buses[stop].push_back(bus);
      buses_to_stops[bus].push_back(stop);
    }
  }

  BusesForStopResponse GetBusesForStop(const string& stop) const {
    BusesForStopResponse bfs;
    bfs.stop = stop;
    bfs.s2b = stops_to_buses;
    return bfs;
  }

  StopsForBusResponse GetStopsForBus(const string& bus) const {
    StopsForBusResponse sfb;
    sfb.bus = bus;
    sfb.s2b = stops_to_buses;
    sfb.b2s = buses_to_stops;
    return sfb;
  }

  AllBusesResponse GetAllBuses() const {
    AllBusesResponse b;
    b.b2s = buses_to_stops;
    b.s2b = stops_to_buses;
    return b;
  }

  // private:
  map<string, vector<string>> buses_to_stops, stops_to_buses;
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
  int query_count;
  Query q;

  cin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
    cin >> q;
    switch (q.type) {
      case QueryType::NewBus:
        bm.AddBus(q.bus, q.stops);
        break;
      case QueryType::BusesForStop:
        cout << bm.GetBusesForStop(q.stop) << endl;
        break;
      case QueryType::StopsForBus:
        cout << bm.GetStopsForBus(q.bus) << endl;
        break;
      case QueryType::AllBuses:
        cout << bm.GetAllBuses() << endl;
        break;
    }
  }

  return 0;
}
