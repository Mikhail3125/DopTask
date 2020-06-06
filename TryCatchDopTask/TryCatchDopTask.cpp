#include <iostream>
#include <cmath> // для sqrt()
#include <string>
using namespace std;
class ArrayException
{
private:
    string m_error;

public:
    ArrayException(std::string error)
        : m_error(error)
    {
    }

    const char* getError() { return m_error.c_str(); }
};

class ArrayInt
{
private:

    int m_data[4]; // ради простоты примера укажем 4 в качестве длины массива
public:
    ArrayInt() {}

    int getLength() { return 4; }

    int& operator[](const int index)
    {
        if (index < 0 || index >= getLength())
            throw ArrayException("Invalid index");

        return m_data[index];
    }

};

// Отдельная функция вычисления квадратного корня числа
double mySqrt(double a)
{
    // Если пользователь ввёл отрицательное число,
    if (a < 0.0)
        throw "Can not take sqrt of negative number"; // то выбрасывается исключение типа const char*

    return sqrt(a);
}
void last() // вызывается функцией three()
{
    std::cout << "Start last\n";
    std::cout << "last throwing int exception\n";
    throw - 1;
    std::cout << "End last\n";

}

void three() // вызывается функцией two()
{
    std::cout << "Start three\n";
    last();
    std::cout << "End three\n";
}

void two() // вызывается функцией one()
{
    std::cout << "Start two\n";
    try
    {
        three();
    }
    catch (double)
    {
        std::cerr << "two caught double exception\n";
    }
    std::cout << "End two\n";
}

void one() // вызывается функцией main()
{
    std::cout << "Start one\n";
    try
    {
        two();
    }
    catch (int)
    {
        std::cerr << "one caught int exception\n";
    }
    catch (double)
    {
        std::cerr << "one caught double exception\n";
    }
    std::cout << "End one\n";
}

int main()
{
    ArrayInt array;

    try
    {
        int value = array[7];
    }
    catch (ArrayException& exception)
    {
        std::cerr << "An array exception occurred (" << exception.getError() << ")\n";
    }
    std::cout << "Start main\n";
    try
    {
        one();
    }
    catch (int)
    {
        std::cerr << "main caught int exception\n";
    }
    std::cout << "End main\n";

    return 0;
}