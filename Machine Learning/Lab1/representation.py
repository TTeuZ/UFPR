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

# Array composition
# u r d l ur rd dl ul ud rl urd rdl udl url urdl
def getConcavityRepresentation(file, chunkConfig):
    for chunk in chunkConfig:
        chunkConcavity = {'u': 0, 'r': 0, 'd': 0, 'l': 0, 'ur': 0, 'rd': 0, 'dl': 0, 'ul': 0, 'ud': 0, 'rl': 0, 'urd': 0, 'rdl': 0, 'udl': 0, 'url': 0, 'urdl': 0}
        for i in range(chunk[2], chunk[3]):
            for j in range(chunk[0], chunk[1]):
                if file['image'][i][j] != 1:
                    
    
    return []


def test(file):
    count = 0
    for i in range(file['height']):
        for j in range(file['width']):
            count += 1
    print(f'teste: {count}')


if __name__ == '__main__':
    representation = []
    files = getFilesList("digits/test.txt")

    for file in files:
        binarizedFile = getBinaryFile(file[0])
        chunkConfig = getChunkConfig(binarizedFile)
        concavity = getConcavityRepresentation(binarizedFile, chunkConfig)
        test(binarizedFile)