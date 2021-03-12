//
// Created by buenos on 2021/3/10.
//

#ifndef INDOOR_SLAM_FRAME_H
#define INDOOR_SLAM_FRAME_H
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>

namespace INDOOR_SLAM{
    class Frame{
    public:
        cv::Mat grayImg;
        std::vector<cv::KeyPoint> keyPoints;
        cv::Mat descriptors;

    public:
        Frame(){}
        Frame(const cv::Mat& img_);
        void ExtractFeatures();
    };
}

#endif //INDOOR_SLAM_FRAME_H
