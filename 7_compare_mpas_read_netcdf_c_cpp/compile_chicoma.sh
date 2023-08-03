#! /bin/bash

module load gcc
module load cray-netcdf-hdf5parallel

# to make meshes:
# planar_hex --nx 16 --ny 16 --dc 64000 -o base_mesh_16x16.nc
# MpasMeshConverter.x base_mesh_16x16.nc mpas_mesh_16x16.nc

#   export file=read_mpas_mesh.cpp

for file in read_mpas_mesh.cpp
do
  echo "Processing $file"
  g++ -I/opt/cray/pe/netcdf-hdf5parallel/4.9.0.1/gnu/9.1/include \
      -L/opt/cray/pe/netcdf-hdf5parallel/4.9.0.1/gnu/9.1/lib \
      -lnetcdf -lnetcdf_c++4 $file -o $file.out
  echo "compiled " $file "running..."
  ./$file.out
done
