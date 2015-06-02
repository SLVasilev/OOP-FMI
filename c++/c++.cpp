#include <iostream>
#include <cstring>
#include <cassert>
#include <cmath>

using namespace std;

struct Point {
    double x, y;

    Point(double p1 = 0.0, double p2 = 0.0) {
        this -> x = p1;
        this -> y = p2;
    }
};

class Figure {
public:
    virtual double area() = 0;
    virtual void print() const = 0;
};

class Triangle : virtual public Figure {
private:
    Point A;
    Point B;
    Point C;

public:
    void setPointA(double x, double y) {
        this -> A.x = x;
        this -> A.y = y;
    }
    void setPointB(double x, double y) {
        this -> B.x = x;
        this -> B.y = y;
    }
    void setPointC(double x, double y) {
        this -> C.x = x;
        this -> C.y = y;
    }

    const Point getPointA() const {
        return this -> A;
    }
    const Point getPointB() const {
        return this -> B;
    }
    const Point getPointC() const {
        return this -> C;
    }

    Triangle() : Figure() {
        setPointA(1, 1);
        setPointB(3, 1);
        setPointC(2, 4);
    }

// Validations for triangles
    bool areTheSame(Point first, Point second) {
        return first.x == second.x && first.y == second.y;
    }
    bool areInColumn(double firstX, double secondX, double thirdX) {
        return firstX == secondX == thirdX;
    }
    bool areInLine(double firstY, double secondY, double thirdY) {
        return firstY == secondY == thirdY;
    }


    void readTriangle() {
        cout << "Enter first coordinates of triangle: ";
        double n, m;
        do {
            cin >> n >> m;
        }
        while(n < 0 || m < 0);

        cout << "Enter second coordinates of triangle: ";
        do {
            cin >> n >> m;
        }
        while(n < 0 || m < 0 );
        setPointB(n, m);

        cout << "Enter third coordinates of triangle: ";
        do {
            cin >> n >> m;
        }
        while(n < 0 || m < 0);
        setPointC(n, m);

        if(!areInColumn(A.x, B.x, C.x) &&
           !areInLine(A.y, B.y, C.y) &&
           !areTheSame(A, B) &&
           !areTheSame(A, C) &&
           !areTheSame(B, C)) {
            cout << "This is a valid figure.\n";
        }
        else {
            cout << "This isn't valid figure. Enter again.\n";
            readTriangle();
        }
    }

    virtual double area() {
        // Formula for triangle area with coordinates
        return abs((A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y)) / 2);
    }

    virtual void print() const {
        cout << "Triangle coordinates are: ";
        cout << A.x << ',' << A.y << ' ';
        cout << B.x << ',' << B.y << ' ';
        cout << C.x << ',' << C.y << endl;
    }
};

class Circle : virtual public Figure {
private:
    Point center;
    double r;

public:
    void setCenter(double x, double y) {
        this -> center.x = x;
        this -> center.y = y;
    }
    void setRadius(double radius) {
        this -> r = radius;
    }

    const Point getCenter() const {
        return this -> center;
    }
    const double getRadius() const {
        return this -> r;
    }

    Circle() : Figure() {
        setCenter(1, 1);
        setRadius(2);
    }

    void readCircle() {
        cout << "Enter the center coordinates: ";
        double n, m;
        do {
            cin >> n >> m;
        }
        while(n < 0 || m < 0);
        setCenter(n, m);

        cout << "Enter the radius coordinates: ";
        double z;
        do {
            cin >> z;
        }
        while(z < 0);
        setRadius(z);
    }

    virtual double area() {
        return 2 * 3.14 * this -> r;
    }

    virtual void print() const {
        cout << "The circle center is in " << this -> center.x
        << ',' << center.y << " and the radius is " << this -> r
        << endl;
    }
};

class Square : virtual public Figure {
private:
    Point firstCorner;
    Point thirdCorner;

public:
    void setFirstCorner(double x, double y) {
        this -> firstCorner.x = x;
        this -> firstCorner.y = y;
    }
    void setThirdCorner(double x, double y) {
        this -> thirdCorner.x = x;
        this -> thirdCorner.y = y;
    }

    const Point getFirstCorner() const {
        return this -> firstCorner;
    }
    const Point getThirdCorner() const {
        return this -> thirdCorner;
    }

    Square() : Figure() {
        setFirstCorner(1, 1);
        setThirdCorner(3, 3);
    }

//Validation for square
    bool isSquare(Point first, Point third) {
        return (third.x / first.x) == (third.y / first.y);
    }

    void readSquare() {
        cout << "Enter coordinates of first corner: ";
        double n, m;
        do {
            cin >> n >> m;
        }
        while(n < 0 || m < 0);
        setFirstCorner(n, m);

        double z, w;
        cout << "Enter coordinates of opposite corner: ";
        do {
            cin >> z >> w;
        }
        while (z < 0 || w < 0);
        setThirdCorner(z, w);

        if(isSquare(firstCorner, thirdCorner)) {
            cout << "This is a square figure.\n";
        }
        else {
            cout << "This isn't a square figure.\n";
            readSquare();
        }
    }

    virtual double area() {
        double side = abs(firstCorner.x - thirdCorner.x);
        return side * side;
    }

    virtual void print() const {
        cout << "The coordinates of the square are:\n";
        cout << this -> firstCorner.x << ','
             << this -> firstCorner.y << ' '
             << this -> thirdCorner.x << ','
             << this -> firstCorner.y << ' '
             << this -> thirdCorner.x << ','
             << this -> thirdCorner.y << ' '
             << this -> firstCorner.x << ','
             << this -> thirdCorner.y << endl;
    }
};


Figure &chooseFigure() {
    cout << "Enter 1 for triangle, 2 for circle, 3 for square: ";
    int n;
    cin >> n;

    switch(n){
        case 1: {
            cout << "You've choosen triangle.\n";
            Triangle *t = new Triangle;
            t -> readTriangle();
            cout << "Triangle area is " << t -> area() << endl;
            t -> print();
            return *t;
        } break;
        case 2: {
            cout << "You've choosen circle.\n";

            Circle *c = new Circle;
            c -> readCircle();
            cout << "Circle area is " << c -> area() << endl;
            c -> print();
            return *c;
        } break;
        case 3: {
            cout << "You've choosen square.\n";
            Square *s = new Square;
            s -> readSquare();
            cout << "Square area is " << s -> area() << endl;
            s -> print();
            return *s;
        }
        default: {
            cout << "Invalid input\n";
            chooseFigure();
        }
    }
}


int main()
{
    chooseFigure();


    return 0;
}
