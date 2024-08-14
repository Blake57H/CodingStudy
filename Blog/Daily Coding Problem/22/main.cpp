#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>
#include <sstream>
#include <unordered_set>

/* some too complicated attempts */

/*
struct WordNode
{
    char ch;     // char (root node == 0)
    bool isWord; //
    std::unordered_map<char, std::shared_ptr<WordNode>> nextNodes;

    WordNode(char c, bool isWord) : ch(c), isWord(isWord) {};

    WordNode(char c) : WordNode(c, false) {};
};

void addBranch(std::shared_ptr<WordNode> &currNode, std::string word)
{ // build the word tree branch
    char c = word.front();
    auto f = currNode->nextNodes.find(c);
    if (f == currNode->nextNodes.end())
    {
        currNode->nextNodes.insert({c, std::make_shared<WordNode>(c)});
        f = currNode->nextNodes.find(c);
    }
    if (word.length() == 1)
        f->second->isWord = true; // duplicate node, but this is a word
    else
        addBranch(f->second, word.substr(1, word.length() - 1));
}

// return empty vector to indicate no result found
std::vector<std::string> checkStr(std::shared_ptr<WordNode> &rootNode, std::string str)
{
    std::shared_ptr<WordNode> currNode = rootNode;
    bool complete_mark = false;
    // std::stack<std::shared_ptr<WordNode>> checkpoints;
    std::vector<std::string> final_result, intermidiate_result;
    // auto next_char = rootNode->nextNodes.find(str.front());
    auto char_ptr = str.begin();
    return final_result;
}

std::string solve(std::vector<std::string> words, std::string_view str)
{
    std::shared_ptr<WordNode> rootNode = std::make_shared<WordNode>((char)0);
    for (std::string word : words)
        addBranch(rootNode, word);
    return "";
}
*/

std::string solve_v2(std::vector<std::string> words, std::string_view str)
{
    if (str.length() == 0)
        return "";

    std::vector<std::string_view::iterator> checkpoints{str.begin()}; // marks the beginning of the next word.
    std::unordered_set<std::string> words_set = std::unordered_set<std::string>{words.begin(), words.end()};
    std::string_view::iterator char_ptr_start = checkpoints.back(),
                               char_ptr_end = char_ptr_start + 1;
    bool complete_mark = false;

    std::string substr;
    while (checkpoints.size() != 0)
    {
        // get a word from str, and check is such word in words set.
        // std::cout << (char_ptr_start - str.begin()) << ' ' << (char_ptr_end - char_ptr_start) << std::endl;
        substr = str.substr(char_ptr_start - str.begin(), char_ptr_end - char_ptr_start);
        if (auto founded_word = words_set.find(substr); founded_word != words_set.end())
        {
            checkpoints.emplace_back(char_ptr_end);
            char_ptr_start = char_ptr_end;
        }

        // after checking a word, do some post-checking action here

        // the whole string is checked, with all words matched.
        if (char_ptr_start == str.end())
            break;

        // with current checkpoints, str isn't a combination of words set
        if (char_ptr_end == str.end())
        {
            char_ptr_end = checkpoints.back() + 1;
            checkpoints.pop_back();
            // current words set could match this string
            if (checkpoints.size() == 0)
                break;
            char_ptr_start = checkpoints.back();
        }

        char_ptr_end += 1; // make sure char_ptr_end!=str.end() before +=1
    }

    std::stringstream ss;
    ss << '[';
    if (checkpoints.size() > 0)
        for (auto cp_ptr = checkpoints.begin() + 1; cp_ptr != checkpoints.end(); cp_ptr++)
        {
            char_ptr_start = *(cp_ptr - 1);
            char_ptr_end = cp_ptr == checkpoints.end() ? str.end() : *cp_ptr;
            ss << str.substr(char_ptr_start - str.begin(), char_ptr_end - char_ptr_start);
            if (cp_ptr + 1 != checkpoints.end()) // <-- wtf?
                ss << ", ";
        }
    ss << ']';
    return ss.str();
}

int main(int argc, char *argv[])
{
    std::vector<std::string>
        words1{"the", "quick", "brown", "fox"},
        words2{"bed", "bath", "bedbath", "and", "beyond"},
        words3{"bed", "bath", "bat", "hand", "beyond"};

    std::string
        str1{"thequickbrownfox"},
        str2{"bedbathandbeyond"};

    // auto result = solve_v2(words1, str1);
    // auto result = solve_v2(words2, str2);
    auto result = solve_v2(words3, str2);

    std::cout << "Result: " << result << "\n";
    return 0;
}