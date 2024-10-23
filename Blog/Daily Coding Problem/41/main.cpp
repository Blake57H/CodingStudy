#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <sstream>

std::string print_vector(const std::vector<std::string> &vtr)
{
    if (vtr.size() == 0)
        return "null";
    std::ostringstream oss;
    for (auto i = vtr.begin(); i != vtr.end(); i++)
    {
        oss << *i;
        if (i != vtr.end() - 1)
            oss << " --> ";
    }
    return oss.str();
}

std::vector<std::string> solve_recursive(const std::unordered_map<std::string, std::vector<std::string>> &flight_map, const std::string &start)
{
    std::vector<std::string> result;
    auto destination_candidates = flight_map.find(start);

    // this is the final destination because map is empty
    if (flight_map.size() == 0)
    {
        result.emplace_back(start);
        return result;
    }

    // next destination not found, cannot proceed, return null
    if (destination_candidates == flight_map.end() || destination_candidates->second.size() == 0)
        return result;

    // iterate through destinations to find a valid route
    // remove this destination from flight map and try recursive solve
    for (size_t i = 0; i < destination_candidates->second.size(); i++)
    {
        std::unordered_map<std::string, std::vector<std::string>> flight_map_copied{flight_map};
        std::string dest;
        {
            auto a = flight_map_copied.find(start); // locate this starting location
            dest = *(a->second.begin() + i);        // select a destination from this starting location

            // remove destination from this starting location value. This destination has been used.
            if (destination_candidates->second.size() == 1)
                flight_map_copied.erase(start);
            else
                a->second.erase(a->second.begin() + i);
        }

        // recursive solve
        if (auto solve_result = solve_recursive(flight_map_copied, dest); solve_result.size() == 0)
            continue; // no result means this route is invalid
        else
        {   // yes result means this route is valid
            // and since destinations are sorted alphabetically, first result will be the lexicographically smallest one

            result = std::vector(solve_result); // copy results
            result.insert(result.begin(), start);
            return result;
        }
    }
    return result;
}

std::vector<std::string> solve(const std::vector<std::pair<std::string, std::string>> &flights, const std::string &start)
{
    // building map
    std::unordered_map<std::string, std::vector<std::string>> flights_alt;
    for (auto flight : flights)
        if (auto search_result = flights_alt.find(flight.first); search_result != flights_alt.end())
            search_result->second.emplace_back(flight.second);
        else
            flights_alt.emplace(flight.first, std::vector<std::string>({flight.second}));
    for (auto flight : flights_alt)
        std::sort(flight.second.begin(), flight.second.end()); // sort destinations so that I could read data in lexicographical order

    return solve_recursive(flights_alt, start);
}

int main(int argc, char *argv[])
{
    // a list of {tickets-starting_point pairs}
    std::vector<std::pair<std::vector<std::pair<std::string, std::string>>, std::string>> test_data{
        // data1
        {{{"SFO", "HKO"}, {"YYZ", "SFO"}, {"YUL", "YYZ"}, {"HKO", "ORD"}}, "YUL"},
        // data2
        {{{"SFO", "COM"}, {"COM", "YYZ"}}, "COM"},
        // data 3
        {{{"A", "B"}, {"A", "C"}, {"B", "C"}, {"C", "A"}}, "A"}
        // end of test data
    };
    for (auto data : test_data)
        std::cout << "Result: " << print_vector(solve(data.first, data.second)) << "\n";
    return 0;
}