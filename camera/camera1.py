from picamera2 import Picamera2, Preview
from time import sleep
import cv2

camera = Picamera2()

try:
  camera_config = camera.create_still_configuration(main = {"size": (1920, 1080)},
                                                    lores = {"size": (640, 480)}, 
                                                    display = "lores")

  camera.configure(camera_config)
  camera.start_preview(Previw.QTGL)
  camera.start()

  sleep(10)
  camera.capture_array()
  print("took picture")
  camera.stop_preview()

except KeyboardInterrupt:
  print("Keyboard Interrupt")
except:
  print("error/exception other than Keyboard Interrupt")
finally:
  camera.stop()
  print("end!")
