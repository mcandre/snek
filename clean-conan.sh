#!/bin/sh
unset IFS
set -euf
rm -f conanbuildinfo.cmake || :
rm -f graph_info.json || :
rm -f conan.lock || :
rm -f conanbuildinfo.txt || :
rm -f conaninfo.txt || :
