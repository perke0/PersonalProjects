import cv2
import tkinter as tk
from tkinter  import filedialog
from keyboard import is_pressed


global videofile
videofile = ""


def Cars():
    global videofile
    if videofile == "":
        video = cv2.VideoCapture("dashcam480p.mp4")
    else:
        video = cv2.VideoCapture(f"{videofile}")
    classifier_file = "cars.xml"
    car_tracker = cv2.CascadeClassifier(classifier_file)
    while True:
        (read_successful, frame) = video.read()
        if read_successful:
            black_white = cv2.cvtColor(frame,cv2.COLOR_RGB2GRAY)
        else:
            break

        cars = car_tracker.detectMultiScale(black_white)

        for (x,y,w,h) in cars:
            cv2.rectangle(frame,(x,y),(x+w,y+h),(0,0,255),2)

        cv2.imshow("Press q to stop",frame)
        cv2.waitKey(1) 
        if is_pressed("q" or "Q"):
            break


def People():
    global videofile
    if videofile == "":
        video = cv2.VideoCapture("peopleonstreet480p.mp4")
    else:
        video = cv2.VideoCapture(f"{videofile}")
    classifier_file = "fullbody.xml"
    people_tracker = cv2.CascadeClassifier(classifier_file)
    while True:
        (read_successful, frame) = video.read()
        if read_successful:
            black_white = cv2.cvtColor(frame,cv2.COLOR_RGB2GRAY)
        else:
            break

        people = people_tracker.detectMultiScale(black_white)

        for (x,y,w,h) in people:
            cv2.rectangle(frame,(x,y),(x+w,y+h),(0,0,255),2)

        cv2.imshow("Press q to stop",frame)
        cv2.waitKey(1) 
        if is_pressed("q" or "Q"):
            break


def Both():
    global videofile
    if videofile == "":
        video = cv2.VideoCapture("bothvideo360p.mp4")
    else:
        video = cv2.VideoCapture(f"{videofile}")
    classifier_file_car = "cars.xml"
    classifier_file_person = "fullbody.xml"
    car_tracker = cv2.CascadeClassifier(classifier_file_car)
    person_tracker = cv2.CascadeClassifier(classifier_file_person)

    while True:
        (read_successful, frame) = video.read()
        if read_successful:
            black_white = cv2.cvtColor(frame,cv2.COLOR_RGB2GRAY)
        else:
            break

        car = car_tracker.detectMultiScale(black_white)
        person = person_tracker.detectMultiScale(black_white)

        for (x,y,w,h) in car:
            cv2.rectangle(frame,(x,y),(x+w,y+h),(0,0,255),2)
        for (x,y,w,h) in person:
            cv2.rectangle(frame,(x,y),(x+w,y+h),(0,255,0),2)

        cv2.imshow("Press q to stop",frame)
        cv2.waitKey(1) 
        if is_pressed("q" or "Q"):
            break

root = tk.Tk()
root.geometry("400x250")
root.title("Simple app for Car/Person detection")


def addVideo():
    filename = filedialog.askopenfilename(initialdir="/", title="Select file",
                filetypes=(("video","*.mp4"),("pictures",["*.png","*.jpg","*.jpeg"])))
    Video_label = tk.Label(root,text = f"You input Video/Picture from location {filename}")
    Video_label.pack(padx=20, pady=7)
    global videofile
    videofile = filename
    

label = tk.Label(root,text = "Input video or picture, have one video for each button by default")
label.pack(padx=20, pady=7)

buttonframe = tk.Frame(root)
buttonframe.columnconfigure(0, weight=1)

button_video=tk.Button(buttonframe,text="Select File", font=("Arial", 18), command=addVideo)
button_video.grid(row=0, column=0,sticky=tk.W + tk.E)

button_car=tk.Button(buttonframe,text="Car detection", font=("Arial", 18), command=Cars)
button_car.grid(row=1, column=0,sticky=tk.W + tk.E)

button_person=tk.Button(buttonframe,text="Person detection", font=("Arial", 18), command=People)
button_person.grid(row=2,column=0,sticky=tk.W+tk.E)

button_both=tk.Button(buttonframe,text="Both detection", font=("Arial", 18), command=Both)
button_both.grid(row=3,column=0,sticky=tk.W+tk.E)

buttonframe.pack(fill='x')
root.mainloop()