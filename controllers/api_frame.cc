#include "api_frame.h"
#include "RS/RSHelper.h"

using namespace api;

// Add definition of your processing function here
void api::frame::get_frame(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    auto req_obj = req->getJsonObject();
    if (req_obj == nullptr) {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(drogon::k400BadRequest);
        resp->setBody("error request body");
        callback(resp);
        return;
    }
    cv::Mat frame;
    if ((*req_obj)["frame_type"].asString() == "depth") {
        frame = RSHelper::getInstance()->get_depth();
    } else if ((*req_obj)["frame_type"].asString() == "color") {
        frame = RSHelper::getInstance()->get_color();
    } else {
        Json::Value val;
        val["img"] = {};
        auto resp = HttpResponse::newHttpJsonResponse(val);
        callback(resp);
        return;
    }
    std::cout << 23 << std::endl;
    std::vector<unsigned char> buf;
    cv::imencode(".jpg", frame, buf);
    auto ret = drogon::utils::base64Encode(buf.data(), buf.size());
    Json::Value val;
    val["img"] = ret;
    auto resp = HttpResponse::newHttpJsonResponse(val);
    callback(resp);
}



