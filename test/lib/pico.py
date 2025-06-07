import os
import picod
from robot.api.deco import keyword, library

@library(scope='GLOBAL')
class TestBoard:

    def __init__(self, pico_port: str = os.getenv("PICO_PORT")):
        self.pico_port = pico_port
        self.pico = picod.pico(device=self.pico_port)

    @keyword
    def set_gpio_as_output(self, gpio_pin: str, state: str):
        self.pico.gpio_set_output(gpio=int(gpio_pin), level=int(state))

    @keyword
    def set_gpio_state(self, gpio_pin: str, state: str):
        self.pico.gpio_write(gpio=int(gpio_pin), level=int(state))

    def __del__(self):
        if self.pico.connected:
            self.pico.close()
