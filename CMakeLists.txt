cmake_minimum_required(VERSION 2.8)
cmake_policy(VERSION 2.8)

project(CPlusPlus_Learn)

# Use Debug Mode x64
message("#### CPlusPlus_Learn    $$$ General Debug Work")

message("#### CMake Source Dir")
message("${CMAKE_SOURCE_DIR}")
# use 64 or 32
if (${CMAKE_CL_64})
	message("#### Use CL 64 bit")
else (${CMAKE_CL_64})
	message("#### Use CL 32 bit")
endif (${CMAKE_CL_64})

# for warning D9002
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

# debug/release 环境设置
set(CMAKE_DEBUG_POSTFIX "_d" CACHE STRING "add a postfix, usually d on windows")  
set(CMAKE_RELEASE_POSTFIX "" CACHE STRING "add a postfix, usually empty on windows")  

set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/libs)

# set biuld path with debug
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/bin)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin)

link_directories(${LIBRARY_OUTPUT_PATH})
message("#### CPlusPlus_Learn Build Libs path:")
message("${LIBRARY_OUTPUT_PATH}")

file(GLOB_RECURSE CPPFILE
	"src/code/*.cpp"
)

file(GLOB_RECURSE HEADFILE
	"src/code/*.h"
)

# prime_learn_code 下的内容 这一部分是 C++ Prime 的读书笔记, 以及课后习题
file(GLOB_RECURSE PRIME_LEARN_CODE_CPPFILE
	"src/prime_learn_code/*.cpp"
)

file(GLOB_RECURSE PRIME_LEARN_CODE_HEADFILE
	"src/prime_learn_code/*.h"
)

# my_comment_source 下的内容 这一部分是我对源码文件的拷贝, 然后会在里面写一些理解性的注释
file(GLOB_RECURSE MY_COMMENT_SOURCE_CPPFILE
	"src/my_comment_source/*.cpp"
)

file(GLOB_RECURSE MY_COMMENT_SOURCE_HEADFILE
	"src/my_comment_source/*.h"
)

# 接入 md 文件
file(GLOB_RECURSE MARKDOWNFILE
	"doc/*.md"
)

# 接入 md 文件
file(GLOB_RECURSE NOTE_MARKDOWNFILE
	"note/*.md"
)

message("#### all CPP files:")
foreach(F ${CPPFILE})
     message(${F})
endforeach(F)
message("#### all H files:")
foreach(F ${HEADFILE})
     message(${F})
endforeach(F)
add_executable(CPlusPlus_Learn ${CPPFILE} ${HEADFILE} ${PRIME_LEARN_CODE_CPPFILE} ${PRIME_LEARN_CODE_HEADFILE} ${MY_COMMENT_SOURCE_CPPFILE} ${MY_COMMENT_SOURCE_HEADFILE} ${MARKDOWNFILE} ${NOTE_MARKDOWNFILE})

set(all_files ${HEADFILE} ${CPPFILE} ${PRIME_LEARN_CODE_CPPFILE} ${PRIME_LEARN_CODE_HEADFILE} ${MY_COMMENT_SOURCE_CPPFILE} ${MY_COMMENT_SOURCE_HEADFILE})

# 添加 定义
if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

# 一个根据文件夹来进行分类的函数, 在windows vs 下有用
macro(source_group_by_dir source_files)
    if(MSVC)
        set(sgbd_cur_dir ${CMAKE_CURRENT_SOURCE_DIR})
        foreach(sgbd_file ${${source_files}})
            string(REGEX REPLACE ${sgbd_cur_dir}/\(.*\) \\1 sgbd_fpath ${sgbd_file})
            string(REGEX REPLACE "\(.*\)/.*" \\1 sgbd_group_name ${sgbd_fpath})
            string(COMPARE EQUAL ${sgbd_fpath} ${sgbd_group_name} sgbd_nogroup)
            string(REPLACE "/" "\\" sgbd_group_name ${sgbd_group_name})
            if(sgbd_nogroup)
                set(sgbd_group_name "\\")
            endif(sgbd_nogroup)
            source_group(${sgbd_group_name} FILES ${sgbd_file})
        endforeach(sgbd_file)
    endif(MSVC)
endmacro(source_group_by_dir)
source_group_by_dir(all_files)

message("#### all md files:")
foreach(F ${MARKDOWNFILE})
     message(${F})
endforeach(F)
#设置 vs sln filter的接口
source_group("_markdownDoc" FILES ${MARKDOWNFILE})

message("#### all note - md files:")
foreach(F ${NOTE_MARKDOWNFILE})
     message(${F})
endforeach(F)
source_group("_markdownNote" FILES ${NOTE_MARKDOWNFILE})
