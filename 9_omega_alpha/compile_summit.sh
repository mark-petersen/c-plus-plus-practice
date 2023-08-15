#! /bin/bash

module load gcc
module load netcdf-c	 
module load netcdf-cxx4/4.3.1

g++ -std=c++17 -lnetcdf -lnetcdf_c++4 MpasMesh.cpp io.cpp main.cpp -o a.out
