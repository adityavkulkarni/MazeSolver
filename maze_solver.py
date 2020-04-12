#!/usr/bin/python3

import cv2
import numpy as np
import matplotlib.pyplot as plt

import sys
if(len(sys.argv)==2):
	path = str(sys.argv[1])
else:
	path = input('Enter path of image: ')
img = cv2.imread(path)
img_out = img
img = cv2.bitwise_not(img)

imgray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
ret,thresh = cv2.threshold(imgray,127,255,0)

contours, hierarchy = cv2.findContours(thresh,cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_NONE)

img1 = cv2.bitwise_and(img,0)

img = cv2.drawContours(img1, contours, 0, (255,255,255), 1)

kernel = np.ones((21,21),np.uint8)
dilation = cv2.dilate(img,kernel,iterations = 1)
erosion = cv2.erode(dilation,kernel,iterations = 1)


op = dilation - erosion

imgray1 = cv2.cvtColor(op,cv2.COLOR_BGR2GRAY)
ret,thresh1 = cv2.threshold(imgray1,127,255,0)
contours1, hierarchy = cv2.findContours(thresh1,cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_NONE)

cv2.drawContours(img_out, contours1, -1, (0,0,255), 1)
cv2.fillPoly(img_out, pts =contours1, color=(0,0,255))

plt.imshow(img_out)
plt.show()

choice = input('Do you want to save the result(Yes/No)?')
if choice in ['yes','Yes','y']:
	cv2.imwrite('output.jpg',img_out)
	print('Image is stored as "output.jpg" in current directory')



