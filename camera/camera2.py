from picamera2 import Picamera2, Preview
from time import sleep
import cv2
import cv2.aruco as aruco

camera = Picamera2()

try:
    print(cv2.__version__)
    camera_config = camera.create_still_configuration(main={"size": (1920, 1080)},
                                                      lores={"size": (640, 480)},
                                                      display="lores")
    camera.configure(camera_config)
    camera.start_preview(Preview.QTGL)
    camera.start()
    #camera.start_preview(Prewview.QTGL)

    sleep(5)
    image = camera.capture_array()
    print("took picture")
    #cv2.imshow('Captured Image', image)
    
    try:
        dictionary = aruco.getPredefinedDictionary(aruco.DICT_6X6_1000)
        #parameters = aruco.DetectorParameters()
        corners, ids, rejectedImgPoints = aruco.detectMarkers(image, dictionary)
    except:
        print("this line sucks")
    
    if corners is not None:
        print("YAY")
    else:
        print("RIP")
    
    camera.stop_preview()
    print("C")

except KeyboardInterrupt:
    print("Keyboard Interrupt")
except:
    print("error/exception other than Keyboard Interrupt")
finally:
    camera.stop()
    print("-->End")

