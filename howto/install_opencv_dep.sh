       # Remove any previous installations of x264</h3>
       sudo apt-get remove x264 libx264-dev -y
       # We will Install dependencies now
       sudo apt-get install build-essential checkinstall cmake pkg-config yasm -y
       sudo apt-get install git gfortran -y
       sudo apt-get install libjpeg8-dev libjasper-dev libpng12-dev -y
       # If you are using Ubuntu 14.04
       # sudo apt-get install libtiff4-dev
       # If you are using Ubuntu 16.04
       sudo apt-get install libtiff5-dev -y
       sudo apt-get install libavcodec-dev libavformat-dev libswscale-dev libdc1394-22-dev -y
       sudo apt-get install libxine2-dev libv4l-dev -y

       # If you are using Ubuntu 16.04
       sudo apt-get install libgstreamer0.10-dev libgstreamer-plugins-base0.10-dev -y
       # If you are using Ubuntu 18.04
       sudo apt install -y libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev

       sudo apt-get install qt5-default libgtk2.0-dev libtbb-dev -y
       sudo apt-get install libatlas-base-dev -y
       sudo apt-get install libfaac-dev libmp3lame-dev libtheora-dev -y
       sudo apt-get install libvorbis-dev libxvidcore-dev -y
       sudo apt-get install libopencore-amrnb-dev libopencore-amrwb-dev -y
       sudo apt-get install x264 v4l-utils -y
       # Optional dependencies
       # DISABLED, cause : conflict with protobuf version needed by tensorflow : sudo apt-get install libprotobuf-dev protobuf-compiler -y
       sudo apt-get install libgoogle-glog-dev libgflags-dev -y
       sudo apt-get install libgphoto2-dev libeigen3-dev libhdf5-dev doxygen -y
