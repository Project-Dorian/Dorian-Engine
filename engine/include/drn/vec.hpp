#ifndef DORIAN_VECTORS
#define DORIAN_VECTORS

#include <cmath>

// General macro for a zero vector. Works with any size vector
#define ZERO_VECTOR {}

namespace drn {

    // `struct drn::Vec2<T> {T x, T y}`
    // A basic template structure for 2D vectors in C++
    // $$\vec{v}=\langle x, y \rangle,\space x, y \in \mathbb{T}$$
    template<class T>
    struct Vec2 {
        T X = 0;
        T Y = 0;

        // returns $\vec{v}+\vec{u}$
        Vec2<T> operator+(Vec2<T> u) {return {X+u.X, Y+u.Y};};
        // returns $\vec{v}-\vec{u}$
        Vec2<T> operator-(Vec2<T> u) {return {X-u.X, Y-u.Y};};
        
        // returns $a\vec{v}$
        Vec2<T> operator*(T a) {return {X*a, Y*a};};
        // returns the dot product of $\vec{v}\cdot \vec{u}$
        T Dot(Vec2<T> u) {return X*u.X + Y*u.Y;};
        // returns the cross product of $\vec{v}\times \vec{u}$ as a scalar
        T Cross(Vec2<T> u) {return X*u.Y - Y*u.X;};

        // returns $\mid \vec{v} \mid$
        T length() {return sqrt(X*X+Y*Y);};
    };

    // `struct drn::Vec3<T> {T x, T y, T z}`
    // A basic template structure for 3D vectors in C++
    // $$\vec{v}=\langle x, y, z \rangle,\space x, y, z \in \mathbb{T}$$
    template<class T>
    struct Vec3 {
        T X = 0;
        T Y = 0;
        T Z = 0;

        // returns $\vec{v}+\vec{u}$
        Vec3<T> operator+(Vec3<T> a) {return {X+a.X, Y+a.Y, Z+a.Z};};
        // returns $\vec{v}-\vec{u}$
        Vec3<T> operator-(Vec3<T> a) {return {X-a.X, Y-a.Y, Z-a.Z};};
        
        // returns $a\vec{v}$
        Vec3<T> operator*(T a) {return {X*a, Y*a, Z*a};};
        // returns the dot product of $\vec{v}\cdot \vec{u}$
        T Dot(Vec3<T> u) {return X*u.X + Y*u.Y + Z*u.Z;};
        // returns the cross product of $\vec{v}\times \vec{u}$ as a vector
        Vec3<T> Cross(Vec3<T> u) {return {Y*u.Z-Z*u.Y, -(X*u.Z-Z*u.X), X*u.Y-Y*u.X};};

        // returns $\mid \vec{v} \mid$
        T length() {return sqrt(X*X+Y*Y+Z*Z);};

        Vec3<T> rotate(Vec3<T> a) {
            return {
                cosf(a.Y)*(sinf(a.Z)*Y+cosf(a.Z)*X)-sinf(a.Y)*Z,
                sinf(a.X)*(cosf(a.Y)*Z+sinf(a.Y)*(sinf(a.Z)*Y+cosf(a.Z)*X))+cosf(a.X)*(cosf(a.Z)*Y-sinf(a.Z)*X),
                sinf(a.X)*(cosf(a.Y)*Z+sinf(a.Y)*(sinf(a.Z)*Y+cosf(a.Z)*X))-sinf(a.X)*(cosf(a.Z)*Y-sinf(a.Z)*X),
            };
        };
    };
}

#endif
