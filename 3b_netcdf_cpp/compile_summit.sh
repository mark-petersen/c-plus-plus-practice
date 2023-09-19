#! /bin/bash

module load gcc
module load netcdf-c
module load netcdf-cxx4/4.3.1

for file in PresTemp4dWr.cpp  SfcPresTempWr.cpp  SimpleXyWr.cpp PresTemp4dRd.cpp  SfcPresTempRd.cpp  SimpleXyRd.cpp
do
  echo "Processing $file"
  g++ -lnetcdf -lnetcdf_c++4 $file -o $file.out
  #g++ -I/sw/summit/spack-envs/base/opt/linux-rhel8-ppc64le/gcc-9.1.0/netcdf-c-4.8.1-2iqkfkn4t5yfw6kygt5q6iilwsbigwqq/lib \
  #    -I/sw/summit/spack-envs/base/opt/linux-rhel8-ppc64le/gcc-9.1.0/netcdf-cxx4-4.3.1-aaaef3f55iyn7mn42y3sy65ihn2xkcwl/lib \
  #    -lnetcdf -lnetcdf_c++4 $file -o $file.out
  echo "compiled " $file "running..."
  ./$file.out
done

#
