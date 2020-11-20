
## Some shocking alpaka

Porting the [shoc](https://github.com/vetter/shoc) benchmark-suit to [alpaka](https://github.com/alpaka-group/alpaka).

###Currently found problems: 

shoc port intermediate-report

#### DeviceMemory.cpp

> *shoc/src/cuda/level0/DeviceMemory.cpp*

**Function:** `TestTextureMem`

| Shoc                     | Cupla/Alpaka                                                 |
| ------------------------ | ------------------------------------------------------------ |
| `cudaArray`              | cupla defines `cuplaArray` but this leads to an empty struct |
| `cudaMallocArray()`      | marked as not existing                                       |
| `cudaMemcpyToArray()`    | marked as not existing                                       |
| `cudaBindTextureToArray` | marked as not existing                                       |



**Kernel:** readTexels / readTexelsInCache /readTexelsRandom

| Shoc      | Cupla/Alpaka                  |
| --------- | ----------------------------- |
| `tex2D()` | not mentioned in cupla/alpaka |



**Handling:** exluded `TestTextureMem`



#### BusSpeedReadback.cpp

> *shoc/src/cuda/level0/BusSpeedReadback.cpp*



| Shoc                                    | Cupla/Alpaka                  |
| --------------------------------------- | ----------------------------- |
| `cudaThreadSynchronize` (*deprecated* ) | not mentioned in cupla/alpaka |



**Handling:** not decided

## Setup
```shell
export CUPLA_ROOT=<cupla>
export CPATH=$CPAHT:$CUPLA_ROOT/include # or -I
export CPATH=$CPATH:$CUPLA_ROOT/alpaka/include # or -I


sh /shoc/configure CXX=<NVCC_ROOT> \
    CXXFLAGS="-x cu --expt-relaxed-constexpr"\
    NVCXXFLAGS="--expt-relaxed-constexpr"\
    --without-opencl\
    --without-mpi

#set CXX because otherwise nvcc wont be used for g++
#CXXFLAGS="-x cu": Tell nvcc to compile .cpp too
#--expt-relaxed-constexpr: ignore calling __host__ from __device__

make VERBOSE=1 -j8 |& tee build.log

make install
```