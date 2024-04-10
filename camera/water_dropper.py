import RPi.GPIO as GPIO
from time import sleep

def activate_pump():

  GPIO.setmode(GPIO.BCM)
  GPIO.setup(17, GPIO.OUT)

  counter = 0

  try:
      while counter <5:
        GPIO.output(17,1)
        sleep(2)
        GPIO.output(17,0)
        sleep(2)
        counter += 1
      print("Target reached: %d" % counter)

  except KeyboardInterrupt:
    print("\n----> Keyboard Interrupt")
    
  except:
    print("----> Other error or exception occurred")

  finally:
    GPIO.cleanup()
