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
        self.ser.reset_input_buffer()
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
            else:
                time.sleep(0.01)
        return lines

    @keyword("Verify Log Contains Action")
    def verify_log_contains_action(self, logs, action):
        for log in logs:
            if log.startswith("[LOG]"):
                fields = log.replace("[LOG] ", "").split(",")
                if len(fields) >= 7 and fields[6].strip().upper() == action.upper():
                    return  # Success
        raise AssertionError(f"Nie znaleziono logu z akcją: {action}")

    @keyword("Verify Log Field Contains")
    def verify_log_field_contains(self, logs, field_name, index, expected_value):
        """
        Sprawdza, czy któryś z logów zawiera wartość `expected_value` w polu o nazwie `field_name` i indeksie `index`.
        """
        for log in logs:
            if log.startswith("[LOG]"):
                fields = log.replace("[LOG] ", "").split(",")
                if len(fields) > index and fields[index].strip() == str(expected_value):
                    print(f"[VERIFY] Znaleziono {field_name} = {expected_value} w logu: {log}")
                    return
        raise AssertionError(f"Nie znaleziono logu z {field_name} = {expected_value}")
