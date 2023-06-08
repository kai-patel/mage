set CC=clang
set CFLAGS=-Wall -Wextra -g
set CXX=clang++
set CXXFLAGS=-Wall -Wextra -g
set LDFLAGS=

cd %~dp0
cd ..

if exist build\ (
    rmdir /S /Q "build"
)

mkdir build
cmake -S . -B build -G"Unix Makefiles" -DBUILD_TESTING=1 -DCMAKE_BUILD_TYPE=Release
cmake --build build

