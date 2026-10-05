#include "vect2.hpp"

vect2::vect2() : _x(0), _y(0){};
vect2::vect2(int x, int y) : _x(x), _y(y){};
vect2::vect2(const vect2& other) : _x(other._x), _y(other._y){};
vect2& vect2::operator=(const vect2& other){
    if (this != &other){
        this->_x = other._x;
        this->_y = other._y;
    }
    return (*this);
}
vect2::~vect2(){};

// Accesssors 
int vect2::operator[](int idx) const {
    return (idx == 0 ? this->_x : this->_y);
}

int &vect2::operator[](int idx){
    return (idx == 0 ? this->_x : this->_y);
}

bool vect2::operator==(const vect2& other){
    return (this->_x == other._x && this->_y == other._y ? true : false);
}

bool vect2::operator!=(const vect2& other){
    return (this->_x != other._x || this->_y != other._y ? true : false);
}

vect2 vect2::operator++(int){
    vect2 obj = *this;
    this->_x++;
    this->_y++;
    return (obj);
}

vect2& vect2::operator++(){
    this->_x++;
    this->_y++;
    return (*this);
}

vect2 vect2::operator--(int){
    vect2 obj = *this;
    this->_x--;
    this->_y--;
    return (obj);
}

vect2& vect2::operator--(){
    this->_x--;
    this->_y--;
    return (*this);
}

vect2& vect2::operator+=(const vect2& other){
    this->_x += other._x;
    this->_y += other._y;
    return (*this);
}

vect2& vect2::operator-=(const vect2& other){
    this->_x -= other._x;
    this->_y -= other._y;
    return (*this);
}

vect2 vect2::operator+(const vect2& other) const {
    return vect2(this->_x + other._x, this->_y + other._y);
}

vect2 vect2::operator-(const vect2& other) const {
    return vect2(this->_x - other._x, this->_y - other._y);
}

vect2 vect2::operator*(int n) const {
    return vect2(this->_x * n, this->_y * n);
}

vect2& vect2::operator*=(int n){
    this->_x *= n;
    this->_y *= n;
    return (*this);
}

vect2 vect2::operator-() const {
    return vect2(-_x, -_y);
}

vect2 operator*(int n, const vect2& other){
    return vect2(other * n);
}

std::ostream& operator<<(std::ostream& os, const vect2& v){
    os << "{" << v[0] << ", " << v[1] << "}";
    return (os);
}