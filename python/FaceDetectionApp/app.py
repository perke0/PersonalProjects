import cv2 
from random import randrange

trained_face_data = cv2.CascadeClassifier("haarcascade_frontalface_default.xml")
webcam = cv2.VideoCapture(0)

while True:
    succesful_frame_read, frame = webcam.read()
    grayscaled_img = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    face_coordinates = trained_face_data.detectMultiScale(grayscaled_img)

    for (x,y,w,h) in face_coordinates:
        cv2.rectangle(frame,(x,y),(x+w,y+h),
        (randrange(256),randrange(256),randrange(256)),2)
    
    cv2.imshow("Face Decector, click q to quit",frame)
    key = cv2.waitKey(1)

    if key == 81 or key == 113: #ascii
        break

webcam.release()
print("Code complited!")
