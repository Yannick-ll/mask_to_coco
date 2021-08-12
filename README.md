# README #

### PURPOSE ###

* INVESTIGATE NEW FEATURE : generate missing annotations (json files)
* TEST API : PixelLib

### What does this repository do? ###

* Split video into frames (cf. src/Main.cpp)
* Generate MISSING json COCO files from color segmentation images (cf ./src/test/Test_Mask_To_Annotation_Coco.cpp) 
* Train network and run model on videos (cf ./src/python)

### Requirements for data preprocessing ###

* [Mandatory] OpenCV 4.0.1 (cf. ./howto/*)

### Get the data and models ###

* [Mandatory] Download the images from this google drive [link](https://drive.google.com/file/d/1crANNINE6hahXJmLmzv96QsC1GzVbQgR/view?usp=sharing) . Unzip the folder under ./data/ and the architecture should be like : ./data/CholecSeg8k_Mine/Final/...
* [Mandatory] Copy the *.h5 files from ./data/CholecSeg8k_Mine/models/ to ./models/

### Requirements for training and inference ###

* [Mandatory] Python. Tested with 3.7
* [Optional] CUDA. Tested with Cuda 11.0 on GeForce RTX 2060
* [Mandatory] PixelLib : https://github.com/ayoolaolafenwa/PixelLib

### Contribution guidelines ###

* Writing tests
* Code review
* Other guidelines

### Who do I talk to? ###

* ...
* ...
