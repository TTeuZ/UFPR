import cv2


def getFilesList(path):
    files = open(path, "r")
    return [(file[5:].split(' ')[0], file.split(' ')[1][:-1]) for file in files]


def getBinaryFile(file):
    fullPath = 'digits/data/' + file
    image = cv2.imread(fullPath, 0)
    h, w = image.shape

    for i in range(h):
        for j in range(w):
            image[i][j] = 1 if image[i][j] < 128 else 0
    return {'width': w, 'height': h, 'image': image}


def getChunkConfig(file):
    chunkConfig = []
    for j in range(3):
        for i in range(2):
            wStart = i * (file['width'] // 2)
            wEnd = (file['width'] // 2) if i == 0 else file['width']
            hStart = j * (file['height'] // 3)
            hEnd = (j + 1) * (file['height'] // 3) if j < 2 else file['height']
            chunkConfig.append((wStart, wEnd, hStart, hEnd))
    return chunkConfig


# chunk[0] = wStart | chunk[1] = wEnd | chunk[2] = hStart | chunk[3] = hEnd
def getResult(chunk, file, pixel):
    result = ''

    # pixel para cima
    for i in range(chunk[2], pixel[1]):
        # print(file['image'][i][pixel[0]])
        print(i)

    # pixel para cima
    # for i in range(chunk[2], pixel[1]):
    #     if file['image'][pixel[0]][i] == 1:
    #         result += 'u'

    #     # for j in range(chunk[0], pixel[0]):
    #     #     if file['image'][j][i] == 1:
    #     #         return '0'

    #     # for j in range(pixel[0], chunk[1]):
    #     #     if file['image'][j][i] == 1:
    #     #         return '1'

    # # pixel para direita
    # for i in range(pixel[0], chunk[1]):
    #     if file['image'][i][pixel[1]] == 1:
    #         result += 'r'

    # # # pixel para baixo
    # for i in range(pixel[1], chunk[3]):
    #     if file['image'][pixel[0]][i] == 1:
    #         result += 'd'

    #     # for j in range(chunk[0], pixel[0]):
    #     #     if file['image'][j][i] == 1:
    #     #         return '2'

    #     # for j in range(pixel[0], chunk[1]):
    #     #     if file['image'][j][i] == 1:
    #     #         return '3'

    # # # pixel para esquerda
    # for i in range(chunk[0], pixel[0]):
    #     if file['image'][i][pixel[1]] == 1:
    #         result += 'l'

    return str(result)


def getConcavity(file, chunkConfig):
    concavity = []
    for chunk in chunkConfig:
        chunkConcavity = {'ur': 0, 'rd': 0, 'dl': 0, 'ul': 0, 'urd': 0, 'rdl': 0,
                          'udl': 0, 'url': 0, 'urdl': 0, '0': 0, '1': 0, '2': 0, '3': 0}
        for i in range(chunk[2], chunk[3]):
            for j in range(chunk[0], chunk[1]):
                if file['image'][i][j] != 1:
                    result = getResult(chunk, file, (i, j))
                    print(result)
                    # if result in chunkConcavity.keys():
                    # chunkConfig[result] += 1
        concavity += chunkConcavity.values()

    return concavity


def getBlackPixelDensity(binarizedFile, chunkConfig):
    densityByChunck = []
    for chunk in chunkConfig:
        chunkArea = (chunk[1] - chunk[0]) * (chunk[3] - chunk[2])
        pixels = 0
        for i in range(chunk[2], chunk[3]):
            for j in range(chunk[0], chunk[1]):
                if binarizedFile['image'][i][j] == 1:
                    pixels += 1
        # density = pixels / chunkArea
        density = pixels
        densityByChunck.append(density)

    return densityByChunck


if __name__ == '__main__':
    representation = []
    files = getFilesList("digits/test.txt")

    for file in files:
        imageRep = []

        # Preparing the data
        binarizedFile = getBinaryFile(file[0])
        chunkConfig = getChunkConfig(binarizedFile)

        # Getting representation
        concavity = getConcavity(binarizedFile, chunkConfig)
        blackPixelDensity = getBlackPixelDensity(binarizedFile, chunkConfig)

        imageRep += concavity
        imageRep += blackPixelDensity
        imageRep += [file[1]]
        representation.append(imageRep)

    # for rep in representation:
        # print(' '.join(str(r) for r in rep))
        # print(len(rep))
