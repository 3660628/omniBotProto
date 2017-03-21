//
// Created by Kris Temmerman on 21/03/17.
//

#include "CameraHandler.h"
#include "GLTexture.h"
using namespace std;
void CameraHandler::setup()
{
    camWidth =640;
    camHeight =480;
   cam = StartCamera(camWidth , camHeight,40,1,false);
   // texture.create( camHeight, camWidth);
}
void CameraHandler::update()
{

    std::vector<cv::Point> centers;
    const void* frame_data; int frame_sz;
    if(cam->BeginReadFrame(0,frame_data,frame_sz)) {
        //void *data = const_cast<void * >(frame_data);


        cv::Mat greyMat(camHeight, camWidth, CV_8UC1, const_cast<void * >(frame_data));

        threshold(greyMat, greyMat, 230, 255, 0);
        cv::Mat color;
        cv::cvtColor(greyMat,color,cv::COLOR_GRAY2RGB);
        texture.setMat(color);
        std::vector <std::vector<cv::Point>> contours;
        cv::findContours(greyMat, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);
        for (size_t index = 0; index < contours.size(); index++) {
            cv::Moments moms = cv::moments(cv::Mat(contours[index]));
            cv::Point p = cv::Point(moms.m10 / moms.m00, moms.m01 / moms.m00);

            centers.push_back(p);

        }


        cam->EndReadFrame(0);
    }


}