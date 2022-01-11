#include <string>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
    string operation_code;
    is >> operation_code;
    if (operation_code == "NEW_BUS") {
        q.type = QueryType::NewBus;
        is >> q.bus;
        int stop_count = 0;
        is >> stop_count;
        q.stops.resize(stop_count);
        for (string& stop : q.stops) {
            is >> stop;
        }
    } else if (operation_code == "BUSES_FOR_STOP") {
        q.type = QueryType::BusesForStop;
        is >> q.stop;
    } else if (operation_code == "STOPS_FOR_BUS") {
        q.type = QueryType::StopsForBus;
        is >> q.bus;
    } else if (operation_code == "ALL_BUSES") {
        q.type = QueryType::AllBuses;
    }
    return is;
}

struct BusesForStopResponse {
    vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    if (r.buses.empty()) {
        os << "No stop";
    } else {
        for (const string& bus : r.buses) {
            os << bus << " ";
        }
    }
    return os;
}

struct StopsForBusResponse {
    string bus;
    vector<string> stops;
    map<string, vector<string> > buses;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    if (r.stops.empty()) {
        os << "No bus";
    } else {
        for (const auto& stop : r.stops) {
            os << "Stop " << stop << ":";
            if (r.buses.count(stop) != 0 ) {
                int counter = 0;
                for (const string& bus : r.buses.at(stop)) {
                    if (bus != r.bus) {
                        os << " " << bus;
                        ++counter;
                    }
                }
                if (counter == 0) {
                    os << " no interchange";
                }
            } else {
                os << " no interchange";
            }
            os << endl;
        }
    }
    return os;
}

struct AllBusesResponse {
    map<string, vector<string>> buses;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
    if (r.buses.empty()) {
        os << "No buses";
    } else {
        for (const auto& bus : r.buses) {
            os << "Bus " << bus.first << ":";
            for (const string& stop : bus.second) {
                os << " " << stop ;
            }
            os << "\n";
        }
    }
    return os;
}

class BusManager {
public:
    void AddBus(const string& bus, const vector<string>& stops) {
        buses_.insert(make_pair(bus, stops));
        for (const auto& stop : stops) {
            stops_[stop].push_back(bus);
        }
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
        if (stops_.find(stop) == stops_.end()) {
            return BusesForStopResponse{vector<string>()};
        } else {
            return BusesForStopResponse{stops_.at(stop)};
        }
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {
        StopsForBusResponse res;
        if (buses_.count(bus) > 0) {
            res.bus = bus;
            res.stops = buses_.at(bus);
            res.buses = stops_;
        }
        return res;
    }

    AllBusesResponse GetAllBuses() const {
        return AllBusesResponse{buses_};
    }
private:
    map<string, vector<string>> buses_;
    map<string, vector<string>> stops_;
};

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
                cout << bm.GetStopsForBus(q.bus);
                break;
            case QueryType::AllBuses:
                cout << bm.GetAllBuses() << endl;
                break;
        }
    }

    return 0;
}
