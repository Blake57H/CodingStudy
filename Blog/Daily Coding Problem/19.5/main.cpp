#include <iostream>
#include <vector>

bool isNQueenValid(const std::vector<size_t> &board)
{
    size_t lastQueenRow, lastQueenCol, colDiff, rowDiff;
    lastQueenRow = board.size() - 1;
    lastQueenCol = board.back();
    for (size_t row = 0; row + 1 < board.size(); row++)
    {
        colDiff = std::llabs(board[row] - lastQueenCol);
        if (colDiff == 0)
            return false; // same column
        if (rowDiff = std::llabs(row - lastQueenRow); rowDiff == colDiff)
            return false; // same diagonal
    }
    return true;
}

// index of board represents row of the queen. value of a board item represents columns of the queen
// n: number of queen. board: board represented as 1D array.
size_t solveNQueen(const size_t &n, std::vector<size_t> &board)
{
    if (board.size() == n)
        return 1;

    size_t count = 0;
    for (size_t col = 0; col < n; col++)
    {
        board.emplace_back(col);
        if (isNQueenValid(board))
        {
            count += solveNQueen(n, board);
        }
        board.pop_back();
    }
    return count;
}

bool isFlightRouteValid(
    std::vector<std::pair<std::string, std::string>> &flights,
    std::vector<std::pair<std::string, std::string>> &routes)
{
    // if flights are exhausted, then a route is complete
    if (flights.size() == 0)
        return true;

    // checking flights are connecting with each other
    for (auto i = routes.begin() + 1; i != routes.end(); i++)
        if ((i - 1)->second != i->first)
            return false;

    // checking if a valid connecting flight is present
    for (auto &flight : flights)
        if (routes.back().second == flight.first)
            return true;
    return false;
}

// using 2d array, "since it's possible to have a cycle in the graph".
std::vector<std::vector<std::pair<std::string, std::string>>> solveFlight(
    std::vector<std::pair<std::string, std::string>> &flights,
    std::vector<std::pair<std::string, std::string>> &flightItinerary)
{
    if (flights.size() == 0)
    {
        return std::vector<std::vector<std::pair<std::string, std::string>>>{flightItinerary};
    }

    std::vector<std::vector<std::pair<std::string, std::string>>> possibleRoutes;
    std::pair<std::string, std::string> flight;
    for (size_t i = 0; i < flights.size(); i++)
    {
        flight = flights.back();
        flights.pop_back(); // take an item from the back, then put it in the front.
        flightItinerary.emplace_back(flight);
        if (isFlightRouteValid(flights, flightItinerary))
            for (auto &route : solveFlight(flights, flightItinerary))
                possibleRoutes.push_back(route);

        flights.insert(flights.begin(), flight); // creating sub array this way...
        flightItinerary.pop_back();
    }
    return possibleRoutes;
}

int main(int argc, char *argv[])
{
    std::vector<size_t> board;
    for (size_t i = 0; i < 10; i++)
    {
        board.clear();
        std::cout << solveNQueen(i, board) << " ";
    }
    std::cout << std::endl;

    std::vector<std::pair<std::string, std::string>>
        route, // empty placeholder
        flights{
            // std::make_pair("HNL", "YUL"),
            std::make_pair("HNL", "AKL"),
            std::make_pair("YUL", "ORD"),
            std::make_pair("ORD", "SFO"),
            std::make_pair("SFO", "HNL")};
    if (auto possibleRoutes = solveFlight(flights, route); possibleRoutes.size() == 0)
        std::cout << "No possible route.\n";
    else
        for (auto &possibleRoute : solveFlight(flights, route))
        {
            std::cout << possibleRoute.front().first;
            for (auto &flight : possibleRoute)
                std::cout << " --> " << flight.second;
            std::cout << std::endl;
        }

    return 0;
}