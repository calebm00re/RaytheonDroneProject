from time import sleep
from gpiozero import Buzzer, DigitalInputDevice

no_rain = DigitalInputDevice(18) # water sensor at pin 18

buzzer = Buzzer(2) # buzzer on pin 2

while no_rain.is_active:
        print("nope")
buzzer.on()
print("water sensed")
sleep(1)
buzzer.off()
