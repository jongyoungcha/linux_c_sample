cmake_minimum_required (VERSION 2.8)
include(CheckCXXCompilerFlag)

set(CC "/usr/local/Cellar/llvm/3.9.1/bin/clang")
set(CXX "/usr/local/Cellar/llvm/3.9.1/bin/clang++") 

CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX11)

if (COMPILER_SUPPORTS_CXX11)
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif (COMPILER_SUPPORTS_CXX01)
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else ()
	 message(STATUS "No support c++11")
endif ()

project (hash_gen_cs CXX)
include_directories(./)

add_executable(hashgen_server main.cpp HashGeneratorServer.cpp HashGeneratorServer.hpp )

