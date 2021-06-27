/** Summary:
* 1. Understand the difference between Copy Constructor and Assignment Operator
* 2. Like passing a parameter by value, returning by value also constructs a copy of the return object.
* 3. Assignment Operator should return by reference.
* 4. Handle self-assignment in Assignment Operator: https://isocpp.org/wiki/faq/assignment-operators
*/

#include <QCoreApplication>
#include <QDebug>

struct MyClass {

    MyClass() {}

    MyClass(int x, int y)
    {
        _x = x;
        _y = y;
    }

    MyClass(const MyClass& src)
    {
        qDebug() << "copy constructor is called!";
        _x = src._x;
        _y = src._y;
    }

    MyClass& operator = (const MyClass& rhs) //return by reference
    {
        qDebug() << "assignment operator is called!";
        if (this == &rhs) return *this; // handle self-assignment. Note the condition "this == &rhs"

        _x = rhs._x;
        _y = rhs._y;

        return *this;
    }

    int _x, _y;
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyClass c1 = MyClass(1,2);
    MyClass c2 = c1; // c2 = MyClass(c1) - Copy Constructor
    MyClass c3 = MyClass(3,5);
    MyClass c4;
    c4 = c1; // Assignment Operator, because c4 has been defaultly initialized above.

    /*
    * The Copy Constructor has been called twice if we return by value. None if by reference -> more efficient
    * The results are the same if Assignment Operator returns by value or by reference.
    */
    c1 = (c2 = c3);

    // The results are the different between returning by value and by reference.
    (c1 = c2) = c3;

    return a.exec();
}
