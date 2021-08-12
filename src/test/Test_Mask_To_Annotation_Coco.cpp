/*
 * Copyright (C) 2021 Yannick Lufimpu Luviya - All Rights Reserved
 */


using namespace std;
#include "Annotation.h"
#include "Base64.h"
using namespace RSRCH::COCO;
using namespace RSRCH::JARVIS::SMTP;

int R = 255; // 255
int G = 160; // 95
int B = 165; // 178


/* Returns a list of files in a directory (except the ones that begin with a dot) */
int readFilenames(std::vector<string> &filenames, const string &directory) {
#ifdef WINDOWS
    HANDLE dir;
    WIN32_FIND_DATA file_data;

    if ((dir = FindFirstFile((directory + "/*").c_str(), &file_data)) == INVALID_HANDLE_VALUE)
        return; /* No files found */

    do {
        const string file_name = file_data.cFileName;
        const string full_file_name = directory + "/" + file_name;
        const bool is_directory = (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;

        if (file_name[0] == '.')
            continue;

        if (is_directory)
            continue;

        filenames.push_back(full_file_name);
    } while (FindNextFile(dir, &file_data));

    FindClose(dir);
#else
    DIR *dir;
    class dirent *ent;
    class stat st;

    dir = opendir(directory.c_str());
    while ((ent = readdir(dir)) != NULL) {
        const string file_name = ent->d_name;
        const string full_file_name = directory + "/" + file_name;

        if (file_name[0] == '.')
            continue;

        if (stat(full_file_name.c_str(), &st) == -1)
            continue;

        const bool is_directory = (st.st_mode & S_IFDIR) != 0;

        if (is_directory)
            continue;

        //        filenames.push_back(full_file_name); // returns full path
        filenames.push_back(file_name); // returns just filename
    }
    closedir(dir);
    delete ent;
#endif
    std::sort(filenames.begin(), filenames.end()); //optional, sort the filenames
    return (filenames.size()); //Return how many we found
} //readFilenames

void MatToBase64(cv::Mat img, std::string & encoded){
    std::vector<uchar> buf;
    cv::imencode(".jpg", img, buf);
    auto *enc_msg = reinterpret_cast<unsigned char*>(buf.data());
    Base64 base64;
    encoded = base64.base64_encode(enc_msg, buf.size());
}

void Base64ToMat(std::string encoded){
    Base64 base64;
    string dec_jpg =  base64.base64_decode(encoded);
    std::vector<uchar> data(dec_jpg.begin(), dec_jpg.end());
    cv::Mat img = cv::imdecode(cv::Mat(data), 1);
}

cv::Mat gallbladderFilter(const Mat& src)
{
    cv::Mat gallbladderOnly;
    if(src.type() == CV_8UC3){
        cv::Mat mat ;
        cv::Mat frame_HSV;
        cv::cvtColor(src, frame_HSV, COLOR_BGR2HSV);
        cv::inRange(frame_HSV, Scalar(178, 95, 255), Scalar(178, 95, 255), mat); // B G R
        //std::cout << mat.size << "\n";
        //std::cout << mat.depth() << "\n";
        //std::cout << mat.type() << "\n";
        //std::cout << "cv::countNonZero(mat) : " << cv::countNonZero(mat) << "\n";
        if( cv::countNonZero(mat) > 0){
            //cv::imshow("gallbladderOnly", mat);
            //cv::waitKey(0);
            gallbladderOnly = mat;
        }
    }
    return gallbladderOnly;
}


void getPoints(cv::Mat maskRGB, std::vector< std::vector <float> > & points ){
    cv::Mat frame_HSV;
    cv::cvtColor(maskRGB, frame_HSV, COLOR_BGR2HSV);
    //cv::imshow("frame_HSV", frame_HSV);
    //cv::waitKey(0);
    cv::Mat gallbladderOnly = gallbladderFilter(maskRGB);
    if(maskRGB.data){
        //cv::imshow("gallbladderOnly", gallbladderOnly);
        //cv::waitKey(0);
    }
    
    std::vector< std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours( gallbladderOnly, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE );
    //std::cout << "contours.size() = " << contours.size() ;
    //std::cout << "contour.size() = " << contours.at(0).size() ;
    
    if(contours.size() > 0){
        std::vector<cv::Point> contour = contours.at(0);
        if(contour.size() > 3){
            for(cv::Point pt : contour){
                std::vector <float> pts;
                pts.push_back(pt.x);
                pts.push_back(pt.y);
                points.push_back(pts);
            }
        }
        
    }    
}

void getPoints(cv::Mat maskRGB, std::vector< std::vector< std::vector <float> > > & VectOfpoints ){
    cv::Mat frame_HSV;
    cv::cvtColor(maskRGB, frame_HSV, COLOR_BGR2HSV);
    //cv::imshow("frame_HSV", frame_HSV);
    //cv::waitKey(0);
    cv::Mat gallbladderOnly = gallbladderFilter(maskRGB);
    if(maskRGB.data){
        //cv::imshow("gallbladderOnly", gallbladderOnly);
        //cv::waitKey(0);
    }
    
    if(gallbladderOnly.data){
        std::vector< std::vector<cv::Point> > contours;
        std::vector<cv::Vec4i> hierarchy;
        cv::findContours( gallbladderOnly, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE );
        //std::cout << "contours.size() = " << contours.size() ;
        //std::cout << "contour.size() = " << contours.at(0).size() ;

        if(contours.size() > 0){
            for(std::vector<cv::Point> contour : contours){
                std::vector< std::vector <float> >  points;
                if(contour.size() > 10){
                    for(cv::Point pt : contour){
                        std::vector <float> pts;
                        pts.push_back(pt.x);
                        pts.push_back(pt.y);
                        points.push_back(pts);
                    }
                }
                if(points.size() > 0){
                    VectOfpoints.push_back(points);
                }            
            }
        }    
    }
}


void make_coco_json(std::string directory, std::string nameRGB, std::string nameMaskRGB, std::string directorySave){
    cv::Mat imgRGB = cv::imread(directory + nameRGB );
    cv::Mat maskRGB = cv::imread(directory + nameMaskRGB );
    
    cv::resize(imgRGB, imgRGB, cv::Size(), 0.4, 0.4);
    cv::resize(maskRGB, maskRGB, cv::Size(), 0.4, 0.4);
    
    RSRCH::COCO::Annotation annotation;
    std::string version = "4.5.6";
    RSRCH::COCO::Flags flags;
    std::vector<RSRCH::COCO::Shape> shapes;
    std::string imagePath = directorySave + nameRGB;
    std::string imageData = "";
    int imageHeight = imgRGB.rows;
    int imageWidth = imgRGB.cols;
    
    imageData = "";
    MatToBase64(imgRGB, imageData);
    
    RSRCH::COCO::Shape shape;
    std::string label = "gallbladder";
    std::vector< std::vector <float> > points;
    std::string shape_type = "polygon";
    
    std::vector< std::vector< std::vector <float> > >  VectOfpoints;
    getPoints(maskRGB,  VectOfpoints );

    if(VectOfpoints.size() == 0){
    }else{
        for(std::vector< std::vector <float> > _points : VectOfpoints){
            RSRCH::COCO::Shape _shape;
            _shape.set_label(label);
            _shape.set_points(_points);
            _shape.set_shape_type(shape_type);
            _shape.set_flags(flags);
            shapes.push_back(_shape);
        }
        annotation.set_version(version);
        annotation.set_shapes(shapes);
        annotation.set_imagePath(imagePath);
        annotation.set_imageData(imageData);
        annotation.set_imageHeight(imageHeight);
        annotation.set_imageWidth(imageWidth);

        nlohmann::json json_annotation_coco = annotation;    
        std::string jsonPath = directorySave + nameRGB.substr(0, nameRGB.length() - 4) + ".json";
        std::ofstream json_file(jsonPath);
        json_file << json_annotation_coco.dump(4);
        cv::waitKey(10);
        cv::imwrite(directorySave + nameRGB, imgRGB);
        cv::waitKey(10);
    
    }

    /*
    getPoints(maskRGB,  points );
    shape.set_label(label);
    shape.set_points(points);
    shape.set_shape_type(shape_type);
    shape.set_flags(flags);
    shapes.push_back(shape);
    
    annotation.set_version(version);
    annotation.set_shapes(shapes);
    annotation.set_imagePath(imagePath);
    annotation.set_imageData(imageData);
    annotation.set_imageHeight(imageHeight);
    annotation.set_imageWidth(imageWidth);
    
    if(points.size() > 0){
        nlohmann::json json_annotation_coco = annotation;    
        std::string jsonPath = directorySave + nameRGB.substr(0, nameRGB.length() - 4) + ".json";
        std::ofstream json_file(jsonPath);
        json_file << json_annotation_coco.dump(4);
        cv::waitKey(10);
        cv::imwrite(directorySave + nameRGB, imgRGB);
        cv::waitKey(10);
    }
    */

}

int main(){
    std::vector<string> filenames;
    std::string step = "test";
    const string directory = "/home/deploy/app/tests/database/CholecSeg8k_Mine/" + step + "/";
    std::string directorySave = "/home/deploy/app/tests/database/CholecSeg8k_Mine/Final/" + step +"/";
    readFilenames(filenames,  directory);
    std::cout << " filenames.size() : " << filenames.size() << "\n";   
    
    if(filenames.size() > 0){
        for(std::string filename : filenames){
            if (filename.find("color") != std::string::npos) {
            }else{
                std::cout << "DEALS with " << filename << '\n';
                std::string nameRGB = filename;
                std::string nameMaskRGB = filename.substr(0, filename.length() - 4) + "_color_mask.png";
                make_coco_json(directory, nameRGB, nameMaskRGB, directorySave);
                cv::waitKey(30);
            }
        }
    }
    return 0;
}