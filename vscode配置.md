# vsCode配置——c语言

现在下载vscode的配置

**下载地址**：

下载后，两项关键插件 中文插件 和 C/C++

![Alt text](F:\MarktextPhoto\50471ecb86d0605957e0260a9c67f2fc08545628.png)

![Alt text](F:\MarktextPhoto\6086af215cab400eb2a97c356e7fff02a0c1b65c.png)

本篇采用gcc编译器：mingw64

下载地址：

[Downloads - MinGW-w64](https://www.mingw-w64.org/downloads/)[Downloads - MinGW-w64](https://www.mingw-w64.org/downloads/)

**编译环境设置**

![Alt text](F:\MarktextPhoto\f8b0a2f0e12dbf30f54c65177ac18c7e5ee82180.png)

验证

![Alt text](F:\MarktextPhoto\9fc635831a657cfe8c9fd7b4d33655127899b81c.png)

下载clangd插件（查错）

![Alt text](F:\MarktextPhoto\23fde8c3299bb7ebe4cfe55d41700773201e489d.png)

配置

于配置中搜索clangd，点击：添加项（设置模仿如下 -I + 地址）

![Alt text](F:\MarktextPhoto\a83c465a38f210dd1532b7ec8e43f2baa6fea3a2.png)

于搜索框内输入 >c 选中

![Alt text](F:\MarktextPhoto\7c9d6fa4e980224a105222239cb48156d0cc3637.png)

配置如下

![Alt text](F:\MarktextPhoto\deb3bf12cf5cb57de504c3bbc93f0ad0cce07a8e.png)

![Alt text](F:\MarktextPhoto\83448051d25abadcfbfc2ee2914d485074c6e971.png)

上面图片其中内容(复制于)：

![Alt text](F:\MarktextPhoto\2e4110b8ae74b6645b87170694e0d1007a422a10.png)

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
