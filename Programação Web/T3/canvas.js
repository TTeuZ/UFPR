// variables
var canvas = document.getElementById("canvas")
var context = canvas.getContext("2d")

const point = (x, y) => ({ x, y })
const line = (begin, end) => ({ begin, end })
const mouse = {
    x: 0, y: 0,
    button: 0,
    dragging: false,
    dragX: 0, dragY: 0
}
var lines = []

// General Functions
function validateInput(value) {
    if (value > 8) value = 8
    if (value < 3) value = 3

    const input = document.getElementById("sides")
    input.value = value
}

function treatInput() {
    const input = document.getElementById("sides")
    createPolygon(parseInt(input.value))
    draw()
}

function cleanCanvas() { context.clearRect(0, 0, 600, 600) }

function clearLines() { lines = [] }

// Draw Functions
function drawLine(line) {
    context.moveTo(line.begin.x, line.begin.y)
    context.lineTo(line.end.x, line.end.y)
}

function drawLines() {
    let count
    for (count = 0; count < lines.length; ++count)
        drawLine(lines[count])
}

function draw() {
    context.beginPath()
    cleanCanvas()
    drawLines()
    context.stroke()
}

// Polygon functions
function initialBeginning() {
    var begin, end, newLine
    begin = point(150, 300)
    end = point(450, 300)
    newLine = line(begin, end)
    lines.push(newLine)
}

function createPolygon(sides) {
    var sideSize, center, x, y, begin, end, newLine, count

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
        newLine = line(begin, end)
        lines.push(newLine)
        begin = end
    }
}

// main
initialBeginning()
draw()