//
// Created by buenos on 2021/3/12.
//
#include "StereoFrame.h"


namespace INDOOR_SLAM {

    StereoFrame::StereoFrame(const cv::Mat &leftImg_, const cv::Mat &rightImg_, const double &timeStamp_,
                             const unsigned long &frameId_) {
        leftFrame = Frame(leftImg_);
        rightFrame = Frame(rightImg_);
        timeStamp = timeStamp_;
        frameId = frameId_;

        MatchStereoFeatures();
        RefineStereoFeatures();
    }

    void StereoFrame::MatchStereoFeatures() {
        cv::Ptr<cv::DescriptorMatcher> matcher = cv::DescriptorMatcher::create("BruteForce-Hamming");
        std::vector<cv::DMatch> matches;
        matcher->match(leftFrame.descriptors, rightFrame.descriptors, matches);

        auto min_max = minmax_element(matches.begin(), matches.end(),
                                      [](const cv::DMatch &m1, const cv::DMatch &m2) {
                                          return m1.distance < m2.distance;
                                      });
        double min_dist = min_max.first->distance;

        matchStatus.resize(leftFrame.descriptors.rows);
        for (int i = 0; i < leftFrame.descriptors.rows; i++) {
            if (matches[i].distance <= fmax(2 * min_dist, 30.0)) {
                matchStatus[i] = true;
            }
        }
    }

    void StereoFrame::RefineStereoFeatures() {
        std::cout << "before refine: " << matchStatus.size() << std::endl;
        int goodMatchNum = 0;
        for (int i = 0; i < matchStatus.size(); i++) {
            // 左右目特征点正确匹配
            if (matchStatus[i]) {
                cv::KeyPoint p_l = leftFrame.keyPoints[i];
                cv::KeyPoint p_r = rightFrame.keyPoints[i];
                // 视差大于1.0
                if (p_l.pt.x - p_r.pt.x > 1.0) {
                    leftFrame.keyPoints[goodMatchNum] = leftFrame.keyPoints[i];
                    rightFrame.keyPoints[goodMatchNum] = rightFrame.keyPoints[i];
                    leftFrame.descriptors.row(goodMatchNum) = leftFrame.descriptors.row(i);
                    rightFrame.descriptors.row(goodMatchNum) = rightFrame.descriptors.row(i);
                    goodMatchNum++;
                }
            }
        }
        leftFrame.keyPoints.resize(goodMatchNum);
        rightFrame.keyPoints.resize(goodMatchNum);
        leftFrame.descriptors = leftFrame.descriptors.rowRange(0, goodMatchNum);
        rightFrame.descriptors = rightFrame.descriptors.rowRange(0, goodMatchNum);

        std::cout << "after refine: " << goodMatchNum << std::endl;
    }


    void StereoFrame::calFeaturesPos(Camera* cam){
        for(int i = 0; i < leftFrame.keyPoints.size(); i++){
            cv::KeyPoint kp = leftFrame.keyPoints[i];
            double disp = leftFrame.keyPoints[i].pt.x - rightFrame.keyPoints[i].pt.x;
            Eigen::Vector2d p(kp.pt.x, kp.pt.y);
            Eigen::Vector3d P = cam->BackProjection(p(0), p(1), disp);
            points3d.push_back(P);
        }
    }

}