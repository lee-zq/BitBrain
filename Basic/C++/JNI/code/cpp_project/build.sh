build_dir="build"

if [ -d "${build_dir}" ]; then
    rm -rf ${build_dir}
fi
mkdir ${build_dir} && cd ${build_dir}
cmake .. -DCMAKE_BUILD_TYPE=Debug 
make -j2