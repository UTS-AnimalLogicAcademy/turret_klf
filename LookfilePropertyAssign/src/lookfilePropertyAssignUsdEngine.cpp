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
#include <usg/engine/GeomSceneContext.h>
#include <usg/engine/GeomEngine.h>
#include <usg/base/Value.h>
#include <UsdProcessingEngine/Engine.h>
#include <FnPluginSystem/FnPlugin.h>

// #include <turretClient.h>

namespace Foundry
{

namespace Katana
{

namespace UPE
{

class LookfilePropertyAssignEngine : public Engine
{

    EnginePtr copy() const override
    {
        return EnginePtr(new LookfilePropertyAssignEngine(*this));
    }

    EngineDescription describe() const override
    {
        EngineDescription desc;
        desc.name = "LookfilePropertyAssignEngine";
        desc.summary = "Assigns RenderMan cryptomatte properties 'lookfile' and 'assetRoot' to prims in the USD stage";
        return desc;
    }
    
public:

    LookfilePropertyAssignEngine()
    {
        //register args here
    }

    static void flush()
    {
        std::cout << "Flushed look file property assign USD engine\n";
    }

protected:
    void process(usg::GeomSceneContext &context) override
    {
        usg::StageRef currentStage = context.stage();

        for (usg::Prim prim : currentStage->traverse())
        {
            // Set attributes on each prim
            if (prim.getAttr("userProperties:lookfileUri").isValid() && !prim.getAttr("primvars:ri:user:lookfile").isValid())
            {

                usg::Value lookfileUri;
                prim.getAttr("userProperties:lookfileUri").getValue(lookfileUri, fdk::defaultTimeValue());
                
                usg::Attribute lookfileAttr = prim.createAttr("primvars:ri:attributes:user:lookfile", usg::Value::String);
                
                usg::Attribute assetRootAttr = prim.createAttr("primvars:ri:attributes:user:assetRoot", usg::Value::Token);
                std::string assetRoot = prim.getPath().asString();

                lookfileAttr.setValue(lookfileUri,fdk::defaultTimeValue());
                assetRootAttr.setValue(assetRoot,fdk::defaultTimeValue());

            }
        }
    }

};

DEFINE_USDENGINE_PLUGIN(LookfilePropertyAssignEngine);

} // namespace UPE
} // namespace Katana
} // namespace Foundry


void registerPlugins()
{
    // PLUGIN_CLASS, PLUGIN_NAME, PLUGIN_MAJOR_VERSION, PLUGIN_MINOR_VERSION
    REGISTER_PLUGIN(Foundry::Katana::UPE::LookfilePropertyAssignEngine, "LookfilePropertyAssignEngine", 0, 1);
}
