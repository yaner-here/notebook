# CMake

参考资料：

- 《Modern CMake for Cpp》 [英文原版](https://github.com/PacktPublishing/Modern-CMake-for-Cpp) [民间中文翻译](https://github.com/xiaoweiChen/Modern-CMake-for-Cpp)

# §1 CMake命令

CMake是一个针对C++的自动化工具，可以自动编译库和程序、管理依赖关系、完成测试和打包、生成文档。该工具包含五个程序：

- `cmake`：配置、生成、构建项目
- `ctest`：测试项目
- `cpack`：打包项目
- `cmake-gui`：CMake的GUI界面
- `ccmake`：CMake的CLI界面，需要手动安装`apt install cmake-curses-gui`

以下面的项目为例，我们可以用`g++`手动编译程序。

```shell
$ ls
hello.cpp

$ cat hello.cpp
#include <iostream>
int main() {
  std::cout << "Hello World!" << std::endl;
  return 0;
}

$ g++ ./hello.cpp -o Hello
$ ./Hello
Hello World!
```

当项目规模变得庞大时，还使用手动编译就显得不太现实了。使用CMake，我们可以自动完成上面的操作。

```shell
$ ls
CMakeLists.txt  hello.cpp

$ cat CMakeLists.txt
cmake_minimum_required(VERSION 3.20.0)
project(Hello)
add_executable(Hello hello.cpp)

$ cmake -B ./buildtree
-- The CXX compiler identification is GNU 13.2.0
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done (2.5s)
-- Generating done (0.1s)
-- Build files have been written to: ./buildtree

$ cmake --build ./buildtree
[ 50%] Building CXX object CMakeFiles/Hello.dir/hello.cpp.o
[100%] Linking CXX executable Hello
[100%] Built target Hello

$ ./buildtree/Hello
Hello World!
```

## §1.1 生成

**在生成阶段，CMake会生成构建系统的配置文件**。其语法为`cmake [OPTIONS] [-S <SOURCE_PATH>] [-B <BUILD_PATH>]`。其中`-S`指定源代码路径，`-B`指定构建路径，两者的缺省值都是当前目录`./`。工程中推荐将两者分隔开来，防止源代码和构建产物相互污染。其语法十分灵活，以下都是合法的命令行参数。

```shell
$ cmake -S <SOURCE_PATH> -B <BUILD_PATH>
$ cmake -S <SOURCE_PATH> <BUILD_PATH>
$ cmake <SOURCE_PATH>
$ cmake <EXISTING_BUILD_PATH>
```

`[-G <GENERATOR>]`用于指定CMake使用哪种构建系统，缺省时读取变量`CMAKE_GENERATOR`的值，再缺省时自动匹配当前环境内可用的构建系统。

某些构建系统支持细粒度的自定义选项，例如使用什么版本的编译器、构建在何种平台上等等，可以分别由`[-T <TOOLSET>]`和`[-A <ARCHITECTURE>]`指定。

CMake同样支持管理命令行参数。`[-C <INIT_SCRIPT_PATH>]`用于预先执行脚本获取参数，`[-D <VAR_NAME>[:<VAR_TYPE>]=<VALUE>]`用于手动指定参数。`[-L[A][H]]`用于展示所有非默认值的环境变量，其中`A`表示所有变量，`H`展示变量含义与帮助信息。`-U <VAR_NAME_REGEX>`表示删除环境变量，支持通配符。

## §1.2 构建

**在构建阶段，CMake会自动调用构建系统进行构建**。其语法为`cmake --build <BUILD_PATH> [--<BUILD_TOOL_OPTIONS>]`。这里的`<BUILD_PATH>`需要与生成阶段的`<BUILD_PATH>`保持一致。

现代构建系统大多支持多线程。CMake将其封装成`[--parallel [<JOBS_NUMBER>]]`或`[-j [<JOBS_NUMBER>]]`，缺省为变量`CMAKE_BUILD_PARALLEL_LEVEL`的值。

CMake允许使用`[--target <TARGET>]*`或`[-t <TARGET>]*`指定本次构建生成的目标。特殊地，`<TARGET>`为`clean`时表示清空构建目录。如果想要先清空再构建，可以使用语法糖`--clean-first`。

部分编译系统支持生成不同配置的编译产物（例如`Ninja`、`XCode`、`Visual Studio`）。CMake使用`--config <CONFIG>`指定配置，可选值有`Debug`、`Release`、`MinSizeRel`、`RelWithDebInfo`，缺省为变量`CMAKE_VERBOSE_MAKEFILE`的值，默认为`Debug`。

CMake允许用于自定义构建产物的安装流程，使用`cmake --install`执行这一流程。

## §1.3 项目文件

源代码和CMake项目文件所在的目录称为源码树（Source Tree）。其根目录必须提供`CMakeLists.txt`配置文件。

存储构建过程中的产物目录称为构建树（Build Tree），内部包含了项目的配置、缓存、日志、构建工具本身创建的文件、最终构建产物。该目录依赖与具体的平台与环境，所以不推荐将该目录添加到Git。

`CMakeLists.txt`用于声明一个构建单元，必须包含`cmake_minimum_required(VERSION <VERSION>)`来指定CMake的最低版本，包含`project(<NAME> <OPTIONS>)`来指定构建单元的名称。每个构建单元可以使用`add_subdirectory(<DIR_RELATIVE_PATH>)`来包含其它构建单元。

`CMakeCache.txt`创建于首次配置阶段，用于存储缓存变量，存储在构建树的根目录。

`<PACKAGE_NAME>-config.cmake`称为包配置文件，用于表示CMake如何使用该配置单元，来组合到其它的配置单元中。

`cmake_install.cmake`用于表示`cmake --install`的安装操作，由CMake自动生成，不推荐手动维护。

`CTestTestfile.cmake`用于表示`ctest`的测试操作，由CMake自动生成，不推荐手动维护。

`CPackConfig.cmake`用于表示`cpack`的打包操作，由CMake自动生成，不推荐手动维护。

`CMakePresets.json`/`CMakeUserPresets.json`用于预先指定生成器、构建树路径等信息。

```json
{
  "version": 1,
  "cmakeMinimumRequired": {
    "major": 3,
    "minor": 19,
    "patch": 3
  },
  "configurePresets": [
    {
      "name": "my-preset",
      "displayName": "Custom Preset",
      "description": "Custom build - Ninja generator",
      "generator": "Ninja",
      "binaryDir": "${sourceDir}/build/ninja",
      "cacheVariables": {
        "FIRST_CACHE_VARIABLE": {
          "type": "BOOL",
          "value": "OFF"
        },
        "SECOND_CACHE_VARIABLE": "Ninjas rock"
      },
      "environment": {
        "MY_ENVIRONMENT_VARIABLE": "Test",
        "PATH": "$env{HOME}/ninja/bin:$penv{PATH}"
      },
      "vendor": {
        "vendor-one.com/ExampleIDE/1.0": {
          "buildQuickly": true
        }
      }
    },
    {
      "name": "my-preset-multi",
      "inherits": "my-preset",
      "displayName": "Custom Ninja Multi-Config",
      "description": "Custom build - Ninja Multi-Config generator",
      "generator": "Ninja Multi-Config"
    }
  ],
  "vendor": {
    "vendor-one.com/ExampleIDE/1.0": {
      "buildQuickly": false
    }
  }
}
```
## §1.A 日志

`cmake --system-information [OUTPUT_FILE_PATH]`用于输出CMake的所有默认配置。

`cmake --log-level=<LEVEL>`用于指定CMake运行过程中的日志级别，从低到高分别为`TRACE`、`DEBUG`、`VERBOSE`、`STATUS`、`NOTICE`、`WARNING`、`ERROR`。缺省时读取变量`CMAKE_MESSAGE_LOG_LEVEL`的值。

`cmake --log-context`用于为每条日志添加产生时的栈名。

`cmake --trace`是最详细、最万能的，它用于开启跟踪模式，输出每个命令调用的文件名、调用位置（即行号）、调用时的参数内容。