#include "gpiocontroller.h"
#include <wiringPi/wiringPi.h>
#include <wiringPi/wiringPiSPI.h>
#include <QDebug>

GPIOController::GPIOController():
    m_pollTimer(this), can(0, 500000, 6)
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

    m_pollTimer.setInterval(80);
    m_pollTimer.setSingleShot(false);

    //initializacition for intake air temperature
    m_intakeAirTemp = 25;

    //initialization for MAF airflow rate
    m_mafAirFloRate = 250;

    QObject::connect(&m_pollTimer, SIGNAL(timeout()), this, SLOT(pollLoop()));

    m_pollTimer.start();
}

void GPIOController::pollLoop() {
    can.readMsgBuf(&m_canMsgId, &m_canMsgDLC, m_canMsgData);

    if (m_canMsgId == OBD_QUERY_ID) {
        handleOBDRequest(m_canMsgData);
    } else {
        setSpeed(m_canMsgData[0]);
        setEngineRpm(m_canMsgData[1]);
        setEngineTemp(m_canMsgData[2]);
        setFuelLevel(m_canMsgData[3]);
        setLeftTurnLight(m_canMsgData[4]);
        setRightTurnLight(m_canMsgData[5]);
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

//determina el modo de OBD en que se hizo la peticion
void GPIOController::handleOBDRequest(int *messageData)
{
    switch (messageData[1])
    {
    case RealTime:
        processRealTimeDataQuery(messageData[2]);
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
    }
}

void GPIOController::processRealTimeDataQuery(INT8U pid)
{
    int messageToSend[MAX_CHAR_IN_MESSAGE] = {0x00, RealTimeRply, pid, 0x00, 0x00, 0x00, 0x00, 0x00};

    if (pid == FirstSupportedPIDs) {
        //can.sendMsgBuf(OBD_REPLY_ID, MAX_CHAR_IN_MESSAGE, MODE_1_00_SUPPORTED_PIDS);
    }
    else if (pid == SecondSUpportedPIDs) {
        //can.sendMsgBuf(OBD_REPLY_ID, MAX_CHAR_IN_MESSAGE, MODE_2_20_SUPPORTED_PIDS);
    }
    else {
        if (pid == FuelLevel) {
            float fuelValue = 100 * (m_fuelLevel / 255);

            messageToSend[0] = 3;
            messageToSend[3] = fuelValue;
        }

        if (pid == RPM) {
            float rpm_Val = m_engineRpm * 4;
            unsigned int rpm_A = (long)rpm_Val / 256;
            unsigned int rpm_B = (long)rpm_Val % 256;

            messageToSend[0] = 4;
            messageToSend[3] = (int)rpm_A;
            messageToSend[4] = (int)rpm_B;
        }

        if (pid == VehicleSpeed) {
            messageToSend[0] = 3;
            messageToSend[3] = m_speed;
        }

        if (pid == IntakeAirTemperature) {
            messageToSend[0] = 3;
            messageToSend[3] = m_intakeAirTemp + 40;
        }

        if (pid == MAF) {
            unsigned int mafValuePartA = (long)m_mafAirFloRate / 256;
            unsigned int mafValuePartB = (long)m_mafAirFloRate;

            messageToSend[0] = 4;
            messageToSend[3] = mafValuePartA;
            messageToSend[4] = mafValuePartB;
        }

        can.sendMsgBuf(OBD_REPLY_ID, MAX_CHAR_IN_MESSAGE, messageToSend);
    }
}

void GPIOController::eraseStoredDTC()
{

}

void GPIOController::processDTCQuery()
{

}

void GPIOController::vehicleInfoReply()
{
    int frame1[8] = {16, 20, 73, 2, 1, (int)m_vehVIN[0], (int)m_vehVIN[1], (int)m_vehVIN[2]};
    int frame2[8] = {33, (int)m_vehVIN[3], (int)m_vehVIN[4], (int)m_vehVIN[5], (int)m_vehVIN[6], (int)m_vehVIN[7], (int)m_vehVIN[8], (int)m_vehVIN[9]};
    int frame3[8] = {34, (int)m_vehVIN[10], (int)m_vehVIN[11], (int)m_vehVIN[12], (int)m_vehVIN[13], (int)m_vehVIN[14], (int)m_vehVIN[15], (int)m_vehVIN[16]};

    can.sendMsgBuf(OBD_REPLY_ID, 0, 8, frame1);
    can.sendMsgBuf(OBD_REPLY_ID, 0, 8, frame2);
    can.sendMsgBuf(OBD_REPLY_ID, 0, 8, frame3);
}
