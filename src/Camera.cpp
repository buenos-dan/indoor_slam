//
// Created by buenos on 2021/3/12.
//
#include "Camera.h"

namespace INDOOR_SLAM {
    Camera::Camera() {
        b = 47.90639384423901;
        fu = 457.587;
        fv = 456.134;
        cu = 379.999;
        cv = 255.238;
    }

    Eigen::Vector3d Camera::BackProjection(const double &u, const double &v, const double &disp) {
        //Eigen::Vector2d pl_(points_l[i1].pt.x, points_l[i1].pt.y);

        Eigen::Vector3d P;
        P(2) = b * fu / disp;
        P(0) = b * (u - cu) / disp;
        P(1) = b * (v - cv) / disp;

        return P;
    }
}
