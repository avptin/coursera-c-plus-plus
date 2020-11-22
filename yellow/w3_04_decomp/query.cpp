#include "query.h"

#include <iostream>


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
