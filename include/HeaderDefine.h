/*
 * Copyright (C) 2021 Yannick Lufimpu Luviya - All Rights Reserved
 */

/* 
 * File:   HeaderDefine.h
 * Author: yannick
 *
 * Created on 9 mars 2021, 22:13
 */

#ifndef HEADERDEFINE_H
#define HEADERDEFINE_H

/******************************************************************************/
// YOLO-cv includes
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include "opencv2/imgcodecs/imgcodecs.hpp"
#include <opencv2/ml/ml.hpp>
#ifdef USE_ODB
#else
#include <opencv2/ximgproc.hpp>
#include <opencv2/dnn.hpp>
#endif
/******************************************************************************/
// OTHER includes
#include <fstream>
#include <iostream>
#include <array>
#include <unistd.h>
#include <ctime>
#include <stdbool.h>
#include <time.h>
#include <cstdint> //uint64_t to store date in 13 digits
#include <sstream>
#include <vector>
#include <string>
/******************************************************************************/
// MULTI TREADING
#include <cstdlib>
#include <pthread.h>
#include <mutex> //mutex
/******************************************************************************/
// list of subdirectories
#include <stdio.h> 

#include <pqxx/pqxx> 
#include <sstream>
#include <vector>
#include <string>

#include <dirent.h> // for linux systems
#include <sys/stat.h> // for linux systems
#include <algorithm>    // std::sort
#include <iostream>   //cout
#include <cstdio> // std::remove()
#include <string.h>

/******************************************************************************/
#include <string>
#include <set>
#include <exception>
#include <iostream>
#include <bits/stdc++.h> 

/******************************************************************************/
#include <boost/filesystem.hpp> //create directories
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string.hpp> 
/******************************************************************************/
#include <iostream>
//#include "QuicktypeTest.h"
#include <boost/filesystem.hpp> //create directories
#include "json.hpp"
using nlohmann::json;


/******************************************************************************/
using namespace cv;
#ifdef USE_ODB
#else
using namespace cv::ximgproc;
using namespace dnn;
#endif

using namespace std;
/******************************************************************************/

namespace RSRCH {
    template <typename T>
    std::ostream& operator<< (std::ostream& out, const std::vector<T>& v) {
      if ( !v.empty() ) {
        out << '[';
        std::copy (v.begin(), v.end(), std::ostream_iterator<T>(out, ", "));
        out << "\b\b]";
      }
      return out;
    }

    template<typename T>
    std::ostream& operator<< (std::ostream& out, const std::vector< std::vector<T> >& v) {
        out << "{";
        size_t last = v.size() - 1;
        for(size_t i = 0; i < v.size(); ++i) {
            out << v[i];
            if (i != last) 
                out << ", ";
        }
        out << "}";
        return out;
    }


    template<typename T>
    std::ostream& operator<< (std::ostream& out, const std::vector< std::vector< std::vector<T> > >& v) {
        out << "{";
        size_t last = v.size() - 1;
        for(size_t i = 0; i < v.size(); ++i) {
            out << v[i];
            if (i != last) 
                out << ", ";
        }
        out << "}";
        return out;
    }

    template <typename T>
    void print_contents(const std::vector<T>& v, const char * const separator = " ")
    {
        if(!v.empty())
        {
            std::copy(v.begin(),
                      --v.end(),
                      std::ostream_iterator<T>(std::cout, separator));
            std::cout << v.back() << "\n";
        }
    }    

    typedef std::pair<std::string,std::string> PAIR_STR_STR;
    typedef std::pair<std::string,int> PAIR_STR_INT;
    typedef std::pair<int,double> PAIR_INT_DOUBLE;
} // namespace RSRCH

/******************************************************************************/
namespace nlohmann {
    bool exists(const json& j, const std::string& key);
    inline bool exists(const json& j, const std::string& key)
    {
        return j.find(key) != j.end();
    }
}
/******************************************************************************/

#endif /* HEADERDEFINE_H */


