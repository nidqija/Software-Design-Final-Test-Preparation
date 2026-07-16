#include <iostream>


using namespace std;

// base class shape with virtual function area() which will be overridden by derived classes
// at least 2 derived classes override area()
// function that processes shapes polymorphically and prints the area of the shape


class Shape {
    public:
       virtual int area() = 0;
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




void printArea(Shape* shape){
    cout << "Area: " << shape->area() << endl;
}


int main(){

    Shape* square = new Square(5);
    Shape* rectangle = new Rectangle(4, 6);

    printArea(square);
    printArea(rectangle);


    return 0;
}