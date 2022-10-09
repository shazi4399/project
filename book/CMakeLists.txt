
#cmake 要求的最低版本
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

#工程名字，支持语言列表可以省略，这里已经省略，使用默认的
PROJECT(HELLO)

#SET指令可以用来显示的定义变量，常用来罗列源码文件名，或常用来设置变量来访问常用的路径
#例如 set(CMAKE_SOURCE out.c)

#PROJECT_SOURCE_DIR 为cmake系统帮助我们预定义的表示源文件路径的变量

#Debug模式下的编译指令
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g")

#设置可执行文件路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/out")
#一旦设置上面的属性，在任何环境下生成的可执行文件都将直接放在你所设置的目录。

#设置动态库文件的输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")
#设置静态库文件的输出目录
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")
#一旦设置上面的属性，在任何环境下生成的库文件都将直接放在你所设置的目录下


#用于向当前工程添加存放源文件的子目录
#这里定义了将src子目录加入工程
#ADD_SUBDIRECTORY("${PROJECT_SOURCE_DIR}/src")

#INCLUDE_DIRECTORIES向工程添加多个特定的头文件搜索路径
#路径之间用空格分割，可以使用双引号将它括起来，默认的行为是追加到当前的头文件搜索路径的
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/../public/")

#库文件搜索目录
#link_directories("${PROJECT_SOURCE_DIR}/../public/")
#查找当前目录下所有的源文件
#AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR} MAIN_LIST)

#指定生成的可执行文件名称，和编译这个可执行文件用到的源文件
ADD_EXECUTABLE(test 2-13-1.cpp ../public/_public.cpp)

#链接指定名称的静态库
#TARGET_LINK_LIBRARIES(test ../public/lib_public.a)

