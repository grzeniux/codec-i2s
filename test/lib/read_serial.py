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
        index = int(index)
        for log in logs:
            if log.startswith("[LOG]"):
                fields = log.replace("[LOG] ", "").split(",")
                if len(fields) > index and fields[index].strip() == str(expected_value):
                    print(f"[VERIFY] Znaleziono {field_name} = {expected_value} w logu: {log}")
                    return
        raise AssertionError(f"Nie znaleziono logu z {field_name} = {expected_value}")

    @keyword("Extract Boot Millis From Lines")
    def extract_boot_millis_from_lines(self, lines):
        for line in lines:
            if "[LOG]" in line and "BOOT_COMPLETE" in line:
                try:
                    millis_part = line.split(",")[0]
                    millis = int(millis_part.replace("[LOG]", "").strip())
                    return millis
                except:
                    continue
        return "NOT_FOUND"

    @keyword("Extract Fields From Logs Matching")
    def extract_fields_from_logs_matching(self, logs, index, keyword_match):
        results = []
        for line in logs:
            if keyword_match in line:
                fields = line.split(",")
                if len(fields) > index:
                    results.append(fields[index].strip())
        return results
