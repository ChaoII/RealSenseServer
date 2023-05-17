#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

namespace Api {
    class Frame : public drogon::HttpController<Frame> {
    public:
        METHOD_LIST_BEGIN
            // use METHOD_ADD to add your custom processing function here;
            METHOD_ADD(Frame::get_frame, "/get_frame", Post);
            METHOD_ADD(Frame::get_align, "/get_align", Post);
            METHOD_ADD(Frame::get_distance, "/get_distance", Post);

            // METHOD_ADD(frame::your_method_name, "/{1}/{2}/list", Get); // path is /api/frame/{arg1}/{arg2}/list
            // ADD_METHOD_TO(frame::your_method_name, "/absolute/path/{1}/{2}/list", Get); // path is /absolute/path/{arg1}/{arg2}/list
        METHOD_LIST_END
        // your declaration of processing function maybe like this:
        void get_frame(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

        void get_align(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

        void get_distance(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    };
}
