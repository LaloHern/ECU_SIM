import QtQuick 2.9
import QtQuick.Window 2.2
import "Widgets"
import "DataPools"
import "../JavaScriptFiles/simulationUtils.js" as SimUtils

Item {
    id: root
    height: 480
    width: 800
    anchors.centerIn: parent

    DataPool{
        id: datapool
    }

    readonly property int canMsgData: gpiosController.canMsg()

    Connections {
        target: gpiosController

        enabled: datapool.operationMode === datapool._ReceiverMode

        onSpeedChanged: speedometer.input = gpiosController.speed
        onEngineRpmChanged: tachometerIndicator.input = gpiosController.engineRpm
        onEngineTempChanged: temperatureIndicator.input = gpiosController.engineTemp
        onFuelLevelChanged: fuelIndicator.input = gpiosController.fuelLevel
    }

    Tacometro {
        id: tachometerIndicator

        height: 300
        width: 300
        anchors {
            left: parent.left
            verticalCenter: parent.verticalCenter
            verticalCenterOffset: -50
            leftMargin: 90
        }

        input: canMsgData
        minOutput: -130
        maxOutput: 130
        maxInput: 255
        minInput: 0

        generatorMode: datapool.operationMode === datapool._GeneratorMode
    }

    Velocimetro {
        id: speedometer
        height: 300
        width: 300
        anchors {
            right: parent.right
            rightMargin: 90
            verticalCenterOffset: -50
            verticalCenter: parent.verticalCenter
        }

        input: canMsgData
        minOutput: -130
        maxOutput: 130
        maxInput: 240
        minInput: 0

        generatorMode: datapool.operationMode === datapool._GeneratorMode
    }

    TurnLights {
        id: turnLights
        height: 50
        width: 150
        anchors {
            top: parent.top
            topMargin: 10
            horizontalCenter: parent.horizontalCenter
        }
    }

    FuelIndicator {
        id: fuelIndicator

        height: 170
        width: 170
        anchors {
            right: parent.right
            bottom: parent.bottom
            rightMargin: 10
            bottomMargin: 10
        }

        input: canMsgData
        minOutput: -131
        maxOutput: 131
        maxInput: 255
        minInput: 0

        generatorMode: datapool.operationMode === datapool._GeneratorMode
    }

    TemperatureIndicator {
        id: temperatureIndicator

        height: 170
        width: 170
        anchors {
            left: parent.left
            bottom: parent.bottom
            leftMargin: 10
            bottomMargin: 10
        }

        input: canMsgData
        minOutput: -65
        maxOutput: 65
        maxInput: 255
        minInput: 0

        generatorMode: datapool.operationMode === datapool._GeneratorMode
    }

    Rtts {
        id: rtts

        height: 130
        width: 140
        anchors {
            horizontalCenter: parent.horizontalCenter
            bottom: parent.bottom
            bottomMargin: 10
        }
    }

    Item {
        id: simulationControls

        anchors.fill: parent
        visible: datapool.operationMode === datapool._GeneratorMode

        onVisibleChanged: {
            speedometerControl.reset = visible
            tachometerControl.reset = visible
            temperatureControl.reset = visible
            fuelControl.reset = visible
        }

        ControlSlider {
            id: speedometerControl

            height: 150
            width: 30

            anchors {
                right: parent.right
                verticalCenter: parent.verticalCenter
                verticalCenterOffset: -40
                rightMargin: 30
            }

            onSliderValueChanged: {
                speedometer.input = sliderValue

                var simulatedSpeedValue = SimUtils.map(sliderValue, 0, 100, 0, 240)

                //gpiosController.setMsgPayload(0, simulatedSpeedValue)
                //gpiosController.writeCANMsg(5, 8)
            }
        }

        ControlSlider {
            id: tachometerControl

            height: 150
            width: 30

            anchors {
                left: parent.left
                verticalCenter: parent.verticalCenter
                verticalCenterOffset: -40
                leftMargin: 30
            }

            onSliderValueChanged: {
                tachometerIndicator.input = sliderValue

                var simulatedRPMValue = SimUtils.map(sliderValue, 0, 100, 0, 8000)
                gpiosController.engineRpm = simulatedRPMValue

                //gpiosController.writeCANMsg(5, 8)
                //gpiosController.setMsgPayload(1, simulatedRPMValue)
            }
        }

        ControlSlider {
            id: temperatureControl

            height: 90
            width: 30

            anchors {
                left: parent.left
                bottom: parent.bottom
                bottomMargin: 30
                leftMargin: 200
            }

            onSliderValueChanged: {
                temperatureIndicator.input = sliderValue

                var simulatedTemperatureValue = SimUtils.map(sliderValue, 0, 100, 0, 130)

                //gpiosController.setMsgPayload(2, simulatedTemperatureValue)
                //gpiosController.writeCANMsg(5, 8)
            }
        }

        ControlSlider {
            id: fuelControl

            width: 30
            height: 90

            anchors {
                right: parent.right
                bottom: parent.bottom
                bottomMargin: 30
                rightMargin: 200
            }

            onSliderValueChanged: {
                fuelIndicator.input = sliderValue

                var simulatedFuelValue = SimUtils.map(sliderValue, 0, 100, 0, 40)

                //gpiosController.writeCANMsg(5, 8)
                //gpiosController.setMsgPayload(3, simulatedFuelValue)
            }
        }
    }


    Rectangle {
        width: 60
        height: 30
        border.color: "#717171"
        visible: menu.width === 0
        anchors {
            left: parent.left
            top: parent.top
            leftMargin: 5
            topMargin: 5
        }

        Text {
            anchors.centerIn: parent
            text: qsTr("Menu")
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            color: "red"
        }

        MouseArea {
            anchors.fill: parent
            onClicked: menu.width = 200
        }
    }

    MouseArea {
        anchors.fill: parent
        enabled: menu.width !== 0

        onClicked: menu.closeDrawer()
    }

    Drawer {
        id: menu
        width: 0
        height: parent.height
        anchors.left: parent.left
        menuTitle: "Modo de funcionamiento"
        controlsEnabled: datapool.operationMode === datapool._GeneratorMode

        Behavior on width { NumberAnimation { duration: 200 } }

        onGeneratorMode: datapool.operationMode = datapool._GeneratorMode
        onReceiverMode: datapool.operationMode = datapool._ReceiverMode
        onTurnLeft: turnLights.leftSequence = !turnLights.leftSequence
        onTurnRight: turnLights.rightSequence = !turnLights.rightSequence
        onEmergencyLights:turnLights.emergencySequence = !turnLights.emergencySequence

        onCheckEngine: rtts.checkEngine = !rtts.checkEngine
        onLowBeam: rtts.lowBeams = !rtts.lowBeams
        onHighBeams: rtts.highBeams = !rtts.highBeams
        onSeatBelt: rtts.seatBelts = !rtts.seatBelts

        onCloseDrawer: width = 0
    }
}
