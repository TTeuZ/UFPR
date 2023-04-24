// variables
var canvas = document.getElementById("canvas")
var context = canvas.getContext("2d")

const point = (x, y) => ({x, y})
const line = (begin, end) => ({begin, end})
var lines = []

const mouse = {
    x: 0, y: 0,
    button: 0,
    dragging: false,
    dragX: 0, dragY: 0
}

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
    const input = document.getElementById("sides")
    const value = input.value
    console.log(value)
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
    const begin = point(section * 2, section * 3)
    const end = point(section * 4, section * 3)
    const newLine = line(begin, end)
    lines.push(newLine)
}

function draw () {
    cleanCanvas()
    drawLines()
    context.stroke()
}

// main
normalBegin()
draw()