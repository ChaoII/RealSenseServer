#include <drogon/drogon.h>
#include "RS/RSHelper.h"

int main() {
    //Set HTTP listener address and port
    RSHelper::getInstance();
    drogon::app().addListener("0.0.0.0", 8897);
    //Load config file
    //drogon::app().loadConfigFile("../config.json");
    //Run HTTP framework,the method will block in the internal event loop
    drogon::app().run();
    return 0;
}
