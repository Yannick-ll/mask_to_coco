### VERSION INFO
set(APP_NAME mask_to_coco)
set(${APP_NAME}_VERSION_MAJOR 1)
set(${APP_NAME}_VERSION_MINOR 0)
set(${APP_NAME}_VERSION_PATCH 0)
set(APP_VERSION ${${APP_NAME}_VERSION_MAJOR}.${${APP_NAME}_VERSION_MINOR}.${${APP_NAME}_VERSION_PATCH})


### FOLDERS INFO
set(VERSION_OPENCV 4.0.1 ) # 3.4.2 # 4.0.1
SET(OpenCV_DIR /home/deploy/lib/opencv/opencv-${VERSION_OPENCV}/build)
SET(COMON_DIR /home/deploy/app/common/cpp)

link_directories(/usr/lib/x86_64-linux-gnu/ 
	/usr/local/lib/
        /opt/Qt5.7.0/5.7/gcc_64/lib/
)

### CMAKE HEADERS/OPTIONS
if (${CMAKE_VERSION} VERSION_GREATER 3.0.0)
    cmake_policy(SET CMP0048 NEW)
    PROJECT(${APP_NAME}-${APP_VERSION}  VERSION ${APP_VERSION})
    OPTION (COMPILE_withVersionName "Compile with version name" ON)
else (${CMAKE_VERSION} VERSION_GREATER 3.0.0)
    project(${APP_NAME})
    OPTION (COMPILE_withVersionName "Compile with version name" OFF)
endif (${CMAKE_VERSION} VERSION_GREATER 3.0.0)
cmake_minimum_required(VERSION 2.8.7 FATAL_ERROR) # min. cmake version recommended by Caffe
message("CMAKE_PROJECT_NAME = ${CMAKE_PROJECT_NAME}") 


### OTHER OPTIONS
OPTION (USE_OpenMP "Use OpenMP" ON)
OPTION (USE_CUDA "Use CUDA" ON)

SET(CMAKE_CXX_COMPILER "g++-6")
SET(CMAKE_CXX_FLAGS "-std=c++11")

SET(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_CXX_FLAGS "-std=c++11")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")


IF(USE_OpenMP)
  FIND_PACKAGE(OpenMP)
  IF(OPENMP_FOUND)
    message(STATUS "Found OpenMP")
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
  ENDIF()
ENDIF(USE_OpenMP)


IF(USE_CUDA)
  find_package(CUDA REQUIRED)
ELSE (USE_CUDA)
  SET(CUDA_FOUND TRUE)
  SET(CUDA_INCLUDE_DIRS ./include/)
ENDIF(USE_CUDA)
find_package(OpenCV REQUIRED)
FIND_PACKAGE(Boost REQUIRED)

if (OpenCV_FOUND )
	message(STATUS "Found OpenCV")
        message(STATUS "OpenCV_INCLUDE_DIRS : " ${OpenCV_INCLUDE_DIRS})
	if (CUDA_FOUND)
            message(STATUS "Found CUDA")
            message(STATUS "CUDA_INCLUDE_DIRS : " ${CUDA_INCLUDE_DIRS})

	    AUX_SOURCE_DIRECTORY(./src DIR_SRCS)

            SET(INCLUDE_DIRS  
                ./include/
                ${OpenCV_DIR}
                ${Boost_INCLUDE_DIR}
            )

            SET(SRC_FILES  
                ./src/test/Test_Mask_To_Annotation_Coco.cpp
                #./src/Main.cpp
                ./src/Base64.cpp
            )

	    INCLUDE_DIRECTORIES(
                ${INCLUDE_DIRS}
	    )

	    add_definitions(-DOPENCV)
	    add_definitions(-DUSE_CAFFE)

            SET(LIBS_AND_FLAGS 
		${CUDA_LIBS}
		${OpenCV_LIBS}
                ${Boost_LIBRARIES}
                -lboost_system -lboost_filesystem -lboost_date_time -lglog -lgflags
                -lpqxx -lpq  -lpthread  -lcrypto -lssl -no-pie #lpthread -ldl 
            )

            if (USE_OpenMP)
                SET(LIBS_AND_FLAGS 
                    ${LIBS_AND_FLAGS}
                    -fopenmp
                )
                message(STATUS "LIBS_AND_FLAGS = ${LIBS_AND_FLAGS}") 
            endif (USE_OpenMP)

            ADD_EXECUTABLE(${APP_NAME} 
                ${SRC_FILES}
            )
	    TARGET_LINK_LIBRARIES(${APP_NAME}
		${LIBS_AND_FLAGS}
	    )

            if (COMPILE_withVersionName)
                ADD_EXECUTABLE(${CMAKE_PROJECT_NAME} 
                    ${SRC_FILES}
                )
                TARGET_LINK_LIBRARIES(${CMAKE_PROJECT_NAME}
                    ${LIBS_AND_FLAGS}
                )
            endif (COMPILE_withVersionName)
	endif (CUDA_FOUND)
endif(OpenCV_FOUND)

