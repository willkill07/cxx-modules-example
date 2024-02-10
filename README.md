# cxx-modules-example

Example getting C++ modules working with clang>=18

If you don't have the latest LLVM with `LIBCXX_INSTALL_MODULES=On` configured
as an explicit option, I provide an ArchLinux PKGBUILD which can be used. You
can also inspect this PKGBUILD file if you want to build LLVM yourself
(regardless of your Linux distribution)

## Build Prerequisites

* a modern LLVM+Clang configured with `LIBCXX_INSTALL_MODULES=On` (>=18 rc1)
* CMake >= 3.28
* Ninja (you must use ninja -- Unix Makefiles will absolutely not work)

## Build Directions

```
cmake -GNinja -Bbuild -DCMAKE_CXX_COMPILER=/path/to/modern/clang++
cmake --build build
```
