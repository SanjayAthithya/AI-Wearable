import socket
import time

from config import *
from csv_writer import CSVWriter


class WiFiLogger:

    def __init__(self):

        self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

        self.server.bind((HOST, PORT))

        self.server.listen(1)

        print("=" * 60)
        print("        AI WEARABLE WIFI LOGGER")
        print("=" * 60)
        print()

        print(f"Listening on {HOST}:{PORT}")
        print()

        self.conn = None
        self.addr = None

        self.writer = CSVWriter()

        self.rows = 0

    # ==============================================
    # Wait for ESP32
    # ==============================================

    def connect(self):

        self.conn, self.addr = self.server.accept()

        print("ESP32 Connected")
        print("IP :", self.addr[0])
        print()

    # ==============================================
    # Record Data
    # ==============================================

    def start(self):

        header_written = False

        buffer = ""

        start_time = time.time()
        lastDisplay = 0

        try:

            while True:

                data = self.conn.recv(BUFFER_SIZE)

                if not data:
                    break

                buffer += data.decode(errors="ignore")

                while "\n" in buffer:

                    line, buffer = buffer.split("\n", 1)

                    line = line.strip()

                    if line == "":
                        continue

                    values = line.split(",")

                    if len(values) != 11:
                        continue

                    if not header_written:

                        self.writer.write_header([
                            "Time",
                            "IR",
                            "RED",
                            "Finger",
                            "AccX",
                            "AccY",
                            "AccZ",
                            "GyroX",
                            "GyroY",
                            "GyroZ",
                            "Temp"
                        ])

                        header_written = True

                    self.writer.write_row(values)

                    self.rows += 1

                if time.time() - lastDisplay >= 1:

                    lastDisplay = time.time()

                    elapsed = max(time.time() - start_time, 1)

                    print(
                        f"\rRows : {self.rows} | "
                        f"Rate : {self.rows/elapsed:.2f} Hz",
                        end=""
                    )

                    self.writer.flush()

        except KeyboardInterrupt:

            pass

        finally:

            print()

            self.writer.close()

            self.conn.close()

            self.server.close()

            print()
            print("=" * 60)
            print("Recording Complete")
            print("=" * 60)
            print()

            print("Samples :", self.rows)
            print()

            print("Saved To")

            print(self.writer.current_path())

            print()
            print("=" * 60)