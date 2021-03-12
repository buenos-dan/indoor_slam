//
// Created by buenos on 2021/3/10.
//

#ifndef INDOOR_SLAM_TRACKER_H
#define INDOOR_SLAM_TRACKER_H
#include "StereoFrame.h"
#include "Camera.h"

namespace INDOOR_SLAM{
    class Tracker{
    public:
        unsigned long nextFrameId;

        StereoFrame prevStereoFrame, curStereoFrame;

    public:
        Tracker();
        void ConsumeImage(
                const cv::Mat& leftImg, const cv::Mat& rightImg, const double& timestamp);
        cv::Mat getDebugImg();

    };
}

#endif //INDOOR_SLAM_TRACKER_H
