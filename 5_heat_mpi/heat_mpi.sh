#! /bin/bash
#
mpicxx -c -Wall heat_mpi.cpp
if [ $? -ne 0 ]; then
  echo "Compile error."
  exit
fi
#
mpicxx heat_mpi.o
if [ $? -ne 0 ]; then
  echo "Load error."
  exit
fi
rm heat_mpi.o
#
echo "Normal end of execution."
