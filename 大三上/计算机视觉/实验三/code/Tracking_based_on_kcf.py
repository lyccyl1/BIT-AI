import cv2
import Tracker

# get video roi
cap = cv2.VideoCapture("lmz.mp4")
is_ok_begin, frame = cap.read()
if not is_ok_begin:
    print("reading error!")
    exit(-1)
roi = cv2.selectROI("tracking project lyc", frame, False, False)
tracker = Tracker.Tracker(frame,roi)
# tracking
while cap.isOpened():
    is_ok_ing, frame = cap.read()
    if not is_ok_ing:
        print("finish!")
        break
    x, y, w, h = tracker.update(frame)
    cv2.rectangle(frame, (x, y), (x + w, y + h), (255, 255, 0), 1)
    cv2.imshow('tracking', frame)
    if cv2.waitKey(1) & 0xFF == ord('l') or cv2.waitKey(1) & 0xFF == ord('y') or cv2.waitKey(1) & 0xFF == ord('c'):
        print("exit success!")
        break
cap.release()
cv2.destroyAllWindows()