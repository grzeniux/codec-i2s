import serial
import time
from robot.api.deco import keyword, library

@library(scope='GLOBAL')
class SerialReaderLibrary:
    def __init__(self):
        self.ser = None

    @keyword("Open Serial Port")
    def open_serial_port(self, port='COM4', baudrate=115200, timeout=1):
        self.ser = serial.Serial(port, baudrate, timeout=timeout)
        print(f"[SerialReader] Opened {port} at {baudrate} baud")

    @keyword("Close Serial Port")
    def close_serial_port(self):
        if self.ser and self.ser.is_open:
            self.ser.close()
            print("[SerialReader] Serial connection closed")

    @keyword("Read From Serial")
    def read_from_serial(self, duration=5):
        end_time = time.time() + duration
        lines = []
        while time.time() < end_time:
            if self.ser.in_waiting:
                line = self.ser.readline().decode('utf-8', errors='ignore').strip()
                if line:
                    print(f"[SERIAL] {line}")
                    lines.append(line)
        return lines
