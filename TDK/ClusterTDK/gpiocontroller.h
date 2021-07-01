#ifndef GPIOCONTROLLER_H
#define GPIOCONTROLLER_H

#include <qobject.h>
#include <QTimer>
#include "mcp_can_rpi/mcp_can_rpi.h"
#include "obdDefinitions.h"

#include <QVariant>
#include <QThread>

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
    Q_PROPERTY(bool malfunctionIndicator READ malfunctionIndicator WRITE setMalfunctionIndicator NOTIFY malfunctionIndicatorChanged)

    Q_DISABLE_COPY(GPIOController);

public:
    GPIOController();
    ~GPIOController();
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

    void setMalfunctionIndicator(bool value);
    bool malfunctionIndicator();

    void handleOBDRequest();
    void processRealTimeDataQuery(unsigned char pid);
    void processFreezedDataQuery();
    void processDTCQuery();
    void eraseStoredDTC();
    void vehicleInfoReply();

private:
    QTimer m_pollTimer;
    MCP_CAN can;

    int m_speed;
    int m_engineRpm;
    int m_engineTemp;
    int m_fuelLevel;
    int m_intakeAirTemp;
    int m_mafAirFloRate;

    bool m_malfunctionIndicator;

    bool m_rightTurnLight;
    bool m_leftTurnLight;    
    unsigned char m_obdMode;
    unsigned char m_obdPID;

    //thread class used to separate the CAN bus write process
    //from the main program thread
    class WriteCANThread: public QThread
    {
    public:
        WriteCANThread(GPIOController *parent = 0);

    protected:
        void run();

    private:
        GPIOController *m_parent;

        friend class GPIOController;
    };

    WriteCANThread m_writeCANThread;

signals:
    void speedChanged();
    void engineRpmChanged();
    void engineTempChanged();
    void fuelLevelChanged();
    void leftTurnLightChanged();
    void rightTurnLightChanged();
    void malfunctionIndicatorChanged();

public slots:
    void pollLoop();
};

#endif // GPIOCONTROLLER_H

