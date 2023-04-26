// --------------------------------------------------------------------------------
//                                Variables
// --------------------------------------------------------------------------------
var canvas = document.getElementById("canvas")
var context = canvas.getContext("2d")

const point = (x, y) => ({ x, y })
const line = (begin, end, isDragging, where) => ({ begin, end, isDragging, where })

var button = null
var lines = []

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

// function cursorInLine(mouse, line) {
//     var beginX, beginY, endX, endY

//     beginX = line.begin.x - 5
//     beginY = line.begin.y - 5
//     endX = line.end.x + 5
//     endY = line.end.y + 5

//     var hitX = mouse.x >= beginX && mouse.x <= (beginX + 10)
//     var hitY = mouse.y >= beginY && mouse.y <= (beginY + 10)

//     if (hitX && hitY && button == 1) return 'begin'

//     var hitX = mouse.x >= (endX - 10) && mouse.x <= endX
//     var hitY = mouse.y >= (endY - 10) && mouse.y <= endY

//     if (hitX && hitY && button == 1) return 'end'

//     var hitX = mouse.x >= (beginX + 10) && mouse.x <= (endX - 10)
//     var hitY = mouse.y >= beginY && mouse.y <= endY

//     if (hitX && hitY) return 'middle'
// }

// function getLineOffsets(mouse, line) {
//     return {
//         beginX: mouse.x - line.begin.x,
//         beginY: mouse.y - line.begin.y,
//         endX: line.end.x - mouse.x,
//         endY: line.end.y - mouse.y
//     }
// }

// --------------------------------------------------------------------------------
//                               Draw Functions
// --------------------------------------------------------------------------------
function drawLine(line) {
    context.moveTo(line.begin.x, line.begin.y)
    context.lineTo(line.end.x, line.end.y)
}

function drawLines() {
    let count

    context.beginPath()
    for (count = 0; count < lines.length; ++count)
        drawLine(lines[count])
    context.stroke()
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
        newLine = line(begin, end, false, null)
        lines.push(newLine)
        begin = end
    }
}

// --------------------------------------------------------------------------------
//                                Move Functions
// --------------------------------------------------------------------------------
// function treatNormalMove(line, mouse, event) {
//     if (line.where == 'middle') {
//         line.begin.x = mouse.x - line.offset.beginX
//         line.begin.y = mouse.y - line.offset.beginY
//         line.end.x = mouse.x + line.offset.endX
//         line.end.y = mouse.y + line.offset.endY
//     } else {
//         console.log(line[line.where])
//     }
// }

// function splitLineAndMove(line, event) {

// }

canvas.addEventListener('mousedown', event => {
    var mouse = getCoordinates(canvas, event)
    button = event.buttons

    // lines.forEach(line => {
    //     switch (cursorInLine(mouse, line)) {
    //         case 'begin':
    //             line.isDragging = true
    //             line.where = 'begin'
    //             line.offset = getLineOffsets(mouse, line)
    //             break
    //         case 'middle':
    //             line.isDragging = true
    //             line.where = 'middle'
    //             line.offset = getLineOffsets(mouse, line)
    //             break
    //         case 'end':
    //             line.isDragging = true
    //             line.where = 'end'
    //             line.offset = getLineOffsets(mouse, line)
    //             break
    //     }
    // })
})

canvas.addEventListener('mouseup', event => {
    button = null
    lines.forEach(line => {
        line.isDragging = false
        line.where = null
    })
})

canvas.addEventListener('mousemove', event => {
    // var mouse = getCoordinates(canvas, event)

    // lines.forEach(line => {
    //     if (line.isDragging) {
    //         if (button == 1) {
    //             treatNormalMove(line, mouse, event)
    //         } else {
    //             splitLineAndMove(line, event)
    //         }
    //     }
    // })
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