import QtQuick 2.0
import "../Components"

Item {
    property string menuTitle

    property bool controlsEnabled

    signal generatorMode
    signal receiverMode
    signal closeDrawer
    signal turnLeft
    signal turnRight
    signal emergencyLights
    signal checkEngine
    signal lowBeam
    signal highBeams
    signal seatBelt

    clip: true

    Rectangle {
        anchors.fill: parent
        color: "#717171"
        opacity: 0.9

        //atrapa los clicks o toques dentro de la caja del menu para evitar que se cierre
        MouseArea {
           anchors.fill: parent

           onClicked: {}
        }
    }

    Text {
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            topMargin: 60
        }

        text: menuTitle
        horizontalAlignment: Text.AlignHCenter
        color: "white"
    }

    Column {
        width: parent.width
        height: 130
        spacing: 10
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            topMargin: 90
        }

        Button {
            width: parent.width - 20
            height: 40
            anchors.horizontalCenter: parent.horizontalCenter
            opacity: 0.95
            label: "Generador"

            onButtonClicked: {
                generatorMode()
                controlsEnabled = true
            }
        }

        Button {
            width: parent.width - 20
            height: 40
            anchors.horizontalCenter: parent.horizontalCenter
            opacity: 0.95
            label: "Receptor"

            onButtonClicked: {
                receiverMode()
                controlsEnabled = false
            }
        }
    }

    Text {
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            topMargin: 200
        }

        text: "Direccionales"
        horizontalAlignment: Text.AlignHCenter
        color: "white"
    }

    Row {
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            topMargin: 230
        }

        spacing: 10
        enabled: controlsEnabled
        opacity: controlsEnabled ? 1 : 0.5

        property double delegateCellWidth: (parent.width - (spacing * 2) - 20) / 3

        Button {
            width: parent.delegateCellWidth
            height: 40
            opacity: 0.95
            icon: "qrc:/images/icons/leftArrow_icon.png"

            onButtonClicked: {
                turnLeft()
            }
        }

        Button {
            width: parent.delegateCellWidth
            height: 40
            opacity: 0.95
            icon: "qrc:/images/icons/hazardLights_icon.png"

            onButtonClicked: {
                emergencyLights()
            }
        }

        Button {
            width: parent.delegateCellWidth
            height: 40
            opacity: 0.95
            icon: "qrc:/images/icons/rightArrow_icon.png"

            onButtonClicked: {
                turnRight()
            }
        }
    }

    Text {
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            topMargin: 290
        }

        text: "Luces"
        horizontalAlignment: Text.AlignHCenter
        color: "white"
    }

    Row {
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            topMargin: 320
        }

        spacing: 10
        enabled: controlsEnabled
        opacity: controlsEnabled ? 1 : 0.5

        property double delegateCellWidth: (parent.width - (spacing * 2) - 20) / 2

        Button {
            id: lowBeamsControl

            width: parent.delegateCellWidth
            height: 40
            opacity: 0.95
            icon: "qrc:/images/icons/lowBeams_icon.png"

            onButtonClicked: {
                lowBeam()
            }
        }

        Button {
            id: highBeamsControl

            width: parent.delegateCellWidth
            height: 40
            opacity: 0.95
            icon: "qrc:/images/icons/highBeams_icon.png"

            onButtonClicked: {
                highBeams()
            }
        }
    }

    Text {
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            topMargin: 390
        }

        text: "Testigos"
        horizontalAlignment: Text.AlignHCenter
        color: "white"
    }

    Row {
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            topMargin: 420
        }

        spacing: 10
        enabled: controlsEnabled
        opacity: controlsEnabled ? 1 : 0.5

        property double delegateCellWidth: (parent.width - (spacing * 2) - 20) / 2

        Button {
            id: checkEngineControl

            width: parent.delegateCellWidth
            height: 40
            opacity: 0.95
            icon: "qrc:/images/icons/check_icon.png"

            onButtonClicked: {
                checkEngine()
            }
        }

        Button {
            id: seatBeltsControl

            width: parent.delegateCellWidth
            height: 40
            opacity: 0.95
            icon: "qrc:/images/icons/seatbelt_icon.png"

            onButtonClicked: {
                seatBelt()
            }
        }
    }

    Rectangle {
        color: "white"
        height: 25
        width: 25
        radius: 3

        anchors {
            right: parent.right
            top: parent.top
            topMargin: 10
            rightMargin: 10
        }

        Image {
            anchors {
                fill: parent
                margins: 1
            }

            source: "qrc:/images/icons/closeIcon.png"
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                closeDrawer()
            }
        }
    }
}
