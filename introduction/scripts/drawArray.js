function drawBox(pen, x, y, width, height) {
    pen.lineWidth = 3;
    pen.fillStyle = "lightgrey";
    pen.fillRect(x, y, width, height);
    pen.strokeRect(x, y, width, height);
}

function drawNum(pen, num, x, y, size, font_family, color) {
    pen.font = size + " " + font_family;
    pen.fillStyle = color;
    pen.lineWidth = 3;
    pen.fillText(num, x, y);
}

function draw2DigitNumBox(pen, num, x, y, color) {
    drawBox(pen, x, y, 75, 55);
    drawNum(pen, num, x + 5, y + 45, "50px", "sans-serif", color);
}

function drawArray(pen, array, x, y) {
    if (arguments.length == 4) {
        for (var i = 0; i < array.length; i++)
            draw2DigitNumBox(pen, array[i], x + i * 75, y, "black");
    } else if (arguments.length == 5) {
        for (var i = 0, inter = 0; i < array.length; i++, inter += 75) {
            if (i != arguments[4]) {
                draw2DigitNumBox(pen, array[i], x + inter, y, "black");
                if (i == arguments[4] + 1)
                    inter += 20;
            } else {
                draw2DigitNumBox(pen, array[i], x + inter, y, "red");
                inter += 20;
            }
        }
    } else if (arguments.length == 6) {
        for (var i = 0; i < array.length; i++)
            if (i < arguments[4] || i > arguments[5])
                draw2DigitNumBox(pen, array[i], x + i * 75, y, "black");
            else
                draw2DigitNumBox(pen, array[i], x + i * 75, y, "red");
    }
}