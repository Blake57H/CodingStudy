#include <iostream>
#include <vector>

int solve(const std::vector<std::pair<int, int>> &lectures)
{
    std::vector<std::vector<int>> schedules; // schedule[classroom[lecture]]
    //                                          ^ 2d-array         ^ element

    std::vector<int> sorted_lecture_index;
    { // sorting lectures
        std::vector<int>::iterator sli_iterator; // sorted lecture index iterator
        for (size_t i = 0; i < lectures.size(); i++)
        {
            sli_iterator = sorted_lecture_index.begin();
            while (sli_iterator != sorted_lecture_index.end() && lectures[i].first > lectures[*sli_iterator].first)
            {
                sli_iterator++;
            }
            sorted_lecture_index.insert(sli_iterator, i); // record the sorted index
        }
    }
    { // lining up lectures
        std::vector<std::vector<int>>::iterator schedule_iterator;
        for (auto i : sorted_lecture_index)
        {
            schedule_iterator = schedules.begin();
            while (schedule_iterator != schedules.end())
            {
                if (lectures[(*schedule_iterator).back()].second < lectures[i].first)
                    break;
                schedule_iterator++;
            }
            if (schedule_iterator == schedules.end())
                schedules.emplace_back(std::vector{i});
            else
                (*schedule_iterator).emplace_back(i);
        }
    }

    return schedules.size();
}

int main(int argc, char *argv[])
{
    // std::vector<std::pair<int, int>> lectures{std::make_pair(30, 75), std::make_pair(0, 50), std::make_pair(60, 150)};
    std::vector<std::pair<int, int>> lectures{std::make_pair(30, 75), std::make_pair(0, 50), std::make_pair(60, 150), std::make_pair(51, 59)};
    auto result = solve(lectures);
    std::cout << "Result: " << result << "\n";
    return 0;
}