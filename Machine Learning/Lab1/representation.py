import cv2

def getFilesList():
    files = open("digits/files.txt", "r")
    filesNormalized = []

    for file in files:
        fileName = file.split('/')[1].split(' ')[0]
        label = file.split('/')[1].split(' ')[1][:-1]
        filesNormalized.append((fileName, label))
    
    return filesNormalized



if __name__ == '__main__':
    representation = []
    files = getFilesList()

    for file in files:

    
    