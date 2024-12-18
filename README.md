# Corydon kernel
A simple x86_64 kernel

### How to build?
##### you will need:
+ cmake
+ gcc
+ nasm
+ git
+ xorriso
+ qemu (optional)

```bash
# clone the project
git clone https://github.com/boprr/corydon
cd corydon
mkdir build
cd build
cmake ..

# build
make
# to create a bootable iso
make iso
```