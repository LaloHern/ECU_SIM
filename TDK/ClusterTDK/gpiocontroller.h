#ifndef GPIOCONTROLLER_H
#define GPIOCONTROLLER_H

#include <qobject.h>
#include <QTimer>
#include "mcp_can_rpi/mcp_can_rpi.h"
#include "obdDefinitions.h"

#include <QVariant>

class GPIOController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(INT8U m_canMsgId READ canMsg)

    //properties for CAN signals
    Q_PROPERTY(int speed READ speed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(int engineRpm READ engineRpm WRITE setEngineRpm NOTIFY engineRpmChanged)
    Q_PROPERTY(int engineTemp READ engineTemp WRITE setEngineTemp NOTIFY engineTempChanged)
    Q_PROPERTY(int fuelLevel READ fuelLevel WRITE setFuelLevel NOTIFY fuelLevelChanged)
    Q_PROPERTY(bool leftTurnLight READ leftTurnLight WRITE setLeftTurnLight NOTIFY leftTurnLightChanged)
    Q_PROPERTY(bool rightTurnLight READ rightTurnLight WRITE setRightTurnLight NOTIFY rightTurnLightChanged)

    Q_DISABLE_COPY(GPIOController);

public:
    GPIOController();
    INT32U m_canMsgId;
    INT8U m_canMsgDLC;
    INT8U m_canMsgData[MAX_CHAR_IN_MESSAGE];

    INT8U *datapayload = &m_canMsgData[0];

    Q_INVOKABLE INT8U canMsg();
    Q_INVOKABLE void writeCANMsg(INT32U id, INT8U len);
    Q_INVOKABLE void setMsgPayload(int, int);

    int speed();
    int engineRpm();
    int engineTemp();
    int fuelLevel();
    bool leftTurnLight();
    bool rightTurnLight();

    void setSpeed (int value);
    void setEngineRpm (int value);
    void setEngineTemp (int value);
    void setFuelLevel (int value);
    void setLeftTurnLight (bool value);
    void setRightTurnLight (bool value);

private:
    QTimer m_pollTimer;
    MCP_CAN can;

    INT8U m_canMsg;

    int m_speed;
    int m_engineRpm;
    int m_engineTemp;
    int m_fuelLevel;
    int m_intakeAirTemp;
    int m_mafAirFloRate;

    bool m_rightTurnLight;
    bool m_leftTurnLight;

    char m_vehVIN[18] = "SCBZK25EXYC813876";

    void handleOBDRequest(INT8U *messageData);
    void processRealTimeDataQuery(INT8U pid);
    void processFreezedDataQuery();
    void processDTCQuery();
    void eraseStoredDTC();
    void vehicleInfoReply();

signals:
    void speedChanged();
    void engineRpmChanged();
    void engineTempChanged();
    void fuelLevelChanged();
    void leftTurnLightChanged();
    void rightTurnLightChanged();

public slots:
    void pollLoop();
};

#endif // GPIOCONTROLLER_H

