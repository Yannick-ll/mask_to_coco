/*
 * Copyright (C) 2021 Yannick Lufimpu Luviya - All Rights Reserved
 */

#include "Main.hpp"
using namespace RSRCH;

Main::Main() {
}

Main::~Main() {
}

int Main::process_main() {
    //--------------------------------------------------------------------------
    //                                                        MAIN BLOCK : start
    //--------------------------------------------------------------------------
    try {        
        std::string step = "test"; // train = vid1.mkv  test = vid2.mp4
        int idxStart = 5289;// Minimum frameNum = 675 for vid1, 5289 for vid2:
        int idxEnd = 158000;
        std::string videoName = "vid1.mkv";
        if(step.compare("test") == 0){
            idxStart = 14000;// Minimum frameNum = 675 for vid1, 5289 for vid2:
            idxEnd = 158000;
            videoName = "vid2.mp4";
        }
        cv::VideoCapture cap("/home/deploy/app/tests/database/video/test/gallbladder/raw_videos/" + videoName); // open the video file
        if (!cap.isOpened()) {// check if we succeeded
            return 0;
        }
        int countFrames = cap.get(cv::CAP_PROP_FRAME_COUNT); 
        std::cout << "COUNT FRAMES = " << countFrames << "\n" ; // countFrames = 12012 for vid1 
        
        
        int frame_width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
        int frame_height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
        frame_width = 0.4*frame_width;
        frame_height = 0.4*frame_height ;
        cv::VideoWriter video("/home/deploy/app/tests/database/video/test/gallbladder/cut_videos/" + videoName, cv::VideoWriter::fourcc('M','J','P','G'), 10, cv::Size(frame_width,frame_height));

        int idx = 0;
        for (int frameNum = 0; frameNum < countFrames ; frameNum++) {           
            
            cv::Mat frame;
            cap >> frame; // get the next frame from video
            if(frame.data){
                cv::imshow("vid", frame);
                cv::waitKey(10);
                if(frameNum >= idxStart && frameNum <= idxEnd){  
                    std::cout << "frameNum = " << frameNum << "\n" ;
                    idx = idx +1;
                    cv::imwrite("/home/deploy/app/tests/database/CholecSegMine/"+ step+"/gallbladder ("+std::to_string(idx) +").jpg",frame);
                    cv::waitKey(10);
                    
                    cv::resize(frame, frame, cv::Size(), 0.4, 0.4);
                    video.write(frame);
                    cv::waitKey(10);
                }
            }
        }
        
        video.release();
    } catch (cv::Exception& e) {
        cerr << e.msg << endl;
        exit(1);
    }
    //--------------------------------------------------------------------------
    //                                                          MAIN BLOCK : end
    //--------------------------------------------------------------------------
    return 0;
}

int main(int argc, char** argv) {
    Main main;
    main.process_main();
    return 0;
}








