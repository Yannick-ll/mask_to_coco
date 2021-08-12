/*
 * Copyright (C) 2021 Yannick Lufimpu Luviya - All Rights Reserved
 */

/* 
 * File:   Flags.h
 * Author: yannick
 *
 * Created on 9 mars 2021, 22:07
 */

#ifndef COCO_FLAGS_H
#define COCO_FLAGS_H

#include "HeaderDefine.h"

#include <boost/optional.hpp>
#include <stdexcept>
#include <regex>

namespace RSRCH {
    
    namespace COCO {
        using nlohmann::json;
        class Flags{
            private:            

            public :
                Flags()= default;
                virtual ~Flags()= default;

            public :              
                
                std::string to_string(){
                    std::ostringstream s;
                    return s.str();
                }
        };
    }    
}

namespace nlohmann {
    void from_json(const json & j, RSRCH::COCO::Flags & x);
    void to_json(json & j, const RSRCH::COCO::Flags & x);

    inline void from_json(const json & j, RSRCH::COCO::Flags& x) {
    }

    inline void to_json(json & j, const RSRCH::COCO::Flags & x) {
        j = json::object();
    }
}

#endif /* COCO_FLAGS_H */

