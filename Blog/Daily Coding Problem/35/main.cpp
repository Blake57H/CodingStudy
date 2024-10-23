#include <iostream>
#include <vector>

const char R = 'R', G = 'G', B = 'B', END = '\0';

void segregate(char *array)
{
    char *front_ptr = array, *back_ptr = array, temp;
    // segregate 'R'
    while (*back_ptr != END && *front_ptr != END)
    {
        if (*back_ptr == R)
        { // find the first occurrence of not 'R' character
            back_ptr++;
            continue;
        }
        if (*front_ptr != R || front_ptr < back_ptr)
        { // find the first occurrence of 'R' character beyond back pointer
            front_ptr++;
            continue;
        }
        // swap
        temp = *front_ptr;
        *front_ptr = *back_ptr;
        *back_ptr = temp;
        back_ptr++;
        front_ptr++;
    }

    // repeat and segregate 'G'
    front_ptr = back_ptr;
    while (*back_ptr != END && *front_ptr != END)
    {
        if (*back_ptr == G)
        { // find the first occurrence of not 'G' character
            back_ptr++;
            continue;
        }
        if (*front_ptr != G || front_ptr < back_ptr)
        { // find the first occurrence of 'G' character beyond back pointer
            front_ptr++;
            continue;
        }
        // swap
        temp = *front_ptr;
        *front_ptr = *back_ptr;
        *back_ptr = temp;
        back_ptr++;
        front_ptr++;
    }

    // since sorting 'R' and 'G' is using the same procedure, 
    // it can be made into a function to reduce duplicated code.
}

void solve(char *array)
{
    std::cout << "Before: " << array << std::endl;
    segregate(array);
    std::cout << "After:  " << array << std::endl;
}

int main(int argc, char *argv[])
{
    std::string a{'G', 'B', 'R', 'R', 'B', 'R', 'G'}; // using std::string because I don't want the hassle of freeing memory
    solve(a.data());

    std::string b("RRRRBBBBBBGGGGGG");
    solve(b.data());

    std::string c("RGBRGBRGB");
    solve(c.data());
    return 0;
}