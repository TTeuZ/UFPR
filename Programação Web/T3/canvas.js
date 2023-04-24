// variables
var canvas = document.getElementById("canvas")
var context = canvas.getContext("2d")

const point = (x, y) => ({x, y})
const line = (begin, end) => ({begin, end})
const mouse = {
    x: 0, y: 0,
    button: 0,
    dragging: false,
    dragX: 0, dragY: 0
}

var lines = []
const size = 600
const section = size / 6

// input functions
function validateInput (value) {
    if (value > 8) value = 8
    if (value < 3) value = 3

    const input = document.getElementById("sides")
    input.value = value
}

function createPoligon () {
    clearLines()

    const input = document.getElementById("sides")
    const value = input.value

    switch (value) {
        case '3':
            lines = createLines(3, 60, 50)
        break
        case '4':
        break
        case '5':
        break
        case '6':
        break
        case '7':
        break
        case '8':
        break
    }
}

function createLines(sides, ang, lineSize) {
    var beginX, beginY, endX, endY
    var radius, cos, sin
    var count, sinal

    sinal = 1
    beginX = section * 2
    beginY = section * 3
    for (count = 0; count < sides; ++count) {
        radius = ((sinal * ang) * Math.PI) / 180
        cos = Math.cos(radius)
        sin = Math.sin(radius)
    }
}

// canva function
function cleanCanvas () { context.clearRect(0,0,size,size) }

// Line functions
function clearLines () { lines = [] }

function drawLine (line) {
    context.moveTo(line.begin.x, line.begin.y)
    context.lineTo(line.end.x, line.end.y)
}

function drawLines () {
    let count
    for (count = 0; count < lines.length; ++count)
        drawLine(lines[count])
}

// Main functions
function normalBegin () {
    clearLines()
    
    const begin = point(section * 2, section * 3)
    const end = point(section * 4, section * 3)
    const newLine = line(begin, end)
    lines.push(newLine)
}

function draw () {
    context.beginPath()
    cleanCanvas()
    drawLines()
    context.stroke()
}

// main
normalBegin()
draw()