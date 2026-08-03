import serial
import serial.tools.list_ports

from config import *


# ==================================================
# Auto Detect ESP32
# ==================================================

def find_serial_port():

    if COM_PORT is not None:
        return COM_PORT

    ports = serial.tools.list_ports.comports()

    for port in ports:
        return port.device

    return None


# ==================================================
# Open Serial Connection
# ==================================================

def open_serial():

    port = find_serial_port()

    if port is None:
        raise Exception("No Serial Device Found")

    print(f"Connected : {port}")

    ser = serial.Serial(
        port,
        BAUDRATE,
        timeout=TIMEOUT
    )

    return ser


# ==================================================
# Read One Line
# ==================================================

def read_line(ser):

    try:

        line = ser.readline().decode(
            "utf-8",
            errors="ignore"
        ).strip()

        return line

    except:

        return ""