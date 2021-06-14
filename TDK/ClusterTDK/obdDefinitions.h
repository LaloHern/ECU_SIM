#ifndef OBDDEFINITIONS_H
#define OBDDEFINITIONS_H

#define OBD_QUERY_ID 0x7DF
#define OBD_REPLY_ID 0x7E8

#define MODE_1_00_SUPPORTED_PIDS {0x06, 0x41, 0x00, 0x88, 0x1F, 0x00, 0x00, 0x00}
#define MODE_2_20_SUPPORTED_PIDS {0x06, 0x41, 0x20, 0x02, 0x00, 0x00, 0x00, 0x00}

enum OBDMode {
    RealTime = 0x01,
    FreezeData,
    DTC,
    EraseDTC,
    VehicleInfo = 0x09
};

enum OBDRplyMode {
    RealTimeRply = 0x41,
    FreezeDataRply,
    DTCRply,
    EraseDTCRply,
    VehicleInfoRply = 0x49
};

enum PIDS {
    FirstSupportedPIDs = 0x00,
    RPM = 0x0C,
    VehicleSpeed,
    IntakeAirTemperature = 0x0F,
    MAF = 0x10,
    SecondSUpportedPIDs = 0x20,
    FuelLevel = 0x2F,
    EngineCoolantTemperature = 0x67
};
#endif // OBDDEFINITIONS_H
