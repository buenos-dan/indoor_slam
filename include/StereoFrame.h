//
// Created by buenos on 2021/3/12.
//

#ifndef INDOOR_SLAM_STEREOFRAME_H
#define INDOOR_SLAM_STEREOFRAME_H
#include "Frame.h"
#include "Camera.h"
#include <Eigen/Core>

namespace INDOOR_SLAM{
    class StereoFrame{
    public:
        unsigned long frameId;
        double timeStamp;
        cv::Mat Tcw;
        // TODO: matches
        std::vector<bool> matchStatus;
        std::vector<Eigen::Vector3d> points3d;
        Frame leftFrame, rightFrame;

    public:
        StereoFrame(){}
        StereoFrame(const cv::Mat& leftImg_, const cv::Mat& rightImg_, const double& timeStamp_, const unsigned long& frameId_);
        void MatchStereoFeatures();
        void RefineStereoFeatures();
        void calFeaturesPos(Camera* cam);

    };
}
#endif //INDOOR_SLAM_STEREOFRAME_H
