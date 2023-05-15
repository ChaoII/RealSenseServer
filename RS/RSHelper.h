//
// Created by AC on 2023/5/15.
//

#pragma once

#include <librealsense2/rs.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <RS/Timer.h>


class RSHelper {

public:
    static std::shared_ptr<RSHelper> getInstance() {
        if (!re_help) {
            re_help = std::make_shared<RSHelper>();
            if (!pipe) {
                pipe = std::make_shared<rs2::pipeline>();
                pipe->start();
            }
        }
        return re_help;
    }

    cv::Mat get_depth();

    cv::Mat get_color();

    void destroy_rs();

private:
    inline static std::shared_ptr<RSHelper> re_help = nullptr;
    inline static std::shared_ptr<rs2::pipeline> pipe = nullptr;
    std::shared_ptr<rs2::colorizer> color_map = nullptr;
};


