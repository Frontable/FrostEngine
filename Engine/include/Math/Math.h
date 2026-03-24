





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

    T& operator[](size_t i)       { return data[i]; }
    const T& operator[](size_t i) const { return data[i]; }
};

// ----------------------
// vec2 specialization
// ----------------------
template<typename T>
struct vec<T,2>
{
    union
    {
        struct { T x, y; };
        struct { T r, g; };
        struct { T s, t; };
        T data[2];
    };

    vec() = default;
    vec(T x, T y) : x(x), y(y) {}

    T& operator[](size_t i)       { return data[i]; }
    const T& operator[](size_t i) const { return data[i]; }

    vec& operator+=(const vec& v) { x+=v.x; y+=v.y; return *this; }
    vec& operator-=(const vec& v) { x-=v.x; y-=v.y; return *this; }
    vec& operator*=(T s)          { x*=s; y*=s; return *this; }
};

// ----------------------
// vec3 specialization
// ----------------------
template<typename T>
struct vec<T,3>
{
    union
    {
        struct { T x, y, z; };
        struct { T r, g, b; };
        struct { T s, t, k; };
        T data[3];
    };

    vec() = default;
    vec(T x, T y, T z = T{}) : x(x), y(y), z(z) {}

    T& operator[](size_t i)       { return data[i]; }
    const T& operator[](size_t i) const { return data[i]; }

    vec& operator+=(const vec& v) { x+=v.x; y+=v.y; z+=v.z; return *this; }
    vec& operator-=(const vec& v) { x-=v.x; y-=v.y; z-=v.z; return *this; }
    vec& operator*=(T s)          { x*=s; y*=s; z*=s; return *this; }
};

// ----------------------
// vec4 specialization
// ----------------------
template<typename T>
struct vec<T,4>
{
    union
    {
        struct { T x, y, z, w; };
        struct { T r, g, b, a; };
        struct { T s, t, k, p; };
        T data[4];
    };

    vec() = default;
    vec(T x, T y, T z = T{}, T w = T{}) : x(x), y(y), z(z), w(w) {}

    T& operator[](size_t i)       { return data[i]; }
    const T& operator[](size_t i) const { return data[i]; }

    vec& operator+=(const vec& v) { x+=v.x; y+=v.y; z+=v.z; w+=v.w; return *this; }
    vec& operator-=(const vec& v) { x-=v.x; y-=v.y; z-=v.z; w-=v.w; return *this; }
    vec& operator*=(T s)          { x*=s; y*=s; z*=s; w*=s; return *this; }
};

// ======================================================
// VECTOR HELPERS
// ======================================================
template<typename T, size_t S>
T magnitude(const vec<T,S>& v)
{
    T sum{};
    for (size_t i = 0; i < S; ++i)
        sum += v.data[i] * v.data[i];
    return std::sqrt(sum);
}

template<typename T, size_t S>
vec<T,S> normalize(const vec<T,S>& v)
{
    T m = magnitude(v);
    vec<T,S> r{};
    if (m == T{}) return r;
    for (size_t i = 0; i < S; ++i)
        r.data[i] = v.data[i] / m;
    return r;
}

// ======================================================
// MATRIX (COLUMN-MAJOR)
// data[column][row]
// column vectors: v' = M * v
// ======================================================
template<typename T, size_t C, size_t R>
struct mat
{
    T data[C][R]{};

    mat() = default;

    explicit mat(T diag)
    {
        for (size_t c = 0; c < C; ++c)
            for (size_t r = 0; r < R; ++r)
                data[c][r] = (c == r ? diag : T{});
    }

    T* operator[](size_t c)             { return data[c]; }
    const T* operator[](size_t c) const { return data[c]; }

    T* dataPtr()             { return &data[0][0]; }
    const T* dataPtr() const { return &data[0][0]; }

    // Matrix * Matrix (column-major)
    mat operator*(const mat& rhs) const
    {
        mat result(T{});
        for (size_t c = 0; c < C; ++c)
            for (size_t r = 0; r < R; ++r)
                for (size_t k = 0; k < C; ++k)
                    result.data[c][r] += data[k][r] * rhs.data[c][k];
        return result;
    }

    mat& operator=(const mat& rhs) const
    {

        mat result(T{});
        for (size_t c = 0; c < C; ++c)
            for (size_t r = 0; r < R; ++r)
                result.data[c][r] = rhs.data[c][r];
        return result;
    }

    void print() const
    {
        for (size_t r = 0; r < R; ++r)
        {
            std::cout << "{ ";
            for (size_t c = 0; c < C; ++c)
                std::cout << data[c][r] << " ";
            std::cout << "}\n";
        }
    }
};

// ======================================================
// TYPEDEFS
// ======================================================
using vec2 = vec<float,2>;
using vec3 = vec<float,3>;
using vec4 = vec<float,4>;

using mat4 = mat<float,4,4>;

// ======================================================
// MATRIX * VECTOR
// ======================================================
inline vec4 operator*(const mat4& m, const vec4& v)
{
    vec4 r{};
    for (int row = 0; row < 4; ++row)
        for (int col = 0; col < 4; ++col)
            r[row] += m[col][row] * v[col];
    return r;
}

// ======================================================
// TRANSFORMS (COLUMN-MAJOR)
// ======================================================
inline mat4 translate(const vec3& v)
{
    mat4 m(1.0f);
    m[3][0] = v.x;
    m[3][1] = v.y;
    m[3][2] = v.z;
    return m;
}

inline mat4 scale(const vec3& s)
{
    mat4 m(1.0f);
    m[0][0] = s.x;
    m[1][1] = s.y;
    m[2][2] = s.z;
    return m;
}

inline mat4 rotateZ(float radians)
{
    mat4 m(1.0f);
    float c = std::cos(radians);
    float s = std::sin(radians);

    m[0][0] =  c;
    m[1][0] =  s;
    m[0][1] = -s;
    m[1][1] =  c;
    return m;
}

inline mat4 ortho(float l, float r, float b, float t)
{
    mat4 m(1.0f);
    m[0][0] =  2.0f / (r - l);
    m[1][1] =  2.0f / (t - b);
    m[2][2] = -1.0f;
    m[3][0] = -(r + l) / (r - l);
    m[3][1] = -(t + b) / (t - b);
    return m;
}
