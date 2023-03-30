cmake_minimum_required(VERSION 3.24)
project(BankProjectWithC C)

set(CMAKE_C_STANDARD 11)

add_executable(BankProjectWithC main.c security.h z_library.h bank.h)
