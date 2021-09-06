#!/bin/sh
unset IFS
set -euf
./clean-cmake.sh || :
./clean-conan.sh || :
