# ArchLinux PKGBUILD for latest LLVM

Please consider this for building/installing a complete LLVM package which has
everything enabled for modern C++ support with C++ standard modules.

## Steps

1. Navigate to this directory
2. Install all dependent packages:
   ```
   sudo pacman -Syu git cmake ninja libffi libedit ncurses libxml2 swig lld python libc++ ocl-icd opencl-headers z3 jsoncpp clang ccache
   ```
3. Invoke `makepkg` from the current directory
4. Be patient
5. Install the generated package via `pacman -U clang-custom-release*.pkg.tar*`
