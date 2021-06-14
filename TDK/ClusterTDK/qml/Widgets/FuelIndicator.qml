import QtQuick 2.0
import "../../JavaScriptFiles/simulationUtils.js" as SimUtils

Item {
    property int input
    property int maxInput
    property int minInput
    property int minOutput
    property int maxOutput

    property int maxSimulationInput: 100
    property bool generatorMode

    onGeneratorModeChanged: {
        input = 0
    }

    Image {
        anchors.fill: parent
        source: "qrc:/images/fuelGauge.png"
    }

    Image {
        anchors.centerIn: parent
        scale: 0.37
        source: "qrc:/images/needle.png"
        rotation: generatorMode ? SimUtils.map(input, 0, maxSimulationInput, minOutput, maxOutput)
                                : SimUtils.map(input, 0, maxInput, minOutput, maxOutput)

        Behavior on rotation { NumberAnimation { duration: 150 } }
    }
}
