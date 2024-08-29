# Some C++ issues that's beyond my skill/understanding

## Release build shared library of JsonCPP using VS2022 seems not working

It won't parse document. Switching back to debug build fix this issue (I have no idea what's the difference...)

## Iterating `cpr::Cookies` causes ITERATOR LIST CORRUPTED! error

I wanna check if my responses contains cookies.

```c++
cpr::Cookies c;
cpr::Cookies::iterator b = c.begin(), e = c.end();  // fine
std::cout << &b << '\n' << &e << std::endl;  // fine
c.begin() == c.end();  // vector iterators incompatible error
&b == &e;  // fine
return;   // ITERATOR LIST CORRUPTED! on return
```

I have no idea what's wrong with it. May be I will try to rebuild all the libraries into static.

**Update**: Maybe it was caused my mismatching release library binary with debug app binary...

## Reading file with buffer length bigger than 1 will print some garbage text at the end

Reference: [https://stackoverflow.com/questions/19247443/c-garbage-at-the-end-of-file](https://stackoverflow.com/questions/19247443/c-garbage-at-the-end-of-file)

```c++
// main.cpp

#include <iostream>
#include <fstream>
#include <format>
#include <vector>

int main(const int argc, const char** argv){
    std::cout << ":)" << std::endl;
    for(int i = 0; i < argc; i++){
        std::cout << std::format("arg[{}]:\t{}\n", i, argv[i]);
    }

    if(argc <= 1)
        return 0;
    std::string_view in_file_path = argv[1];
    std::ifstream ifs;
    ifs.open(in_file_path.data(), std::ios::in|std::ios::binary);
    int length = 20;
    std::vector<char> buffer_data(length+1);
    if(!ifs.good()){
        std::cerr << std::format("bad file stream: {}\n", in_file_path);
        return -1;
    }
    while(ifs.good() && !ifs.eof()){
        ifs.read(buffer_data.data(), length);
        std::cout << buffer_data.data();
    }
    ifs.close();
    // delete buffer_data;
}
```

Using the code above to read the cpp file (`file-checksum-cpp.exe main.cpp`), produces the following result:

```text
:)
arg[0]: file-checksum-cpp.exe
arg[1]: main.cpp
#include <iostream>
#include <fstream>
#include <format>
#include <vector>

int main(const int argc, const char** argv){
    std::cout << ":)" << std::endl;
    for(int i = 0; i < argc; i++){
        std::cout << std::format("arg[{}]:\t{}\n", i, argv[i]);
    }

    if(argc <= 1)
        return 0;
    std::string_view in_file_path = argv[1];
    std::ifstream ifs;
    ifs.open(in_file_path.data(), std::ios::in|std::ios::binary);
    int length = 20;
    std::vector<char> buffer_data(length+1);
    if(!ifs.good()){
        std::cerr << std::format("bad file stream: {}\n", in_file_path);
        return -1;
    }
    while(ifs.good() && !ifs.eof()){
        ifs.read(buffer_data.data(), length);
        std::cout << buffer_data.data();
    }
    ifs.close();
    // delete buffer_data;
}lete buffer_
```

Clearly there is garbage text at the end.

If I read 1 byte at a time, the problem wouldn't exist.

WHat tHe FuCk?

**update:** manually setting the last character right after `ifs.read` seem helped the issue.

```c++
...
ifs.read(buffer_data.data(), length);
buffer_data[ifs.gcount()] = '\0';
```
