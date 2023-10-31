import cv2
import cv2.aruco as aruco
import time

# Create a VideoCapture object to capture video from your camera (0 is typically the built-in camera)
cap = cv2.VideoCapture(0)

# Define the ArUco dictionary and parameters
aruco_dict = aruco.getPredefinedDictionary(aruco.DICT_4X4_50)
parameters = aruco.DetectorParameters()

while True:
    ret, frame = cap.read()

    if not ret:
        break

    # Detect markers in the frame
    corners, ids, rejectedImgPoints = aruco.detectMarkers(frame, aruco_dict, parameters=parameters)

    if ids is not None:
        # Print positional data for each detected marker
        for i in range(len(ids)):
            marker_id = ids[i][0]
            marker_corners = corners[i][0]

            # Calculate marker position and orientation
            rvec, tvec, _ = aruco.estimatePoseSingleMarkers(marker_corners, 0.05, cameraMatrix, distCoeffs)

            # Print positional data
            print(f"Marker ID {marker_id}:")
            print(f"Translation Vector (x, y, z): {tvec}")
            print(f"Rotation Vector (rX, rY, rZ): {rvec}")

    # Display the frame
    cv2.imshow('ArUco Marker Detection', frame)

    if cv2.waitKey(1000) & 0xFF == 27:  # Break the loop if the 'Esc' key is pressed
        break

cap.release()
cv2.destroyAllWindows()
