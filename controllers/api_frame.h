#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

namespace api {
    class frame : public drogon::HttpController<frame> {
    public:
        METHOD_LIST_BEGIN
            // use METHOD_ADD to add your custom processing function here;
            METHOD_ADD(frame::get_frame, "/get_frame", Post);
            // METHOD_ADD(frame::your_method_name, "/{1}/{2}/list", Get); // path is /api/frame/{arg1}/{arg2}/list
            // ADD_METHOD_TO(frame::your_method_name, "/absolute/path/{1}/{2}/list", Get); // path is /absolute/path/{arg1}/{arg2}/list
        METHOD_LIST_END

        // your declaration of processing function maybe like this:
        void get_frame(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    };
}
