/**
 *
 *  RealSenseSDK.h
 *
 */

#pragma once

#include <drogon/plugins/Plugin.h>
#include <librealsense2/rs.hpp>
#include <opencv2/opencv.hpp>


class RealSenseSDK : public drogon::Plugin<RealSenseSDK> {
public:
    RealSenseSDK() {}

    /// This method must be called by drogon to initialize and start the plugin.
    /// It must be implemented by the user.
    void initAndStart(const Json::Value &config) override;
    /// 获取深度图像
    /// \return
    cv::Mat get_depth();
    /// 获取RGB彩色图像
    /// \return
    cv::Mat get_color();
    ///
    /// \param alpha 深度图像与RGB图像的叠加比例[0.0f-1.0f]，值越大RGB图越深
    /// \param direction_flag 0：叠加向深度方向，非0，叠加到RGB图像
    /// \return 返回叠加后的cv::Mat
    cv::Mat get_align(float alpha = 0.5, int direction_flag = 0);

    std::vector<int> get_compress_params();
    /// 获取深度图中某个坐标点距离摄像头的距离，可以在可见光图像对齐深度图后，利用深度学习检测到物理坐标，然后将坐标输入进来计算距离
    /// \param x 深度图x坐标
    /// \param y 深度图y坐标
    /// \return 返回深度float
    float get_distance(int x, int y);


    /// This method must be called by drogon to shutdown the plugin.
    /// It must be implemented by the user.
    void shutdown() override;

private:
    std::shared_ptr<rs2::pipeline> pipe = nullptr;
    int jpg_quality;
};

