import csv
import os
import time
from datetime import datetime

import serial
import serial.tools.list_ports

from config import *

# ------------------------------------------------
# Auto Detect ESP32
# ------------------------------------------------

def find_port():

    if COM_PORT is not None:
        return COM_PORT

    ports = serial.tools.list_ports.comports()

    for port in ports:

        if "Bluetooth" in port.description:
            continue

        return port.device

    return None


# ------------------------------------------------
# Main
# ------------------------------------------------

print("=" * 60)
print("           AI WEARABLE DATA LOGGER")
print("=" * 60)

port = find_port()

if port is None:
    print("No Serial Port Found")
    exit()

print("Connected :", port)

ser = serial.Serial(port, BAUDRATE, timeout=1)

time.sleep(2)

os.makedirs(DATASET_FOLDER, exist_ok=True)

filename = datetime.now().strftime(
    "wearable_%Y%m%d_%H%M%S.csv"
)

filepath = os.path.join(DATASET_FOLDER, filename)

print()
print("Saving CSV To :")
print(filepath)
print()

csvfile = open(filepath, "w", newline="")

writer = csv.writer(csvfile)

header_saved = False
rows = 0

start_time = time.time()
lastDisplay = 0

print("Recording...")
print("Press CTRL+C to Stop")
print()

try:

    while True:

        line = ser.readline().decode(
            "utf-8",
            errors="ignore"
        ).strip()

        if line == "":
            continue

        data = line.split(",")

        if len(data) != 13:
            continue

        writer.writerow(data)
        csvfile.flush()

        rows += 1

        # -----------------------------------------
        # Live Dashboard (updates every second)
        # -----------------------------------------

        if time.time() - lastDisplay >= 1:

            lastDisplay = time.time()

            elapsed = int(time.time() - start_time)

            minutes = elapsed // 60
            seconds = elapsed % 60

            samplingRate = rows / max(elapsed, 1)

            os.system("cls")

            print("=" * 60)
            print("           AI WEARABLE DATA LOGGER")
            print("=" * 60)
            print()

            print("Status           : Recording")
            print()

            print(f"COM Port         : {port}")
            print()

            print(f"Current File     : {filename}")
            print()

            print(
                f"Elapsed Time     : {minutes:02d}:{seconds:02d}"
            )

            print()

            print(f"Rows Recorded    : {rows}")

            print()

            print(
                f"Sampling Rate    : {samplingRate:.2f} Hz"
            )

            print()

            print("=" * 60)

except KeyboardInterrupt:

    print()
    print("Stopping Recording...")

finally:

    csvfile.close()
    ser.close()

    elapsed = int(time.time() - start_time)

    print()
    print("=" * 60)
    print("Recording Complete")
    print("=" * 60)

    print(f"Samples Recorded : {rows}")

    print(f"Recording Time   : {elapsed} sec")

    print(f"Average Rate     : {rows/max(elapsed,1):.2f} Hz")

    print()

    print("Saved File")

    print(filepath)

    print("=" * 60)