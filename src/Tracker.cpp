//
// Created by buenos on 2021/3/10.
//
#include "Tracker.h"
#include "StereoFrame.h"

namespace INDOOR_SLAM {

    Tracker::Tracker(){

    }

    void Tracker::ConsumeImage(const cv::Mat& leftImg, const cv::Mat& rightImg, const double& timeStamp){
        curStereoFrame = StereoFrame(leftImg, rightImg, timeStamp, nextFrameId++);

        Camera* cam = new Camera();
        curStereoFrame.calFeaturesPos(cam);

    }

    cv::Mat Tracker::getDebugImg(){
        cv::Mat img = curStereoFrame.leftFrame.grayImg.clone();
        std::vector<cv::KeyPoint> keyPoints = curStereoFrame.leftFrame.keyPoints;
        cv::drawKeypoints(img, keyPoints, img, cv::Scalar::all(-1), cv::DrawMatchesFlags::DEFAULT);
        return img;
    }



}


