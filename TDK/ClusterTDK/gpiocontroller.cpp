#include "gpiocontroller.h"
#include <wiringPi/wiringPi.h>
#include <wiringPi/wiringPiSPI.h>
#include <QDebug>
#include <QString>

GPIOController::GPIOController():
    m_pollTimer(this),
    can(0, 500000, 6),
    m_canMsgId(0),
    m_canMsgDLC(0),
    m_engineRpm(1000),
    m_engineTemp(95),
    m_fuelLevel(100),
    m_intakeAirTemp(90),
    m_mafAirFloRate(900),
    m_malfunctionIndicator(false),
    m_writeCANThread(this)
{
    //*class instance of MCP CAN*//
    //initializing SPI parameters
    // SPI0
    // baudrate 500 kbit/s
    // interrupt pin 25 (BCM 6)
    wiringPiSetup();
    can.setupSpi();
    can.setupInterruptGpio();
    can.begin(MCP_NORMAL, CAN_500KBPS, MCP_8MHZ);
    can.setMode(MCP_NORMAL);

    m_writeCANThread.start(QThread::TimeCriticalPriority);
}

GPIOController::~GPIOController()
{
    m_writeCANThread.requestInterruption();
}

void GPIOController::pollLoop() {
    can.readMsgBuf(&m_canMsgId, &m_canMsgDLC, m_canMsgData);

    if (m_canMsgId == OBD_QUERY_ID) {
        m_obdMode = m_canMsgData[1];
        m_obdPID = m_canMsgData[2];
        handleOBDRequest();
        //clean received message id buffer after processing it to avoid
        //re-entering this condition if no OBD message is received
        m_canMsgId = 0x00;
    }
}

INT8U GPIOController::canMsg() {
    return m_canMsgData[0];
}

void GPIOController::writeCANMsg(INT32U id, INT8U len) {
    can.sendMsgBuf(id, len, m_canMsgData);
}

void GPIOController::setMsgPayload(int index, int dataBite) {
    m_canMsgData[index] = dataBite;
}

void GPIOController::setSpeed (int value) {
    if (m_speed != value) {
        m_speed = value;
        emit speedChanged();
    }
}

void GPIOController::setEngineRpm (int value) {
    if (m_engineRpm != value) {
        m_engineRpm = value;
        emit engineRpmChanged();
    }
}

void GPIOController::setEngineTemp (int value) {
    if (m_engineTemp != value) {
        m_engineTemp = value;
        emit engineTempChanged();
    }
}

void GPIOController::setFuelLevel (int value) {
    if (m_fuelLevel != value) {
        m_fuelLevel = value;
        emit fuelLevelChanged();
    }
}

void GPIOController::setLeftTurnLight (bool value) {
    if (m_rightTurnLight != value) {
        m_rightTurnLight = value;
        emit leftTurnLightChanged();
    }
}

void GPIOController::setRightTurnLight (bool value) {
    if (m_leftTurnLight != value) {
        m_leftTurnLight = value;
        emit rightTurnLightChanged();
    }
}

int GPIOController::speed() {
    return m_speed;
}

int GPIOController::engineRpm() {
    return m_engineRpm;
}

int GPIOController::engineTemp() {
    return m_engineTemp;
}

int GPIOController::fuelLevel() {
    return m_fuelLevel;
}

bool GPIOController::leftTurnLight() {
    return m_leftTurnLight;
}

bool GPIOController::rightTurnLight() {
    return m_rightTurnLight;
}

void GPIOController::handleOBDRequest()
{
    switch (m_obdMode)
    {
    case RealTime:
        processRealTimeDataQuery(m_obdPID);
        break;
    case DTC:
        processDTCQuery();
        break;
    case EraseDTC:
        eraseStoredDTC();
        break;
    case VehicleInfo:
        vehicleInfoReply();
        break;
    case PendingDTC:
        processDTCQuery();
        break;
    default:
        break;
    }
}

void GPIOController::processRealTimeDataQuery(INT8U pid)
{
    unsigned char messageToSend[MAX_CHAR_IN_MESSAGE] = {0x00, RealTimeRply, pid, 0x00, 0x00, 0x00, 0x00, 0x00};

    if (pid == FirstSupportedPIDs) {
        unsigned char msgToSendOne[8] = {0x06, 0x41, 0x00, 0x88, 0x1F, 0x00, 0x01, 0x00};
        can.sendMsgBuf(OBD_REPLY_ID, MAX_CHAR_IN_MESSAGE, msgToSendOne);
    }

    if (pid == SecondSUpportedPIDs) {
        unsigned char msgToSendTwo[8] = {0x06, 0x41, 0x20, 0x80, 0x02, 0x00, 0x00, 0x00};
        can.sendMsgBuf(OBD_REPLY_ID, MAX_CHAR_IN_MESSAGE, msgToSendTwo);
    }

    if (pid == 28)
    {
        unsigned char obd_Std_Msg[8] = {4, 65, 0x1C, 0x0A};
        can.sendMsgBuf(OBD_REPLY_ID, MAX_CHAR_IN_MESSAGE, obd_Std_Msg);
    }

    if (pid == FuelLevel) {
        messageToSend[0] = 3;
        messageToSend[3] = 100 * m_fuelLevel / 255;

        can.sendMsgBuf(OBD_REPLY_ID, MAX_CHAR_IN_MESSAGE, messageToSend);
    }

    if (pid == RPM) {
        unsigned int rpm_A = (long)m_engineRpm * 4 / 256;
        unsigned int rpm_B = (long)m_engineRpm * 4 % 256;

        messageToSend[0] = 4;
        messageToSend[3] = (unsigned char)rpm_A;
        messageToSend[4] = (unsigned char)rpm_B;

        can.sendMsgBuf(OBD_REPLY_ID, MAX_CHAR_IN_MESSAGE, messageToSend);
    }

    if (pid == VehicleSpeed) {
        messageToSend[0] = 3;
        messageToSend[3] = m_speed;

        can.sendMsgBuf(OBD_REPLY_ID, MAX_CHAR_IN_MESSAGE, messageToSend);
    }

    if (pid == IntakeAirTemperature) {
        messageToSend[0] = 3;
        messageToSend[3] = m_intakeAirTemp + 40;

        can.sendMsgBuf(OBD_REPLY_ID, MAX_CHAR_IN_MESSAGE, messageToSend);
    }

    if (pid == MAF) {
        messageToSend[0] = 4;
        messageToSend[3] = (long)m_mafAirFloRate / 255;
        messageToSend[4] = (long)m_mafAirFloRate;

        can.sendMsgBuf(OBD_REPLY_ID, MAX_CHAR_IN_MESSAGE, messageToSend);
    }

    if (pid == EngineCoolantTemperature) {
        messageToSend[0] = 3;
        messageToSend[3] = m_engineTemp + 40;

        can.sendMsgBuf(OBD_REPLY_ID, MAX_CHAR_IN_MESSAGE, messageToSend);
    }
}

void GPIOController::eraseStoredDTC()
{
    setMalfunctionIndicator(false);
}

void GPIOController::processDTCQuery()
{
    //simulated DTCs:
    //P0261 ----> Cylinder 1 injector circuit low voltage
    //P0700 ----> Transmission Control System Malfunction
    unsigned char DTC[] = {6, DTCRply, 0x02, 0x02, 0x61, 0x07, 0x00, 0};

    if (m_malfunctionIndicator)
        can.sendMsgBuf(OBD_REPLY_ID, MAX_CHAR_IN_MESSAGE, DTC);
}

void GPIOController::vehicleInfoReply()
{
    unsigned char vinStr[18] = "SCBZK25EXYC813876";
    unsigned char calibration_ID[18] = "FW00116MHZ1111111";

    if (m_canMsgData[2] == 0)
    {
        unsigned char msgToSendNine[8] = {0x06, 0x49, 0x00, 0x28, 0x28, 0x00, 0x00, 0x00};

        can.sendMsgBuf(OBD_REPLY_ID, MAX_CHAR_IN_MESSAGE, msgToSendNine);
    }

    if (m_canMsgData[2] == 2)
    {
        unsigned char frame1[8] = {16, 20, 73, 2, 1, vinStr[0], vinStr[1], vinStr[2]};
        unsigned char frame2[8] = {33, vinStr[3], vinStr[4], vinStr[5], vinStr[6], vinStr[7], vinStr[8], vinStr[9]};
        unsigned char frame3[8] = {34, vinStr[10], vinStr[11], vinStr[12], vinStr[13], vinStr[14], vinStr[15], vinStr[16]};

        can.sendMsgBuf(OBD_REPLY_ID, MAX_CHAR_IN_MESSAGE, frame1);
        can.sendMsgBuf(OBD_REPLY_ID, MAX_CHAR_IN_MESSAGE, frame2);
        can.sendMsgBuf(OBD_REPLY_ID, MAX_CHAR_IN_MESSAGE, frame3);
    }
    else if (m_canMsgData[2] == 4)
    {
        unsigned char frame1[8] = {16, 20, 73, 4, 1, calibration_ID[0], calibration_ID[1], calibration_ID[2]};
        unsigned char frame2[8] = {33, calibration_ID[3], calibration_ID[4], calibration_ID[5], calibration_ID[6], calibration_ID[7], calibration_ID[8], calibration_ID[9]};
        unsigned char frame3[8] = {34, calibration_ID[10], calibration_ID[11], calibration_ID[12], calibration_ID[13], calibration_ID[14], calibration_ID[15], calibration_ID[16]};

        can.sendMsgBuf(OBD_REPLY_ID, MAX_CHAR_IN_MESSAGE, frame1);
        can.sendMsgBuf(OBD_REPLY_ID, MAX_CHAR_IN_MESSAGE, frame2);
        can.sendMsgBuf(OBD_REPLY_ID, MAX_CHAR_IN_MESSAGE, frame3);
    }
}

GPIOController::WriteCANThread::WriteCANThread(GPIOController *parent) :
    m_parent(parent)
{
}

void GPIOController::WriteCANThread::run()
{
    while(!isInterruptionRequested())
    {
        m_parent->pollLoop();
        msleep(30);
    }
}

bool GPIOController::malfunctionIndicator() {
    return m_malfunctionIndicator;
}

void GPIOController::setMalfunctionIndicator(bool value) {
    if (m_malfunctionIndicator != value) {
        m_malfunctionIndicator = value;
        emit malfunctionIndicatorChanged();
    }
}
