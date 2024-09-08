#include <iostream>
#include <stack>

// A silly attempt to make pairs more programmable
class Brackets
{
public:
    const char ROUND = '(',
               CURLY = '{',
               SQUARE = '[';

    bool isOpeningBracket(const char &c)
    {
        return true;
    }
};

bool solve(std::string_view str)
{
    std::stack<char> stack;
    for (char c : str)
    {
        // opening bracket
        switch (c)
        {
        case '(':
        case '{':
        case '[':
            stack.emplace(c);
            continue;
        default:
            // do nothing
            break;
        }

        // closing bracket
        if (stack.size() == 0)
            goto ret_false;
        switch (stack.top())
        {
        case '(':
            if (c != ')')
                goto ret_false;
            stack.pop();
            break;
        case '{':
            if (c != '}')
                goto ret_false;
            stack.pop();
            break;
        case '[':
            if (c != ']')
                goto ret_false;
            stack.pop();
            break;

        default:
            break;
        }
    }

    if (stack.size() == 0)
        return 1;
ret_false:
    return 0;
}

int main(int argc, char *argv[])
{
    std::cout << std::boolalpha << "Result: " << solve("([])[]({})") << "\n";
    std::cout << std::boolalpha << "Result: " << solve("([)]") << "\n";
    std::cout << std::boolalpha << "Result: " << solve("((()") << "\n";
    return 0;
}