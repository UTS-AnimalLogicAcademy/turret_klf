"""
UsdSubLayerAdd.py

Provides a node for adding USD SubLayers.
"""
import collections
import AssetAPI
import NodegraphAPI
import usg
from UsdProcessingEngine import EngineArgsBuilder
from NodesUsdAPI import Args, NodeUsd

class alaLookfilePropertyAssignUSD(NodeUsd):
    """
    A USD Node to add subLayers.
    """

    def __init__(self):
        super().__init__()
        self.addInputPort('in')
        self.addOutputPort('out')
        #self.getParameters().parseXML(_Parameter_XML)

    def _getEngineChain(self, engineChainInterface):
        frameTime = engineChainInterface.getGraphState().getTime()
        args = EngineArgsBuilder(frameTime)
        # args[Args.ASSET] = usg.Value(self.getParameter('asset').getValue(0))
        # args[Args.TIME_OFFSET] = usg.Value(self.getParameter('time.timeOffset').getValue(0), usg.Value.Float)
        # args[Args.TIME_SCALE] = usg.Value(self.getParameter('time.timeScale').getValue(0), usg.Value.Float)
        engineChainInterface.appendEngine('LookfilePropertyAssignEngine', args.build())

    #def addParameterHints(self, attrName, inputDict):
    #    inputDict.update(_ExtraHints.get(attrName, {}))
#_Parameter_XML = '\n<group_parameter>\n    <string_parameter name=\'asset\' value=\'\'/>\n    <group_parameter name="time">\n        <number_parameter name=\'timeOffset\' value=\'0\'/>\n        <number_parameter name=\'timeScale\' value=\'1\'/>\n    </group_parameter>\n</group_parameter>\n'
#_ExtraHints = collections.OrderedDict({'UsdSubLayerAdd.asset': {'widget': 'assetIdInput', 'context': AssetAPI.kAssetContextUsd, 'fileTypes': 'usd|usda|usdc|usdz', 'help': 'Loads in the attached file as a SubLayer.'}, 'UsdSubLayerAdd.time.timeOffset': {'constant': 'True', 'help': 'Sets the time offset.'}, 'UsdSubLayerAdd.time.timeScale': {'constant': 'True', 'help': 'Sets the time scale factor.'}})
NodegraphAPI.RegisterPythonNodeType('alaLookfilePropertyAssignUSD', alaLookfilePropertyAssignUSD)
NodegraphAPI.AddNodeFlavor('alaLookfilePropertyAssignUSD', 'nativeusd')
NodegraphAPI.AddNodeFlavor('alaLookfilePropertyAssignUSD', 'composition')