import cv2
import cv2.aruco as aruco
import sys
from picamera2 import Picamera2

def main():
    # Set up the video capture
    cap = Picamera2()
    cap.resolution = (1920, 1080)
    cap.start()
    # Check if the webcam is opened correctly
    #if not cap.isOpened():
    #    print("Error: Could not open video source.")
    #    sys.exit()

    # Load the predefined dictionary
    dictionary = aruco.getPredefinedDictionary(aruco.DICT_6X6_1000)
    parameters = aruco.DetectorParameters()
    detector = aruco.ArucoDetector(dictionary, parameters)
    try:
        while True:
            # Capture a frame
            origimage = cap.capture_array()
            image = cv2.cvtColor(origimage, cv2.COLOR_BGR2GRAY)
            #ret, frame = cap.capture_array()
            #if not ret:
            #    print("Error: Could not read frame.")
            #    break
            #print("yep")
            # Detect ArUco markers
            corners, ids, rejectedImgPoints = detector.detectMarkers(image)

            # If we've found markers, print their ID and position
            if ids is not None:
                for corner, id in zip(corners, ids):
                    x, y = corner[0][0]
                    print(f"ID: {id[0]}, X: {x}, Y: {y}")

            # Add a small delay for easier CPU usage
            cv2.waitKey(10)

    except KeyboardInterrupt:
        print("\nStopped by user.")
    finally:
        # Clean up
        cap.stop()

if __name__ == '__main__':
    main()

