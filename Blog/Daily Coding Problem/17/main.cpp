#include <iostream>
#include <vector>
#include <memory>
#include <map>      // using ordered map to preserve string order.
#include <sstream>  // string stream
#include <assert.h> // some safety check, shouldn't trigger
// #include <cmath>

class PathObj
{
public:
    std::string mPathName;
    std::shared_ptr<PathObj> mParent = nullptr;      // use both child and parent pointer to make navigation easier
    bool isDir;                                      // infer from path name (contains period or not)
    std::vector<std::shared_ptr<PathObj>> mDirItems; // if PathObj is dir, record childs here

    PathObj(std::string_view pathName, const PathObj *parent)
    {
        this->mPathName = std::string{pathName};
        this->isDir = pathName.find('.') == std::string::npos;
        this->mParent = parent == nullptr ? nullptr : std::make_shared<PathObj>(*parent);
    }

    PathObj(std::string_view pathName) : PathObj(pathName, nullptr)
    {
    }

    std::string absolutePath()
    { // something similar to python's pathlib
        if (mParent == nullptr)
            return mPathName;

        std::stringstream stream;
        stream << mParent->absolutePath() << '/' << mPathName;
        return stream.str();
    }
};

static void printPathObj(std::shared_ptr<PathObj> obj, const int &currDepth)
{
    for (int i = 0; i < currDepth; i++)
        std::cout << '\t';
    std::cout << obj->mPathName << std::endl;
    for (auto i : obj->mDirItems)
        printPathObj(i, currDepth + 1);
}

static void pathParser(const std::string_view str, std::shared_ptr<PathObj> pathObj)
{ //                                               ^^^^^^^ I wanna edit this inplace
    std::vector<std::string> paths;

    for (size_t pathItemStrStart = 0, pathItemStrEnd = 0; pathItemStrEnd != std::string::npos; pathItemStrStart = pathItemStrEnd + 1)
    {                                                               // split the whole string by '\n', and save all substring to `paths`
        pathItemStrEnd = str.find_first_of('\n', pathItemStrStart); // from current to next '\n'
        // if(pathItemStrEnd==std::string::npos) pathItemStrEnd = str.length();
        paths.push_back(std::string{str.substr(pathItemStrStart, pathItemStrEnd - pathItemStrStart)});
    }

    int currentDepth = 0, pathDepth;
    std::shared_ptr<PathObj> currentPath = pathObj;

    // std::cout << (size_t)&(*currentPath) << std::endl << (size_t)&(*pathObj) << std::endl;
    // std::cout << "Parsed paths: \n";
    for (std::string_view item : paths)
    {
        // std::cout << item << std::endl; // test

        pathDepth = item.find_first_not_of('\t', 0);
        assert(abs(pathDepth - currentDepth) <= 1);
        if (pathDepth > currentDepth)
        { // this path item is a child of current path
            currentPath = currentPath->mDirItems.back();
            currentDepth += 1;
        }
        else if (pathDepth < currentDepth)
        { // this path item is its parent's neighbour
            currentDepth -= 1;
            currentPath = currentPath->mParent;
        } // else, this path is current path's neighbour
        assert(currentPath != nullptr);
        // std::cout << pathDepth << ": " << item.substr(pathDepth, std::string::npos) << std::endl;
        currentPath->mDirItems.push_back(std::make_shared<PathObj>(item.substr(pathDepth, std::string::npos)));
        currentPath->mDirItems.back()->mParent = currentPath;
    }

    // printPathObj(pathObj, -1);
    // printPathObj(currentPath, 0);
}

std::string_view longestPathLengthFinder(std::shared_ptr<PathObj> pathObj)
{ // why returning string view works?
    // std::cout << "Current path: " << pathObj->mPathName << std::endl;
    if (pathObj->mDirItems.size() == 0)
        return pathObj->absolutePath();

    std::string longestPath = pathObj->absolutePath();
    size_t longestLength = longestPath.length();
    for (std::shared_ptr<PathObj> &item : pathObj->mDirItems)
    {
        if (std::string_view p = longestPathLengthFinder(item); p.length() > longestLength)
        {
            longestLength = p.length();
            // longestPath = std::string{p};
            longestPath = p;
            // std::cout << p << std::endl;
        }
    }
    return longestPath;
}

int solve()
{
    // std::shared_ptr<PathObj> rootDir = std::make_shared<PathObj>("");
    std::shared_ptr<PathObj> rootDir = std::make_shared<PathObj>("");
    pathParser("dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext", rootDir);

    // std::cout << "rootDir at solve:";
    // printPathObj(rootDir, -1);
    // std::cout << rootDir->mDirItems.size() << std::endl;

    std::string_view result = longestPathLengthFinder(rootDir);
    std::cout << "Longest path: size=" << result.length() << "; path=\"" << result << "\"\n";
    return result.length();
}

int main(int argc, char *argv[])
{
    auto result = solve();
    std::cout << "Result (initial slash removed): " << (result == 0 ? 0 : result - 1) << "\n";
    return 0;
}