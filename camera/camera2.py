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

    sleep(5)
    image = camera.capture_array("main")
    im_gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    print("took picture")
    #cv2.imshow('Captured Image', im_gray)
    
    try:
        dictionary = aruco.getPredefinedDictionary(aruco.DICT_6X6_1000)
        #parameters = aruco.DetectorParameters()
        corners, ids, rejectedImgPoints = aruco.detectMarkers(im_gray, dictionary)
        if ids is not None:
            print(len(ids), " Markers Found")
            # If we've found markers, print their ID and position
            if np.all(ids is not None):
                for i, corner in zip(ids, corners):
                    if(i == 4):
                        # friendly
                        print('IT'S ME, DON'T SHOOT')
                    else:
                        # foe
                        print('SHOOT THE ENEMY')
                        # call the water thing
                    corner = corner[0]
                    center_x = int(np.mean([c[0] for c in corner]))
                    center_y = int(np.mean([c[1] for c in corner]))
                    print(f"Marker ID: {i[0]}, Marker Center: ({center_x}, {center_y})")
        
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

