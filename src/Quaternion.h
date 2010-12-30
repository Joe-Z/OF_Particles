#ifndef QUATERNION_H_INCLUDED
#define QUATERNION_H_INCLUDED

#include "Vector.h"

#include <iostream>
#include <cmath>

class Quaternion {

private:
    double a;
    Vector b;

public:
    Quaternion() {
        a = 0;
    }
    
    Quaternion(double a, Vector b) {
        this->a = a;
        this->b = b;
    }
    
    Quaternion(double a, double x, double y, double z) {
        this->a = a;
        b = Vector(x, y, z);
    }
    
    void set(double a, Vector b) {
        this->a = a;
        this->b = b;
    }
    
    void print() {
         std::cout << a << " ";
         b.print();
    }
    
     Quaternion operator+(Quaternion q) {
        return Quaternion(
            a + q.a,
            b + q.b
        );
    }
    
    Quaternion operator-(Quaternion q) {
        return Quaternion(
            a - q.a,
            b - q.b
        );
    }
    
    Quaternion conj() {
        return Quaternion(
            a,
            b * -1
        );
    }
    
    double norm() {
        return sqrt(
            a * a + b.dot(b)
        );
    }
    
    Quaternion operator*(Quaternion q) {
        return Quaternion(
            a * q.a - b.x * q.b.x - b.y * q.b.y - b.z * q.b.z,
            a * q.b.x + b.x * q.a + b.y * q.b.z - b.z * q.b.y,
            a * q.b.y - b.x * q.b.z + b.y * q.a + b.z * q.b.x,
            a * q.b.z + b.x * q.b.y - b.y * q.b.x + b.z * q.a
        );
    }
    
    static Vector rotate(Vector vector, double phi, Vector axis) {
        axis = axis.toLength(sin(phi/2));
        
        Quaternion u(cos(phi/2), axis);
        Quaternion v(0, vector);
        
        v = u * v * u.conj();
        return v.b;
    }
};


#endif //QUATERNION_H_INCLUDED