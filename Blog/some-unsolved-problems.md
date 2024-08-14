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
