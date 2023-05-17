#include "api_frame.h"
#include "plugins/RealSenseSDK.h"

using namespace Api;

// Add definition of your processing function here
void Api::Frame::get_frame(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    auto req_obj = req->getJsonObject();
    if (req_obj == nullptr) {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(drogon::k400BadRequest);
        resp->setBody("error request body");
        callback(resp);
        return;
    }
    cv::Mat frame;
    std::string frame_type = req_obj->get("frame_type", "").asString();
    if (frame_type == "depth") {
        frame = app().getPlugin<RealSenseSDK>()->get_depth();
    } else if (frame_type == "color") {
        frame = app().getPlugin<RealSenseSDK>()->get_color();
    } else {
        LOG_WARN << "frame_type must in ['depth' , 'color']";
        Json::Value val;
        val["img"] = {};
        auto resp = HttpResponse::newHttpJsonResponse(val);
        callback(resp);
        return;
    }
    std::vector<unsigned char> buf;
    cv::imencode(".jpg", frame, buf, app().getPlugin<RealSenseSDK>()->get_compress_params());
    auto ret = drogon::utils::base64Encode(buf.data(), buf.size());
    Json::Value val;
    val["img"] = ret;
    auto resp = HttpResponse::newHttpJsonResponse(val);
    callback(resp);
}

void Api::Frame::get_align(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    auto req_obj = req->getJsonObject();
    float alpha = 0.0f;
    int direction_flag = 0;
    if (req_obj != nullptr) {
        alpha = req_obj->get("alpha", 0.0f).asFloat();
        direction_flag = req_obj->get("direction_flag", 0).asInt();
    }
    cv::Mat align = app().getPlugin<RealSenseSDK>()->get_align(alpha, direction_flag);
    std::vector<unsigned char> buf;
    cv::imencode(".jpg", align, buf, app().getPlugin<RealSenseSDK>()->get_compress_params());
    auto ret = drogon::utils::base64Encode(buf.data(), buf.size());
    Json::Value val;
    val["img"] = ret;
    auto resp = HttpResponse::newHttpJsonResponse(val);
    callback(resp);
}

void Api::Frame::get_distance(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {

    auto req_obj = req->getJsonObject();
    if (req_obj == nullptr) {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(drogon::k400BadRequest);
        resp->setBody("error request body");
        callback(resp);
        return;
    }
    int x = req_obj->get("x", -1).asInt();
    int y = req_obj->get("y", -1).asInt();

    float distance = app().getPlugin<RealSenseSDK>()->get_distance(x, y);
    Json::Value val;
    val["distance"] = distance;
    auto resp = HttpResponse::newHttpJsonResponse(val);
    callback(resp);
}



