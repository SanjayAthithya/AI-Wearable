from serial_logger import *

ser = open_serial()

print("Connected Successfully")

while True:

    line = read_line(ser)

    if line != "":
        print(line)