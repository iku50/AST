# AST

这是一个c语言格式化工具。用AST命名主要是其采用抽象语法树（Abstract Syntax Tree，AST）构建，而我懒得给其起名字。

实际上，这是华中科技大学21级数据结构试验课程设计的内容。

因不知能否用其他相比于c更方便的语言构建，因此我使用c++但用的还是c的语法（未用c++的智能指针或类等特性，只是想钻个空子使用STL库里的string和unordered_map等类方便构建）。项目工程管理使用cmake和makefile。文件结构如后文所示。

现在，项目已经基本完成，可以准确识别各式表达式，函数和基础语法，并将其以统一的代码风格格式化。到这里这份课程设计已经达成了课程设计指导文档里的目标功能。缺憾是基础语法中switch case的语法还未完成，也不能对指针和宏进行识别。但大体上已经可以使用了。

未来的完善计划（如果我能想得起来的话），主要是对上述那些缺憾的补足，并对使用方式进行进一步的优化。

## ABOUT

Project: Hust Data structure curriculum design 2022 summer.

Name: AST tree builder of C language

License: `GNU GENERAL PUBLIC LICENSE V3.0`

Developing language: C

## REQUIRMENTS

platform:`GNU/LINUX X86/64`

complier:`gcc version 12.1.1`

CMake :`version 3.23.2`

## USEAGE

this tool can be simply used by:

```bash
./AST -h
```

to check more information about this program.

if you didn't choose the outputfile,the outputfile will be generated in the output folder

## FILE STRUCTURE

```
.
├── AST
├── CMakeLists.txt
├── LICENSE
├── main.c++
├── Makefile
├── output
├── README.md
├── src
│   ├── ASTgenerate.c++
│   ├── ASTgenerate.h
│   ├── CMakeLists.txt
│   ├── Makefile
│   ├── src.c++
│   └── src.h
└── target
```
