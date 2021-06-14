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
        source: "qrc:/images/tachometer.png"
    }

    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: 80
        text: "RPM x 1000"
        font.pixelSize: 17
        color: "black"
        horizontalAlignment: Text.AlignHCenter
    }

    Image {
        anchors.centerIn: parent
        scale: 0.65
        source: "qrc:/images/needle.png"
        rotation: generatorMode ? SimUtils.map(input, 0, maxSimulationInput, minOutput, maxOutput)
                                : SimUtils.map(input, 0, maxInput, minOutput, maxOutput)

        Behavior on rotation { NumberAnimation { duration: 150 } }
    }
}