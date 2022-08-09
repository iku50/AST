# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.7)

# 项目信息
project (AST)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

# 添加 math 子目录
add_subdirectory(src)

# 指定生成目标 
add_executable(AST main.c++)

# 添加链接库
target_link_libraries(AST source)
set (Demo_VERSION_MAJOR 1)
set (Demo_VERSION_MINOR 0)
