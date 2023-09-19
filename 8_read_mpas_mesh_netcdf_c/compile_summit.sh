#! /bin/bash

module load gcc
module load netcdf-c
module load netcdf-cxx4/4.3.1

# to make meshes:
# planar_hex --nx 16 --ny 16 --dc 64000 -o base_mesh_16x16.nc
# MpasMeshConverter.x base_mesh_16x16.nc mpas_mesh_16x16.nc

#   export file=read_mpas_mesh.cpp

for file in read_mpas.cpp
do
  echo "Processing $file"
  g++ -lnetcdf -lnetcdf_c++4 $file -o $file.out
  echo "compiled " $file "running..."
  ./$file.out
done

#
