import cv2

image = cv2.imread('img.jpg', 0)
h, w = image.shape
print (h, w)

for i in range(h):
    for j in range(w):
        if( image[i][j] > 128):
            print ('.', end='')
        else:
            print ('1', end='')
    print('\n', end='')

