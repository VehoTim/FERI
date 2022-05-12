#include <iostream>
#include "Canvas.h"
#include "Text.h"
#include "Rectangle.h"
#include <ctime>

int main() {
    srand(time(nullptr));

    Canvas canvas(500, 500);
    // add at least five shapes to the canvas
    canvas.addShape(new Text(Color::red, 3, 5, 11, "Lorem ipsum"));
    canvas.addShape(new Text(Color(30,50,70), 5, 3, 1, "Tim"));
    canvas.addShape(new Text(Color::blue, 100, 20, 13, "Daljse besedilo je tukaj notri to bo verjetno out of bounds"));
    canvas.addShape(new Rectangle(Color(29, 200, 195), 3, 5, 10, 10));
    canvas.addShape(new Rectangle(Color::green, 10, 25, 15, 30));
    canvas.draw();
    canvas.undo();
    canvas.draw();
    canvas.resize(100, 100);
    canvas.draw();

    return 0;
}