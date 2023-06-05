import numpy as np
import cv2
# load data
y_test = np.load("y_test.npy")
# show image
cv2.imshow("Image", y_test[10001])
cv2.waitKey (0)
cv2.destroyAllWindows()
