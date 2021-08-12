/*
 * Copyright (C) 2021 Yannick Lufimpu Luviya - All Rights Reserved
 */

/* 
 * File:   Annotation.h
 * Author: yannick
 *
 * Created on 9 mars 2021, 22:06
 */


#ifndef COCO_ANNOTATION_H
#define COCO_ANNOTATION_H

#include "HeaderDefine.h"
#include "Flags.h"
#include "Shape.h"

#include <boost/optional.hpp>
#include <stdexcept>
#include <regex>

namespace RSRCH {
    
    namespace COCO {
        using nlohmann::json;
        class Annotation{
            private:            
                std::string version = "4.5.6";
                RSRCH::COCO::Flags flags;
                std::vector<RSRCH::COCO::Shape> shapes;
                std::string imagePath;
                std::string imageData;
                int imageHeight;
                int imageWidth;
                
            public :
                Annotation()= default;
                virtual ~Annotation()= default;

            public : 
                const std::string & get_version() const {return version;}
                std::string & get_version() {return version;}
                void set_version(const std::string & version){this->version = version;}                
                
                const RSRCH::COCO::Flags & get_flags() const {return flags;}
                RSRCH::COCO::Flags & get_flags() {return flags;}
                void set_flags(const RSRCH::COCO::Flags & flags){this->flags = flags;}
                
                const std::vector<RSRCH::COCO::Shape> & get_shapes() const {return shapes;}
                std::vector<RSRCH::COCO::Shape> & get_shapes() {return shapes;}
                void set_shapes(const std::vector<RSRCH::COCO::Shape> & shapes){this->shapes = shapes;}    
                
                const std::string & get_imagePath() const {return imagePath;}
                std::string & get_imagePath() {return imagePath;}
                void set_imagePath(const std::string & imagePath){this->imagePath = imagePath;}  
                
                const std::string & get_imageData() const {return imageData;}
                std::string & get_imageData() {return imageData;}
                void set_imageData(const std::string & imageData){this->imageData = imageData;} 
                
                const int & get_imageHeight() const {return imageHeight;}
                int & get_imageHeight() {return imageHeight;}
                void set_imageHeight(const int & imageHeight){this->imageHeight = imageHeight;}    
                
                const int & get_imageWidth() const {return imageWidth;}
                int & get_imageWidth() {return imageWidth;}
                void set_imageWidth(const int & imageWidth){this->imageWidth = imageWidth;}    
                
                std::string to_string(){
                    std::ostringstream s;
                    s << "\n - label = " << version << " \n";
                    return s.str();
                }
        };
    }    
}

namespace nlohmann {
    void from_json(const json & j, RSRCH::COCO::Annotation & x);
    void to_json(json & j, const RSRCH::COCO::Annotation & x);

    inline void from_json(const json & j, RSRCH::COCO::Annotation& x) {
        x.set_version(j.at("version").get<std::string>());
        x.set_flags(j.at("flags").get< RSRCH::COCO::Flags >());
        x.set_shapes(j.at("shapes").get< std::vector<RSRCH::COCO::Shape> >());
        x.set_imagePath(j.at("imagePath").get<std::string>());
        x.set_imageData(j.at("imageData").get<std::string>());
        x.set_imageHeight(j.at("imageHeight").get<int>());
        x.set_imageWidth(j.at("imageWidth").get<int>());

    }

    inline void to_json(json & j, const RSRCH::COCO::Annotation & x) {
        j = json::object();
        j["version"] = x.get_version();
        j["flags"] = x.get_flags();
        j["shapes"] = x.get_shapes();
        j["imagePath"] = x.get_imagePath();
        j["imageData"] = x.get_imageData();
        j["imageHeight"] = x.get_imageHeight();
        j["imageWidth"] = x.get_imageWidth();

    }
}

#endif /* COCO_ANNOTATION_H */



