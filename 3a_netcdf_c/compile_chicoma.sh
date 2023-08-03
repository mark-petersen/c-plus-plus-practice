#! /bin/bash

module load gcc
module load cray-netcdf-hdf5parallel

for file in pres_temp_4D_wr.c pres_temp_4D_rd.c sfc_pres_temp_wr.c sfc_pres_temp_rd.c  simple_xy_wr.c simple_xy_rd.c 
do
  echo "Processing $file"
  g++ -I/opt/cray/pe/netcdf-hdf5parallel/4.9.0.1/gnu/9.1/include \
      -L/opt/cray/pe/netcdf-hdf5parallel/4.9.0.1/gnu/9.1/lib \
      -lnetcdf -lnetcdf_c++4 $file -o $file.out
  echo "compiled " $file "running..."
  ./$file.out
done
