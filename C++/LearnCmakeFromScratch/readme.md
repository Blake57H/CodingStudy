# Learning material is a Youtube playlist

This folder is my code-along with [CMAKE TUTORIAL by Code, Tech, and Tutorials](https://www.youtube.com/playlist?list=PLalVdRk2RC6o5GHu618ARWh0VO0bFlif4)

I am using Windows 11.

## Notes

### Basic cmake build command

Current dir: "1. Getting started\out\build_mingw_make"

```bash
cmake -S ..\..\ -B . -G "MinGW Makefiles"   <-- cmake to make
cmake --build .                             <-- make to executable
```