#cleanup stuff
rm -rf CMake* cmake* Make*

cmake \
    -D ENABLE_DEBUG="ON" \
    -D ENABLE_PREVERSION="ON" \
    -DCMAKE_C_COMPILER="gcc" \
    -DCMAKE_CXX_COMPILER="g++" \
    -DCMAKE_C_FLAGS="-Wall -g" \
    -DCMAKE_CXX_FLAGS="-Wall -g" \
    ..