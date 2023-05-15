//
// Created by AC on 2023/5/15.
//

#include "RSHelper.h"
#include <drogon/drogon.h>


cv::Mat RSHelper::get_depth() {

    START_TIMER
    color_map = std::make_shared<rs2::colorizer>();
    rs2::frameset data = pipe->wait_for_frames(); // Wait for next set of frames from the camera
    STOP_TIMER
    rs2::frame depth = data.get_depth_frame().apply_filter(*color_map);
    const int depth_w = depth.as<rs2::video_frame>().get_width();
    const int depth_h = depth.as<rs2::video_frame>().get_height();
//    START_TIMER
    START_TIMER
    cv::Mat depth_image(cv::Size(depth_w, depth_h), CV_8UC3, (void *) depth.get_data(), cv::Mat::AUTO_STEP);
    STOP_TIMER
//    STOP_TIMER
    return depth_image;
}

cv::Mat RSHelper::get_color() {
    rs2::frameset data = pipe->wait_for_frames(); // Wait for next set of frames from the camera
    rs2::frame color = data.get_color_frame();
    // Query frame size (width and height)
    const int color_w = color.as<rs2::video_frame>().get_width();
    const int color_h = color.as<rs2::video_frame>().get_height();
    cv::Mat color_image(cv::Size(color_w, color_h), CV_8UC3, (void *) color.get_data(), cv::Mat::AUTO_STEP);
    return color_image;
}


void RSHelper::destroy_rs() {
    pipe->stop();
}



