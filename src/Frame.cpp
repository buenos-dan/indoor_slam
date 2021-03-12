//
// Created by buenos on 2021/3/10.
//
#include "Frame.h"

namespace INDOOR_SLAM{

    Frame::Frame(const cv::Mat& img_){
        cv::cvtColor(img_, grayImg, CV_GRAY2BGR);
        ExtractFeatures();
    }

    void Frame::ExtractFeatures(){
        // TODO: params
        cv::Ptr<cv::ORB> orb = cv::ORB::create();
        orb->detectAndCompute( grayImg, cv::Mat(), keyPoints, descriptors, false);
    }
}
