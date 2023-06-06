set CC=clang
set CXX=clang++

cd %~dp0
cd ..

if exist build\ (
    rmdir /S /Q "build"
)

mkdir build
cmake -S . -B build -G"Unix Makefiles" -DBUILD_TESTING=1
cmake --build build

