#cleanup stuff
rm -rf CMake* cmake* Make*

cmake \
    -DCMAKE_C_COMPILER="gcc" \
    -DCMAKE_CXX_COMPILER="g++" \
    -DCMAKE_C_FLAGS="-Wall -g" \
    -DCMAKE_CXX_FLAGS="-Wall -g" \
    ..