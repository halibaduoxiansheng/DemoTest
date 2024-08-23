# vsCode配置——c语言

现在下载vscode

**下载地址**：

[https://code.visualstudio.com/](https://code.visualstudio.com/)

下载后，两项关键插件 中文插件 和 C/C++

![Alt text](F:\MarkTextProject\photo\2024-08-19-17-45-17-image.png)

![Alt text](F:\MarkTextProject\photo\2024-08-19-17-45-25-image.png)

本篇采用gcc编译器：mingw64

下载地址：

[Downloads - MinGW-w64](https://www.mingw-w64.org/downloads/)[Downloads - MinGW-w64](https://www.mingw-w64.org/downloads/)

**编译环境设置**

![](F:\MarkTextProject\photo\2024-08-19-17-48-38-image.png)

验证

![](F:\MarkTextProject\photo\2024-08-19-17-49-47-image.png)

下载clangd插件（查错）

![](F:\MarkTextProject\photo\2024-08-19-17-50-28-image.png)

配置

于配置中搜索clangd，点击：添加项（设置模仿如下 -I + 地址）

![](F:\MarkTextProject\photo\2024-08-19-17-51-47-image.png)

于搜索框内输入 >c 选中

![](F:\MarkTextProject\photo\2024-08-19-17-52-25-image.png)

配置如下

![](F:\MarkTextProject\photo\2024-08-19-17-52-52-image.png)

![](F:\MarkTextProject\photo\2024-08-19-17-53-12-image.png)

上面图片其中内容(复制于)：

![Alt text](F:\MarkTextProject\photo\2024-08-19-17-54-03-image.png)

**找到最下面去复制**

（运行后才会有tasks.json文件） 依次给出配置

![](F:\MarktextPhoto\2024-08-19-17-55-18-image.png)

```
{
    "configurations": [
        {
            "name": "windows-gcc-x64",
            "includePath": [
                "${workspaceFolder}/**",
                "D:/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/8.1.0/include/c++",
                "D:/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/8.1.0/include/c++/x86_64-w64-mingw32",
                "D:/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/8.1.0/include/c++/backward",
                "D:/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/8.1.0/include",
                "D:/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/8.1.0/include-fixed",
                "D:/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/8.1.0/../../../../x86_64-w64-mingw32/include"
            ],
            "compilerPath": "D:/mingw64/bin/gcc.exe",
            "cStandard": "${default}",
            "cppStandard": "${default}",
            "intelliSenseMode": "windows-gcc-x64",
            "compilerArgs": [
                ""
            ]
        }
    ],
    "version": 4
}
```

```
{
  "version": "0.2.0",
  "configurations": [
    {
      "name": "g++.exe build and debug active file",
      "type": "cppdbg",
      "request": "launch",
      "program": "${fileDirname}/${fileBasenameNoExtension}.exe",
      "args": [],
      "stopAtEntry": false,
      "cwd": "${fileDirname}",
      "environment": [],
      "externalConsole": true,
      "MIMode": "gdb",
      "miDebuggerPath": "D:\\mingw64\\bin\\gdb.exe",
      "preLaunchTask": "g++.exe build active file",
      "setupCommands": [
        {
          "description": "为 gdb 启用整齐打印",
          "text": "-enable-pretty-printing",
          "ignoreFailures": true
        }
      ]
    },
    {
      "name": "C/C++ Runner: Debug Session",
      "type": "cppdbg",
      "request": "launch",
      "args": [],
      "stopAtEntry": false,
      "externalConsole": true,
      "cwd": "f:/MarkTextProject/testGUI",
      "program": "f:/MarkTextProject/testGUI/build/Debug/outDebug",
      "MIMode": "gdb",
      "miDebuggerPath": "gdb",
      "setupCommands": [
        {
          "description": "Enable pretty-printing for gdb",
          "text": "-enable-pretty-printing",
          "ignoreFailures": true
        }
      ]
    }
  ]
}
```

```
{
  "C_Cpp_Runner.cCompilerPath": "gcc",
  "C_Cpp_Runner.cppCompilerPath": "g++",
  "C_Cpp_Runner.debuggerPath": "gdb",
  "C_Cpp_Runner.cStandard": "",
  "C_Cpp_Runner.cppStandard": "",
  "C_Cpp_Runner.msvcBatchPath": "C:/Program Files/Microsoft Visual Studio/VR_NR/Community/VC/Auxiliary/Build/vcvarsall.bat",
  "C_Cpp_Runner.useMsvc": false,
  "C_Cpp_Runner.warnings": [
    "-Wall",
    "-Wextra",
    "-Wpedantic",
    "-Wshadow",
    "-Wformat=2",
    "-Wcast-align",
    "-Wconversion",
    "-Wsign-conversion",
    "-Wnull-dereference"
  ],
  "C_Cpp_Runner.msvcWarnings": [
    "/W4",
    "/permissive-",
    "/w14242",
    "/w14287",
    "/w14296",
    "/w14311",
    "/w14826",
    "/w44062",
    "/w44242",
    "/w14905",
    "/w14906",
    "/w14263",
    "/w44265",
    "/w14928"
  ],
  "C_Cpp_Runner.enableWarnings": true,
  "C_Cpp_Runner.warningsAsError": false,
  "C_Cpp_Runner.compilerArgs": [],
  "C_Cpp_Runner.linkerArgs": [],
  "C_Cpp_Runner.includePaths": [],
  "C_Cpp_Runner.includeSearch": [
    "*",
    "**/*"
  ],
  "C_Cpp_Runner.excludeSearch": [
    "**/build",
    "**/build/**",
    "**/.*",
    "**/.*/**",
    "**/.vscode",
    "**/.vscode/**"
  ],
  "C_Cpp_Runner.useAddressSanitizer": false,
  "C_Cpp_Runner.useUndefinedSanitizer": false,
  "C_Cpp_Runner.useLeakSanitizer": false,
  "C_Cpp_Runner.showCompilationTime": false,
  "C_Cpp_Runner.useLinkTimeOptimization": false,
  "C_Cpp_Runner.msvcSecureNoWarnings": false,
  "files.associations": {
    "stdio.h": "c",
    "STDIO.H": "cpp",
    "time.h": "c"
  }
}
```

```

```
