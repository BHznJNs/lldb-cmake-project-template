# lldb-cmake-project-template

This is a template C++ project used with cmake, lldb and clang in VSCode.

## Before Started

Before you start using this template, please install these requirements:

1. cmake
2. bear
3. clang
4. clangd
5. lldb

And some VSCode extensions:

1. clangd
2. CMake
3. CMake Tools
4. CodeLLDB

## Get Started

Clone this repo
```shell
git clone https://github.com/BHznJNs/lldb-cmake-project-template
cd lldb-cmake-project-template
```

Create build directory
```shell
mkdir build && cd build
```

Compile project
```shell
# build/
cmake ..
make
```

If there is no `compile_commands.json` file in the build directory, use this command
```shell
# build/
bear -- make
```
