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
    for h in range(3):
        for w in range(2):
            wStart = w * (file['width'] // 2)
            wEnd = (file['width'] // 2) if w == 0 else file['width']
            hStart = h * (file['height'] // 3)
            hEnd = (h + 1) * (file['height'] // 3) if h < 2 else file['height']
            chunkConfig.append((wStart, wEnd, hStart, hEnd))
    return chunkConfig


# chunk[0] = wStart | chunk[1] = wEnd | chunk[2] = hStart | chunk[3] = hEnd
# the position of x and y are inverted in everythin
# pixel(w, h)
def getResult(chunk, file, pixel):
    result = ''

    # pixel para cima
    # hasFoundBlackLeft = False
    # hasFoundBlackRight = False
    for i in range(chunk[2], pixel[1]):
        if file['image'][i][pixel[0]] == 1 and 'u' not in result:
            result += 'u'

        # if 'u' not in result:
        #     blackInThisRow = False
        #     for j in range(chunk[0], pixel[0]):
        #         if file['image'][i][j] == 1:
        #             hasFoundBlackLeft = blackInThisRow = True
        #         if j == (pixel[0] - 1) and hasFoundBlackLeft and not blackInThisRow:
        #             return '0'

        #     blackInThisRow = False
        #     for j in range(pixel[0], chunk[1]):
        #         if file['image'][i][j] == 1:
        #             hasFoundBlackLeft = blackInThisRow = True
        #         if j == (chunk[1] - 1) and hasFoundBlackRight and not blackInThisRow:
        #             return '1'

    # pixel para direita
    for i in range(pixel[0], chunk[1]):
        if file['image'][pixel[1]][i] == 1 and 'r' not in result:
            result += 'r'

    # pixel para baixo
    # hasFoundBlackLeft = False
    # hasFoundBlackRight = False
    for i in range(pixel[1], chunk[3]):
        if file['image'][i][pixel[0]] == 1 and 'd' not in result:
            result += 'd'

        # if 'd' not in result:
        #     blackInThisRow = False
        #     for j in range(chunk[0], pixel[0]):
        #         if file['image'][i][j] == 1:
        #             hasFoundBlackLeft = blackInThisRow = True
        #         if j == (pixel[0] - 1) and hasFoundBlackLeft and not blackInThisRow:
        #             return '2'

        #     blackInThisRow = False
        #     for j in range(pixel[0], chunk[1]):
        #         if file['image'][i][j] == 1:
        #             hasFoundBlackLeft = blackInThisRow = True
        #         if j == (chunk[1] - 1) and hasFoundBlackRight and not blackInThisRow:
        #             return '3'

    # pixel para esquerda
    for i in range(chunk[0], pixel[0]):
        if file['image'][pixel[1]][i] == 1 and 'l' not in result:
            result += 'l'

    return result


def getConcavity(file, chunkConfig):
    concavity = []
    for chunk in chunkConfig:
        # chunkArea = (chunk[1] - chunk[0]) * (chunk[3] - chunk[2])

        # chunkConcavity = {'ur': 0, 'rd': 0, 'dl': 0, 'ul': 0, 'urd': 0, 'rdl': 0, 'udl': 0, 'url': 0, 'urdl': 0, '0': 0, '1': 0, '2': 0, '3': 0}
        chunkConcavity = {'ur': 0, 'rd': 0, 'dl': 0, 'ul': 0, 'urd': 0, 'rdl': 0,
                          'udl': 0, 'url': 0, 'urdl': 0, 'u': 0, 'r': 0, 'd': 0, 'l': 0}
        for h in range(chunk[2], chunk[3]):
            for w in range(chunk[0], chunk[1]):
                if file['image'][h][w] != 1:
                    result = getResult(chunk, file, (w, h))
                    if result in chunkConcavity.keys():
                        chunkConcavity[result] += 1

        concavity += chunkConcavity.values()
        # concavity += [value//(chunkArea if chunkArea != 0 else 1)
        #               for value in chunkConcavity.values()]

    return concavity


def getBlackPixelDensity(binarizedFile, chunkConfig):
    densityByChunck = []
    for chunk in chunkConfig:
        # chunkArea = (chunk[1] - chunk[0]) * (chunk[3] - chunk[2])
        pixels = 0
        for h in range(chunk[2], chunk[3]):
            for w in range(chunk[0], chunk[1]):
                if binarizedFile['image'][h][w] == 1:
                    pixels += 1

        # density = pixels / chunkArea if chunkArea != 0 else pixels
        density = pixels
        densityByChunck.append(density)

    return densityByChunck


if __name__ == '__main__':
    representation = []
    files = getFilesList("digits/files.txt")

    for file in files:
        imageRep = []

        # Preparing the data
        binarizedFile = getBinaryFile(file[0])
        chunkConfig = getChunkConfig(binarizedFile)

        # print(binarizedFile['height'], binarizedFile['width'])
        # print(chunkConfig)

        # Getting representation
        concavity = getConcavity(binarizedFile, chunkConfig)
        blackPixelDensity = getBlackPixelDensity(binarizedFile, chunkConfig)

        imageRep += concavity
        imageRep += blackPixelDensity
        imageRep += [file[1]]
        representation.append(imageRep)

    for rep in representation:
        print(' '.join(str(r) for r in rep))
        # print(len(rep))

    # for chunk in chunkConfig:
    #     for h in range(chunk[2], chunk[3]):
    #         for w in range(chunk[0], chunk[1]):
    #             print(binarizedFile['image'][h][w])

        # for h in range(chunkConfig[0][2], chunkConfig[0][3]):
        #     for w in range(chunkConfig[0][0], chunkConfig[0][1]):
        #         print(binarizedFile['image'][h][w], end='')
        #     print('\n', end='')
