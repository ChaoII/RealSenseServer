#include <drogon/drogon.h>

#if defined(WIN32) && defined(_MSC_VER)

#pragma warning(disable:4267)

#endif


int main() {
    //Set HTTP listener address and port
//    drogon::app().addListener("0.0.0.0", 8897);
    //Load config file
    drogon::app().loadConfigFile("../../config.json");
    //Run HTTP framework,the method will block in the internal event loop
    drogon::app().run();
    return 0;
}
