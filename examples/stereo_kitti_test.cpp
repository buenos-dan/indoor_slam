//
// Created by buenos on 2021/3/11.
//
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
//#include <assert.h>
#include "Tracker.h"

using namespace std;

void LoadImages(vector<string> &leftImgSeq, vector<string>& rightImgSeq, vector<double>& timeStampSeq);

int main(int argc, char** argv){

    vector<string> leftImgSeq, rightImgSeq;
    vector<double> timeStampSeq;
    LoadImages(leftImgSeq, rightImgSeq, timeStampSeq);
    int nImages = leftImgSeq.size();
    assert(
        !leftImgSeq.empty() &&
        !rightImgSeq.empty() &&
        leftImgSeq.size() == rightImgSeq.size()
          );

    INDOOR_SLAM::Tracker tracker;
    for(int i = 0; i < nImages; i++){
        cv::Mat leftImg = cv::imread(leftImgSeq[i], CV_LOAD_IMAGE_UNCHANGED);
        cv::Mat rightImg = cv::imread(rightImgSeq[i], CV_LOAD_IMAGE_UNCHANGED);
        double timeStamp = timeStampSeq[i];

        tracker.ConsumeImage(leftImg, rightImg, timeStamp);

        // display
        cv::imshow("debug", tracker.getDebugImg());
        cv::waitKey(10);
    }

    return 0;
}

void LoadImages(vector<string>& leftImgSeq, vector<string>& rightImgSeq, vector<double>& timeStampSeq){

    ifstream f;
    string projectPath = "/Users/buenos/slam/buenos/indoor_slam";
    string timeSeqFile = projectPath + "/examples/MH01.txt";
    string leftImgPath = projectPath + "/dataset/mav0/cam0/data";
    string rightImgPath = projectPath + "/dataset/mav0/cam1/data";
    f.open(timeSeqFile);

    while(!f.eof())
    {
        string s;
        getline(f,s);
        if(!s.empty())
        {
            stringstream ss;
            ss << s;
            leftImgSeq.push_back(leftImgPath + "/" + ss.str() + ".png");
            rightImgSeq.push_back(rightImgPath + "/" + ss.str() + ".png");
            double t;
            ss >> t;
            timeStampSeq.push_back(t/1e9);
        }
    }
}