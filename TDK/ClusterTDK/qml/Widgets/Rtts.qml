import QtQuick 2.0

Item {

    property bool checkEngine
    property bool lowBeams
    property bool highBeams
    property bool seatBelts

    ListModel {
        id: rtts

        ListElement {
            url: ""
            xPosition: 5
            yPosition: 5
        }
        ListElement {
            url: ""
            xPosition: 50
            yPosition: 5
        }
        ListElement {
            url: ""
            xPosition: 95
            yPosition: 5
        }
        ListElement {
            url: ""
            xPosition: 50
            yPosition: 60
        }
    }

    onCheckEngineChanged: {
        if (checkEngine)
            rtts.setProperty(0, "url", "qrc:/images/check.png")
        else
            rtts.setProperty(0, "url", "")
    }

    onLowBeamsChanged: {
        if (lowBeams)
                rtts.setProperty(1, "url", "qrc:/images/lowBeams.png")
        else
            rtts.setProperty(1, "url", "")
    }

    onHighBeamsChanged: {
        if (highBeams)
            rtts.setProperty(2, "url", "qrc:/images/highBeams.png")
        else
            rtts.setProperty(2, "url", "")
    }

    onSeatBeltsChanged: {
        if (seatBelts)
            rtts.setProperty(3, "url", "qrc:/images/seatbelt.png")
        else
            rtts.setProperty(3, "url", "")
    }

    Rectangle {
        anchors.fill: parent
        color: "black"
    }

    Repeater {
        model: rtts

        delegate: Image {
            height: 40
            width: 40
            x: xPosition
            y: yPosition
            source: url
            fillMode: Image.Stretch
        }
    }
}
