# OpenCV Hood Detection (OHD)


# 1) Install Tools and add each tool to Windows path (system variables)
-CMake

-MSYS2(with mingw-w64) or directly Mingw-W64 (Adjust mingw settings, I used mingw-w64 8.1.0, x86_64, posix threads, seh)

-Ninja

-GoogleTest

-OpenCV
    -Download opencv release 4.6.0
    -Configure and generate the opencv CMake files (I used the cmake-gui. I had to disable GStreamer as it caused problems).
    -call mingw32-make in /build
    -Also see https://www.youtube.com/watch?v=Rda-AfBXme4&ab_channel=MuchlisHarlyWinata for details

(Optionally, get VSCode and extensions for C/C++ and CMake)

# Initial usage of project in VS Code
Let VSCode autoconfigure the CMake setup (when it detects a CMakeLists.txt)

# Building
-Visual Studio Code:

    Ctrl+Shift+P -> "CMake: Run Tests"

-Manually:

    cmake -S . -B build    (-S == SourceDirectory, -B == BuildDirectory)

    cmake --build build

# Executing the code
-Visual Studio Code:

    Ctrl+Shift+P -> "CMake: Run without Debugging" (or Shift+F5)

# Executing the tests
-Visual Studio Code:

    Ctrl+Shift+P -> "CMake: Run Tests"

-Manually:

    cd build && ctest
# Debugging
-Visual Studio Code:

    Ctrl+Shift+P -> "CMake: Debug" (or Ctrl+F5) -> select the executable of either the production-executable or the unittest-executable. Set your desired breakpoints before.

# Troubleshooting
-If VSCode cannot find gdb in your MSYS2 MinGW64 bin directory, probably gdb is missing in the Mingw64 installation. Add it with "pacman -S mingw-w64-x86_64-gdb".
