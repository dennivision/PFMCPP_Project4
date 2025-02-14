/*
Prject 4: Part 8 / 9
 video: Chapter 5 Part 6 Task 

Create a branch named Part8

 R-Values L-Values Move Semantics.

 This Task is going to demonstrate R-Values and writing Generic Code

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
    it's very easy to mess this task up. 
 
 Your job is to replace the owned type (the primitive specified by your template argument) from the 
     Templated Class you created in Ch5 p04 with a struct named Temporary that can behave ENTIRELY as a temporary object.
 
 That means you must use conversion functions to interact with what it owns.
 
 You need to figure out how to use conversion functions to be able to GET and SET the 'value' member variable.
    hint: conversion functions can return by value and also by ___...
  
 1) Here is a starting point for how to implement your Temporary struct.
 */

#include <typeinfo>
template<typename NumericType>
struct Temporary
{
    Temporary(NumericType t) : v(t)
    {
        std::cout << "I'm a Temporary<" << typeid(v).name() << "> object, #"
                  << counter++ << std::endl;
    }
    /*
     revise these conversion functions to read/write to 'v' here
     hint: what qualifier do read-only functions usually have?
     */
    operator ___() { /* read-only function */ }
    operator ___() { /* read/write function */ }
private:
    static int counter;
    NumericType v;
};

/*
 2) add the definition of Temporary::counter here, which is a static variable and must be defined outside of the class.
    Remember the rules about how to define a Template member variable/function outside of the class.
*/

/*
 3) You'll need to template your overloaded math operator functions in your Templated Class from Ch5 p04
    use static_cast to convert whatever type is passed in to your template's NumericType before performing the +=, -=, etc.  here's an example implementation:
 */
namespace example
{
template<typename NumericType>
struct Numeric
{
    //snip
    template<typename OtherType>
    Numeric& operator-=(const OtherType& o) 
    { 
        *value -= static_cast<NumericType>(o); 
        return *this; 
    }
    //snip
};
}

/*
 4) remove your specialized <double> template of your Numeric<T> class from the previous task (ch5 p04)
    replace the 2 apply() functions in your Numeric<T> with the single templated apply() function from the specialized <double> template.
 */

/*
 5) Template your pow() function the same way you templated the overloaded math operators
    Remove the call to powInternal() and just call std::pow() directly.
    you'll need to static_cast<> the pow() argument the same way you did in the overloaded math operators, when you pass it to std::pow()
 */

/*
 6) Finally, your conversion function in your templated class is going to be returning this Temporary, 
        so you should probably NOT return by copy if you want your templated class's owned object to be modified by any math operation.
    See the previous hint for implementing the conversion functions for the Temporary if you want to get the held value
*/


/*
 7) replace main() with the main below
        you can remove or fix all previous partX() functions if they cause compiler errors. 
        you can leave them where they are if they don't produce any errors.
      
 If you did everything correctly, this is the output you should get:
 
I'm a Temporary<f> object, #0
I'm a Temporary<i> object, #0
I'm a Temporary<d> object, #0
f: -1.89
d: -3.024
i: -9
Point { x: -1.89, y: -9 }
d: 3.024
I'm a Temporary<d> object, #1
I'm a Temporary<d> object, #2
d: 1.49519e+08
Point { x: -2.82591e+08, y: -1.34567e+09 }
I'm a Temporary<f> object, #1
I'm a Temporary<i> object, #1
I'm a Temporary<i> object, #2
I'm a Temporary<i> object, #3
intNum: 5
I'm a Temporary<f> object, #2
f squared: 3.5721
I'm a Temporary<f> object, #3
f cubed: 45.5796
I'm a Temporary<d> object, #3
d squared: 2.2356e+16
I'm a Temporary<d> object, #4
d cubed: 1.11733e+49
I'm a Temporary<i> object, #4
i squared: 81
I'm a Temporary<i> object, #5
i cubed: 531441

Use a service like https://www.diffchecker.com/diff to compare your output. 
*/

#include <iostream>
int main()
{
    Numeric<float> f(0.1f);
    Numeric<int> i(3);
    Numeric<double> d(4.2);
    
    f += 2.f;
    f -= i;
    f *= d;
    f /= 2.f;
    std::cout << "f: " << f << std::endl;
    
    d += 2.f;
    d -= i;
    d *= f;
    d /= 2.f;
    std::cout << "d: " << d << std::endl;
    
    i += 2.f; i -= f; i *= d; i /= 2.f;
    std::cout << "i: "<< i << std::endl;
    
    Point p(f, i);
    p.toString();
    
    d *= -1;
    std::cout << "d: " << d << std::endl;
    
    p.multiply(d.pow(f).pow(i));
    std::cout << "d: " << d << std::endl;
    
    p.toString();
    
    Numeric<float> floatNum(4.3f);
    Numeric<int> intNum(2);
    Numeric<int> intNum2(6);
    intNum = 2 + (intNum2 - 4) + static_cast<double>(floatNum) / 2.3;
    std::cout << "intNum: " << intNum << std::endl;
    
    {
        using Type = decltype(f)::Type;
        f.apply([&f](std::unique_ptr<Type>&value) -> decltype(f)&
                {
                    auto& v = *value;
                    v = v * v;
                    return f;
                });
        std::cout << "f squared: " << f << std::endl;
        
        f.apply( cube<Type> );
        std::cout << "f cubed: " << f << std::endl;
    }
    
    {
        using Type = decltype(d)::Type;
        d.apply([&d](std::unique_ptr<Type>&value) -> decltype(d)&
                {
                    auto& v = *value;
                    v = v * v;
                    return d;
                });
        std::cout << "d squared: " << d << std::endl;
        
        d.apply( cube<Type> );
        std::cout << "d cubed: " << d << std::endl;
    }
    
    {
        using Type = decltype(i)::Type;
        i.apply([&i](std::unique_ptr<Type>&value) -> decltype(i)&
                {
                    auto& v = *value;
                    v = v * v;
                    return i;
                });
        std::cout << "i squared: " << i << std::endl;
        
        i.apply( cube<Type> );
        std::cout << "i cubed: " << i << std::endl;
    }
}


struct A {};
struct HeapA
{
    HeapA() : a(new A) {}
    ~HeapA()
    {
        delete a;
    }
    A* a = nullptr;
};




#include <iostream>
#include <cmath>
#include <functional>
#include <memory>

template<class T>
struct Numeric
{
    using Type = T;
    explicit Numeric(Type v) : value(std::make_unique<Type>(v)) {}

    Numeric& operator+= (const Type& val)
    {
        *value += val;
        return *this;
    }
    Numeric& operator-= (const Type& val)
    {
        *value -= val;
        return *this;
    }
    Numeric& operator*= (const Type& val)
    {
        *value *= val;
        return *this;
    }

    template<typename P>
    Numeric& operator/= (const P& val)
    {
        if (std::is_same<Type, int>::value)
        {
            // Type is int
            if (std::is_same<P, int>::value)
            {
                // Passed in P is int too 
                if (std::abs(val) <= std::numeric_limits<Type>::epsilon())
                {
                    std::cout << "error: integer division by zero is an error and will crash the program!" << std::endl;
                    return *this;
                }
            }
            else if (std::abs(val) <= std::numeric_limits<Type>::epsilon())
            {
                // trying to divide an int by a float or double thats zero
                std::cout << "can't divide integers by zero!" << std::endl;
                return *this;
            }
        }
        else if (std::abs(val) <= std::numeric_limits<Type>::epsilon())
        {
            std::cout << "warning: floating point division by zero!" << std::endl;
        }
        *value /= val;
        return *this;
    }

    template<typename P>
    Numeric<Type>& pow(const P& exp)
    {
        return powInternal(static_cast<Type>(exp));
    }

    operator Type() const { return *value; }

    Numeric& apply(std::function<Numeric& (Type&)> func)
    {
        if (func)
            return func(*value);
        return *this;
    }

    Numeric& apply(void(*func)(Type&))
    {
        if (func)
            func(*value);
        return *this;
    }


private:
    std::unique_ptr<Type> value;
    Numeric& powInternal(const Type exp)
    {
        *value = static_cast<Type>(std::pow(*value, exp));
        return *this;
    }
};
//==============================================================================


template<>
struct Numeric<double>
{
    using Type = double;
    explicit Numeric(Type v) : value(std::make_unique<Type>(v)) {}

    Numeric& operator+= (const Type& val)
    {
        *value += val;
        return *this;
    }
    Numeric& operator-= (const Type& val)
    {
        *value -= val;
        return *this;
    }
    Numeric& operator*= (const Type& val)
    {
        *value *= val;
        return *this;
    }

    Numeric& operator/= (const Type& val)
    {
        if (std::abs(val) <= std::numeric_limits<Type>::epsilon())
        {
            std::cout << "warning: floating point division by zero!" << std::endl;
        }
        *value /= val;
        return *this;
    }

    template<typename P>
    Numeric& pow(const P& exp)
    {
        return powInternal(static_cast<Type>(exp));
    }

    operator Type() const { return *value; }

    template<typename T>
    Numeric& apply(T func)
    {
        func(*value);
        return *this;
    }


private:
    std::unique_ptr<Type> value;
    Numeric& powInternal(const Type exp)
    {
        *value = static_cast<Type>(std::pow(*value, exp));
        return *this;
    }
};


//==============================================================================

struct Point
{
    template <typename T>
    Point(const T& x_, const T& y_) : x(static_cast<float>(x_)), y(static_cast<float>(y_)) {}

    Point& multiply(float m)
    {
        x *= m;
        y *= m;
        return *this;
    }

    template <typename T>
    Point& multiply(const T& m)
    {
        return multiply(static_cast<float>(m));
    }

    void toString()
    {
        std::cout << "Point { x: " << x << ", y: " << y << " }" << std::endl;
    }
private:
    float x{ 0 }, y{ 0 };
};

//==============================================================================

/*
 MAKE SURE YOU ARE NOT ON THE MASTER BRANCH

 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].

 If you didn't already:
    Make a pull request after you make your first commit
    pin the pull request link and this repl.it link to our DM thread in a single message.

 send me a DM to review your pull request when the project is ready for review.

 Wait for my code review.
 */

void part3()
{
    Numeric ft(5.5f);
    Numeric dt(11.1);
    Numeric it(34);
    Numeric pi(3.14);

    ft *= ft;
    ft *= ft;
    ft /= it;
    std::cout << "The result of FloatType^4 divided by IntType is: " << ft << std::endl;

    dt *= 3;
    dt += it;
    std::cout << "The result of DoubleType times 3 plus IntType is : " << dt << std::endl;

    it /= static_cast<int>(pi);
    it *= static_cast<int>(dt);
    it -= static_cast<int>(ft);
    std::cout << "The result of IntType divided by 3.14 multiplied by DoubleType minus FloatType is: " << it << std::endl;

    std::cout << "An operation followed by attempts to divide by 0, which are ignored and warns user:" << std::endl;

    it *= it;
    it /= 0;
    it /= 0.f;
    it /= 0.0;

    std::cout << it << std::endl;

    it *= static_cast<int>(ft);
    std::cout << "FloatType x IntType  =  " << it << std::endl;
    it += static_cast<int>(dt);
    it += static_cast<int>(ft);
    it *= 24;
    std::cout << "(IntType + DoubleType + FloatType) x 24 = " << it << std::endl;
}

void part4()
{
    // ------------------------------------------------------------
    //                          Power tests
    // ------------------------------------------------------------
    Numeric ft1(2);
    Numeric dt1(2);
    Numeric it1(2);
    float floatExp = 2.0f;
    double doubleExp = 2.0;
    int intExp = 2;
    Numeric itExp(2);
    Numeric ftExp(2.0f);
    Numeric dtExp(2.0);

    // Power tests with FloatType
    std::cout << "Power tests with FloatType" << std::endl;
    std::cout << "pow(ft1, floatExp) = " << ft1 << "^" << floatExp << " = " << ft1.pow(floatExp) << std::endl;
    std::cout << "pow(ft1, itExp) = " << ft1 << "^" << itExp << " = " << ft1.pow(itExp) << std::endl;
    std::cout << "pow(ft1, ftExp) = " << ft1 << "^" << ftExp << " = " << ft1.pow(ftExp) << std::endl;
    std::cout << "pow(ft1, dtExp) = " << ft1 << "^" << dtExp << " = " << ft1.pow(dtExp) << std::endl;
    std::cout << "---------------------\n" << std::endl;

    // Power tests with DoubleType
    std::cout << "Power tests with DoubleType" << std::endl;
    std::cout << "pow(dt1, doubleExp) = " << dt1 << "^" << doubleExp << " = " << dt1.pow(intExp) << std::endl;
    std::cout << "pow(dt1, itExp) = " << dt1 << "^" << itExp << " = " << dt1.pow(itExp) << std::endl;
    std::cout << "pow(dt1, ftExp) = " << dt1 << "^" << ftExp << " = " << dt1.pow(ftExp) << std::endl;
    std::cout << "pow(dt1, dtExp) = " << dt1 << "^" << dtExp << " = " << dt1.pow(dtExp) << std::endl;
    std::cout << "---------------------\n" << std::endl;

    // Power tests with IntType
    std::cout << "Power tests with IntType" << std::endl;
    std::cout << "pow(it1, intExp) = " << it1 << "^" << intExp << " = " << it1.pow(intExp) << std::endl;
    std::cout << "pow(it1, itExp) = " << it1 << "^" << itExp << " = " << it1.pow(itExp) << std::endl;
    std::cout << "pow(it1, ftExp) = " << it1 << "^" << ftExp << " = " << it1.pow(ftExp) << std::endl;
    std::cout << "pow(it1, dtExp) = " << it1 << "^" << dtExp << " = " << it1.pow(dtExp) << std::endl;
    std::cout << "===============================\n" << std::endl;

    // ------------------------------------------------------------
    //                          Point tests
    // ------------------------------------------------------------
    Numeric ft2(3.0f);
    Numeric dt2(4.0);
    Numeric it2(5);
    float floatMul = 6.0f;

    // Point tests with float
    std::cout << "Point tests with float argument:" << std::endl;
    Point p0(static_cast<float>(ft2), floatMul);
    p0.toString();
    std::cout << "Multiplication factor: " << floatMul << std::endl;
    p0.multiply(floatMul);
    p0.toString();
    std::cout << "---------------------\n" << std::endl;

    // Point tests with FloatType
    std::cout << "Point tests with FloatType argument:" << std::endl;
    Point p1(ft2, ft2);
    p1.toString();
    std::cout << "Multiplication factor: " << ft2 << std::endl;
    p1.multiply(ft2);
    p1.toString();
    std::cout << "---------------------\n" << std::endl;

    // Point tests with DoubleType
    std::cout << "Point tests with DoubleType argument:" << std::endl;
    Point p2(static_cast<float>(ft2), static_cast<float>(dt2));
    p2.toString();
    std::cout << "Multiplication factor: " << dt2 << std::endl;
    p2.multiply(dt2);
    p2.toString();
    std::cout << "---------------------\n" << std::endl;

    // Point tests with IntType
    std::cout << "Point tests with IntType argument:" << std::endl;
    Point p3(static_cast<float>(ft2), static_cast<float>(dt2));
    p3.toString();
    std::cout << "Multiplication factor: " << it2 << std::endl;
    p3.multiply(it2);
    p3.toString();
    std::cout << "---------------------\n" << std::endl;
}

/*

void myFloatFreeFunct(float& f) { f += 7.0f; }

void myDoubleFreeFunct(double& d) { d += 6.0; }

void myIntFreeFunct(int& i) { i += 5; }

void part6()
{
    FloatType ft3(3.0f);
    DoubleType dt3(4.0);
    IntType it3(5);

    std::cout << "Calling FloatType::apply() using a lambda (adds 7.0f) and FloatType as return type:" << std::endl;
    std::cout << "ft3 before: " << ft3 << std::endl;
    ft3.apply( [&ft3](float& f) -> FloatType&
    {
            f += 7.0f;
            return ft3;
    } );

    std::cout << "ft3 after: " << ft3 << std::endl;
    std::cout << "Calling FloatType::apply() using a free function (adds 7.0f) and void as return type:" << std::endl;
    std::cout << "ft3 before: " << ft3 << std::endl;
    ft3.apply(myFloatFreeFunct);
    std::cout << "ft3 after: " << ft3 << std::endl;
    std::cout << "---------------------\n" << std::endl;

    std::cout << "Calling DoubleType::apply() using a lambda (adds 6.0) and DoubleType as return type:" << std::endl;
    std::cout << "dt3 before: " << dt3 << std::endl;
    dt3.apply( [&dt3](double& dd) -> DoubleType&
    {
            dd += 6.0;
            return dt3;
    } );;
    std::cout << "dt3 after: " << dt3 << std::endl;
    std::cout << "Calling DoubleType::apply() using a free function (adds 6.0) and void as return type:" << std::endl;
    std::cout << "dt3 before: " << dt3 << std::endl;
    dt3.apply(myDoubleFreeFunct);
    std::cout << "dt3 after: " << dt3 << std::endl;
    std::cout << "---------------------\n" << std::endl;

    std::cout << "Calling IntType::apply() using a lambda (adds 5) and IntType as return type:" << std::endl;
    std::cout << "it3 before: " << it3 << std::endl;
    it3.apply( [&it3](int& i) -> IntType&
    {
            i += 5;
            return it3;
    } );
    std::cout << "it3 after: " << it3 << std::endl;
    std::cout << "Calling IntType::apply() using a free function (adds 5) and void as return type:" << std::endl;
    std::cout << "it3 before: " << it3 << std::endl;
    it3.apply(myIntFreeFunct);
    std::cout << "it3 after: " << it3 << std::endl;
    std::cout << "---------------------\n" << std::endl;
}
*/

template<typename T>
void myNumericFreeFunct(T& t)
{
    t += static_cast<T>(7);
}


void part7()
{
    Numeric ft3(3.0f);
    Numeric dt3(4.0);
    Numeric it3(5);

    std::cout << "Calling Numeric<float>::apply() using a lambda (adds 7.0f) and Numeric<float> as return type:" << std::endl;
    std::cout << "ft3 before: " << ft3 << std::endl;

    {
        using Type = decltype(ft3)::Type;
        ft3.apply([&](Type& t) -> Numeric<float>&
            {
                t += 7.f;
                return ft3;
            });
    }

    std::cout << "ft3 after: " << ft3 << std::endl;
    std::cout << "Calling Numeric<float>::apply() twice using a free function (adds 7.0f) and void as return type:" << std::endl;
    std::cout << "ft3 before: " << ft3 << std::endl;
    ft3.apply(myNumericFreeFunct).apply(myNumericFreeFunct);
    std::cout << "ft3 after: " << ft3 << std::endl;
    std::cout << "---------------------\n" << std::endl;

    std::cout << "Calling Numeric<double>::apply() using a lambda (adds 6.0) and Numeric<double> as return type:" << std::endl;
    std::cout << "dt3 before: " << dt3 << std::endl;

    {
        using Type = decltype(dt3)::Type;
        dt3.apply([&](Type& t) -> Numeric<double>&
            {
                t += 6.0;
                return dt3;
            });
    }

    std::cout << "dt3 after: " << dt3 << std::endl;
    std::cout << "Calling Numeric<double>::apply() twice using a free function (adds 7.0) and void as return type:" << std::endl;
    std::cout << "dt3 before: " << dt3 << std::endl;
    dt3.apply(myNumericFreeFunct<double>).apply(myNumericFreeFunct<double>); // This calls the templated apply fcn
    std::cout << "dt3 after: " << dt3 << std::endl;
    std::cout << "---------------------\n" << std::endl;

    std::cout << "Calling Numeric<int>::apply() using a lambda (adds 5) and Numeric<int> as return type:" << std::endl;
    std::cout << "it3 before: " << it3 << std::endl;

    {
        using Type = decltype(it3)::Type;
        it3.apply([&](Type& t) -> Numeric<int>&
            {
                t += 5;
                return it3;
            });
    }
    std::cout << "it3 after: " << it3 << std::endl;
    std::cout << "Calling Numeric<int>::apply() twice using a free function (adds 7) and void as return type:" << std::endl;
    std::cout << "it3 before: " << it3 << std::endl;
    it3.apply(myNumericFreeFunct).apply(myNumericFreeFunct);
    std::cout << "it3 after: " << it3 << std::endl;
    std::cout << "---------------------\n" << std::endl;
}

int main()
{
    //testing instruction 0
    HeapA heapA;

    //assign heap primitives
    Numeric<float> ft(2.0f);
    Numeric<double> dt(2);
    Numeric<int> it(2);

    std::cout << "FloatType add result=" << (ft += 2.0f) << std::endl;
    std::cout << "FloatType subtract result=" << (ft -= 2.0f) << std::endl;
    std::cout << "FloatType multiply result=" << (ft *= 2.0f) << std::endl;
    std::cout << "FloatType divide result=" << (ft /= 16.0f) << std::endl << std::endl;

    std::cout << "DoubleType add result=" << (dt += 2.0) << std::endl;
    std::cout << "DoubleType subtract result=" << (dt -= 2.0) << std::endl;
    std::cout << "DoubleType multiply result=" << (dt *= 2.0) << std::endl;
    std::cout << "DoubleType divide result=" << (dt /= static_cast<double>(5.f)) << std::endl << std::endl;

    std::cout << "IntType add result=" << (it += 2) << std::endl;
    std::cout << "IntType subtract result=" << (it -= 2) << std::endl;
    std::cout << "IntType multiply result=" << (it *= 2) << std::endl;
    std::cout << "IntType divide result=" << (it /= 3) << std::endl << std::endl;
    it *= 1000;
    it /= 2;
    it -= 10;
    it += 100;
    std::cout << "Chain calculation = " << it << std::endl;

    // FloatType object instantiation and method tests
    // --------
    ft += 3.0f;
    ft *= 1.5f;
    ft /= 5.0f;
    std::cout << "New value of ft = (ft + 3.0f) * 1.5f / 5.0f = " << ft << std::endl;

    std::cout << "---------------------\n" << std::endl;

    // DoubleType/IntType object instantiation and method tests
    // --------
    std::cout << "Initial value of dt: " << dt << std::endl;
    std::cout << "Initial value of it: " << it << std::endl;
    // --------
    std::cout << "Use of function concatenation (mixed type arguments)" << std::endl;
    dt *= it;
    dt /= static_cast<double>(5.0f);
    dt += static_cast<double>(ft);
    std::cout << "New value of dt = (dt * it) / 5.0f + ft = " << dt << std::endl;

    std::cout << "---------------------\n" << std::endl;

    // Intercept division by 0
    // --------
    std::cout << "Intercept division by 0" << std::endl;

    std::cout << "New value of it = it / 0 = " << (it /= 0) << std::endl;

    std::cout << "New value of ft = ft / 0 = " << (ft /= 0) << std::endl;

    std::cout << "New value of dt = dt / 0 = " << (dt /= 0) << std::endl;

    std::cout << "---------------------\n" << std::endl;

    part3();

    part4();

    //part6();

    part7();

    std::cout << "good to go!\n";

    return 0;
}
