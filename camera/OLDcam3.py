import cv2
import cv2.aruco as aruco
import numpy as np

# Load the camera parameters from the calibration process
camera_matrix = np.array([[fx, 0, cx], [0, fy, cy], [0, 0, 1]])  # Replace fx, fy, cx, cy with your values
dist_coeffs = np.array([k1, k2, p1, p2, k3])  # Replace k1, k2, p1, p2, k3 with your values

# Initialize the camera capture
cap = cv2.VideoCapture(0)  # Adjust the device number if necessary

# Define the ArUco dictionary
aruco_dict = aruco.getPredefinedDictionary(aruco.DICT_6X6_250)

while True:
    # Capture frame-by-frame
    ret, frame = cap.read()

    # Convert to grayscale
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # Detect ArUco markers
    corners, ids, rejectedImgPoints = aruco.detectMarkers(gray, aruco_dict)

    # If markers are detected
    if ids is not None:
        # Estimate pose of each marker
        rvecs, tvecs, _ = aruco.estimatePoseSingleMarkers(corners, marker_length, camera_matrix, dist_coeffs)
        for rvec, tvec in zip(rvecs, tvecs):
            # Draw the pose of the marker
            aruco.drawAxis(frame, camera_matrix, dist_coeffs, rvec, tvec, 0.1)

            # Print the translation vectors (x, y, z)
            x, y, z = tvec[0]
            print(f'ID: {ids[0]} X: {x} Y: {y} Z: {z}')

    # Display the resulting frame
    cv2.imshow('frame', frame)

    # Wait for 'q' key to stop
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()
