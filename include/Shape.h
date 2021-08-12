/*
 * Copyright (C) 2021 Yannick Lufimpu Luviya - All Rights Reserved
 */

/* 
 * File:   Shape.h
 * Author: yannick
 *
 * Created on 9 mars 2021, 22:08
 */

#ifndef COCO_SHAPE_H
#define COCO_SHAPE_H

#include "HeaderDefine.h"

#include <boost/optional.hpp>
#include <stdexcept>
#include <regex>

namespace RSRCH {
    
    namespace COCO {
        using nlohmann::json;
        class Shape{
            private:            
                std::string label ;
                std::vector< std::vector <float> > points;
                std::string shape_type = "polygon";
                RSRCH::COCO::Flags flags;

            public :
                Shape()= default;
                virtual ~Shape()= default;

            public : 
                const std::string & get_label() const {return label;}
                std::string & get_label() {return label;}
                void set_label(const std::string & label){this->label = label;}
                
                const std::vector< std::vector <float> >  get_points() const {return points;}
                std::vector< std::vector <float> > & get_points() {return points;}
                void set_points(const std::vector< std::vector <float> > & points){this->points = points;}
                
                const std::string & get_shape_type() const {return shape_type;}
                std::string & get_shape_type() {return shape_type;}
                void set_shape_type(const std::string & shape_type){this->shape_type = shape_type;}
                
                const RSRCH::COCO::Flags & get_flags() const {return flags;}
                RSRCH::COCO::Flags & get_flags() {return flags;}
                void set_flags(const RSRCH::COCO::Flags & flags){this->flags = flags;}
                
                std::string to_string(){
                    std::ostringstream s;
                    s << "\n - label = " << label << " \n";
                    return s.str();
                }
        };
    }    
}

namespace nlohmann {
    void from_json(const json & j, RSRCH::COCO::Shape & x);
    void to_json(json & j, const RSRCH::COCO::Shape & x);

    inline void from_json(const json & j, RSRCH::COCO::Shape& x) {
        x.set_label(j.at("label").get<std::string>());
        x.set_points(j.at("points").get< std::vector< std::vector <float> > >());
        x.set_shape_type(j.at("shape_type").get<std::string>());
        x.set_flags(j.at("flags").get< RSRCH::COCO::Flags >());
    }

    inline void to_json(json & j, const RSRCH::COCO::Shape & x) {
        j = json::object();
        j["label"] = x.get_label();
        j["points"] = x.get_points();
        j["shape_type"] = x.get_shape_type();
        j["flags"] = x.get_flags();
    }
}

#endif /* COCO_SHAPE_H */



