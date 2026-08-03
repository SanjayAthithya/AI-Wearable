#include "comm.h"
#include "comm_config.h"

#ifdef COMM_SERIAL
#include "serial_stream.h"
#endif

#ifdef COMM_WIFI
#include "wifi_stream.h"
#endif

//--------------------------------------------------
// Initialize Communication
//--------------------------------------------------

bool commBegin()
{
#ifdef COMM_SERIAL
    return serialBegin(115200);
#endif

#ifdef COMM_WIFI
    return wifiBegin();
#endif
}

//--------------------------------------------------
// Send Data
//--------------------------------------------------

void commSend(const String &data)
{
#ifdef COMM_SERIAL
    serialSend(data);
#endif

#ifdef COMM_WIFI
    wifiSend(data);
#endif
}

//--------------------------------------------------
// Connection Status
//--------------------------------------------------

bool commConnected()
{
#ifdef COMM_SERIAL
    return serialConnected();
#endif

#ifdef COMM_WIFI
    return wifiConnected();
#endif
}