#pragma once
#include <iostream>
#include <random>
#include <time.h>

typedef unsigned int uint;

float absl(float x);

float cpysign(float x, float y);

float ranf();

float ranpf();

bool isN(float x);

bool is0(float x);

float sign(float x);

struct ct {
	static constexpr float intmax2 = 2.f / INT_MAX;
	static constexpr float intmax  = 1.f / INT_MAX;
	inline static std::mt19937 m = std::mt19937(time(0));
	static constexpr float eps = FLT_EPSILON;
	static constexpr float e = 2.7182818284590452353f;
	static constexpr float tau = 6.2831853071795864769f;
	static constexpr float pi = 3.1415926535897932384f;
	static constexpr float pi_2 = 1.5707963267948966192f;
	static constexpr float pi_3 = 1.0471975511965977461f;
	static constexpr float pi_4 = 0.7853981633974483096f;
	static constexpr float pi_5 = 0.6283185307179586476f;
	static constexpr float pi_6 = 0.5235987755982988730f;
	static constexpr float pi_9 = 0.3490658503988659153f;
	static constexpr float pi_10 = 0.3141592653589793238f;
	static constexpr float pi_12 = 0.2617993877991494365f;
	static constexpr float pi_15 = 0.2094395102393195492f;
	static constexpr float pi_18 = 0.1745329251994329576f;
	static constexpr float pi_20 = 0.1570796326794896619f;
	static constexpr float pi_30 = 0.1047197551196597746f;
	static constexpr float pi_36 = 0.0872664625997164788f;
	static constexpr float pi_45 = 0.0698131700797731830f;
	static constexpr float pi_60 = 0.0523598775598298873f;
	static constexpr float pi_90 = 0.0349065850398865915f;
	static constexpr float rad = 0.0174532925199432957f;
	static constexpr float deg = 57.295779513082320876f;
	static constexpr float sqrt2 = 1.4142135623730950488f;
	static constexpr float sqrt3 = 1.7320508075688772935f;
	static constexpr float sqrt5 = 2.2360679774997896964f;
	static constexpr float sqrt10 = 3.1622776601683793319f;
	static constexpr float half = 0.5f;
	static constexpr float _3half = 1.5f;
};

class xfstr {
	size_t size_, cap_;
	char* data_;
	char* newblock(size_t n) const;
	char* copy(size_t n) const;
	void alloc();
	void alloc(size_t n);
	void range(char*& i, char*& j) const;
	static bool NaN(char);
	static bool N(char);
	static bool WS(char);
	static bool NWS(char);
	static bool dot(char);
public:
	xfstr();
	xfstr(size_t n);
	xfstr(const char*);
	xfstr(const xfstr&);
	xfstr(xfstr&&) noexcept;
	xfstr& operator = (const xfstr&);
	xfstr& operator = (xfstr&&) noexcept;
	~xfstr();
	xfstr& operator +=(char);
	xfstr& operator +=(const char*);
	xfstr& operator +=(const xfstr&);
	xfstr  operator +(char) const;
	xfstr  operator +(const char*) const;
	xfstr  operator +(const xfstr&) const;
	bool operator == (const char*) const;
	bool operator != (const char*) const;
	bool operator == (const xfstr&) const;
	bool operator != (const xfstr&) const;
	xfstr& operator <<(int n);
	xfstr& operator <<(uint n);
	xfstr& operator << (long);
	xfstr& operator << (unsigned long);
	xfstr& operator << (float);
	xfstr& operator << (double);
	xfstr& operator >> (long& n);
	xfstr& operator >> (unsigned long&);
	xfstr& operator>>(int& n);
	xfstr& operator>>(unsigned int& n);
	xfstr& operator >> (float&);
	xfstr& operator >> (double&);
	std::istream& getline(std::istream&, char = '\n');
	void erase(char*, char*);
	void erase(char* i);
	const char* c_str();
	char& operator[](size_t);
	char operator[](size_t) const;
	char* find(char, size_t = 1) const;
	char* findif(bool (*f)(char), size_t = 1) const;
	char* find(char, char*, char*, size_t = 1) const;
	char* findif(bool (*f)(char), char*, char*, size_t = 1) const;
	xfstr substr(size_t, size_t) const;
	xfstr substr(size_t) const;
	xfstr map(char(*f)(char)) const;
	void clear();
	bool empty() const;
	size_t size() const;
	size_t cap() const;
	char* begin() const;
	char* end() const;
	char* rbegin() const;
	char* rend() const;
	char* data() const;
	char* begin();
	char* end();
	char* rbegin();
	char* rend();
	char* data();
};

std::ostream& operator << (std::ostream& s, const xfstr& str);
std::istream& operator >> (std::istream& s, xfstr& str);
xfstr operator + (const char* c, const xfstr& s);

template<class c>
class xfvec {
	static constexpr size_t byte = sizeof(c);
	static constexpr bool destructible = !std::is_trivially_destructible<c>::value;
	size_t size_, cap_;
	c* data_;
	c* newblock(size_t n) const;
	void destruct();
	void destruct(c*, c*);
	c* copy(size_t n) const;
	void alloc();
	void alloc(size_t n);
	void range(c*& i, c*& j);
public:
	xfvec();
	xfvec(size_t n);
	xfvec(const xfvec&);
	xfvec(xfvec&&);
	xfvec(std::initializer_list<c>);
	xfvec& operator = (const xfvec&);
	xfvec& operator = (xfvec&&);
	~xfvec();
	void push(const c& item);
	void push(c&& item);
	template<class...Cs>
	void emplace(const Cs&... cs);
	template<class...Cs>
	void emplace(Cs&&... cs);
	void erase(c*, c*);
	void erase(c*);
	c* insert(c* pos, const c& item);
	c* insert(c*, c&&);
	void reserve(size_t);
	void resize(size_t);
	c& operator[](size_t);
	c& operator[](size_t) const;
	void sort();
	c* find(const c&, size_t = 1) const;
	c* findif(bool (*f)(c), size_t = 1) const;
	c* findif(bool (*f)(const c&), size_t = 1) const;
	c* find(const c&, c*, c*, size_t = 1) const;
	c* findif(bool (*f)(c), c*, c*, size_t = 1) const;
	c* findif(bool (*f)(const c&), c*, c*, size_t = 1) const;
	xfvec subvec(c*, c*) const;
	xfvec map(c(*f)(c)) const;
	xfvec map(c(*f)(const c&)) const;
	template<class c2>
	xfvec<c2> map(c2(*f)(c)) const;
	template<class c2>
	xfvec<c2> map(c2(*f)(const c&)) const;
	void clear();
	bool empty() const;
	size_t size() const;
	size_t cap() const;
	c* begin() const;
	c* end() const;
	c* rbegin() const;
	c* rend() const;
	c* data() const;
	c& front() const;
	c& back() const;
	c* begin();
	c* end();
	c* rbegin();
	c* rend();
	c* data();
	c& front();
	c& back();
};

template<class T>
struct complex {
	union {
		struct { T x, y; };
		T data[2];
	};
	complex() {}
	complex(T x, T y) : data{ x, y } {}
	complex(T x) : data{ x, 0 } {}
	T phase() const;
	T len2() const;
	T len() const;
	complex operator -() const;
	complex operator ~() const;
	complex& operator +=(const complex&);
	complex& operator -=(const complex&);
	complex  operator + (const complex&) const;
	complex  operator - (const complex&) const;
	complex& operator +=(T);
	complex& operator -=(T);
	complex& operator *=(T);
	complex& operator /=(T);
	complex  operator + (T) const;
	complex  operator - (T) const;
	complex  operator * (T) const;
	complex  operator / (T) const;
	complex  operator * (const complex&) const;
	complex  operator / (const complex&) const;
	complex& operator *=(const complex&);
	complex& operator /=(const complex&);
};

template<class key, class val>
class xfmap;

template<class key, class val>
struct xfpair {
	key k;
	val v;
	xfpair();
	xfpair(const key& k);
	xfpair(const key& k, const val& v);
	xfpair(const xfpair& p);
	xfpair& operator = (const xfpair& p);
	xfpair(xfpair&& p);
	xfpair& operator = (xfpair&& p);
	bool operator > (const xfpair& p) const;
	bool operator < (const xfpair& p) const;
	bool operator ==(const xfpair& p) const;
	bool operator <=(const xfpair& p) const;
	bool operator >=(const xfpair& p) const;
	bool operator !=(const xfpair& p) const;
};

template<class key, class val>
class vref {
	friend class xfmap<key, val>;
	inline static const val val0 = val();
	inline static xfpair<key, val> *i, *j;
	key k;
	xfvec<xfpair<key, val>>& data;
	vref(const key&, xfvec<xfpair<key, val>>&);
public:
	val& operator = (const val&);
	val& operator += (const val&);
	val& operator -= (const val&);
	val& operator *= (const val&);
	val& operator /= (const val&);
	operator const val& () const;
};

template<class key, class val>
class xfmap {
	xfvec<xfpair<key, val>> data;
public:
	xfmap();
	xfmap(const xfmap&);
	xfmap(xfmap&&);
	xfmap& operator = (const xfmap&);
	xfmap& operator = (xfmap&&);
	xfpair<key, val>* insert(const key&);
	xfpair<key, val>* insert(const key&, const val&);
	val* find(const key& k);
	val* find(const key& k) const;
	vref<key, val> operator[](const key&);
	const val& operator[](const key&) const;
	xfpair<key, val>* begin() const;
	xfpair<key, val>* end() const;
	xfpair<key, val>* rbegin() const;
	xfpair<key, val>* rend() const;
	bool empty() const;
	size_t size() const;
	void clear();
};

template<class T>
class xfpoly {
	xfmap<int, T> c;
	T power(const T&, int);
public:
	xfpoly();
	xfpoly(const T& x);
	template<class...Ts>
	xfpoly(const Ts&...);
	xfpoly(const xfpoly&);
	xfpoly(xfpoly&&);
	vref<int, T> operator [] (size_t i);
	T  operator [] (size_t i) const;
	xfpoly& operator = (const xfpoly&);
	xfpoly& operator = (xfpoly&&);
	xfpoly& operator +=(const xfpoly&);
	xfpoly& operator -=(const xfpoly&);
	xfpoly  operator + (const xfpoly&);
	xfpoly  operator - (const xfpoly&);
	xfpoly  operator * (const xfpoly&);
	xfpoly& operator *=(const xfpoly&);
	xfpoly divide(const T&);
	void resize(size_t);
	int degree() const;
	xfpoly derivative() const;
	T discriminant() const;
	T operator()(const T&);
	xfvec<T> roots();
	T root1();
	const xfmap<int, T>& coeffs() const;
};
template<int...> struct base;
template<int...> struct swizz;
template<int...> struct vec;
template<class> struct t_vec2;
template<class> struct t_vec3;
template<class> struct t_vec4;

template<template<int...> class V, int h, int... t>
struct type_proxy : type_proxy<V, h - 1, h - 1, t...>
{
};

template<template<int...> class V, int...t>
struct type_proxy <V, 0, t...>
{
	using type = V<t...>;

	template<int n>
	struct mul
	{
		using type = V<n * t...>;
	};
	template<int n>
	struct add
	{
		using type = V<n + t...>;
	};
};

template<int...x>
struct vect
{
	using type = typename type_proxy<vec, sizeof...(x)>::type;
};

template<int n>
using dvec = typename type_proxy<swizz, n>::template mul<n + 1>::type;
template<int n>
using cvec = typename type_proxy<swizz, n>::template mul<n>::type;

using vec2 = vec<0, 1>;
using vec3 = vec<0, 1, 2>;
using vec4 = vec<0, 1, 2, 3>;
using ivec2 = t_vec2<int>;
using ivec3 = t_vec3<int>;
using ivec4 = t_vec4<int>;
using uvec2 = t_vec2<uint>;
using uvec3 = t_vec3<uint>;
using uvec4 = t_vec4<uint>;
using dvec2 = t_vec2<double>;
using dvec3 = t_vec3<double>;
using dvec4 = t_vec4<double>;
template<int...x>
struct alignas(sizeof(float)) base {
	operator typename vect<x...>::type() const;
	typename vect<x...>::type operator -() const;
	swizz<x...>& operator = (const base & v);
	template<int ...y>	swizz<x...>& operator =  (const base<y...> & v);
	template<int ...y>	swizz<x...>& operator += (const base<y...> & v);
	template<int ...y>	swizz<x...>& operator -= (const base<y...> & v);
	template<int ...y>	swizz<x...>& operator *= (const base<y...> & v);
	template<int ...y>	swizz<x...>& operator /= (const base<y...> & v);

	template<int ...y>	typename vect<x...>::type operator + (const base<y...> & v) const;
	template<int ...y>	typename vect<x...>::type operator - (const base<y...> & v) const;
	template<int ...y>	typename vect<x...>::type operator * (const base<y...> & v) const;
	template<int ...y>	typename vect<x...>::type operator / (const base<y...> & v) const;

	swizz<x...>& operator =  (float n);
	swizz<x...>& operator += (float n);
	swizz<x...>& operator -= (float n);
	swizz<x...>& operator *= (float n);
	swizz<x...>& operator /= (float n);

	typename vect<x...>::type operator + (float n) const;
	typename vect<x...>::type operator - (float n) const;
	typename vect<x...>::type operator * (float n) const;
	typename vect<x...>::type operator / (float n) const;
	

	template<int ...y> float dot(const base<y...> & v) const;
	template<int ...y> float operator ^ (const base<y...> & v) const;

	typename vect<x...>::type norm() const;
	swizz<x...>& xnorm();
	float len() const;
	float len2() const;

	swizz<x...>& operator()() { return *(swizz<x...>*)this; }
	typename vect<x...>::type copy() const;
};

template<int...x>
std::ostream& operator << (std::ostream&, const base<x...>& v);

template<int...x>
struct swizz : base<x...>
{
	using base<x...>::operator=;
};

template <int x>
struct alignas(sizeof(float)) swizz<x>
{
	float& operator =(float f);
	operator float& ();
	operator float() const;
};

template<int x, int y>
struct swizz<x, y> : base<x, y> {
	using base<x, y>::operator=;
	union {
		base<x, y> xy;
		base<y, x> yx;
		swizz<x> x;
		swizz<y> y;
	};
};

template<int x, int y, int z>
struct swizz<x, y, z> : base<x, y, z> {
	using base<x, y, z>::operator=;
	union {
		base<x, y> xy;
		base<x, z> xz;
		base<y, x> yx;
		base<y, z> yz;
		base<z, x> zx;
		base<z, y> zy;
		base<x, y, z> xyz;
		base<x, z, y> xzy;
		base<y, x, z> yxz;
		base<y, z, x> yzx;
		base<z, x, y> zxy;
		base<z, y, x> zyx;
		swizz<x> x;
		swizz<y> y;
		swizz<z> z;
	};
};

template<int x, int y, int z, int w>
struct swizz<x, y, z, w> : base<x, y, z, w> {
	using base<x, y, z, w>::operator=;
	union {
		base<x, y> xy;
		base<x, z> xz;
		base<x, w> xw;
		base<y, x> yx;
		base<y, z> yz;
		base<y, w> yw;
		base<z, x> zx;
		base<z, y> zy;
		base<z, w> zw;
		base<w, x> wx;
		base<w, y> wy;
		base<w, z> wz;
		base<x, y, z> xyz;
		base<x, y, w> xyw;
		base<x, z, y> xzy;
		base<x, z, w> xzw;
		base<x, w, y> xwy;
		base<x, w, z> xwz;
		base<y, x, z> yxz;
		base<y, x, w> yxw;
		base<y, z, x> yzx;
		base<y, z, w> yzw;
		base<y, w, x> ywx;
		base<y, w, z> ywz;
		base<z, x, y> zxy;
		base<z, x, w> zxw;
		base<z, y, x> zyx;
		base<z, y, w> zyw;
		base<z, w, x> zwx;
		base<z, w, y> zwy;
		base<w, x, y> wxy;
		base<w, x, z> wxz;
		base<w, y, x> wyx;
		base<w, y, z> wyz;
		base<w, z, x> wzx;
		base<w, z, y> wzy;
		base<x, y, z, w> xyzw;
		base<x, y, w, z> xywz;
		base<x, z, y, w> xzyw;
		base<x, z, w, y> xzwy;
		base<x, w, y, z> xwyz;
		base<x, w, z, y> xwzy;
		base<y, x, z, w> yxzw;
		base<y, x, w, z> yxwz;
		base<y, z, x, w> yzxw;
		base<y, z, w, x> yzwx;
		base<y, w, x, z> ywxz;
		base<y, w, z, x> ywzx;
		base<z, x, y, w> zxyw;
		base<z, x, w, y> zxwy;
		base<z, y, x, w> zyxw;
		base<z, y, w, x> zywx;
		base<z, w, x, y> zwxy;
		base<z, w, y, x> zwyx;
		base<w, x, y, z> wxyz;
		base<w, x, z, y> wxzy;
		base<w, y, x, z> wyxz;
		base<w, y, z, x> wyzx;
		base<w, z, x, y> wzxy;
		base<w, z, y, x> wzyx;
		swizz<x> x;
		swizz<y> y;
		swizz<z> z;
		swizz<w> w;
	};
};

template<>
struct vec<0, 1> : base<0, 1> {
	using base<0, 1>::operator=;
	vec& operator=(const vec& v);
	vec();
	vec(float x);
	vec(float x, float y);
	vec(const vec& v);
	template<int a, int b>
	vec(const base<a, b>& v);
	union {
		float data[2];
		struct { float x, y; };
		swizz<0, 1> xy;
		swizz<1, 0> yx;
	};
};

template<>
struct vec<0, 1, 2> : base<0, 1, 2> {
	using base<0, 1, 2>::operator=;
	vec& operator=(const vec& v);
	vec();
	vec(float x);
	vec(float x, float y, float z);
	vec(const vec& v);
	template<int a, int b, int c>
	vec(const base<a, b, c>& v);
	template<int a, int b>
	vec(float x, const base<a, b>& v);
	template<int a, int b>
	vec(const base<a, b>& v, float z);
	union {
		float data[3];
		struct { float x, y, z; };
		swizz<0, 1> xy;
		swizz<0, 2> xz;
		swizz<1, 0> yx;
		swizz<1, 2> yz;
		swizz<2, 0> zx;
		swizz<2, 1> zy;
		swizz<0, 1, 2> xyz;
		swizz<0, 2, 1> xzy;
		swizz<1, 0, 2> yxz;
		swizz<1, 2, 0> yzx;
		swizz<2, 0, 1> zxy;
		swizz<2, 1, 0> zyx;
	};
};

template<>
struct vec<0, 1, 2, 3> : base<0, 1, 2, 3> {
	using base<0, 1, 2, 3>::operator=;
	vec& operator=(const vec& v);
	vec();
	vec(float x);
	vec(float x, float y, float z, float w);
	vec(const vec& v);
	template<int a, int b, int c, int d>
	vec(const base<a, b, c, d>& v);
	template<int a, int b>
	vec(float x, float y, const base<a, b>& v);
	template<int a, int b>
	vec(const base<a, b>& v, float z, float w);
	template<int a, int b>
	vec(float x, const base<a, b>& v, float w);
	template<int a, int b, int c, int d>
	vec(const base<a, b>& l, const base<c, d>& r);
	template<int a, int b, int c>
	vec(const base<a, b, c>& v, float w);
	template<int a, int b, int c>
	vec(float x, const base<a, b, c>& v);
	union {
		float data[4];
		struct { float x, y, z, w; };
		swizz<0, 1> xy;
		swizz<0, 2> xz;
		swizz<0, 3> xw;
		swizz<1, 0> yx;
		swizz<1, 2> yz;
		swizz<1, 3> yw;
		swizz<2, 0> zx;
		swizz<2, 1> zy;
		swizz<2, 3> zw;
		swizz<3, 0> wx;
		swizz<3, 1> wy;
		swizz<3, 2> wz;
		swizz<0, 1, 2> xyz;
		swizz<0, 1, 3> xyw;
		swizz<0, 2, 1> xzy;
		swizz<0, 2, 3> xzw;
		swizz<0, 3, 1> xwy;
		swizz<0, 3, 2> xwz;
		swizz<1, 0, 2> yxz;
		swizz<1, 0, 3> yxw;
		swizz<1, 2, 0> yzx;
		swizz<1, 2, 3> yzw;
		swizz<1, 3, 0> ywx;
		swizz<1, 3, 2> ywz;
		swizz<2, 0, 1> zxy;
		swizz<2, 0, 3> zxw;
		swizz<2, 1, 0> zyx;
		swizz<2, 1, 3> zyw;
		swizz<2, 3, 0> zwx;
		swizz<2, 3, 1> zwy;
		swizz<3, 0, 1> wxy;
		swizz<3, 0, 2> wxz;
		swizz<3, 1, 0> wyx;
		swizz<3, 1, 2> wyz;
		swizz<3, 2, 0> wzx;
		swizz<3, 2, 1> wzy;
		swizz<0, 1, 2, 3> xyzw;
		swizz<0, 1, 3, 2> xywz;
		swizz<0, 2, 1, 3> xzyw;
		swizz<0, 2, 3, 1> xzwy;
		swizz<0, 3, 1, 2> xwyz;
		swizz<0, 3, 2, 1> xwzy;
		swizz<1, 0, 2, 3> yxzw;
		swizz<1, 0, 3, 2> yxwz;
		swizz<1, 2, 0, 3> yzxw;
		swizz<1, 2, 3, 0> yzwx;
		swizz<1, 3, 0, 2> ywxz;
		swizz<1, 3, 2, 0> ywzx;
		swizz<2, 0, 1, 3> zxyw;
		swizz<2, 0, 3, 1> zxwy;
		swizz<2, 1, 0, 3> zyxw;
		swizz<2, 1, 3, 0> zywx;
		swizz<2, 3, 0, 1> zwxy;
		swizz<2, 3, 1, 0> zwyx;
		swizz<3, 0, 1, 2> wxyz;
		swizz<3, 0, 2, 1> wxzy;
		swizz<3, 1, 0, 2> wyxz;
		swizz<3, 1, 2, 0> wyzx;
		swizz<3, 2, 0, 1> wzxy;
		swizz<3, 2, 1, 0> wzyx;
	};
};

template<class T>
struct t_vec2 {
	T x, y;
	t_vec2();
	t_vec2(T x, T y);
	t_vec2(const vec2& v);
	t_vec2(const t_vec2& v);
	template<class T2>
	t_vec2(const t_vec2<T2>& v);
	operator vec2();
};

template<class T>
struct t_vec3 {
	T x, y, z;
	t_vec3();
	t_vec3(T x, T y, T z);
	t_vec3(const vec3& v);
	t_vec3(const t_vec3& v);
	template<class T2>
	t_vec3(const t_vec3<T2>& v);
	operator vec3();
};
template<class T>
struct t_vec4 {
	T x, y, z, w;
	t_vec4();
	t_vec4(T x, T y, T z, T w);
	t_vec4(const vec4& v);
	t_vec4(const t_vec4& v);
	template<class T2>
	t_vec4(const t_vec4<T2>& v);
	operator vec4();
};

template<int x, int y, int z, int x1, int y1, int z1>
vec<0, 1, 2> cross(const base<x, y, z>& l, const base<x1, y1, z1>& r);

vec<0, 1, 2> perp(const vec<0, 1, 2>& v);

vec<0, 1> norm(float x, float y);

vec<0, 1, 2> norm(float x, float y, float z);

vec<0, 1, 2, 3> norm(float x, float y, float z, float w);

vec<0, 1, 2, 3> cross(const vec<0, 1, 2, 3>& v1, const vec<0, 1, 2, 3>& v2, const vec<0, 1, 2, 3>& v3);

struct mat2 {
	template<int x, int y, int x1, int y1>
	mat2(const base<x, y>& a, const base<x1, y1>& b);
	mat2();
	mat2(float x);
	mat2(float x, float y, float z, float w);
	mat2(const mat2& m);
	mat2& operator = (const mat2& m);
	union {
		float data[4];
		vec<0, 1> row[2];
		cvec<2> col[2];
		dvec<2> diag;
	};
	float det() const;
	mat2 inv() const;
	mat2 xpos() const;
	mat2 operator *(const mat2& r) const;
	template<int x, int y>
	vec<0, 1> operator *(const base<x, y>& v) const;
	mat2& operator *=	(float s);
	mat2& operator /=	(float s);
	mat2  operator *	(float s) const;
	mat2  operator /	(float s) const;
};

struct mat3 {
	template<
		int  x, int  y, int z,
		int x1, int y1, int z1,
		int x2, int y2, int z2>
		mat3(const base<x, y, z>& a, const base<x1, y1, z1>& b, const base<x2, y2, z2>& c);
	mat3();
	mat3(float x);
	mat3(float  x, float  y, float z, float x1, float y1, float z1, float x2, float y2, float z2);
	mat3(const mat3& m);

	mat3& operator = (const mat3& m);
	union {
		float data[9];
		vec<0, 1, 2> row[3];
		cvec<3> col[3];
		dvec<3> diag;
	};
	float det() const;
	mat3 xpos() const;
	mat3 operator * (const mat3& r) const;
	template<int x, int y, int z>
	vec<0, 1, 2> operator *(const base<x, y, z>& v) const;
	float& operator()(int r, int c);
	float  operator()(int r, int c) const;
	mat3& operator *=(float s);
	mat3 operator *		(float s) const;
	mat3& operator /=	(float s);
	mat3 operator /		(float s) const;
};


struct mat4 {
	template<
		int  x, int  y, int  z, int  w,
		int x1, int y1, int z1, int w1,
		int x2, int y2, int z2, int w2,
		int x3, int y3, int z3, int w3>
		mat4(const base<x, y, z, w>& a,
			const base<x1, y1, z1, w1>& b,
			const base<x2, y2, z2, w2>& c,
			const base<x3, y3, z3, w3>& d);
	mat4();
	mat4(float x);
	mat4(float  x, float  y, float  z, float w,
		float x1, float y1, float z1, float w1,
		float x2, float y2, float z2, float w2,
		float x3, float y3, float z3, float w3);
	mat4(const mat4& m);
	mat4& operator = (const mat4& m);

	union {
		float data[16];
		vec<0, 1, 2, 3> row[4];
		cvec<4> col[4];
		dvec<4> diag;
	};
	float det() const;
	mat4 inv() const;
	mat4 xpos() const;
	mat4 operator *(const mat4& r) const;
	template<int x, int y, int z, int w>
	vec<0, 1, 2, 3> operator *(const base<x, y, z, w>& v) const;
	float& operator()(int r, int c);
	float  operator()(int r, int c) const;
	mat4& operator *= (float s);
	mat4& operator /=	(float s);
	mat4 operator *		(float s) const;
	mat4 operator /		(float s) const;
};

mat3 rotx(float angle);
mat3 roty(float angle);
mat3 rotz(float angle);

mat4 perspective(float fov, float aspect, float n, float f);

mat4 ortho(float l, float r, float b, float t);

mat4 ortho(float l, float r, float b, float t, float n, float f);

mat4 view(const vec<0, 1, 2>& p, const vec<0, 1, 2>& r, const vec<0, 1, 2>& u, const vec<0, 1, 2>& d);
template<int x, int y>
vec<0, 1> operator *(const base<x, y>& v, const mat2& m);
template<int x, int y, int z>
vec<0, 1, 2> operator *(const base<x, y, z>& v, const mat3& m);
template<int x, int y, int z, int w>
vec<0, 1, 2, 3> operator *(const base<x, y, z, w>& v, const mat4& m);

struct quat {
	union {
		float data[4];
		struct { float x, y, z, w; };
		struct { float i, j, k, s; };
		vec<0, 1, 2> v;
		vec<0, 1, 2, 3> q;
	};
	template<int a, int b, int c>
	quat(const base<a, b, c>& v, float w);
	quat();
	quat(float x, float y, float z, float w);
	quat(const vec<0, 1, 2>& v, float w);
	quat(const quat& q);
	float len() const;
	float len2() const;
	quat& operator=(const quat& q);
	quat  operator ~() const;
	quat  operator -() const;
	quat& operator += (const quat& q);
	quat& operator -= (const quat& q);
	quat  operator +  (const quat& q) const;
	quat  operator -  (const quat& q) const;
	quat& operator *= (float s);
	quat& operator /= (float s);
	quat  operator *  (float s);
	quat  operator /  (float s);
	friend quat  operator *  (float s, const quat& q);
	friend quat  operator /  (float s, const quat& q);
	quat  operator /  (const quat& q) const;
	quat  operator *= (const quat& q);
	quat  operator /= (const quat& q);
	quat  operator * (const quat& q) const;
	operator mat3() const;
	operator mat4() const;
	template<int x, int y, int z>
	vec<0, 1, 2> operator * (const base<x, y, z>& v) const;
};

template<int x, int y, int z>
vec<0, 1, 2> operator * (const base<x, y, z>& v, const quat& q);
quat axAng(float x, float y, float z, float w);
quat axAng(const vec<0, 1, 2>& v, float w);
quat axAng(const vec<0, 1, 2, 3>& q);
quat axAng(const quat& q);
template<int x, int y, int z>
quat axAng(const base<x, y, z>& v, float w);

xfstr tostr(float x);
xfstr tostr(double x);
xfstr tostr(long x);
xfstr tostr(unsigned long x);
xfstr tostr(int x);
xfstr tostr(uint x);
xfstr tostr(const vec2& v);
xfstr tostr(const vec3& v);
xfstr tostr(const vec4& v);


inline quat axAng(float x, float y, float z, float w)
{
	return { norm(x, y, z) *= sinf(w * 0.5f), cosf(w * 0.5f) };
}

inline quat axAng(const vec<0, 1, 2>& v, float w)
{
	return { v.norm() *= sinf(w * 0.5f), cosf(w * 0.5f) };
}

inline quat axAng(const vec<0, 1, 2, 3>& q)
{
	return { q.xyz.norm() *= sinf(q.w * 0.5f), cosf(q.w * 0.5f) };
}

inline quat axAng(const quat& q)
{
	return { q.v.norm() *= sinf(q.w * 0.5f), cosf(q.w * 0.5f) };
}

template <int x, int y, int z>
inline quat axAng(const base<x, y, z>& v, float w)
{
	return { v.norm() *= sinf(w * 0.5f), cosf(w * 0.5f) };
}

inline float absl(float x) {
	static int abs;
	abs = *(int*)&x & 2147483647;
	return *(float*)&abs;
}

inline float cpysign(float x, float y) {
	static int sum;
	sum =	*(int*)&x & 2147483648 |
			*(int*)&y & 2147483647;
	return *(float*)&sum;
}

inline float ranf() {
	return float(ct::m()) * ct::intmax2 - 1.f;
}

inline float ranpf() {
	return float(ct::m()) * ct::intmax;
}

inline bool isN(float x) {
	return *(int*)&x != -4194304 && *(int*)&x != 2139095040;
}

inline bool is0(float x) {
	return absl(x) <= FLT_EPSILON;
}

inline bool is0(double x) {
	return abs(x) <= DBL_EPSILON;
}

inline bool is0(long double x) {
	return abs(x) <= DBL_EPSILON;
}

inline float sign(float x) {
	static int sign;
	sign = (*(int*)&x & 2147483648) + 1065353216;
	return (*(float*)&sign);
}

inline char* xfstr::newblock(size_t n) const
{
	return (char*)malloc(n);
}

inline char* xfstr::copy(size_t n) const
{
	char* temp = newblock(n);
	memcpy(temp, data_, size_ + 1);
	return temp;
}

inline void xfstr::alloc()
{
	if (size_ + 1 == cap_) {
		char* temp = copy(cap_ = (cap_ + 1) * 2);
		free(data_);
		data_ = temp;
	}
}

inline void xfstr::alloc(size_t n)
{
	if (n > cap_) {
		char* temp = copy(cap_ = n);
		free(data_);
		data_ = temp;
	}
}

inline void xfstr::range(char*& i, char*& j) const
{
	if (i > j) {
		char* t = ++i;
		i = ++j;
		j = t;
	}
	if (!(i >= data_ && j <= data_ + size_)) throw;
}


inline bool xfstr::NaN(char c)
{
	return c < 48 || c > 57;
}

inline bool xfstr::N(char c)
{
	return c > 47 && c < 58;
}

inline bool xfstr::WS(char c)
{
	return c == 32;
}

inline bool xfstr::NWS(char c)
{
	return c != 32;
}

inline bool xfstr::dot(char c)
{
	return c == 46;
}

inline xfstr::xfstr()
	: size_(0), cap_(1), data_(new char(0))
{
}

inline xfstr::xfstr(size_t n)
	: size_(n), cap_(n + 1), data_(newblock(cap_))
{
	new(data_ + size_)char(0);
}

inline xfstr::xfstr(const char* c)
	: size_(strlen(c)), cap_(size_ + 1), data_(newblock(cap_))
{
	memcpy(data_, c, cap_);
}

inline xfstr::xfstr(const xfstr& s)
	: size_(s.size_), cap_(s.cap_), data_(s.copy(cap_))
{
}

inline xfstr::xfstr(xfstr&& s) noexcept
	: size_(s.size_), cap_(s.cap_), data_(s.data_)
{
	s.data_ = nullptr;
}

inline xfstr& xfstr::operator=(const xfstr& s)
{
	free(data_);
	size_ = s.size_;
	cap_ = s.cap_;
	data_ = s.copy(cap_);
	return *this;
}

inline xfstr& xfstr::operator=(xfstr&& s) noexcept
{
	free(data_);
	size_ = s.size_;
	cap_ = s.cap_;
	data_ = s.data_;
	s.data_ = nullptr;
	return *this;
}

inline xfstr::~xfstr()
{
	free(data_);
}

inline xfstr& xfstr::operator+=(char c)
{
	alloc();
	new(data_ + size_++)char(c);
	new(data_ + size_)char(0);
	return *this;
}

inline xfstr& xfstr::operator+=(const char* c)
{
	size_t len = strlen(c);
	alloc(size_ + len + 1);
	memcpy(data_ + size_, c, len);
	size_ += len;
	new(data_ + size_)char(0);
	return *this;
}

inline xfstr& xfstr::operator+=(const xfstr& s)
{
	alloc(size_ + s.size_ + 1);
	memcpy(data_ + size_, s.data_, s.size_);
	size_ += s.size_;
	new(data_ + size_)char(0);
	return *this;
}

inline xfstr xfstr::operator +(char c) const
{
	xfstr re(size_ + 1);
	memcpy(re.data_, data_, size_);
	new(re.data_ + size_)char(c);
	return re;
}

inline xfstr xfstr::operator +(const char* c) const
{
	size_t len = strlen(c);
	xfstr re(size_ + len);
	memcpy(re.data_, data_, size_);
	memcpy(re.data_ + size_, c, len);
	return re;
}

inline xfstr xfstr::operator +(const xfstr& s) const
{
	xfstr re(size_ + s.size_);
	memcpy(re.data_, data_, size_);
	memcpy(re.data_ + size_, s.data_, s.size_);
	return re;
}

inline bool xfstr::operator==(const char* c) const
{
	return strcmp(data_, c) == 0;
}

inline bool xfstr::operator!=(const char* c) const
{
	return strcmp(data_, c) != 0;
}

inline bool xfstr::operator==(const xfstr& s) const
{
	return strcmp(data_, s.data_) == 0;
}

inline bool xfstr::operator!=(const xfstr& s) const
{
	return strcmp(data_, s.data_) != 0;
}

inline xfstr& xfstr::operator<<(int n)
{
	const uint len = static_cast<uint>(_scprintf("%d", n));
	free(data_);
	data_ = newblock(len + 1);
	sprintf_s(data_, len + 1, "%d", n);
	return *this;
}

inline xfstr& xfstr::operator<<(uint n)
{
	const uint len = static_cast<uint>(_scprintf("%u", n));
	free(data_);
	data_ = newblock(len + 1);
	sprintf_s(data_, len + 1, "%u", n);
	return *this;
}

inline xfstr& xfstr::operator<<(long n)
{
	const uint len = static_cast<uint>(_scprintf("%d", n));
	free(data_);
	data_ = newblock(len + 1);
	sprintf_s(data_, len + 1, "%d", n);
	return *this;
}

inline xfstr& xfstr::operator<<(unsigned long n)
{
	const uint len = static_cast<uint>(_scprintf("%ul", n));
	free(data_);
	data_ = newblock(len + 1);
	sprintf_s(data_, len + 1, "%ul", n);
	return *this;
}

inline xfstr& xfstr::operator<<(float n)
{
	const uint len = static_cast<uint>(_scprintf("%f", n));
	free(data_);
	data_ = newblock(len + 1);
	sprintf_s(data_, len + 1, "%f", n);
	return *this;
}

inline xfstr& xfstr::operator<<(double n)
{
	const uint len = static_cast<uint>(_scprintf("%f", n));
	free(data_);
	data_ = newblock(len + 1);
	sprintf_s(data_, len + 1, "%f", n);
	return *this;
}

inline xfstr& xfstr::operator>>(long& n)
{
	char* end;
	n = strtol(data_, &end, 10);
	erase(data_, end);
	return *this;
}

inline xfstr& xfstr::operator>>(unsigned long& n)
{
	char* end;
	n = strtoul(data_, &end, 10);
	erase(data_, end);
	return *this;
}

inline xfstr& xfstr::operator>>(int& n)
{
	char* end;
	n = strtoul(data_, &end, 10);
	erase(data_, end);
	return *this;
}

inline xfstr& xfstr::operator>>(uint& n)
{
	char* end;
	n = strtoul(data_, &end, 10);
	erase(data_, end);
	return *this;
}

inline xfstr& xfstr::operator>>(float& n)
{
	char* end;
	n = strtof(data_, &end);
	erase(data_, end);
	return *this;
}

inline xfstr& xfstr::operator>>(double& n)
{
	char* end;
	n = strtod(data_, &end);
	erase(data_, end);
	return *this;
}

inline std::istream& xfstr::getline(std::istream& s, char delim)
{
	clear(); char c;
	while (s.get(c) && c != delim) operator+=(c);
	return s;
}

inline void xfstr::erase(char* i, char* j)
{
	range(i, j);
	memcpy(i, j, data_ + size_ - j);
	size_ -= (j - i);
	new(data_ + size_)char(0);

}

inline void xfstr::erase(char* i)
{
	if (i < data_ || i >= data_ + size_) return;
	memcpy(i, i + 1, data_ + size_ - i - 1);
	new(data_ + --size_)char(0);
}

inline const char* xfstr::c_str()
{
	return data_;
}

inline char& xfstr::operator[](size_t i)
{
	if (!(i < size_)) throw;
	return *(data_ + i);
}

inline char xfstr::operator[](size_t i) const
{
	if (!(i < size_)) throw;
	return *(data_ + i);
}

inline char* xfstr::data() const
{
	return data_;
}

inline char* xfstr::begin()
{
	return data_;
}

inline char* xfstr::end()
{
	return data_ + size_;
}

inline char* xfstr::rbegin()
{
	return data_ + size_ - 1;
}

inline char* xfstr::rend()
{
	return data_ - 1;
}

inline char* xfstr::data()
{
	return data_;
}

inline char* xfstr::find(char c, size_t pos) const
{
	char* i = begin();
	char* j = end();
	for (; i != j; ++i) {
		if (*i == c) {
			--pos;
			if (!pos) return i;
		}
	}
	return 0;
}

inline char* xfstr::findif(bool (*f)(char), size_t pos) const
{
	char* i = begin();
	char* j = end();
	for (; i != j; ++i) {
		if (f(*i)) {
			--pos;
			if (!pos) return i;
		}
	}
	return 0;
}

inline char* xfstr::find(char c, char* i, char* j, size_t pos) const
{
	range(i, j);
	for (; i != j; ++i) {
		if (*i == c) {
			--pos;
			if (!pos) return i;
		}
	}
	return 0;
}

inline char* xfstr::findif(bool (*f)(char), char* i, char* j, size_t pos) const
{
	range(i, j);
	for (; i != j; ++i) {
		if (f(*i)) {
			--pos;
			if (!pos) return i;
		}
	}
	return 0;
}

inline xfstr xfstr::substr(size_t pos, size_t len) const
{
	if (pos >= size_) return xfstr();
	xfstr re(len);
	memcpy(re.data_, data_ + pos, len);
	new(re.data_ + re.size_)char(0);
	return re;
}

inline xfstr xfstr::substr(size_t pos) const
{
	if (pos >= size_) return xfstr();
	xfstr re(size_ - pos);
	memcpy(re.data_, data_ + pos, re.size_);
	new(re.data_ + re.size_)char(0);
	return re;
}

inline xfstr xfstr::map(char(*f)(char)) const
{
	char* re = new char[size_ + 1];
	for (size_t i = 0; i < size_; ++i) re[i] = f(*(data_ + i));
	re[size_] = 0;
	return re;
}

inline void xfstr::clear()
{
	size_ = 0;
}

inline bool xfstr::empty() const
{
	return size_ == 0;
}

inline size_t xfstr::size() const
{
	return size_;
}

inline size_t xfstr::cap() const
{
	return cap_;
}

inline char* xfstr::begin() const
{
	return data_;
}

inline char* xfstr::end() const
{
	return data_ + size_;
}

inline char* xfstr::rbegin() const
{
	return data_ + size_ - 1;
}

inline char* xfstr::rend() const
{
	return data_ - 1;
}

inline std::ostream& operator << (std::ostream& s, const xfstr& str) {
	return s << str.data();
}

inline std::istream& operator>>(std::istream& s, xfstr& str)
{
	str.clear(); char c;
	while (s.get(c)) str += c;
	return s;
}

inline xfstr operator + (const char* c, const xfstr& s) {
	size_t len = strlen(c);
	xfstr re(len + s.size());
	memcpy(re.data(), c, len);
	memcpy(re.data() + len, s.data(), s.size());
	return re;
}

template<class c>
inline std::ostream& operator << (std::ostream& s, const xfvec<c>& v) {
	for (const c& i : v) s << i << ' ';
	return s << '\n';
}

template<class c>
inline c* xfvec<c>::newblock(size_t n) const
{
	return (c*)malloc(n * byte);
}

template<class c>
inline void xfvec<c>::destruct()
{
	if constexpr (destructible)
		for (size_t i = 0; i < size_; ++i) (data_ + i)->~c();
	free(data_);
}

template<class c>
inline void xfvec<c>::destruct(c* i, c* j)
{
	if constexpr (destructible)
		for (; i != j; ++i) i->~c();
}

template<class c>
inline c* xfvec<c>::copy(size_t n) const
{
	c* temp = newblock(n);
	for (size_t i = 0; i < size_; ++i)
		new(temp + i) c(*(data_ + i));
	return temp;
}

template<class c>
inline void xfvec<c>::alloc()
{
	if (size_ == cap_) {
		c* temp = newblock(cap_ = (cap_ + 1) * 2);
		memcpy(temp, data_, size_ * byte);
		free(data_);
		data_ = temp;
	}
}

template<class c>
inline void xfvec<c>::alloc(size_t n)
{
	if (n > cap_) {
		c* temp = newblock(cap_ = n);
		memcpy(temp, data_, size_ * byte);
		free(data_);
		data_ = temp;
	}
}

template<class c>
inline void xfvec<c>::range(c*& i, c*& j)
{
	if (i > j) {
		c* t = ++i;
		i = ++j;
		j = t;
	}
	if (!(i >= data_ && j <= data_ + size_)) throw;
}

template<class c>
inline void xfvec<c>::push(const c& item)
{
	alloc();
	new(data_ + size_++)c(item);
}

template<class c>
inline void xfvec<c>::push(c&& item)
{
	alloc();
	new(data_ + size_++)c((c&&)item);
}

template<class c>
inline void xfvec<c>::erase(c* i, c* j)
{
	range(i, j);
	destruct(i, j);
	memcpy(i, j, (data_ + size_ - j) * byte);
	size_ -= (j - i);
}

template<class c>
inline void xfvec<c>::erase(c* i)
{
	if (i < data_ || i >= data_ + size_) return;
	if constexpr (destructible) i->~c();
	memcpy(i, i + 1, (data_ + --size_ - i) * byte);

}

template<class c>
inline c* xfvec<c>::insert(c* pos, const c& item)
{
	if (pos < data_ || pos > data_ + size_) throw;
	size_t p = pos - data_;
	if (size_ == cap_) {
		c* temp = newblock(cap_ = (cap_ + 1) * 2);
		memcpy(temp, data_, p * byte);
		memcpy(temp + p + 1, data_ + p, (size_ - p) * byte);
		free(data_);
		data_ = temp;
	}
	else {
		memcpy(data_ + p + 1, data_ + p, (size_ - p) * byte);
	}
	++size_;
	return new(data_ + p) c(item);
}

template<class c>
inline c* xfvec<c>::insert(c* pos, c&& item)
{
	if (pos < data_ || pos > data_ + size_) throw;
	size_t p = pos - data_;
	if (size_ == cap_) {
		c* temp = newblock(cap_ = (cap_ + 1) * 2);
		memcpy(temp, data_, p * byte);
		memcpy(temp + p + 1, data_ + p, (size_ - p) * byte);
		free(data_);
		data_ = temp;
	}
	else {
		memcpy(data_ + p + 1, data_ + p, (size_ - p) * byte);
	}
	++size_;
	return new(data_ + p) c((c&&)item);
}

template<class c>
inline void xfvec<c>::reserve(size_t n)
{
	alloc(n);
}

template<class c>
inline void xfvec<c>::resize(size_t n)
{
	if (n > size_) {
		alloc(n);
		while (size_ != n) new(data_ + size_++)c();
	}
}

template<class c>
inline c& xfvec<c>::operator[](size_t i)
{
	if (i >= size_) throw;
	return *(data_ + i);
}

template<class c>
inline c& xfvec<c>::operator[](size_t i) const
{
	if (!(i < size_)) throw;
	return *(data_ + i);
}

template<class c>
inline void xfvec<c>::sort()
{
	static void (*swap)(c*, c*) = [](c* a, c* b) {
		c t = *a;
		*a = *b;
		*b = t;
	};
	static int (*partition)(c*, int, int) = [](c* arr, int low, int high)
	{
		c& pivot = arr[high];
		int i = (low - 1);
		for (int j = low; j <= high - 1; j++) {
			if (arr[j] <= pivot) {
				i++;
				swap(&arr[i], &arr[j]);
			}
		}
		swap(&arr[i + 1], &arr[high]);
		return (i + 1);
	};
	static void (*qSort)(c*, int, int) = [](c* arr, int low, int high)
	{
		if (low < high) {
			int pi = partition(arr, low, high);
			qSort(arr, low, pi - 1);
			qSort(arr, pi + 1, high);
		}
	};
	qSort(data_, 0, size_ - 1);
}

template<class c>
inline c* xfvec<c>::find(const c& item, size_t pos) const
{
	c* i = begin();
	c* j = end();
	for (; i != j; ++i) {
		if (*i == item) {
			--pos;
			if (!pos) return i;
		}
	}
	return 0;
}

template<class c>
inline c* xfvec<c>::findif(bool (*f)(c), size_t pos) const
{
	c* i = begin();
	c* j = end();
	for (; i != j; ++i) {
		if (f(*i)) {
			--pos;
			if (!pos) return i;
		}
	}
	return 0;
}

template<class c>
inline c* xfvec<c>::findif(bool (*f)(const c&), size_t pos) const
{
	c* i = begin();
	c* j = end();
	for (; i != j; ++i) {
		if (f(*i)) {
			--pos;
			if (!pos) return i;
		}
	}
	return 0;
}

template<class c>
inline c* xfvec<c>::find(const c& item, c* i, c* j, size_t pos) const
{
	range(i, j);
	for (; i != j; ++i) {
		if (*i == item) {
			--pos;
			if (!pos) return i;
		}
	}
	return 0;
}

template<class c>
inline c* xfvec<c>::findif(bool (*f)(c), c* i, c* j, size_t pos) const
{
	range(i, j);
	for (; i != j; ++i) {
		if (f(*i)) {
			--pos;
			if (!pos) return i;
		}
	}
	return 0;
}

template<class c>
inline c* xfvec<c>::findif(bool (*f)(const c&), c* i, c* j, size_t pos) const
{
	if (!inrange(i, j)) throw;
	swapper(i, j);
	for (; i != j; ++i) {
		if (f(*i)) {
			--pos;
			if (!pos) return i;
		}
	}
	return 0;
}

template<class c>
inline xfvec<c> xfvec<c>::subvec(c* i, c* j) const
{
	range(i, j);
	xfvec re(j - i);
	for (; i != j; ++i) re.push(*i);
	return re;
}

template<class c>
inline xfvec<c> xfvec<c>::map(c(*f)(c)) const
{
	xfvec re(size_);
	for (size_t i = 0; i < size_; ++i) re.push(f(*(data_ + i)));
	return re;
}

template<class c>
inline xfvec<c> xfvec<c>::map(c(*f)(const c&)) const
{
	xfvec re(size_);
	for (size_t i = 0; i < size_; ++i) re.push(f(*(data_ + i)));
	return re;
}

template<class c>
inline xfvec<c>::xfvec()
	: size_(0), cap_(0), data_(nullptr)
{
}

template<class c>
inline xfvec<c>::xfvec(size_t n)
	: size_(0), cap_(n), data_(newblock(n))
{
}

template<class c>
inline xfvec<c>::xfvec(const xfvec& v)
	: size_(v.size_), cap_(v.cap_), data_(v.copy(cap_))
{
}

template<class c>
inline xfvec<c>::xfvec(xfvec&& v)
	: size_(v.size_), cap_(v.cap_), data_(v.data_)
{
	v.data_ = nullptr;
}

template<class c>
inline xfvec<c>::xfvec(std::initializer_list<c> list)
	: size_(list.size()), cap_(size_), data_(newblock(cap_))
{
	for (size_t i = 0; i < size_; ++i)
		new(data_ + i) c((c&&)*(list.begin() + i));
}

template<class c>
inline xfvec<c>& xfvec<c>::operator=(const xfvec& v)
{
	destruct();
	size_ = v.size_;
	cap_ = v.cap_;
	data_ = v.copy(cap_);
	return *this;
}

template<class c>
inline xfvec<c>& xfvec<c>::operator=(xfvec&& v)
{
	destruct();
	size_ = v.size_;
	cap_ = v.cap_;
	data_ = v.data_;
	v.size_ = 0;
	v.cap_  = 0;
	v.data_ = nullptr;
	return *this;
}

template<class c>
inline xfvec<c>::~xfvec()
{
	destruct();
}

template<class c>
template<class ...Cs>
inline void xfvec<c>::emplace(const Cs& ...cs)
{
	alloc();
	new(data_ + size_++)c(cs...);
}

template<class c>
template<class ...Cs>
inline void xfvec<c>::emplace(Cs&& ...cs)
{
	alloc();
	new(data_ + size_++)c((Cs&&)cs...);
}

template<class c>
template<class c2>
inline xfvec<c2> xfvec<c>::map(c2(*f)(c)) const
{
	xfvec<c2> re(size_);
	for (size_t i = 0; i < size_; ++i) re.push(f(*(data_ + i)));
	return re;
}

template<class c>
template<class c2>
inline xfvec<c2> xfvec<c>::map(c2(*f)(const c&)) const
{
	xfvec<c2> re(size_);
	for (size_t i = 0; i < size_; ++i) re.push(f(*(data_ + i)));
	return re;
}

template<class c>
inline void xfvec<c>::clear()
{
	destruct(data_, data_ + size_);
	size_ = 0;
}

template<class c>
inline bool xfvec<c>::empty() const
{
	return size_ == 0;
}

template<class c>
inline size_t xfvec<c>::size() const
{
	return size_;
}

template<class c>
inline size_t xfvec<c>::cap() const
{
	return cap_;
}

template<class c>
inline c* xfvec<c>::begin() const
{
	return data_;
}

template<class c>
inline c* xfvec<c>::end() const
{
	return data_ + size_;
}

template<class c>
inline c* xfvec<c>::rbegin() const
{
	return data_ + size_ - 1;
}

template<class c>
inline c* xfvec<c>::rend() const
{
	return data_ - 1;
}

template<class c>
inline c* xfvec<c>::data() const
{
	return data_;
}

template<class c>
inline c& xfvec<c>::front() const
{
	return *data_;
}

template<class c>
inline c& xfvec<c>::back() const
{
	return *rbegin();
}

template<class c>
inline c* xfvec<c>::begin()
{
	return data_;
}

template<class c>
inline c* xfvec<c>::end()
{
	return data_ + size_;
}

template<class c>
inline c* xfvec<c>::rbegin()
{
	return data_ + size_ - 1;
}

template<class c>
inline c* xfvec<c>::rend()
{
	return data_ - 1;
}

template<class c>
inline c* xfvec<c>::data()
{
	return data_;
}

template<class c>
inline c& xfvec<c>::front()
{
	return *data_;
}

template<class c>
inline c& xfvec<c>::back()
{
	return *rbegin();
}

template<class T>
inline std::ostream& operator << (std::ostream& s, const complex<T>& c) {
	return s << c.x << ' ' << c.y << '\n';
}

template<class T>
inline T complex<T>::phase() const
{
	return atan2(y, x);
}

template<class T>
inline T complex<T>::len2() const
{
	return x * x + y * y;
}

template<class T>
inline T complex<T>::len() const
{
	return sqrtf(len2());
}

template<class T>
inline complex<T> operator * (T n, const complex<T>& c)
{
	return { n * c.x, n * c.y };
}

template<class T>
inline complex<T> operator / (T n, const complex<T>& c)
{
	n /= c.len2();
	return { n * c.x, -n * c.y };
}

template<class T>
inline complex<T> complex<T>::operator-() const
{
	return { -x, -y };
}

template<class T>
inline complex<T> complex<T>::operator~() const
{
	return { x, -y };
}

template<class T>
inline complex<T>& complex<T>::operator+=(const complex& c)
{
	x += c.x; y += c.y;
	return *this;
}

template<class T>
inline complex<T>& complex<T>::operator-=(const complex& c)
{
	x -= c.x; y -= c.y;
	return *this;
}

template<class T>
inline complex<T> complex<T>::operator+(const complex& c) const
{
	return { x + c.x, y + c.y };
}

template<class T>
inline complex<T> complex<T>::operator-(const complex& c) const
{
	return { x - c.x, y - c.y };
}

template<class T>
inline complex<T>& complex<T>::operator+=(T n)
{
	x += n;
	return *this;
}

template<class T>
inline complex<T>& complex<T>::operator-=(T n)
{
	x -= n;
	return *this;
}

template<class T>
inline complex<T>& complex<T>::operator*=(T n)
{
	x *= n; y *= n;
	return *this;
}

template<class T>
inline complex<T>& complex<T>::operator/=(T n)
{
	n = static_cast<T>(1) / n;
	x *= n; y *= n;
	return *this;
}

template<class T>
inline complex<T> complex<T>::operator+(T n) const
{
	return { x + n, y };
}

template<class T>
inline complex<T> complex<T>::operator-(T n) const
{
	return { x - n, y };
}

template<class T>
inline complex<T> complex<T>::operator*(T n) const
{
	return { x * n, y * n };
}

template<class T>
inline complex<T> complex<T>::operator/(T n) const
{
	n = static_cast<T>(1) / n;
	return { x * n, y * n };
}

template<class T>
inline complex<T> complex<T>::operator*(const complex& c) const
{
	return { x * c.x - y * c.y, x * c.y + y * c.x };
}

template<class T>
inline complex<T> complex<T>::operator/(const complex& c) const
{
	T l = static_cast<T>(1) / c.len2();
	return { l * (x * c.x + y * c.y), l * (y * c.x - x * c.y) };
}

template<class T>
inline complex<T>& complex<T>::operator*=(const complex& c)
{
	T t = x;
	x = x * c.x - y * c.y;
	y = t * c.y + y * c.x;
	return *this;
}

template<class T>
inline complex<T>& complex<T>::operator/=(const complex& c)
{
	T t = x; T l = static_cast<T>(1) / c.len2();
	x = (x * c.x + y * c.y) * l;
	y = (y * c.x - t * c.y) * l;
	return *this;
}

template<class key, class val>
inline std::ostream& operator << (std::ostream& s, const xfpair<key, val>& p) {
	return s << '<' << p.k << ',' << p.v << '>';
}

template<class key, class val>
inline xfpair<key, val>::xfpair() : k(), v()
{
}

template<class key, class val>
inline xfpair<key, val>::xfpair(const key& k) : k(k), v()
{
}

template<class key, class val>
inline xfpair<key, val>::xfpair(const key& k, const val& v) : k(k), v(v)
{
}

template<class key, class val>
inline xfpair<key, val>::xfpair(const xfpair& p) : k(p.k), v(p.v)
{
}

template<class key, class val>
inline xfpair<key, val>& xfpair<key, val>::operator=(const xfpair& p)
{
	k = p.k; v = p.v;
	return *this;
}

template<class key, class val>
inline xfpair<key, val>::xfpair(xfpair&& p)
	: k((key&&)p.k), v((val&&)p.v)
{
}

template<class key, class val>
inline xfpair<key, val>& xfpair<key, val>::operator=(xfpair&& p)
{
	k = (key&&)p.k;
	v = (val&&)p.v;
	return *this;
}

template<class key, class val>
inline bool xfpair<key, val>::operator<(const xfpair& p) const
{
	return k < p.k;
}

template<class key, class val>
inline bool xfpair<key, val>::operator>(const xfpair& p) const
{
	return k > p.k;
}

template<class key, class val>
inline bool xfpair<key, val>::operator==(const xfpair& p) const
{
	return k == p.k;
}

template<class key, class val>
inline bool xfpair<key, val>::operator<=(const xfpair& p) const
{
	return k <= p.k;
}

template<class key, class val>
inline bool xfpair<key, val>::operator>=(const xfpair& p) const
{
	return k >= p.k;
}

template<class key, class val>
inline bool xfpair<key, val>::operator!=(const xfpair& p) const
{
	return k != p.k;
}

template<class key, class val>
vref<key, val>::vref(const key& k, xfvec<xfpair<key, val>>& data)
	: k(k), data(data) {}

template<class key, class val>
val& vref<key, val>::operator = (const val& n) {
	i = data.begin(), j = data.end();
	for (; i != j && i->k <= k; ++i)
		if (i->k == k) return i->v = n;
	return data.insert(i, { k, n })->v;
}

template<class key, class val>
inline val& vref<key, val>::operator+=(const val& n)
{
	i = data.begin(), j = data.end();
	for (; i != j && i->k <= k; ++i)
		if (i->k == k) return i->v += n;
	return data.insert(i, { k, n })->v;
}

template<class key, class val>
inline val& vref<key, val>::operator-=(const val& n)
{
	i = data.begin(), j = data.end();
	for (; i != j && i->k <= k; ++i)
		if (i->k == k) return i->v -= n;
	return data.insert(i, { k, -n })->v;
}

template<class key, class val>
inline val& vref<key, val>::operator*=(const val& n)
{
	i = data.begin(), j = data.end();
	for (; i != j && i->k <= k; ++i)
		if (i->k == k) return i->v *= n;
	return data.insert(i, { k })->v;
}

template<class key, class val>
inline val& vref<key, val>::operator/=(const val& n)
{
	i = data.begin(), j = data.end();
	for (; i != j && i->k <= k; ++i)
		if (i->k == k) return i->v /= n;
	return data.insert(i, { k })->v;
}

template<class key, class val>
vref<key, val>::operator const val& () const {
	i = data.begin(), j = data.end();
	for (; i != j && i->k <= k; ++i)
		if (i->k == k) return i->v;
	return vref<key, val>::val0;
}

template<class key, class val>
inline xfmap<key, val>::xfmap() : data()
{
}

template<class key, class val>
inline xfmap<key, val>::xfmap(const xfmap& map) : data(map.data)
{
}

template<class key, class val>
inline xfmap<key, val>::xfmap(xfmap&& map)
	: data((xfvec<xfpair<key, val>>&&)(map.data))
{
}

template<class key, class val>
inline xfmap<key, val>& xfmap<key, val>::operator=(const xfmap& map)
{
	data = map.data;
	return *this;
}

template<class key, class val>
inline xfmap<key, val>& xfmap<key, val>::operator=(xfmap&& map)
{
	data = (xfvec<xfpair<key, val>>&&)(map.data);
	return *this;
}

template<class key, class val>
inline xfpair<key, val>* xfmap<key, val>::insert(const key& k)
{
	xfpair<key, val>* begin = data.begin(), * end = data.end();
	for (; begin != end && begin->k <= k; ++begin);
	return data.insert(begin, { k });
}

template<class key, class val>
inline xfpair<key, val>* xfmap<key, val>::insert(const key& k, const val& v)
{
	xfpair<key, val>* begin = data.begin(), * end = data.end();
	for (; begin != end && begin->k <= k; ++begin);
	return data.insert(begin, { k, v });
}

template<class key, class val>
inline val* xfmap<key, val>::find(const key& k)
{
	xfpair<key, val>* begin = data.begin(), * end = data.end();
	for (; begin != end && begin->k <= k; ++begin)
		if (k == begin->k) return &begin->v;
	return 0;
}

template<class key, class val>
inline val* xfmap<key, val>::find(const key& k) const
{
	xfpair<key, val>* begin = data.begin(), * end = data.end();
	for (; begin != end && begin->k <= k; ++begin)
		if (k == begin->k) return &begin->v;
	return 0;
}

template<class key, class val>
inline vref<key, val> xfmap<key, val>::operator[](const key& k)
{
	return  { k, data };
}

template<class key, class val>
inline const val& xfmap<key, val>::operator[](const key& k) const
{
	xfpair<key, val>* begin = data.begin(), * end = data.end();
	for (; begin != end && begin->k <= k; ++begin)
		if (k == begin->k) return begin->v;
	return vref<key, val>::val0;
}

template<class key, class val>
inline xfpair<key, val>* xfmap<key, val>::begin() const
{
	return data.begin();
}

template<class key, class val>
inline xfpair<key, val>* xfmap<key, val>::end() const
{
	return data.end();
}

template<class key, class val>
inline xfpair<key, val>* xfmap<key, val>::rbegin() const
{
	return data.rbegin();
}

template<class key, class val>
inline xfpair<key, val>* xfmap<key, val>::rend() const
{
	return data.rend();
}

template<class key, class val>
inline bool xfmap<key, val>::empty() const
{
	return data.empty();
}

template<class key, class val>
inline size_t xfmap<key, val>::size() const
{
	return data.size();
}

template<class key, class val>
inline void xfmap<key, val>::clear()
{
	data.clear();
}

template<class key, class val>
inline std::ostream& operator << (std::ostream& s, const xfmap<key, val>& v) {
	for (const xfpair<key, val>& p : v) s << p;
	return s;
}

template<class T>
std::ostream& operator << (std::ostream& s, const xfpoly<T>& p) {
	return s << p.coeffs();
}

template<class T>
inline T xfpoly<T>::power(const T& n, int p)
{
	if (p == 0) return 1;
	T re = n;
	while (--p, p > 0)re *= n;
	return re;
}

template<class T>
inline xfpoly<T>::xfpoly()
{
}

template<class T>
inline xfpoly<T>::xfpoly(const T& x)
{
	c[0] = x;
}

template<class T>
template<class ...Ts>
inline xfpoly<T>::xfpoly(const Ts& ... t)
{
	static int i = 0;
	i = -1;
	((c[++i] = t), ...);
}

template<class T>
inline xfpoly<T>::xfpoly(const xfpoly& p) : c(p.c)
{
}

template<class T>
inline xfpoly<T>::xfpoly(xfpoly&& p) : c((xfmap<int, T>&&)(p.c))
{
}

template<class T>
inline vref<int, T> xfpoly<T>::operator[](size_t i)
{
	return c[i];
}

template<class T>
inline T xfpoly<T>::operator[](size_t i) const
{
	return c[i];
}

template<class T>
inline xfpoly<T>& xfpoly<T>::operator=(const xfpoly& p)
{
	c = p.c;
	return *this;
}

template<class T>
inline xfpoly<T>& xfpoly<T>::operator=(xfpoly&& p)
{
	c = (xfmap<int, T>&&)(p.c);
	return *this;
}

template<class T>
inline xfpoly<T>& xfpoly<T>::operator+=(const xfpoly& p)
{
	for (int i = p.degree(); i >= 0; ++i) c[i] += p[i];
	return *this;
}

template<class T>
inline xfpoly<T>& xfpoly<T>::operator-=(const xfpoly& p)
{
	for (int i = p.degree(); i >= 0; ++i) c[i] -= p[i];
	return *this;
}

template<class T>
inline xfpoly<T> xfpoly<T>::operator+(const xfpoly& p)
{
	return xfpoly(*this) += p;
}

template<class T>
inline xfpoly<T> xfpoly<T>::operator-(const xfpoly& p)
{
	return xfpoly(*this) -= p;
}

template<class T>
inline xfpoly<T> xfpoly<T>::operator * (const xfpoly& p)
{
	int d1 = degree(), d2 = p.degree();
	xfpoly re;
	for (int i = 0; i <= d1; ++i)
		for (int j = 0; j <= d2; ++j)
			re[i + j] += c[i] * p[j];
	return re;
}

template<class T>
inline xfpoly<T>& xfpoly<T>::operator*=(const xfpoly& p)
{
	return *this = *this * p;
}

template<class T>
inline xfpoly<T> xfpoly<T>::divide(const T& root)
{
	int d = degree();
	xfpoly div;
	for (int i = 0; i < d; i++)
		for (int j = i; j < d; j++)
			div.c[i] += c[j + 1] * power(root, j - i);
	return div;
}

template<class T>
inline void xfpoly<T>::resize(size_t n)
{
	c.resize(n);
}

template<class T>
inline int xfpoly<T>::degree() const
{
	if (!c.empty())
		return c.rbegin()->k;
	return 0;
}

template<class T>
inline xfpoly<T> xfpoly<T>::derivative() const
{
	xfpoly re;
	for (const xfpair<int, T>& n : c) {
		T x = n.k * c[n.k];
		if (x != 0)
			re[n.k - 1] = x;
	}
	return re;
}

template<class T>
inline T xfpoly<T>::discriminant() const
{
	return T();
}

template<class T>
inline T xfpoly<T>::operator()(const T& in)
{
	T re = 0;
	for (const xfpair<int, T>& n : c)
		re += n.v * power(in, n.k);
	return re;
}

template<class T>
inline xfvec<T> xfpoly<T>::roots()
{
	xfvec<T> re;
	T r = root1();
	xfpoly p = *this;
	while (p.degree() != 0) {
		re.push(r);
		p = p.divide(r);
		r = p.root1();
	}
	return re;
}

template<class T>
T  xfpoly<T>::root1() {
	xfpoly der = derivative();
	T p = der(0);
	T y = operator()(0);
	T x = -y / p;
	int it = 0;
	while (!is0(y)) {
		it++;
		if (is0(p)) {
			//std::cout << y << "derivative is 0\n";
			T r = T(rand() % 100) - 200.;
			x = operator()(r) / der(r);
			y = operator()(x);
			p = der(x);
		}
		else {
			x = x - y / p;
			y = operator()(x);
			p = der(x);
			//cout << x << "\n";
		}
		if (it > 200) return x;
	}
	return x;
}

template<class T>
inline const xfmap<int, T>& xfpoly<T>::coeffs() const
{
	return c;
}

template<int x>
inline float& swizz<x>::operator=(float f)
{
	return *(float*)(this + x) = f;
}

template<int x>
inline swizz<x>::operator float& ()
{
	return *(float*)(this + x);
}

template<int x>
inline swizz<x>::operator float() const
{
	return *(float*)(this + x);
}

inline vec<0, 1>& vec<0, 1>::operator=(const vec& v)
{
	x = v.x;
	y = v.y;
	return *this;
}

inline vec<0, 1>::vec() : data{}
{
}


inline vec<0, 1>::vec(float x) : data{ x, x }
{
}


inline vec<0, 1>::vec(float x, float y) : data{ x, y }
{
}


inline vec<0, 1>::vec(const vec& v) : data{ v.x, v.y }
{
}


template<int a, int b>
inline vec<0, 1>::vec(const base<a, b>& v) : data{ *(float*)(&v + a), *(float*)(&v + b) }
{
}


inline vec<0, 1, 2>& vec<0, 1, 2>::operator=(const vec& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}


inline vec<0, 1, 2>::vec() : data{}
{
}


inline vec<0, 1, 2>::vec(float x) : data{ x, x, x }
{
}


inline vec<0, 1, 2>::vec(float x, float y, float z) : data{ x, y, z }
{
}


inline vec<0, 1, 2>::vec(const vec& v) : data{ v.x, v.y, v.z }
{
}


template<int a, int b, int c>
inline vec<0, 1, 2>::vec(const base<a, b, c>& v)
	: data{ *(float*)(&v + a), *(float*)(&v + b),  *(float*)(&v + c) }
{
}


template<int a, int b>
inline vec<0, 1, 2>::vec(float x, const base<a, b>& v)
	: data{ x, *(float*)(&v + a),*(float*)(&v + b) }
{
}

template<int a, int b>
inline vec<0, 1, 2>::vec(const base<a, b>& v, float z)
	: data{ *(float*)(&v + a),*(float*)(&v + b), z }
{
}

inline vec<0, 1, 2, 3>& vec<0, 1, 2, 3>::operator=(const vec& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
	return *this;
}

inline vec<0, 1, 2, 3>::vec()
	: data{}
{
}

inline vec<0, 1, 2, 3>::vec(float x)
	: data{ x, x, x, x }
{
}

inline vec<0, 1, 2, 3>::vec(float x, float y, float z, float w)
	: data{ x, y, z, w }
{
}

inline vec<0, 1, 2, 3>::vec(const vec& v) : data{ v.x, v.y, v.z, v.w }
{
}

template<int a, int b, int c, int d>
inline vec<0, 1, 2, 3>::vec(const base<a, b, c, d>& v)
	: data{ *(float*)(&v + a), *(float*)(&v + b),  *(float*)(&v + c), *(float*)(&v + d) }
{
}

template<int a, int b>
inline vec<0, 1, 2, 3>::vec(float x, float y, const base<a, b>& v)
	: data{ x, y, *(float*)(&v + a),*(float*)(&v + b) }
{
}

template<int a, int b>
inline vec<0, 1, 2, 3>::vec(const base<a, b>& v, float z, float w)
	: data{ *(float*)(&v + a),*(float*)(&v + b), z, w }
{
}

template<int a, int b>
inline vec<0, 1, 2, 3>::vec(float x, const base<a, b>& v, float w)
	: data{ x, *(float*)(&v + a),*(float*)(&v + b), w }
{
}

template<int a, int b, int c, int d>
inline vec<0, 1, 2, 3>::vec(const base<a, b>& l, const base<c, d>& r)
	: data{ *(float*)(&l + a),*(float*)(&l + b), *(float*)(&r + c), *(float*)(&r + d) }
{
}

template<int a, int b, int c>
inline vec<0, 1, 2, 3>::vec(const base<a, b, c>& v, float w)
	: data{ *(float*)(&v + a), *(float*)(&v + b), *(float*)(&v + c), w }
{
}

template<int a, int b, int c>
inline vec<0, 1, 2, 3>::vec(float x, const base<a, b, c>& v)
	: data{ x, *(float*)(&v + a), *(float*)(&v + b), *(float*)(&v + c) }
{
}

template<int ...x>
inline typename vect<x...>::type base<x...>::copy() const
{
	return { *(float*)(this + x)... };
}

template<int ...x>
inline base<x...>::operator typename vect<x...>::type() const
{
	return { *(float*)(this + x)... };
}

template<int ...x>
inline typename vect<x...>::type base<x...>::operator-() const
{
	return { -*(float*)(this + x)... };
}

template<int ...x>
inline swizz<x...>& base<x...>::operator=(const base& v)
{
	((*(float*)(this + x) = *(float*)(&v + x)), ...);
	return *(swizz<x...>*)this;
}

template<int ...x>
template<int ...y>
inline swizz<x...>& base<x...>::operator=(const base<y...>& v)
{
	if ((float*)this == (float*)&v)
		return operator=(typename vect<y...>::type(v));
	((*(float*)(this + x) = *(float*)(&v + y)), ...);
	return *(swizz<x...>*)this;
}

template<int ...x>
template<int ...y>
inline swizz<x...>& base<x...>::operator+=(const base<y...>& v)
{
	if ((float*)this == (float*)&v)
		return operator=(typename vect<y...>::type(v));
	((*(float*)(this + x) += *(float*)(&v + y)), ...);
	return *(swizz<x...>*)this;
}

template<int ...x>
template<int ...y>
inline swizz<x...>& base<x...>::operator-=(const base<y...>& v)
{
	if ((float*)this == (float*)&v)
		return operator=(typename vect<y...>::type(v));
	((*(float*)(this + x) -= *(float*)(&v + y)), ...);
	return *(swizz<x...>*)this;
}

template<int ...x>
template<int ...y>
inline swizz<x...>& base<x...>::operator*=(const base<y...>& v)
{
	if ((float*)this == (float*)&v)
		return operator=(v.copy());
	((*(float*)(this + x) *= *(float*)(&v + y)), ...);
	return *(swizz<x...>*)this;
}

template<int ...x>
template<int ...y>
inline swizz<x...>& base<x...>::operator/=(const base<y...>& v)
{
	if ((float*)this == (float*)&v)
		return operator=(v.copy());
	((*(float*)(this + x) /= *(float*)(&v + y)), ...);
	return *(swizz<x...>*)this;
}

template<int ...x>
template<int ...y>
inline typename vect<x...>::type base<x...>::operator+(const base<y...>& v) const
{
	return { *(float*)(this + x) + *(float*)(&v + y)... };
}

template<int ...x>
template<int ...y>
inline typename vect<x...>::type base<x...>::operator-(const base<y...>& v) const
{
	return { *(float*)(this + x) - *(float*)(&v + y)... };
}

template<int ...x>
template<int ...y>
inline typename vect<x...>::type base<x...>::operator*(const base<y...>& v) const
{
	return { *(float*)(this + x) * *(float*)(&v + y)... };
}

template<int ...x>
template<int ...y>
inline typename vect<x...>::type base<x...>::operator/(const base<y...>& v) const
{
	return { *(float*)(this + x) / *(float*)(&v + y)... };
}

template<int ...x>
template<int ...y>
inline float base<x...>::dot(const base<y...>& v) const
{
	return ((*(float*)(this + x) * *(float*)(&v + y)) + ...);
}

template<int ...x>
template<int ...y>
inline float base<x...>::operator^(const base<y...>& v) const
{
	return  acosf(dot(v) / len() / v.len());
}

template<int ...x>
inline swizz<x...>& base<x...>::operator=(float n)
{
	((*(float*)(this + x) = n), ...);
	return *(swizz<x...>*)this;
}

template<int ...x>
inline swizz<x...>& base<x...>::operator+=(float n)
{
	((*(float*)(this + x) += n), ...);
	return *(swizz<x...>*)this;
}

template<int ...x>
inline swizz<x...>& base<x...>::operator-=(float n)
{
	((*(float*)(this + x) -= n), ...);
	return *(swizz<x...>*)this;
}

template<int ...x>
inline swizz<x...>& base<x...>::operator*=(float n)
{
	((*(float*)(this + x) *= n), ...);
	return *(swizz<x...>*)this;
}

template<int ...x>
inline swizz<x...>& base<x...>::operator/=(float n)
{
	n = 1.f / n;
	((*(float*)(this + x) *= n), ...);
	return *(swizz<x...>*)this;
}

template<int ...x>
inline typename vect<x...>::type base<x...>::operator+(float n) const
{
	return { *(float*)(this + x) + n... };
}

template<int ...x>
inline typename vect<x...>::type base<x...>::operator-(float n) const
{
	return { *(float*)(this + x) - n... };
}

template<int ...x>
inline typename vect<x...>::type base<x...>::operator*(float n) const
{
	return { *(float*)(this + x) * n... };
}

template<int ...x>
inline typename vect<x...>::type base<x...>::operator/(float n) const
{
	n = 1.f / n;
	return { *(float*)(this + x) * n... };
}

template<int ...x>
inline typename vect<x...>::type base<x...>::norm() const
{
	float l = 1.f / len();
	return { *(float*)(this + x) * l... };
}

template<int ...x>
inline swizz<x...>& base<x...>::xnorm()
{
	float l = 1.f / len();
	((*(float*)(this + x) *= l), ...);
	return *(swizz<x...>*)this;
}

template<int ...x>
inline float base<x...>::len() const
{
	return sqrtf(((*(float*)(this + x) * *(float*)(this + x)) + ...));
}

template<int ...x>
inline float base<x...>::len2() const
{
	return ((*(float*)(this + x) * *(float*)(this + x)) + ...);
}

template<int ...x>
inline std::ostream& operator<<(std::ostream& s, const base<x...>& v)
{
	((s << *(float*)(&v + x) << ' '), ...);
	return s << '\n';
}

template<int x, int y, int z, int x1, int y1, int z1>
inline vec<0, 1, 2> cross(const base<x, y, z>& l, const base<x1, y1, z1>& r)
{
	return
	{
		*(float*)(&l + y) * *(float*)(&r + z1) - *(float*)(&l + z) * *(float*)(&r + y1),
		*(float*)(&l + z) * *(float*)(&r + x1) - *(float*)(&l + x) * *(float*)(&r + z1),
		*(float*)(&l + x) * *(float*)(&r + y1) - *(float*)(&l + y) * *(float*)(&r + x1)
	};
}


inline vec<0, 1, 2> perp(const vec<0, 1, 2>& v) {
	struct bvec {
		bool x, y, z;
		bvec(const vec<0, 1, 2>& v) : x(absl(v.x) > FLT_EPSILON), y(absl(v.y) > FLT_EPSILON), z(absl(v.z) > FLT_EPSILON) {}
		inline operator int() const { return { x + y * 2 + z * 4 }; }
	};
	switch (bvec(v)) {
	case 1: return { 0.f, v.len(), 0.f }; //x
	case 2: return { 0.f, 0.f, v.len() }; //y
	case 4: return { v.len(), 0.f, 0.f }; //z
	case 3: return { -v.y, v.x,  0.f }; //xy
	case 5: return { v.z, 0.f, -v.x };  //xz
	case 6: return { 0.f, -v.z, v.y };  //yz
	case 7: return { -v.y * v.z, v.x * v.z, 0.f }; //xyz
	default: return {};
	}
}


inline vec<0, 1> norm(float x, float y) {
	float s = 1.f / sqrtf(x * x + y * y);
	if (!isN(s)) return 0;
	return { x * s, y * s };
}

inline vec<0, 1, 2> norm(float x, float y, float z) {
	float s = 1.f / sqrtf(x * x + y * y + z * z);
	if (!isN(s)) return 0;
	return { x * s, y * s, z * s };
}

inline vec<0, 1, 2, 3> norm(float x, float y, float z, float w) {
	float s = 1.f / sqrtf(x * x + y * y + z * z + w * w);
	if (!isN(s)) return 0;
	return { x * s, y * s, z * s, w * s };
}


inline vec<0, 1, 2, 3> cross(const vec<0, 1, 2, 3>& v1, const vec<0, 1, 2, 3>& v2, const vec<0, 1, 2, 3>& v3) {
	return {
	v1.yzw.dot(cross(v2.yzw, v3.yzw)),
	-v1.xzw.dot(cross(v2.xzw, v3.xzw)),
	v1.xyw.dot(cross(v2.xyw, v3.xyw)),
	-v1.xyz.dot(cross(v2.xyz, v3.xyz)) };
}


template<int x, int y, int x1, int y1>
inline mat2::mat2(const base<x, y>& a, const base<x1, y1>& b)
	: data
{
	*(float*)(&a + x), *(float*)(&a + x1),
	*(float*)(&b + y), *(float*)(&b + y1)
}
{
}


inline mat2::mat2()
	: data{ 1.f, 0.f, 0.f, 1.f }
{
}

inline mat2::mat2(float x)
	: data{ x, 0.f, 0.f, x }
{
}


inline mat2::mat2(float x, float y, float z, float w)
	: data{ x, y, z, w }
{
}


inline mat2::mat2(const mat2& m)
	: data{ *m.data, *(m.data + 1), *(m.data + 2), *(m.data + 3) }
{
}


inline mat2& mat2::operator=(const mat2& m)
{
	*data = *m.data;
	*(data + 1) = *(m.data + 1);
	*(data + 2) = *(m.data + 2);
	*(data + 3) = *(m.data + 3);
	return *this;
}


inline float mat2::det() const
{
	return *data * *(data + 3) - *(data + 1) * *(data + 2);
}


inline mat2 mat2::inv() const
{
	float det = 1.f / (*(data) * *(data + 3) - *(data + 1) * *(data + 2));
	return { det * *(data + 3), -det * *(data + 1), -det * *(data + 2), det * *(data) };
}


inline mat2 mat2::xpos() const
{
	return { *data, *(data + 2), *(data + 1), *(data + 3) };
}


inline mat2 mat2::operator*(const mat2& r) const
{
	return {
		*(data) * *(r.data) + *(data + 1) * *(r.data + 2),
		*(data) * *(r.data + 1) + *(data + 1) * *(r.data + 3),
		*(data + 2) * *(r.data) + *(data + 3) * *(r.data + 2),
		*(data + 2) * *(r.data + 1) + *(data + 3) * *(r.data + 3),
	};
}


template <int x, int y>
inline vec<0, 1> mat2::operator*(const base<x, y>& v) const
{
	return {
		*(float*)(&v + x) * *(data)+*(float*)(&v + y) * *(data + 1),
		*(float*)(&v + x) * *(data + 2) + *(float*)(&v + y) * *(data + 3),
	};
}


inline mat2& mat2::operator*=(float s)
{
	*data *= s;
	*(data + 1) *= s;
	*(data + 2) *= s;
	*(data + 3) *= s;
	return *this;
}


inline mat2& mat2::operator/=(float s)
{
	return operator*=(1.f / s);
}


inline mat2 mat2::operator*(float s) const
{
	return mat2(*this) *= s;
}


inline mat2 mat2::operator/(float s) const
{
	return mat2(*this) *= (1.f / s);
}



template <int x, int y, int z, int x1, int y1, int z1, int x2, int y2, int z2>
inline mat3::mat3(const base<x, y, z>& a, const base<x1, y1, z1>& b, const base<x2, y2, z2>& c)
	: data{ *(float*)(&a + x), *(float*)(&a + y), *(float*)(&a + z), *(float*)(&b + x1), *(float*)(&b + y1),
		*(float*)(&b + z1), *(float*)(&c + x2), *(float*)(&c + y2), *(float*)(&c + z2) }
{
}


inline  mat3::mat3()
	: data{ 1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f }
{
}


inline  mat3::mat3(float x)
	: data{ x, 0.f, 0.f, 0.f, x, 0.f, 0.f, 0.f, x }
{
}


inline  mat3::mat3(float x, float y, float z, float x1, float y1, float z1, float x2, float y2, float z2)
	: data{ x, y, z, x1, y1, z1, x2, y2, z2 }
{
}


inline  mat3::mat3(const mat3& m)
	: data{ *m.data, *(m.data + 1), *(m.data + 2), *(m.data + 3), *(m.data + 4), *(m.data + 5),
		*(m.data + 6), *(m.data + 7), *(m.data + 8) }
{
}


inline  mat3& mat3::operator=(const mat3& m)
{
	*data = *m.data;
	*(data + 1) = *(m.data + 1);
	*(data + 2) = *(m.data + 2);
	*(data + 3) = *(m.data + 3);
	*(data + 4) = *(m.data + 4);
	*(data + 5) = *(m.data + 5);
	*(data + 6) = *(m.data + 6);
	*(data + 7) = *(m.data + 7);
	*(data + 8) = *(m.data + 8);
	return *this;
}


inline float mat3::det() const
{
	return *(data) * (*(data + 4) * *(data + 8) - *(data + 5) * *(data + 7))
		+ *(data + 1) * (*(data + 5) * *(data + 6) - *(data + 3) * *(data + 8))
		+ *(data + 2) * (*(data + 3) * *(data + 7) - *(data + 4) * *(data + 6));
}

inline mat3 mat3::xpos() const
{
	return { *data, *(data + 3), *(data + 6), *(data + 1), *(data + 4), *(data + 7), *(data + 2),
		*(data + 5), *(data + 8) };
}


inline mat3 mat3::operator*(const mat3& r) const
{
	return {
		*(data) * *(r.data) + *(data + 1) * *(r.data + 3) + *(data + 2) * *(r.data + 6),
		*(data) * *(r.data + 1) + *(data + 1) * *(r.data + 4) + *(data + 2) * *(r.data + 7),
		*(data) * *(r.data + 2) + *(data + 1) * *(r.data + 5) + *(data + 2) * *(r.data + 8),

		*(data + 3) * *(r.data) + *(data + 4) * *(r.data + 3) + *(data + 5) * *(r.data + 6),
		*(data + 3) * *(r.data + 1) + *(data + 4) * *(r.data + 4) + *(data + 5) * *(r.data + 7),
		*(data + 3) * *(r.data + 2) + *(data + 4) * *(r.data + 5) + *(data + 5) * *(r.data + 8),

		*(data + 6) * *(r.data) + *(data + 7) * *(r.data + 3) + *(data + 8) * *(r.data + 6),
		*(data + 6) * *(r.data + 1) + *(data + 7) * *(r.data + 4) + *(data + 8) * *(r.data + 7),
		*(data + 6) * *(r.data + 2) + *(data + 7) * *(r.data + 5) + *(data + 8) * *(r.data + 8),
	};
}


template <int x, int y, int z>
inline vec<0, 1, 2> mat3::operator*(const base<x, y, z>& v) const
{
	return {
		*(float*)(&v + x) * *(data)+*(float*)(&v + y) * *(data + 1) + *(float*)(&v + z) * *(data + 2),
		*(float*)(&v + x) * *(data + 3) + *(float*)(&v + y) * *(data + 4) + *(float*)(&v + z) * *(data + 5),
		*(float*)(&v + x) * *(data + 6) + *(float*)(&v + y) * *(data + 7) + *(float*)(&v + z) * *(data + 8),
	};
}


inline float& mat3::operator()(int r, int c)
{
	return *(data + 3 * r + c);
}


inline float mat3::operator()(int r, int c) const
{
	return *(data + 3 * r + c);
}


inline mat3& mat3::operator*=(float s)
{
	*data *= s;
	*(data + 1) *= s;
	*(data + 2) *= s;
	*(data + 3) *= s;
	*(data + 4) *= s;
	*(data + 5) *= s;
	*(data + 6) *= s;
	*(data + 7) *= s;
	*(data + 8) *= s;
	return *this;
}


inline mat3 mat3::operator*(float s) const
{
	return mat3(*this) *= s;
}


inline mat3& mat3::operator/=(float s)
{
	return operator*=(1.f / s);
}


inline mat3 mat3::operator/(float s) const
{
	return mat3(*this) *= (1.f / s);
}



template <int x, int y, int z, int w, int x1, int y1, int z1, int w1, int x2, int y2, int z2,
	int w2, int x3, int y3, int z3, int w3>
	inline mat4::mat4(const base<x, y, z, w>& a, const base<x1, y1, z1, w1>& b,
		const base<x2, y2, z2, w2>& c, const base<x3, y3, z3, w3>& d)
	: data
{
		*(float*)(&a + x), *(float*)(&a + y), *(float*)(&a + z), *(float*)(&a + w),
		*(float*)(&b + x1), *(float*)(&b + y1), *(float*)(&b + z1), *(float*)(&b + w1),
		*(float*)(&c + x2), *(float*)(&c + y2), *(float*)(&c + z2), *(float*)(&c + w2),
		*(float*)(&d + x3), *(float*)(&d + y3), *(float*)(&d + z3), *(float*)(&d + w3),
}
{
}


inline mat4::mat4()
	: data{ 1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f }
{
}

inline mat4::mat4(float x)
	: data{ x, 0.f, 0.f, 0.f, 0.f, x, 0.f, 0.f, 0.f, 0.f, x, 0.f, 0.f, 0.f, 0.f, 1.f }
{
}


inline mat4::mat4(
	float x, float y, float z, float w, float x1, float y1, float z1, float w1, float x2, float y2, float z2, float w2, float x3, float y3, float z3, float w3)
	: data{ x, y, z, w, x1, y1, z1, w1, x2, y2, z2, w2, x3, y3, z3, w3 }
{
}


inline mat4::mat4(const mat4& m)
	: data{ *m.data, *(m.data + 1), *(m.data + 2), *(m.data + 3), *(m.data + 4), *(m.data + 5),
		*(m.data + 6), *(m.data + 7), *(m.data + 8), *(m.data + 9), *(m.data + 10), *(m.data + 11),
		*(m.data + 12), *(m.data + 13), *(m.data + 14), *(m.data + 15) }
{
}


inline mat4& mat4::operator=(const mat4& m)
{
	*data = *m.data;
	*(data + 1) = *(m.data + 1);
	*(data + 2) = *(m.data + 2);
	*(data + 3) = *(m.data + 3);
	*(data + 4) = *(m.data + 4);
	*(data + 5) = *(m.data + 5);
	*(data + 6) = *(m.data + 6);
	*(data + 7) = *(m.data + 7);
	*(data + 8) = *(m.data + 8);
	*(data + 9) = *(m.data + 9);
	*(data + 10) = *(m.data + 10);
	*(data + 11) = *(m.data + 11);
	*(data + 12) = *(m.data + 12);
	*(data + 13) = *(m.data + 13);
	*(data + 14) = *(m.data + 14);
	*(data + 15) = *(m.data + 15);
	return *this;
}


inline float mat4::det() const
{
	float det_08_09 = (*(data + 8) * *(data + 13) - *(data + 9) * *(data + 12));
	float det_08_10 = (*(data + 8) * *(data + 14) - *(data + 10) * *(data + 12));
	float det_08_11 = (*(data + 8) * *(data + 15) - *(data + 11) * *(data + 12));
	float det_09_10 = (*(data + 9) * *(data + 14) - *(data + 10) * *(data + 13));
	float det_09_11 = (*(data + 9) * *(data + 15) - *(data + 11) * *(data + 13));
	float det_10_11 = (*(data + 10) * *(data + 15) - *(data + 11) * *(data + 14));
	return *(data)
		* (*(data + 5) * (det_10_11)-*(data + 6) * (det_09_11)+*(data + 7) * (det_09_10))
		- *(data + 1)
		* (*(data + 4) * (det_10_11)-*(data + 6) * (det_08_11)+*(data + 7) * (det_08_10))
		+ *(data + 2)
		* (*(data + 4) * (det_09_11)-*(data + 5) * (det_08_11)+*(data + 7) * (det_08_09))
		- *(data + 3)
		* (*(data + 4) * (det_09_10)-*(data + 5) * (det_08_10)+*(data + 6) * (det_08_09));
}


inline mat4 mat4::inv() const
{
	float zw0 = *(data + 10) * *(data + 15) - *(data + 11) * *(data + 14);
	float yw0 = *(data + 9) * *(data + 15) - *(data + 11) * *(data + 13);
	float yz0 = *(data + 9) * *(data + 14) - *(data + 10) * *(data + 13);
	float xw0 = *(data + 8) * *(data + 15) - *(data + 11) * *(data + 12);
	float xz0 = *(data + 8) * *(data + 14) - *(data + 10) * *(data + 12);
	float xy0 = *(data + 8) * *(data + 13) - *(data + 9) * *(data + 12);

	float zw1 = *(data + 3) * *(data + 14) - *(data + 2) * *(data + 15);
	float yw1 = *(data + 3) * *(data + 13) - *(data + 1) * *(data + 15);
	float yz1 = *(data + 2) * *(data + 13) - *(data + 1) * *(data + 14);
	float xw1 = *(data + 3) * *(data + 12) - *(data + 0) * *(data + 15);
	float xz1 = *(data + 2) * *(data + 12) - *(data + 0) * *(data + 14);
	float xy1 = *(data + 1) * *(data + 12) - *(data + 0) * *(data + 13);

	float zw2 = *(data + 2) * *(data + 7) - *(data + 3) * *(data + 6);
	float yw2 = *(data + 1) * *(data + 7) - *(data + 3) * *(data + 5);
	float yz2 = *(data + 1) * *(data + 6) - *(data + 2) * *(data + 5);
	float xw2 = *(data) * *(data + 7) - *(data + 3) * *(data + 4);
	float xz2 = *(data) * *(data + 6) - *(data + 2) * *(data + 4);
	float xy2 = *(data) * *(data + 5) - *(data + 1) * *(data + 4);

	float zw3 = *(data + 11) * *(data + 6) - *(data + 10) * *(data + 7);
	float yw3 = *(data + 11) * *(data + 5) - *(data + 9) * *(data + 7);
	float yz3 = *(data + 10) * *(data + 5) - *(data + 9) * *(data + 6);
	float xw3 = *(data + 11) * *(data + 4) - *(data + 8) * *(data + 7);
	float xz3 = *(data + 10) * *(data + 4) - *(data + 8) * *(data + 6);
	float xy3 = *(data + 9) * *(data + 4) - *(data + 8) * *(data + 5);

	float x0 = *(data + 5) * zw0 - *(data + 6) * yw0 + *(data + 7) * yz0;
	float y0 = *(data + 4) * zw0 - *(data + 6) * xw0 + *(data + 7) * xz0;
	float z0 = *(data + 4) * yw0 - *(data + 5) * xw0 + *(data + 7) * xy0;
	float w0 = *(data + 4) * yz0 - *(data + 5) * xz0 + *(data + 6) * xy0;

	float x1 = *(data + 9) * zw1 - *(data + 10) * yw1 + *(data + 11) * yz1;
	float y1 = *(data + 8) * zw1 - *(data + 10) * xw1 + *(data + 11) * xz1;
	float z1 = *(data + 8) * yw1 - *(data + 9) * xw1 + *(data + 11) * xy1;
	float w1 = *(data + 8) * yz1 - *(data + 9) * xz1 + *(data + 10) * xy1;

	float x2 = *(data + 13) * zw2 - *(data + 14) * yw2 + *(data + 15) * yz2;
	float y2 = *(data + 12) * zw2 - *(data + 14) * xw2 + *(data + 15) * xz2;
	float z2 = *(data + 12) * yw2 - *(data + 13) * xw2 + *(data + 15) * xy2;
	float w2 = *(data + 12) * yz2 - *(data + 13) * xz2 + *(data + 14) * xy2;

	float x3 = *(data + 1) * zw3 - *(data + 2) * yw3 + *(data + 3) * yz3;
	float y3 = *(data)*zw3 - *(data + 2) * xw3 + *(data + 3) * xz3;
	float z3 = *(data)*yw3 - *(data + 1) * xw3 + *(data + 3) * xy3;
	float w3 = *(data)*yz3 - *(data + 1) * xz3 + *(data + 2) * xy3;

	float det = 1.f / (*(data)*x0 - *(data + 1) * y0 + *(data + 2) * z0 - *(data + 3) * w0);
	return { det * x0, det * -x1, det * x2, det * -x3, det * -y0, det * y1, det * -y2, det * y3,
		det * z0, det * -z1, det * z2, det * -z3, det * -w0, det * w1, det * -w2, det * w3 };
}


inline mat4 mat4::xpos() const
{
	return { *data, *(data + 4), *(data + 8), *(data + 12), *(data + 1), *(data + 5), *(data + 9),
		*(data + 13), *(data + 2), *(data + 6), *(data + 10), *(data + 14), *(data + 3),
		*(data + 7), *(data + 11), *(data + 15) };
}


inline mat4 mat4::operator*(const mat4& r) const
{
	return { *(data) * *(r.data) + *(data + 1) * *(r.data + 4) + *(data + 2) * *(r.data + 8)
			+ *(data + 3) * *(r.data + 12),
		*(data) * *(r.data + 1) + *(data + 1) * *(r.data + 5) + *(data + 2) * *(r.data + 9)
			+ *(data + 3) * *(r.data + 13),
		*(data) * *(r.data + 2) + *(data + 1) * *(r.data + 6) + *(data + 2) * *(r.data + 10)
			+ *(data + 3) * *(r.data + 14),
		*(data) * *(r.data + 3) + *(data + 1) * *(r.data + 7) + *(data + 2) * *(r.data + 11)
			+ *(data + 3) * *(r.data + 15),

		*(data + 4) * *(r.data) + *(data + 5) * *(r.data + 4) + *(data + 6) * *(r.data + 8)
			+ *(data + 7) * *(r.data + 12),
		*(data + 4) * *(r.data + 1) + *(data + 5) * *(r.data + 5) + *(data + 6) * *(r.data + 9)
			+ *(data + 7) * *(r.data + 13),
		*(data + 4) * *(r.data + 2) + *(data + 5) * *(r.data + 6) + *(data + 6) * *(r.data + 10)
			+ *(data + 7) * *(r.data + 14),
		*(data + 4) * *(r.data + 3) + *(data + 5) * *(r.data + 7) + *(data + 6) * *(r.data + 11)
			+ *(data + 7) * *(r.data + 15),

		*(data + 8) * *(r.data) + *(data + 9) * *(r.data + 4) + *(data + 10) * *(r.data + 8)
			+ *(data + 11) * *(r.data + 12),
		*(data + 8) * *(r.data + 1) + *(data + 9) * *(r.data + 5) + *(data + 10) * *(r.data + 9)
			+ *(data + 11) * *(r.data + 13),
		*(data + 8) * *(r.data + 2) + *(data + 9) * *(r.data + 6) + *(data + 10) * *(r.data + 10)
			+ *(data + 11) * *(r.data + 14),
		*(data + 8) * *(r.data + 3) + *(data + 9) * *(r.data + 7) + *(data + 10) * *(r.data + 11)
			+ *(data + 11) * *(r.data + 15),

		*(data + 12) * *(r.data) + *(data + 13) * *(r.data + 4) + *(data + 14) * *(r.data + 8)
			+ *(data + 15) * *(r.data + 12),
		*(data + 12) * *(r.data + 1) + *(data + 13) * *(r.data + 5) + *(data + 14) * *(r.data + 9)
			+ *(data + 15) * *(r.data + 13),
		*(data + 12) * *(r.data + 2) + *(data + 13) * *(r.data + 6) + *(data + 14) * *(r.data + 10)
			+ *(data + 15) * *(r.data + 14),
		*(data + 12) * *(r.data + 3) + *(data + 13) * *(r.data + 7) + *(data + 14) * *(r.data + 11)
			+ *(data + 15) * *(r.data + 15) };
}


template <int x, int y, int z, int w>
inline vec<0, 1, 2, 3> mat4::operator*(const base<x, y, z, w>& v) const
{
	return { *(float*)(&v + x) * *(data)+*(float*)(&v + y) * *(data + 1) + *(float*)(&v + z) * *(data + 2)
			+ *(float*)(&v + w) * *(data + 3),
		*(float*)(&v + x) * *(data + 4) + *(float*)(&v + y) * *(data + 5) + *(float*)(&v + z) * *(data + 6)
			+ *(float*)(&v + w) * *(data + 7),
		*(float*)(&v + x) * *(data + 8) + *(float*)(&v + y) * *(data + 9) + *(float*)(&v + z) * *(data + 10)
			+ *(float*)(&v + w) * *(data + 11),
		*(float*)(&v + x) * *(data + 12) + *(float*)(&v + y) * *(data + 13) + *(float*)(&v + z) * *(data + 14)
			+ *(float*)(&v + w) * *(data + 15) };
}


inline float& mat4::operator()(int r, int c)
{
	return *(data + 4 * r + c);
}


inline float mat4::operator()(int r, int c) const
{
	return *(data + 4 * r + c);
}


inline mat4& mat4::operator*=(float s)
{
	*data *= s;
	*(data + 1) *= s;
	*(data + 2) *= s;
	*(data + 3) *= s;
	*(data + 4) *= s;
	*(data + 5) *= s;
	*(data + 6) *= s;
	*(data + 7) *= s;
	*(data + 8) *= s;
	*(data + 9) *= s;
	*(data + 10) *= s;
	*(data + 11) *= s;
	*(data + 12) *= s;
	*(data + 13) *= s;
	*(data + 14) *= s;
	*(data + 15) *= s;
	return *this;
}


inline mat4& mat4::operator/=(float s)
{
	return mat4::operator*=(1.f / s);
}


inline mat4 mat4::operator*(float s) const
{
	return mat4(*this) *= s;
}


inline mat4 mat4::operator/(float s) const
{
	return mat4(*this) *= (1.f / s);
}


inline mat3 rotx(float angle)
{
	float c = cosf(angle), s = sinf(angle);
	return
	{
		1.f, 0.f, 0.f,
		0.f, c, -s,
		0.f, s, c
	};
}

inline mat3 roty(float angle)
{
	float c = cosf(angle), s = sinf(angle);
	return
	{
		  c, 0.f, s,
		0.f, 1.f, 0.f,
		 -s, 0.f, c
	};
}

inline mat3 rotz(float angle)
{
	float c = cosf(angle), s = sinf(angle);
	return
	{
		c, -s, 0.f,
		s, c, 0.f,
		0.f, 0.f, 1.f
	};
}

inline mat4 perspective(float fov, float aspect, float n, float f) {
	float tan = 1.f / float(tanf(fov * ct::rad * 0.5f));
	float fn = 1.f / (f - n);
	return{
		tan * aspect,	0.f,			0.f,		 0.f,
			0.f,		tan,			0.f,		 0.f,
			0.f,		0.f,		-fn * (f + n),	-1.f,
			0.f,		0.f,	 -2.f * f * n * fn,	 0.f
	};

}


inline mat4 ortho(float l, float r, float b, float t) {
	float rl = 1.f / (r - l);
	float tb = 1.f / (t - b);
	return {
		2.f * rl,				0.f,			 0.f,		0.f,
			 0.f,		   2.f * tb,			 0.f,		0.f,
			 0.f,				0.f,			 1.f,		0.f,
		-rl * (r + l), -tb * (t + b),			0.f,		1.f
	};
}


inline mat4 ortho(float l, float r, float b, float t, float n, float f) {
	float rl = 1.f / (r - l);
	float tb = 1.f / (t - b);
	float fn = 1.f / (f - n);
	return {
		2.f * rl,			 0.f,			 0.f,		0.f,
			 0.f,		2.f * tb,			 0.f,		0.f,
			 0.f,			 0.f,		2.f * fn,		0.f,
		-rl * (r + l), -tb * (t + b), -fn * (f + n),	1.f
	};
}


inline mat4 view(const vec<0, 1, 2>& p, const vec<0, 1, 2>& r, const vec<0, 1, 2>& u, const vec<0, 1, 2>& d) {
	return{
		r.x, u.x, d.x, 0.f,
		r.y, u.y, d.y, 0.f,
		r.z, u.z, d.z, 0.f,
		-r.dot(p), -u.dot(p), -d.dot(p), 1.f
	};
}

template<int x, int y>
inline vec<0, 1> operator *(const base<x, y>& v, const mat2& m) {
	return {
		*(float*)(&v + x) * *(m.data) + *(float*)(&v + y) * *(m.data + 2),
		*(float*)(&v + x) * *(m.data + 1) + *(float*)(&v + y) * *(m.data + 3),
	};
}

template<int x, int y, int z>
inline  vec<0, 1, 2> operator *(const base<x, y, z>& v, const mat3& m) {
	return {
		*(float*)(&v + x) * *(m.data) + *(float*)(&v + y) * *(m.data + 3) + *(float*)(&v + z) * *(m.data + 6),
		*(float*)(&v + x) * *(m.data + 1) + *(float*)(&v + y) * *(m.data + 4) + *(float*)(&v + z) * *(m.data + 7),
		*(float*)(&v + x) * *(m.data + 2) + *(float*)(&v + y) * *(m.data + 5) + *(float*)(&v + z) * *(m.data + 8),
	};
}
template<int x, int y, int z, int w>
inline vec<0, 1, 2, 3> operator *(const base<x, y, z, w>& v, const mat4& m) {
	return {
		*(float*)(&v + x) * *(m.data) + *(float*)(&v + y) * *(m.data + 4) + *(float*)(&v + z) * *(m.data + 8) + *(float*)(&v + w) * *(m.data + 12),
		*(float*)(&v + x) * *(m.data + 1) + *(float*)(&v + y) * *(m.data + 5) + *(float*)(&v + z) * *(m.data + 9) + *(float*)(&v + w) * *(m.data + 13),
		*(float*)(&v + x) * *(m.data + 2) + *(float*)(&v + y) * *(m.data + 6) + *(float*)(&v + z) * *(m.data + 10) + *(float*)(&v + w) * *(m.data + 14),
		*(float*)(&v + x) * *(m.data + 3) + *(float*)(&v + y) * *(m.data + 7) + *(float*)(&v + z) * *(m.data + 11) + *(float*)(&v + w) * *(m.data + 15)
	};
}

template<int x, int y, int z>
inline vec<0, 1, 2> operator * (const base<x, y, z>& v, const quat& q) {
	float _x = *(float*)(&v + y) * q.k - *(float*)(&v + z) * q.j + *(float*)(&v + x) * q.s;
	float _y = *(float*)(&v + z) * q.i - *(float*)(&v + x) * q.k + *(float*)(&v + y) * q.s;
	float _z = *(float*)(&v + x) * q.j - *(float*)(&v + y) * q.i + *(float*)(&v + z) * q.s;
	float _w = *(float*)(&v + x) * q.i + *(float*)(&v + y) * q.j + *(float*)(&v + z) * q.k;
	return vec3(_y * q.k - _z * q.j + _x * q.s + q.i * _w,
		_z * q.i - _x * q.k + _y * q.s + q.j * _w,
		_x * q.j - _y * q.i + _z * q.s + q.k * _w);
}


template <int a, int b, int c>
inline quat::quat(const base<a, b, c>& v, float w)
	: data{ *(float*)(&v + a), *(float*)(&v + b), *(float*)(&v + c), w }
{
}


inline quat::quat()
	: data{ 0.f, 0.f, 0.f, 1.f }
{
}

inline quat::quat(float x, float y, float z, float w)
	: data{ x, y, z, w }
{
}

inline quat::quat(const vec<0, 1, 2>& v, float w)
	: data{ v.x, v.y, v.z, w }
{
}

inline quat::quat(const quat& q)
	: data{ q.x, q.y, q.z, q.w }
{
}

inline float quat::len() const
{
	return sqrtf(x * x + y * y + z * z + w * w);
}

inline float quat::len2() const
{
	return x * x + y * y + z * z + w * w;
}

inline quat& quat::operator=(const quat& q)
{
	x = q.x, y = q.y, z = q.z, w = q.w;
	return *this;
}

inline quat quat::operator~() const
{
	return { -x, -y, -z, w };
}

inline quat quat::operator-() const
{
	return { -x, -y, -z, -w };
}

inline quat& quat::operator+=(const quat& q)
{
	x += q.x, y += q.y, z += q.z, w += q.w;
	return *this;
}

inline quat& quat::operator-=(const quat& q)
{
	x -= q.x, y -= q.y, z -= q.z, w -= q.w;
	return *this;
}

inline quat quat::operator+(const quat& q) const
{
	return quat(*this) += q;
}

inline quat quat::operator-(const quat& q) const
{
	return quat(*this) -= q;
}

inline quat& quat::operator*=(float s)
{
	x *= s, y *= s, z *= s, w *= s;
	return *this;
}

inline quat& quat::operator/=(float s)
{
	s = 1.f / s;
	x *= s, y *= s, z *= s, w *= s;
	return *this;
}

inline quat quat::operator*(float s)
{
	return { x * s, y * s, z * s, w * s };
}

inline quat quat::operator/(float s)
{
	s = 1.f / s;
	return { x * s, y * s, z * s, w * s };
}

inline quat operator*(float s, const quat& q)
{
	return { q.x * s, q.y * s, q.z * s, q.w * s };
}

inline quat operator/(float s, const quat& q)
{
	s /= q.len2();
	return ~q *= s;
}

inline quat quat::operator/(const quat& q) const
{
	return (*this * ~q) /= q.len2();
}

inline quat quat::operator*=(const quat& q)
{
	return *this = *this * q;
}

inline quat quat::operator/=(const quat& q)
{
	return *this = *this / q;
}

inline quat quat::operator*(const quat& q) const
{
	return { s * q.i + i * q.s + j * q.k - k * q.j, s * q.j + j * q.s + k * q.i - i * q.k,
		s * q.k + k * q.s + i * q.j - j * q.i, s * q.s - i * q.i - j * q.j - k * q.k };
}

inline quat::operator mat3() const
{
	float i2 = i + i, j2 = j + j, k2 = k + k;
	float ii = i * i2, ij = i * j2, ik = i * k2;
	float jj = j * j2, jk = j * k2, kk = k * k2;
	float si = s * i2, sj = s * j2, sk = s * k2;
	return { 1.f - (jj + kk), ij - sk, ik + sj, ij + sk, 1.f - (ii + kk), jk - si, ik - sj, jk + si,
		1.f - (ii + jj) };
}

inline quat::operator mat4() const
{
	float i2 = i + i, j2 = j + j, k2 = k + k;
	float ii = i * i2, ij = i * j2, ik = i * k2;
	float jj = j * j2, jk = j * k2, kk = k * k2;
	float si = s * i2, sj = s * j2, sk = s * k2;
	return { 1.f - (jj + kk), ij - sk, ik + sj, 0, ij + sk, 1.f - (ii + kk), jk - si, 0, ik - sj,
		jk + si, 1.f - (ii + jj), 0, 0, 0, 0, 1 };
}

template<int a, int b, int c>
inline vec<0, 1, 2> quat::operator *(const base<a, b, c>& v) const
{
	float _x = j * *(float*)(&v + c) - k * *(float*)(&v + b) + s * *(float*)(&v + a);
	float _y = k * *(float*)(&v + a) - i * *(float*)(&v + c) + s * *(float*)(&v + b);
	float _z = i * *(float*)(&v + b) - j * *(float*)(&v + a) + s * *(float*)(&v + c);
	float _w = i * *(float*)(&v + a) + j * *(float*)(&v + b) + k * *(float*)(&v + c);
	return { j * _z - k * _y + s * _x + i * _w, k * _x - i * _z + s * _y + j * _w,
		i * _y - j * _x + s * _z + k * _w };
}

template<class T>
inline t_vec2<T>::t_vec2() : x(), y()
{
}

template<class T>
inline t_vec2<T>::t_vec2(T x, T y) : x(x), y(y)
{
}

template<class T>
inline t_vec2<T>::t_vec2(const vec2& v) : x(v.x), y(v.y)
{
}

template<class T>
inline t_vec2<T>::t_vec2(const t_vec2& v) : x(v.x), y(v.y)
{
}

template<class T>
inline t_vec2<T>::operator vec2()
{
	return vec2(x, y);
}

template<class T>
inline t_vec3<T>::t_vec3() : x(), y(), z()
{
}

template<class T>
inline t_vec3<T>::t_vec3(T x, T y, T z) : x(x), y(y), z(z)
{
}

template<class T>
inline t_vec3<T>::t_vec3(const vec3& v) : x(v.x), y(v.y), z(v.z)
{
}

template<class T>
inline t_vec3<T>::t_vec3(const t_vec3& v) : x(v.x), y(v.y), z(v.z)
{
}

template<class T>
inline t_vec3<T>::operator vec3()
{
	return vec3(x, y, z);
}

template<class T>
inline t_vec4<T>::t_vec4() : x(), y(), z(), w()
{
}

template<class T>
inline t_vec4<T>::t_vec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w)
{
}

template<class T>
inline t_vec4<T>::t_vec4(const vec4& v) : x(v.x), y(v.y), z(v.z), w(v.w)
{
}

template<class T>
inline t_vec4<T>::t_vec4(const t_vec4& v) : x(v.x), y(v.y), z(v.z), w(v.w)
{
}

template<class T>
inline t_vec4<T>::operator vec4()
{
	return vec4(x, y, z, w);
}

inline xfstr tostr(float x) {
	const uint len = static_cast<uint>(_scprintf("%f", x));
	xfstr re(len);
	sprintf_s(re.data(), len + 1, "%f", x);
	return re;
}

inline xfstr tostr(double x) {
	const uint len = static_cast<uint>(_scprintf("%f", x));
	xfstr re(len);
	sprintf_s(re.data(), len + 1, "%f", x);
	return re;
}

inline xfstr tostr(long x) {
	const uint len = static_cast<uint>(_scprintf("%d", x));
	xfstr re(len);
	sprintf_s(re.data(), len + 1, "%d", x);
	return re;
}

inline xfstr tostr(unsigned long x) {
	const uint len = static_cast<uint>(_scprintf("%ul", x));
	xfstr re(len);
	sprintf_s(re.data(), len + 1, "%ul", x);
	return re;
}

inline xfstr tostr(int x) {
	const uint len = static_cast<uint>(_scprintf("%d", x));
	xfstr re(len);
	sprintf_s(re.data(), len + 1, "%d", x);
	return re;
}

inline xfstr tostr(uint x) {
	const uint len = static_cast<uint>(_scprintf("%d", x));
	xfstr re(len);
	sprintf_s(re.data(), len + 1, "%d", x);
	return re;
}

inline xfstr tostr(const vec2& v) {
	return (tostr(v.x) + ' ' + tostr(v.y));
}

inline xfstr tostr(const vec3& v) {
	return (tostr(v.x) + ' ' + tostr(v.y) + ' ' + tostr(v.z));
}

inline xfstr tostr(const vec4& v) {
	return (tostr(v.x) + ' ' + tostr(v.y) + ' ' +
		tostr(v.z) + ' ' + tostr(v.w));
}

inline mat2 m2id;
inline mat3 m3id;
inline mat4 m4id;
