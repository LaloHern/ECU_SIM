import QtQuick 2.0

Item {
    property int operationMode
    //enums for module operation mode
    readonly property int _GeneratorMode: 0
    readonly property int _ReceiverMode: 1

    enum Modes{
        OBDGenerator = 0,
        NormalCAN
    }
}
