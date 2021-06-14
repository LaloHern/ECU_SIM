import QtQuick 2.0

Row {
    property bool leftSequence
    property bool rightSequence
    property bool emergencySequence

    property bool turnLeft
    property bool turnRight

    spacing: 50

    Image {
        id: leftArrow
        height: 50
        width: 50
        source: turnLeft ? "qrc:/images/leftArrow.png" : ""
    }

    Image {
        id: rightArrow
        height: 50
        width: 50
        source: turnRight ? "qrc:/images/rightArrow.png" : ""
    }

    Timer {
        id: onTimer
        interval: 600

        onTriggered: {
            if (leftSequence) {
                turnLeft = true
            } else if (rightSequence) {
                turnRight = true
            } else if (emergencySequence) {
                turnLeft = true
                turnRight = true
            }

            offTimer.restart()
        }
    }

    Timer {
        id: offTimer
        interval: 600

        onTriggered: {
            if (leftSequence) {
                turnLeft = false
            } else if (rightSequence) {
                turnRight = false
            } else if (emergencySequence) {
                turnLeft = false
                turnRight = false
            }

            onTimer.restart()
        }
    }

    onLeftSequenceChanged: {
        if (leftSequence) {
            if (rightSequence)
                rightSequence = false
            turnLeft = true
            offTimer.restart()
        } else {
            turnLeft = false
        }
    }

    onRightSequenceChanged: {
        if (rightSequence) {
            if (leftSequence)
                leftSequence = false
            turnRight = true
            offTimer.restart()
        } else {
            turnRight = false
        }
    }

    onEmergencySequenceChanged: {
        if (emergencySequence) {
            rightSequence = false
            leftSequence = false
            turnLeft = true
            turnRight = true
            offTimer.restart()
        } else {
            turnLeft = false
            turnRight = false
        }
    }

    onTurnLeftChanged: {
        if(turnLeft) {
            gpiosController.setMsgPayload(4, 1)
            gpiosController.writeCANMsg(5, 8)
        } else {
            gpiosController.setMsgPayload(4, 0)
            gpiosController.writeCANMsg(5, 8)
        }
    }

    onTurnRightChanged: {
        if(turnLeft) {
            gpiosController.setMsgPayload(5, 1)
            gpiosController.writeCANMsg(5, 8)
        } else {
            gpiosController.setMsgPayload(5, 0)
            gpiosController.writeCANMsg(5, 8)
        }
    }
}
