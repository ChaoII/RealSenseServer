/**
 *
 *  RealSenseSDK.h
 *
 */

#pragma once

#include <drogon/plugins/Plugin.h>


class RealSenseSDK : public drogon::Plugin<RealSenseSDK>
{
  public:
    RealSenseSDK() {}
    /// This method must be called by drogon to initialize and start the plugin.
    /// It must be implemented by the user.
    void initAndStart(const Json::Value &config) override;

    /// This method must be called by drogon to shutdown the plugin.
    /// It must be implemented by the user.
    void shutdown() override;
};

