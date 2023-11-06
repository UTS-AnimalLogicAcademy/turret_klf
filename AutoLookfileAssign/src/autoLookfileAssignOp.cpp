//
// Copyright 2019 University of Technology, Sydney
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
// documentation files (the "Software"), to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and
// to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
//   * The above copyright notice and this permission notice shall be included in all copies or substantial portions of
//     the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

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

#include <turretClient.h>

namespace { //anonymous
    turret_client::turretClient g_turretClient("klf");

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
        std::cout << "Flushed auto look file op\n";
    }

    static void cook(Foundry::Katana::GeolibCookInterface & interface)
    {
        FnAttribute::StringAttribute usdLookFileURI = interface.getAttr("userProperties.lookfileUri", interface.getOutputLocationPath());
        FnAttribute::StringAttribute outputLocationPath = interface.getOutputLocationPath();
        FnAttribute::StringAttribute inputLocationPath = interface.getInputLocationPath();

        std::string query;

        if(usdLookFileURI.isValid()) {
            query = usdLookFileURI.getValue();

            // Check USD_ASSET_TIME env var
            if(const char* envUsdAssetTime = std::getenv("USD_ASSET_TIME")) {
                // If time var exists, append asset time to query
                query += "&time=" + std::string(envUsdAssetTime);
            }

            // -- Begin querying
            std::string resolvedPath = g_turretClient.resolve_name(query);

            if(resolvedPath == "Unable to parse query") {
                const char* env_p = std::getenv("TURRET_AUTOLOOKFILEASSIGN_LOG_LEVEL");
                const std::string env_s = std::string(env_p);
                if (env_s == "1"){
                    std::cout << "ALA Lookfile Resolver - Tank query failed to resolve file." << std::endl;
                }
                return;
            }

            if(resolvedPath == "uncached_query") {
                return;
            }

            // cache now includes null paths, so handle them:
            if(resolvedPath == "NOT_FOUND") {
                return;
            }

            FnAttribute::StringAttribute klfFilePath = FnAttribute::StringAttribute(resolvedPath);

            interface.setAttr("lookfile.asset", klfFilePath);

            // set an additional renderman attribute, useful for cyrptomatte:
            interface.setAttr("prmanStatements.attributes.user.lookfile", klfFilePath);
            interface.setAttr("prmanStatements.attributes.user.assetRoot", outputLocationPath);
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
