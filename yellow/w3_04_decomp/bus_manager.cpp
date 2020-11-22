

#include "bus_manager.h"

void BusManager::AddBus(const string& bus, const vector<string>& stops) {
  for (auto& stop : stops) {
    stops_to_buses[stop].push_back(bus);
    buses_to_stops[bus].push_back(stop);
  }
}

BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
  BusesForStopResponse bfs;
  bfs.stop = stop;
  bfs.s2b = stops_to_buses;
  return bfs;
}

StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
  StopsForBusResponse sfb;
  sfb.bus = bus;
  sfb.s2b = stops_to_buses;
  sfb.b2s = buses_to_stops;
  return sfb;
}

AllBusesResponse BusManager::GetAllBuses() const {
  AllBusesResponse b;
  b.b2s = buses_to_stops;
  b.s2b = stops_to_buses;
  return b;
}
