import QtQuick 2.0
import "../../JavaScriptFiles/simulationUtils.js" as SimUtils

Item {
    id: sliderContainer

    property double sliderValue
    property bool reset

    onResetChanged: {
        if (reset)
            resetAnimation.running = true
    }

    Rectangle {
        width: 6
        height: parent.height
        radius: 3
        color: "#DDDDDD"
        anchors.centerIn: parent
    }

    Rectangle {
        width: 6
        radius: 3
        color: "#717171"

        anchors {
            top: sliderIndicator.verticalCenter
            bottom: parent.bottom
            horizontalCenter: parent.horizontalCenter
        }
    }

    Rectangle {
        id: sliderIndicator

        y: sliderContainer.height - sliderIndicator.height
        width: 30
        height: 30
        radius: 15
        color: "#363636"

        anchors.horizontalCenter: parent.horizontalCenter

        Drag.active: dragArea.drag.active
        Drag.hotSpot.x: 5
        Drag.hotSpot.y: 5

        onYChanged: sliderValue = SimUtils.map(sliderIndicator.y, sliderContainer.height - sliderIndicator.height, 0, 0, 100)

        MouseArea {
            id: dragArea
            anchors.fill: parent
            drag.target: parent
            drag.minimumY: 0
            drag.maximumY: sliderContainer.height - sliderIndicator.height
            drag.axis: Drag.YAxis
        }

        PropertyAnimation {
            id: resetAnimation
            target: sliderIndicator
            property: "y"
            to: sliderContainer.height - sliderIndicator.height
            duration: 100
            easing.type: Easing.InOutQuad
        }
    }    
}
