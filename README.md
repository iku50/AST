# AST

It is a AST(Abstract Syntax Tree) for C language.

The purpose is to build a C language formatter commands tool.

so far, this program has already completed the original condition.

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
./main [-f file] [-o outfile]
```

you can use 

```bash
./main -h
```

to check more information about this program.

if you didn't choose the outputfile,the outputfile will be generated in the output folder

## FILE STRUCTURE

```
├── AST
├── CMakeLists.txt
├── main.c++
├── output
├── README.md
├── src
│   ├── ASTgenerate.c++
│   ├── ASTgenerate.h
│   ├── CMakeLists.txt
│   ├── src.c++
│   └── src.h
└── target
```
