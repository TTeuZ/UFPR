// --------------------------------------------------------------------------------
//                                Variables
// --------------------------------------------------------------------------------
var canvas = document.getElementById("canvas")
var context = canvas.getContext("2d")

const point = (x, y) => ({ x, y })
const line = (begin, end, isDragging, where) => ({ begin, end, isDragging, where })

var button = null
var lines = []

const input = document.getElementById("sides")
input.value = 3

// --------------------------------------------------------------------------------
//                             General Functions
// --------------------------------------------------------------------------------
function validateInput(value) {
    if (value > 8) value = 8
    if (value < 3) value = 3

    const input = document.getElementById("sides")
    input.value = value
}

function treatInput() {
    const input = document.getElementById("sides")
    createPolygon(parseInt(input.value))
}

function cleanCanvas() { context.clearRect(0, 0, 600, 600) }

function clearLines() { lines = [] }

function getCoordinates(canvas, event) {
    let coordinates = canvas.getBoundingClientRect()
    return {
        x: event.pageX - coordinates.left,
        y: event.pageY - coordinates.top
    }
}

function cursorInLine(mouse, line) {
    var dBegin, dEnd, dMiddle

    dBegin = Math.sqrt(Math.pow((line.begin.x - mouse.x), 2) + Math.pow((line.begin.y - mouse.y), 2))
    dEnd = Math.sqrt(Math.pow((line.end.x - mouse.x), 2) + Math.pow((line.end.y - mouse.y), 2))
    dMiddle = Math.abs(
        (line.end.y - line.begin.y) * mouse.x -
        (line.end.x - line.begin.x) * mouse.y +
        line.end.x * line.begin.y -
        line.end.y * line.begin.x
    ) / Math.sqrt((line.end.y - line.begin.y) ** 2 + (line.end.x - line.begin.x) ** 2)

    const lineSize = Math.sqrt(Math.pow(Math.abs(line.end.x - line.begin.x), 2) + Math.pow(Math.abs(line.end.y - line.begin.y), 2))

    if (dBegin <= 10 && button == 1) return 'begin'
    if (dEnd <= 10 && button == 1) return 'end'
    if (dMiddle <= 10 && Math.ceil(Math.abs(dEnd - dBegin) + 1) < lineSize) return 'middle'
}

function getLineOffsets(mouse, line) {
    return {
        begin: {
            x: mouse.x - line.begin.x,
            y: mouse.y - line.begin.y,
        },
        end: {
            x: line.end.x - mouse.x,
            y: line.end.y - mouse.y
        }
    }
}

// --------------------------------------------------------------------------------
//                               Draw Functions
// --------------------------------------------------------------------------------
function drawLine(line) {
    context.beginPath()
    context.strokeStyle = '#fff';
    context.moveTo(line.begin.x, line.begin.y)
    context.lineTo(line.end.x, line.end.y)
    context.stroke()
}

function drawLines() {
    let count
    for (count = 0; count < lines.length; count++)
        drawLine(lines[count])
}

// --------------------------------------------------------------------------------
//                              Polygon Functions
// --------------------------------------------------------------------------------
function initialBeginning() {
    var begin, end, newLine
    begin = point(150, 300)
    end = point(450, 300)
    newLine = line(begin, end, false, null)
    lines.push(newLine)
}

function createPolygon(sides) {
    var sideSize, center, x, y, begin, end, newLine, clone, count
    clearLines()

    sideSize = 150
    center = 300

    x = center + sideSize * Math.cos(0)
    y = center + sideSize * Math.sin(0)
    begin = point(x, y)

    for (count = 1; count <= sides; ++count) {
        x = center + sideSize * Math.cos(count * 2 * Math.PI / sides)
        y = center + sideSize * Math.sin(count * 2 * Math.PI / sides)
        end = point(x, y)
        newLine = line(begin, end, false, null)
        lines.push(newLine)
        clone = JSON.parse(JSON.stringify(end));
        begin = clone
    }
}

// --------------------------------------------------------------------------------
//                                Move Functions
// --------------------------------------------------------------------------------
function treatNormalMove(mouse, line) {
    if (line.where == 'middle') {
        line.begin.x = mouse.x - line.offset.begin.x
        line.begin.y = mouse.y - line.offset.begin.y
        line.end.x = mouse.x + line.offset.end.x
        line.end.y = mouse.y + line.offset.end.y
    } else {
        line[line.where].x = mouse.x - line.offset[line.where].x
        line[line.where].y = mouse.y - line.offset[line.where].y
    }
}

function splitLine(mouse, actualLine) {
    var begin, end, newLine

    begin = point(actualLine.begin.x, actualLine.begin.y)
    end = point(mouse.x, mouse.y)
    newLine = line(begin, end, true, 'end')
    newLine.offset = getLineOffsets(mouse, newLine)
    lines.push(newLine)

    begin = point(mouse.x, mouse.y)
    end = point(actualLine.end.x, actualLine.end.y)
    newLine = line(begin, end, true, 'begin')
    newLine.offset = getLineOffsets(mouse, newLine)
    lines.push(newLine)

    lines.splice(lines.indexOf(actualLine), 1)
}

canvas.addEventListener('mousedown', event => {
    var mouse = getCoordinates(canvas, event)
    button = event.buttons

    lines.forEach(line => {
        switch (cursorInLine(mouse, line)) {
            case 'begin':
                line.isDragging = true
                line.where = 'begin'
                line.offset = getLineOffsets(mouse, line)
                break
            case 'middle':
                if (button == 1) {
                    line.isDragging = true
                    line.where = 'middle'
                    line.offset = getLineOffsets(mouse, line)
                } else splitLine(mouse, line)
                break
            case 'end':
                line.isDragging = true
                line.where = 'end'
                line.offset = getLineOffsets(mouse, line)
                break
        }
    })
})

canvas.addEventListener('mouseup', event => {
    button = null
    lines.forEach(line => {
        line.isDragging = false
        line.where = null
    })
})

canvas.addEventListener('mousemove', event => {
    var mouse = getCoordinates(canvas, event)

    lines.forEach(line => {
        if (line.isDragging) {
            treatNormalMove(mouse, line)
        }
    })
})

// --------------------------------------------------------------------------------
//                                  main loop
// --------------------------------------------------------------------------------
function update() {
    cleanCanvas()
    drawLines()
    window.requestAnimationFrame(update)
}

initialBeginning()
update()