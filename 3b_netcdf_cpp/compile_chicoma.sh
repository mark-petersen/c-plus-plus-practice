#! /bin/bash

module load gcc
module load cray-netcdf-hdf5parallel

for file in PresTemp4dWr.cpp  SfcPresTempWr.cpp  SimpleXyWr.cpp PresTemp4dRd.cpp  SfcPresTempRd.cpp  SimpleXyRd.cpp 
do
  echo "Processing $file"
  g++ -I/opt/cray/pe/netcdf-hdf5parallel/4.9.0.1/gnu/9.1/include \
      -L/opt/cray/pe/netcdf-hdf5parallel/4.9.0.1/gnu/9.1/lib \
      -lnetcdf -lnetcdf_c++4 $file -o $file.out
  echo "compiled " $file "running..."
  ./$file.out
done
