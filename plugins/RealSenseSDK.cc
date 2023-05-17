/**
 *
 *  RealSenseSDK.cc
 *
 */

#include "RealSenseSDK.h"

using namespace drogon;

void RealSenseSDK::initAndStart(const Json::Value &config) {
    /// Initialize and start the plugin
    jpg_quality = config.get("jpg_quality", 95).asInt();
    pipe = std::make_shared<rs2::pipeline>();
    pipe->start();
}

void RealSenseSDK::shutdown() {
    /// Shutdown the plugin
    pipe->stop();
}

cv::Mat RealSenseSDK::get_depth() {
    rs2::colorizer color_map;
    rs2::frameset data = pipe->wait_for_frames();
    auto depth_ = data.get_depth_frame();
    auto depth = color_map.colorize(depth_);

    const int depth_w = depth.get_width();
    const int depth_h = depth.get_height();
    cv::Mat depth_image(cv::Size(depth_w, depth_h),
                        CV_8UC3,
                        (void *) depth.get_data(),
                        cv::Mat::AUTO_STEP);
    return depth_image.clone();
}

cv::Mat RealSenseSDK::get_color() {
    rs2::frameset data = pipe->wait_for_frames(); // Wait for next set of frames from the camera
    rs2::frame color = data.get_color_frame();
    const int color_w = color.as<rs2::video_frame>().get_width();
    const int color_h = color.as<rs2::video_frame>().get_height();
    cv::Mat color_image(cv::Size(color_w, color_h),
                        CV_8UC3,
                        (void *) color.get_data(),
                        cv::Mat::AUTO_STEP);
    cv::cvtColor(color_image, color_image, cv::COLOR_BGR2RGB);
    return color_image;
}

std::vector<int> RealSenseSDK::get_compress_params() {
    std::vector<int> compress_params;
    compress_params.push_back(cv::IMWRITE_JPEG_QUALITY);
    compress_params.push_back(jpg_quality);
    return compress_params;
}

float RealSenseSDK::get_distance(int x, int y) {
    rs2::frameset data = pipe->wait_for_frames();
    rs2::depth_frame depth = data.get_depth_frame();
    const int depth_w = depth.as<rs2::video_frame>().get_width();
    const int depth_h = depth.as<rs2::video_frame>().get_height();
    if (x > depth_w || x < 0 || y > depth_h || y < 0) {
        return -1.0f;
    }
    return depth.get_distance(x, y);
}

cv::Mat RealSenseSDK::get_align(float alpha, int direction_flag) {
    rs2::colorizer color_map;
    rs2::align align_to_color(RS2_STREAM_COLOR);
    rs2::align align_to_depth(RS2_STREAM_DEPTH);
    rs2::frameset frameset = pipe->wait_for_frames();
    if (direction_flag == 0) {
        // Align all frames to depth
        frameset = align_to_depth.process(frameset);
    } else {
        frameset = align_to_color.process(frameset);
    }
    // With the aligned frameset we proceed as usual
    auto depth_ = frameset.get_depth_frame();
    auto color = frameset.get_color_frame();
    auto depth = color_map.colorize(depth_);

    // Use the Alpha channel for blending
    const int w = color.get_width();
    const int h = color.get_height();
    cv::Mat color_image(cv::Size(w, h),
                        CV_8UC3,
                        (void *) color.get_data(),
                        cv::Mat::AUTO_STEP);

    cv::Mat depth_image(cv::Size(w, h),
                        CV_8UC3,
                        (void *) depth.get_data(),
                        cv::Mat::AUTO_STEP);

    cv::Mat dst;
    // apply deepcopy so it is not needed to add .clone() on return result;
    cv::addWeighted(color_image, alpha, depth_image, 1 - alpha, 0, dst);
    cv::cvtColor(dst, dst, cv::COLOR_BGR2RGB);
    return dst;
}


