#include "csv_logger.h"

#include "imu.h"
#include "hr_module.h"
#include "comm.h"

//--------------------------------------------------
// CSV Transmission Rate
//--------------------------------------------------

#define CSV_SEND_INTERVAL 50    // 50 ms = 20 Hz

//--------------------------------------------------
// CSV Header
//--------------------------------------------------

void csvPrintHeader()
{
    commSend(
        "Time,IR,RED,Finger,"
        "AccX,AccY,AccZ,"
        "GyroX,GyroY,GyroZ,"
        "Temp");
}

//--------------------------------------------------
// Send CSV
//--------------------------------------------------

void csvLog()
{
    static unsigned long lastSend = 0;

    if (millis() - lastSend >= CSV_SEND_INTERVAL)
    {
        lastSend = millis();

        commSend(csvGetLine());
    }
}

//--------------------------------------------------
// Create CSV Line
//--------------------------------------------------

String csvGetLine()
{
    IMUData imu = getIMUData();

    String csv = "";

    csv += String(millis());
    csv += ",";

    csv += String(getIRValue());
    csv += ",";

    csv += String(getRedValue());
    csv += ",";

    csv += String(fingerDetected());
    csv += ",";

    csv += String(imu.accX, 4);
    csv += ",";

    csv += String(imu.accY, 4);
    csv += ",";

    csv += String(imu.accZ, 4);
    csv += ",";

    csv += String(imu.gyroX, 4);
    csv += ",";

    csv += String(imu.gyroY, 4);
    csv += ",";

    csv += String(imu.gyroZ, 4);
    csv += ",";

    csv += String(imu.temperature, 2);

    return csv;
}