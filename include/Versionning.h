/*
 * Copyright (C) 2021 Yannick Lufimpu Luviya - All Rights Reserved
 */

/* 
 * File:   Versionning.h
 * Author: Yannick Lufimpu Luviya <yannick.lufimpu.luviya@gmail.com>
 *
 * Created on 9 mars 2021, 22:22
 */

#ifndef VERSIONING_H
#define VERSIONING_H

#include <string>
#include <stdio.h>  //openmp
#include <omp.h>    //openmp
#include <chrono>  // for high_resolution_clock

#define _MY_VERSION_MAJOR 1
#define _MY_VERSION_MINOR 0
#define _MY_VERSION_PATCH 0

using namespace std;

std::string _version = std::to_string(_MY_VERSION_MAJOR) + "."
        + std::to_string(_MY_VERSION_MINOR) + "."
        + std::to_string(_MY_VERSION_PATCH) ;
static std::string projectName = "mask_to_coco";
static std::string str_version = "\n \033[1;32m/**********************************************************/\n /*                                                        */\n /*  " + projectName + _version +" */\n /*                                                          */\n /**********************************************************/ \033[0m "; 

static std::string pathToGitprojects = "/home/deploy/app";


#endif /* VERSIONING_H */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * version  1.0.0 : MAJOR					20210309 à 22h00
 * a) Initial version
 * a) Initial version
 * 
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
