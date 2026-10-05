#pragma once

#include <iostream>

class vect2 {
    private:
        int _x;
        int _y;
    public:
        vect2();
        vect2(int x, int y);
        vect2(const vect2& other);
        vect2& operator=(const vect2& other);
        ~vect2();

    // Accesssors 
    int &operator[](int idx);
    int operator[](int idx) const;

    // Comparaisons
    bool operator==(const vect2& other);
    bool operator!=(const vect2& other);

    // Maths
    vect2 operator++(int);
    vect2&  operator++();
    vect2 operator--(int);
    vect2&  operator--();

    vect2& operator+=(const vect2& other);
    vect2& operator-=(const vect2& other);
    
    vect2 operator+(const vect2& other) const;
    vect2 operator-(const vect2& other) const;

    vect2  operator*(int n) const;
    vect2& operator*=(int n);

    // Negative switch
    vect2 operator-() const;
    
};

vect2 operator*(int n, const vect2& other);

// Ostream overload
std::ostream& operator<<(std::ostream& os, const vect2& other);