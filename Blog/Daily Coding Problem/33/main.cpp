#include <iostream>
#include <cmath>
#include <vector>

class MedianValue
{
    // by design, this must be true or program breaks: abs(overflow_l - overflow_r) <= 1
    std::vector<double> lst;

    void print_list(){
        using namespace std;
        cout << '[';
        for(auto i : lst)
            cout << i << ',';
        cout << ']' << endl;
    }

public:
    /**
     * add an value and return the new median
     */
    double add_val(double d)
    {
        // auto iter = lst.begin();
        // while (iter != lst.end())
        // {
        //     if (d <= *iter)
        //         break;
        //     iter++;
        // }

        auto iter_l = lst.begin(), iter_r = lst.end(), iter = iter_l + (iter_r-iter_l) / 2;
        // if(lst.size() == 0)
        //     goto insert;
        // iter_r--;
        while(iter_r > iter_l){
            // std::cout << iter - lst.begin() << ',' << '\n';
            // if (iter_l == iter_r)
            //     break;
            if (*iter < d)
                iter_l = iter + 1;
            else
                iter_r = iter;
            iter = iter_l + (iter_r-iter_l) / 2;
        }

insert:
        lst.insert(iter, d);
        // print_list();
        return get_median();
    }

    double get_median()
    {
        size_t lst_len = lst.size();
        if (lst_len == 0)
            return INFINITY;
        else if (lst_len % 2 == 0)
            return lst[lst_len / 2 - 1] / 2 + lst[lst_len / 2] / 2;
        else
            // lst_len % 2 == 1
            return lst[(lst_len + 1) / 2 - 1];
    }
};

void solve(const std::vector<double> &seq)
{
    MedianValue mv;
    for (double val : seq)
        std::cout << mv.add_val(val) << std::endl;
    std::cout << std::endl;
}

int main(int argc, char *argv[])
{
    solve(std::vector<double>{2, 1, 5, 7, 2, 0, 5});
    return 0;
}