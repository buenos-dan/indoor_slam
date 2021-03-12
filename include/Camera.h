//
// Created by buenos on 2021/3/12.
//

#ifndef INDOOR_SLAM_CAMERA_H
#define INDOOR_SLAM_CAMERA_H
#include <Eigen/Core>

namespace INDOOR_SLAM{

    class Camera{
    public:
        double b;        // baseLine
        double fu, fv;   // focal length
        double cu, cv;   // optical center (cu, cv)

    public:
        Camera();
        Eigen::Vector3d BackProjection(const double &u, const double &v, const double &disp );
    };
}

#endif //INDOOR_SLAM_CAMERA_H
