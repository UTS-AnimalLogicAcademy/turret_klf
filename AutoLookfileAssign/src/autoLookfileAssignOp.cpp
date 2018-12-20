#include <sstream>
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

#include <FnAttribute/FnAttribute.h>
#include <FnAttribute/FnGroupBuilder.h>

#include <FnPluginSystem/FnPlugin.h>
#include <FnGeolib/op/FnGeolibOp.h>
#include <FnGeolib/util/Path.h>

#include <FnGeolibServices/FnGeolibCookInterfaceUtilsService.h>


#include <zmq_client_cpp/zmqClient.h>

namespace { //anonymous
    zmq_client::zmqClient g_zmq("klf");

class AutoLookfileAssignOp : public Foundry::Katana::GeolibOp
{
public:

    static void setup(Foundry::Katana::GeolibSetupInterface &interface)
    {
        interface.setThreading(
            // ThreadModeConcurrent is not safe, will result in glitchy lookfile assignments.
            // Use ThreadModeGlobalUnsafe instead:
            Foundry::Katana::GeolibSetupInterface::ThreadModeGlobalUnsafe);
    }

    static void flush()
    {
        std::cout << "Flushed look file op\n";
    }

    static void cook(Foundry::Katana::GeolibCookInterface & interface)
    {
        FnAttribute::StringAttribute usdLookFileURI = interface.getAttr("userProperties.lookfileUri", interface.getOutputLocationPath());

        std::string query;

        if(usdLookFileURI.isValid()) {
            query = usdLookFileURI.getValue();

            //if(query.find("=set&")!=std::string::npos)
            //    return;

            // Check USD_ASSET_TIME env var
            if(const char* envUsdAssetTime = std::getenv("USD_ASSET_TIME")) {
                // If time var exists, append asset time to query
                query += "&time=" + std::string(envUsdAssetTime);
            }

            // -- Begin querying
            std::string resolvedPath = g_zmq.resolve_name(query);

            if(resolvedPath == "NOT_FOUND") {

                const char* env_p = std::getenv("TURRET_AUTOLOOKFILEASSIGN_LOG_LEVEL");
                const std::string env_s = std::string(env_p);
                if (env_s == "1"){
                    std::cout << "ALA Lookfile Resolver - Tank query failed to resolve file." << std::endl;
                }

                return;
            }

            FnAttribute::StringAttribute klfFilePath = FnAttribute::StringAttribute(resolvedPath);

            interface.setAttr("lookfile.asset", klfFilePath);
            interface.stopChildTraversal();
            return;
        }

    }

};

DEFINE_GEOLIBOP_PLUGIN(AutoLookfileAssignOp);

} // anonymous

void registerPlugins()
{
    REGISTER_PLUGIN(AutoLookfileAssignOp, "AutoLookfileAssign", 0, 1);
}
