#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <iostream>
#include <cmath>
#include <cassert>

#ifndef PI
#define PI (2*acos(0))
#endif

class Vector {
public:
    double x, y, z;
    
    Vector() {
        x = y = z = 0;
    }
    
    Vector(double x, double y, double z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    void set(double x, double y, double z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    
    void print() {
         std::cout << "(" << x << ", " << y << ", " << z << ")\n";
    }

    bool operator==(Vector v) {
        if (x == v.x && y == v.y && z == v.z)
            return true;
        else 
            return false;
    }
    
    Vector operator+(Vector v) {
        return Vector(x + v.x, y + v.y, z + v.z);
    }
    
    Vector operator-(Vector v) {
        return Vector(x - v.x, y - v.y, z - v.z);
    }
    
    Vector operator*(double k) {
        return Vector(x * k, y * k, z * k);
    }
    
    Vector operator/(double k) {
        assert(k);
        return Vector(x / k, y / k, z / k);
    }
    
    double dot(Vector v) {
        return x * v.x + y * v.y + z * v.z;
    }
    
    double norm() {
        return sqrt(dot(*this));
    }
    
    Vector cross(Vector v) {
        return Vector(
            y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x
        );
    }
    
    double angle(Vector v) {
        return acos(dot(v)/(norm()*v.norm()));
    }
    
    Vector toLength(double l) {
        return ((*this)/norm()) *l;
    }
    
    double distance(Vector v) {
        return ((*this)-v).norm();
    }
    
    //double distanceToLine(Vector a, Vector b) {
    //    assert(b.x || b.y || b.z);
    //    double t = (b.x * (x - a.x) + b.y * (y - a.y) + b.z * (z - a.z)) / (b.x * b.x + b.y * b.y + b.z * b.z);
    //    Vector c(a.x + b.x * t - x, a.y + b.y * t - y, a.z + b.z * t - z);
    //    return c.norm();
    //}
    //
    //static Vector projectionVector(Vector a, Vector b) {
    //    return mul(b, dot(a, b) / dot(b, b));
    //}
    //
    //static double maxValue(Vector v) {
    //    double x = v.x < 0 ? -v.x : v.x;
    //    double y = v.y < 0 ? -v.y : v.y;
    //    double z = v.z < 0 ? -v.z : v.z;            
    //    return x > y ? (x > z ? x : z) : (y > z ? y : z);
    //}
};

#endif //VECTOR_H_INCLUDED