from time import sleep
from gpiozero import Buzzer, DigitalInputDevice
 
no_rain = DigitalInputDevice(18)

no_rain.wait_for_inactive()
print("yep")
