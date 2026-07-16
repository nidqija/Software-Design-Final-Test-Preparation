#include <iostream>


using namespace std;

// base class shape with virtual function area() which will be overridden by derived classes
// at least 2 derived classes override area()
// function that processes shapes polymorphically and prints the area of the shape


class Shape {
    public:
       virtual int area() = 0;

       virtual ~Shape() = default; // setup virtual destructor by default to ensure proper cleanup of derived classes
};


class Square : public Shape {
    private :
       int side;


    public :
        Square(int side ) : side(side) {}


        virtual int area( )  override{
            return side * side;
        }
};


class Circle : public Shape {
    private :
       int radius;


    public:
       Circle(int r ) : radius(r){}


       virtual int area() override {
            return 3.14 * radius * radius;
       }

};


class Rectangle : public Shape {
    private :
    int length;
    int width;


    public:
       Rectangle(int l , int w ) : length(l), width(w){}


       virtual int area() override {
        return length * width;
       }
};



// function that takes a pointer to Shape and prints the area of the shape
// this function demonstrates polymorphism as it can take any derived class of Shape and call the appropriate area() function

void printArea(Shape* shape){
    cout << "Area: " << shape->area() << endl;
}


int main(){

    Shape* square = new Square(5);
    Shape* rectangle = new Rectangle(4, 6);
    Shape* circle = new Circle(3);

    printArea(square);
    printArea(rectangle);
    printArea(circle);


    return 0;
}