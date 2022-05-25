cmake_minimum_required(VERSION 3.19)
project(Carshowrooms)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(Carshowrooms
        include/Buy_Rent_Process.h
        include/Car.h
        include/Customer.h
        include/Garages.h
        include/Service.h
        include/Service_Process.h
        include/Showrooms.h
        src/Admin.cpp
        src/Buy_Rent_Process.cpp
        src/Car.cpp
        src/Customer.cpp
        src/Garages.cpp
        src/Service.cpp
        src/Service_Process.cpp
        src/Showrooms.cpp
        main.cpp)
