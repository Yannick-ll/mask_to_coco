       # # in case it is the first install of OCV, uncomment the following line
       # sudo sh ./install_opencv_dep.sh
       # # in case you have not dowloaded OCV yet, uncomment the following lines
       git clone https://github.com/opencv/opencv.git opencv-4.0.1
       cd opencv-4.0.1
       git checkout 4.0.1
       cd ..
       # # in case you have not dowloaded OCV_contrib yet, uncomment the following lines
       git clone https://github.com/opencv/opencv_contrib.git opencv_contrib-4.0.1
       cd opencv_contrib-4.0.1
       git checkout 4.0.1
       cd ..
       cd opencv-4.0.1
       mkdir build
       mkdir release
       cd build
       cmake -D CMAKE_BUILD_TYPE=RELEASE \
             -D CMAKE_INSTALL_PREFIX=/home/deploy/lib/opencv/opencv-4.0.1/release \
             -D WITH_CUDA=ON \
             -D CUDA_TOOLKIT_ROOT_DIR=/usr/local/cuda-10.2 \
             -D CUDA_NVCC_FLAGS=--expt-relaxed-constexpr \
	     -D BUILD_opencv_cudacodec=OFF \
             -D INSTALL_C_EXAMPLES=ON \
             -D INSTALL_PYTHON_EXAMPLES=ON \
             -D WITH_TBB=OFF \
             -D WITH_V4L=ON \
             -D WITH_QT=ON \
             -D WITH_OPENGL=ON \
             -D ENABLE_PRECOMPILED_HEADERS=OFF \
             -D BUILD_EXAMPLES=ON \
             -D BUILD_TIFF=ON \
             -D WITH_VTK=ON \
             -D OPENCV_EXTRA_MODULES_PATH=../../opencv_contrib-4.0.1/modules ..
             # -D BUILD_EXAMPLES=ON ..
       # make -j{nproc}
       make -j12
       sudo make install
       # # Only in case you install into /usr/local, uncomment the following 2 lines
       # sudo sh -c 'echo "/usr/local/lib" >> /etc/ld.so.conf.d/opencv.conf'
       # sudo ldconfig
       # VTK 7.1.1
