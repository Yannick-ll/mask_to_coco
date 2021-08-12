/*
 * Copyright (C) 2021 Yannick Lufimpu Luviya - All Rights Reserved
 */

/* 
 * File:   Main.hpp
 * Author: Yannick Lufimpu Luviya <yannick.lufimpu.luviya@gmail.com>
 *
 * Created on 9 mars 2021, 21:58
 */

#ifndef MAIN_HPP
#define MAIN_HPP

/******************************************************************************/
// namespace RSRCH includes
#include "Versionning.h"
#include "HeaderDefine.h"
//--
#include <utility>

//--
// Annotations
#include <boost/algorithm/string/replace.hpp>
#include <chrono>
#include <thread> //unsigned num_cpus = std::thread::hardware_concurrency();
#include <list> //thread
#include <algorithm> //thread
#include <iostream>

/******************************************************************************/
// Class definitions
namespace RSRCH {    
    class Main {
    public:        
        Main();
        ~Main();
        int process_main();        
    };
} // namespace RSRCH

#endif /* MAIN_HPP */

