from config import MODE

if MODE == "SERIAL":

    import serial_logger

elif MODE == "WIFI":

    from wifi_logger import WiFiLogger

    logger = WiFiLogger()

    logger.connect()

    logger.start()

else:

    print("Invalid MODE selected.")