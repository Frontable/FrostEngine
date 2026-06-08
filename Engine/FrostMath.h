#pragma once
#include <cmath>
#include <iostream>

// ======================================================
// CONSTANTS
// ======================================================
constexpr float PI = 3.14159265359f;

// ======================================================
// VECTOR
// ======================================================
template<typename T, size_t S>
struct vec
{
    T data[S]{};

    T& operator[](size_t i) { return data[i]; }
    const T& operator[](size_t i) const { return data[i]; }
};

// ----------------------
// vec2 specialization
// ----------------------
template<typename T>
struct vec<T, 2>
{
    union
    {
        struct { T x, y; };
        struct { T r, g; };
        struct { T s, t; };
        T data[2];
    };

    vec() : x(T{}), y(T{}) {}
    vec(T value) : x(value), y(value) {}
    vec(T _x, T _y) : x(_x), y(_y) {}

    T& operator[](size_t i) { return data[i]; }
    const T& operator[](size_t i) const { return data[i]; }

    vec& operator+=(const vec& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    vec& operator-=(const vec& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    vec& operator*=(T scalar)
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }

};

// ----------------------
// vec3 specialization
// ----------------------
template<typename T>
struct vec<T, 3>
{
    union
    {
        struct { T x, y, z; };
        struct { T r, g, b; };
        struct { T s, t, p; };
        T data[3];
    };

    vec() : x(T{}), y(T{}), z(T{}) {}
    vec(T value) : x(value), y(value), z(value) {}
    vec(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}

    T& operator[](size_t i) { return data[i]; }
    const T& operator[](size_t i) const { return data[i]; }

    vec& operator+=(const vec& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    vec& operator-=(const vec& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }

    vec& operator*=(T scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }
};

// ----------------------
// vec4 specialization
// ----------------------
template<typename T>
struct vec<T, 4>
{
    union
    {
        struct { T x, y, z, w; };
        struct { T r, g, b, a; };
        struct { T s, t, p, q; };
        T data[4];
    };

    vec() : x(T{}), y(T{}), z(T{}), w(T{}) {}
    vec(T value) : x(value), y(value), z(value), w(value) {}
    vec(T _x, T _y, T _z, T _w) : x(_x), y(_y), z(_z), w(_w) {}

    T& operator[](size_t i) { return data[i]; }
    const T& operator[](size_t i) const { return data[i]; }

    vec& operator+=(const vec& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        w += rhs.w;
        return *this;
    }

    vec& operator-=(const vec& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        w -= rhs.w;
        return *this;
    }

    vec& operator*=(T scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        w *= scalar;
        return *this;
    }
};

// ======================================================
// VECTOR HELPERS
// ======================================================
template<typename T, size_t S>
T magnitude(const vec<T, S>& v)
{
    T sum{};
    for (size_t i = 0; i < S; ++i)
        sum += v[i] * v[i];
    return std::sqrt(sum);
}

template<typename T, size_t S>
vec<T, S> normalize(const vec<T, S>& v)
{
    T mag = magnitude(v);
    vec<T, S> result{};

    if (mag == T{})
        return result;

    for (size_t i = 0; i < S; ++i)
        result[i] = v[i] / mag;

    return result;
}

// ======================================================
// MATRIX (COLUMN-MAJOR)
// data[column][row]
// Compatible with OpenGL when sent with GL_FALSE
// ======================================================
template<typename T, size_t C, size_t R>
struct mat
{
    T data[C][R]{};

    mat() = default;

    explicit mat(T diagonal)
    {
        for (size_t c = 0; c < C; ++c)
        {
            for (size_t r = 0; r < R; ++r)
            {
                data[c][r] = (c == r) ? diagonal : T{};
            }
        }
    }

    T* operator[](size_t column) { return data[column]; }
    const T* operator[](size_t column) const { return data[column]; }

    T* dataPtr() { return &data[0][0]; }
    const T* dataPtr() const { return &data[0][0]; }

    void print() const
    {
        for (size_t row = 0; row < R; ++row)
        {
            std::cout << "{ ";
            for (size_t col = 0; col < C; ++col)
            {
                std::cout << data[col][row] << " ";
            }
            std::cout << "}\n";
        }
    }
};

// ======================================================
// TYPEDEFS
// ======================================================
using vec2 = vec<float, 2>;
using vec3 = vec<float, 3>;
using vec4 = vec<float, 4>;
using mat4 = mat<float, 4, 4>;

// ======================================================
// MATRIX * MATRIX
// result(col,row) = sum(lhs(k,row) * rhs(col,k))
// ======================================================
inline mat4 operator*(const mat4& lhs, const mat4& rhs)
{
    mat4 result(0.0f);

    for (int col = 0; col < 4; ++col)
    {
        for (int row = 0; row < 4; ++row)
        {
            for (int k = 0; k < 4; ++k)
            {
                result[col][row] += lhs[k][row] * rhs[col][k];
            }
        }
    }

    return result;
}

// ======================================================
// MATRIX * VECTOR
// ======================================================
inline vec4 operator*(const mat4& m, const vec4& v)
{
    vec4 result{0.f, 0.f, 0.f, 0.f};

    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 4; ++col)
        {
            result[row] += m[col][row] * v[col];
        }
    }

    return result;
}

inline vec4 operator*(const mat4& m, const vec2& v)
{
    vec4 vec{v.x, v.y, 0, 1};
    vec4 result;

    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 4; ++col)
        {
            result[row] += m[col][row] * vec[col];
        }
    }

    return result;
}

inline vec2 operator*(const vec2& v, const float& s)
{
    return vec2{v.x * s, v.y * s};
}

inline vec3 operator*(const vec3& v, const float& s)
{
    return vec3{v.x * s, v.y * s, v.z * s};
}

inline vec2 operator+(const vec2& l, const vec2& r)
{
    return vec2{{l.x + r.x}, {l.y + r.y}};
}

// ======================================================
// TRANSFORMS
// ======================================================
inline mat4 translate(const vec3& t)
{
    mat4 result(1.0f);
    result[3][0] = t.x;
    result[3][1] = t.y;
    result[3][2] = t.z;
    return result;
}

inline mat4 scale(const vec3& s)
{
    mat4 result(1.0f);
    result[0][0] = s.x;
    result[1][1] = s.y;
    result[2][2] = s.z;
    return result;
}

inline mat4 rotateZ(float radians)
{
    mat4 result(1.0f);
    float c = std::cos(radians);
    float s = std::sin(radians);

    result[0][0] =  c;
    result[1][0] = -s;
    result[0][1] =  s;
    result[1][1] =  c;

    return result;
}

inline mat4 ortho(float left, float right, float bottom, float top)
{
    mat4 result(1.0f);

    result[0][0] =  2.0f / (right - left);
    result[1][1] =  2.0f / (top - bottom);
    result[2][2] = -1.0f;

    result[3][0] = -(right + left) / (right - left);
    result[3][1] = -(top + bottom) / (top - bottom);
    result[3][2] = 0.0f;

    return result;
}

