#pragma once
#include <iostream>
#include <fstream>
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
	static constexpr float intmax = 1.f / INT_MAX;
	inline static std::mt19937 m = std::mt19937((uint)time(0));
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

template<class> class xfvec;

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
	bool operator <  (const xfstr&) const;
	bool operator <= (const xfstr&) const;
	bool operator >  (const xfstr&) const;
	bool operator >= (const xfstr&) const;

	xfstr& operator << (int n);
	xfstr& operator << (uint n);
	xfstr& operator << (long);
	xfstr& operator << (unsigned long);
	xfstr& operator << (float);
	xfstr& operator << (double);
	xfstr& operator >> (long& n);
	xfstr& operator >> (unsigned long&);
	xfstr& operator >> (int& n);
	xfstr& operator >> (uint& n);
	xfstr& operator >> (float&);
	xfstr& operator >> (double&);
	xfstr& read(const char*);
	std::istream& getline(std::istream&, char = '\n');
	void erase(char*, char*);
	void erase(char* i);
	const char* c_str() const;
	operator const char* () const;
	uint count(const char*) const;
	char* find(const char*, uint = 1) const;
	char* find(const char*, char*, uint = 1) const;
	char* find(char, size_t = 1) const;
	char* findif(bool (*f)(char), size_t = 1) const;
	char* find(char, char*, char*, size_t = 1) const;
	char* findif(bool (*f)(char), char*, char*, size_t = 1) const;
	xfstr substr(const char*, const char*, uint = 1);
	xfstr inbtwn(char a, char b) const;
	xfstr exbtwn(char a, char b) const;
	xfstr substr(size_t, size_t) const;
	xfstr substr(size_t) const;
	xfstr map(char(*f)(char)) const;
	xfstr& cls();
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
xfstr tostr(float x);
xfstr tostr(double x);
xfstr tostr(long x);
xfstr tostr(unsigned long x);
xfstr tostr(int x);

inline xfstr tostr(uint x);
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
	void reverse();
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

template<class c1, class c2>
struct xfcouple
{
	c1 first;
	c2 second;
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
	inline static xfpair<key, val>* i, * j;
	key k;
	xfvec<xfpair<key, val>>& data;
	vref(const key&, xfvec<xfpair<key, val>>&);
public:
	val& operator =  (const val&);
	val& operator += (const val&);
	val& operator -= (const val&);
	val& operator *= (const val&);
	val& operator /= (const val&);
	operator const val& () const;
	const val& ref() const;
};

template<class key, class val>
class xfmap {
protected:
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
	xfvec<xfpair<key, val>>& container();
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


template<class T, uint...> struct base;
template<class T, uint...> struct swizz;
template<class T, uint> struct vec;

using  vec2 = vec<float, 2>;
using ivec2 = vec<int, 2>;
using uvec2 = vec<uint, 2>;
using  vec3 = vec<float, 3>;
using ivec3 = vec<int, 3>;
using uvec3 = vec<uint, 3>;
using  vec4 = vec<float, 4>;
using ivec4 = vec<int, 4>;
using uvec4 = vec<uint, 4>;

template<template<class, uint...> class V, class T, uint h, uint... t>
struct type_proxy : type_proxy<V, T, h - 1, h - 1, t...>
{
};

template<template<class, uint...> class V, class T, uint...t>
struct type_proxy <V, T, 0, t...>
{
	using type = V<T, t...>;

	template<uint n>
	struct mul
	{
		using type = V<T, n * t...>;
	};
};

template<class T, uint n>
using dvec = typename type_proxy<swizz, T, n>::template mul<n + 1>::type;
template<class T, uint n>
using cvec = typename type_proxy<swizz, T, n>::template mul<n>::type;

using cvec2 = cvec<float, 2>;
using cvec3 = cvec<float, 3>;
using cvec4 = cvec<float, 4>;
using dvec2 = dvec<float, 2>;
using dvec3 = dvec<float, 3>;
using dvec4 = dvec<float, 4>;

template<class T, uint...x>
struct alignas(sizeof(T)) base
{
	operator vec<T, sizeof...(x)>() const;
	swizz<T, x...>& operator = (const base & v);
	template<uint ...y>	swizz<T, x...>& operator =  (const base<T, y...> & v);
	template<uint ...y>	swizz<T, x...>& operator += (const base<T, y...> & v);
	template<uint ...y>	swizz<T, x...>& operator -= (const base<T, y...> & v);
	template<uint ...y>	swizz<T, x...>& operator *= (const base<T, y...> & v);
	template<uint ...y>	swizz<T, x...>& operator /= (const base<T, y...> & v);

	template<uint ...y>	vec<T, sizeof...(x)> operator + (const base<T, y...> & v) const;
	template<uint ...y>	vec<T, sizeof...(x)> operator - (const base<T, y...> & v) const;
	template<uint ...y>	vec<T, sizeof...(x)> operator * (const base<T, y...> & v) const;
	template<uint ...y>	vec<T, sizeof...(x)> operator / (const base<T, y...> & v) const;

	swizz<T, x...>& operator =  (T n);
	swizz<T, x...>& operator += (T n);
	swizz<T, x...>& operator -= (T n);
	swizz<T, x...>& operator *= (T n);
	swizz<T, x...>& operator /= (T n);

	vec<T, sizeof...(x)> operator + (T n) const;
	vec<T, sizeof...(x)> operator - (T n) const;
	vec<T, sizeof...(x)> operator * (T n) const;
	vec<T, sizeof...(x)> operator / (T n) const;

	vec<T, sizeof...(x)> norm() const;
	vec<T, sizeof...(x)> operator -() const;
	swizz<T, x...>& operator ~();

	template<uint ...y>
	T operator ^ (const base<T, y...> & v) const;
	template<uint ...y>
	vec<T, sizeof...(x)> operator % (const base<T, y...> & v) const;
	T len() const;
	T operator !() const;
	template<uint ...y>
	bool operator == (const base<T, y...> & v) const;
	template<uint ...y>
	bool operator != (const base<T, y...> & v) const;
	template<uint ...y>
	bool operator < (const base<T, y...> & v) const;
	template<uint ...y>
	bool operator <= (const base<T, y...> & v) const;
	template<uint ...y>
	bool operator > (const base<T, y...> & v) const;
	template<uint ...y>
	bool operator >= (const base<T, y...> & v) const;

	T& operator [](uint n) const;
};

template<class T, uint...x>
std::ostream& operator << (std::ostream&, const base<T, x...>& v);
template<class T, uint...x>
xfstr tostr(const base<T, x...>& v);
template<class T, uint...x, uint...y>
T dot(const base<T, x...>& l, const base<T, y...>& r);
template<class T, uint x, uint y, uint z, uint x1, uint y1, uint z1>
vec<T, 3> cross(const base<T, x, y, z>& l, const base<T, x1, y1, z1>& r);
template<class T>
vec<T, 3> perp(const vec<T, 3>& v);
template<class T>
vec<T, 2> norm(T x, T y);
template<class T>
vec<T, 3> norm(T x, T y, T z);
template<class T>
vec<T, 4> norm(T x, T y, T z, T w);

template <class T, uint x>
struct alignas(sizeof(T)) swizz<T, x>
{
	T& operator  =(T f);
	T& operator +=(T f);
	T& operator -=(T f);
	T& operator *=(T f);
	T& operator /=(T f);
	operator T& ();
	operator T() const;
};

template<class T, uint x, uint y>
struct swizz<T, x, y> : base<T, x, y> {
	using base<T, x, y>::operator=;
	swizz& operator=(const swizz&);
	template<uint a, uint b>
	swizz& operator=(const swizz<T, a, b>&);
	union {
		base<T, x, y> xy;
		base<T, y, x> yx;
		swizz<T, x> x;
		swizz<T, y> y;
	};
};

template<class T, uint x, uint y, uint z>
struct swizz<T, x, y, z> : base<T, x, y, z> {
	using base<T, x, y, z>::operator=;
	swizz& operator=(const swizz&);
	template<uint a, uint b, uint c>
	swizz& operator=(const swizz<T, a, b, c>&);
	union {
		swizz<T, x, y> xy;
		swizz<T, x, z> xz;
		swizz<T, y, x> yx;
		swizz<T, y, z> yz;
		swizz<T, z, x> zx;
		swizz<T, z, y> zy;
		base<T, x, y, z> xyz;
		base<T, x, z, y> xzy;
		base<T, y, x, z> yxz;
		base<T, y, z, x> yzx;
		base<T, z, x, y> zxy;
		base<T, z, y, x> zyx;
		swizz<T, x> x;
		swizz<T, y> y;
		swizz<T, z> z;
	};
};

template<class T, uint x, uint y, uint z, uint w>
struct swizz<T, x, y, z, w> : base<T, x, y, z, w> {
	using base<T, x, y, z, w>::operator=;
	swizz& operator=(const swizz&);
	template<uint a, uint b, uint c, uint d>
	swizz& operator=(const swizz<T, a, b, c, d>&);
	union {
		swizz<T, x, y> xy;
		swizz<T, x, z> xz;
		swizz<T, x, w> xw;
		swizz<T, y, x> yx;
		swizz<T, y, z> yz;
		swizz<T, y, w> yw;
		swizz<T, z, x> zx;
		swizz<T, z, y> zy;
		swizz<T, z, w> zw;
		swizz<T, w, x> wx;
		swizz<T, w, y> wy;
		swizz<T, w, z> wz;
		swizz<T, x, y, z> xyz;
		swizz<T, x, y, w> xyw;
		swizz<T, x, z, y> xzy;
		swizz<T, x, z, w> xzw;
		swizz<T, x, w, y> xwy;
		swizz<T, x, w, z> xwz;
		swizz<T, y, x, z> yxz;
		swizz<T, y, x, w> yxw;
		swizz<T, y, z, x> yzx;
		swizz<T, y, z, w> yzw;
		swizz<T, y, w, x> ywx;
		swizz<T, y, w, z> ywz;
		swizz<T, z, x, y> zxy;
		swizz<T, z, x, w> zxw;
		swizz<T, z, y, x> zyx;
		swizz<T, z, y, w> zyw;
		swizz<T, z, w, x> zwx;
		swizz<T, z, w, y> zwy;
		swizz<T, w, x, y> wxy;
		swizz<T, w, x, z> wxz;
		swizz<T, w, y, x> wyx;
		swizz<T, w, y, z> wyz;
		swizz<T, w, z, x> wzx;
		swizz<T, w, z, y> wzy;
		base<T, x, y, z, w> xyzw;
		base<T, x, y, w, z> xywz;
		base<T, x, z, y, w> xzyw;
		base<T, x, z, w, y> xzwy;
		base<T, x, w, y, z> xwyz;
		base<T, x, w, z, y> xwzy;
		base<T, y, x, z, w> yxzw;
		base<T, y, x, w, z> yxwz;
		base<T, y, z, x, w> yzxw;
		base<T, y, z, w, x> yzwx;
		base<T, y, w, x, z> ywxz;
		base<T, y, w, z, x> ywzx;
		base<T, z, x, y, w> zxyw;
		base<T, z, x, w, y> zxwy;
		base<T, z, y, x, w> zyxw;
		base<T, z, y, w, x> zywx;
		base<T, z, w, x, y> zwxy;
		base<T, z, w, y, x> zwyx;
		base<T, w, x, y, z> wxyz;
		base<T, w, x, z, y> wxzy;
		base<T, w, y, x, z> wyxz;
		base<T, w, y, z, x> wyzx;
		base<T, w, z, x, y> wzxy;
		base<T, w, z, y, x> wzyx;
		swizz<T, x> x;
		swizz<T, y> y;
		swizz<T, z> z;
		swizz<T, w> w;
	};
};

template<class T, uint n>
struct vec : type_proxy<base, T, n>::type
{
	using base = typename type_proxy<base, T, n>::type;
	using base::operator=;
	vec& operator=(const vec& v);
	vec();
	T data[n];
};
template<class T>
struct vec<T, 2> : base<T, 0, 1> {
	using base<T, 0, 1>::operator=;
	vec& operator=(const vec& v);
	vec();
	vec(T x);
	vec(T x, T y);
	vec(const vec& v);

	template<class T2>
	vec(const vec<T2, 2>&);

	template<uint a, uint b>
	vec(const base<T, a, b>& v);
	union {
		T data[2];
		struct { T x, y; };
		swizz<T, 0, 1> xy;
		swizz<T, 1, 0> yx;
	};
};

template<class T>
struct vec<T, 3> : base<T, 0, 1, 2> {
	using base<T, 0, 1, 2>::operator=;
	vec& operator=(const vec& v);
	vec();
	vec(T x);
	vec(T x, T y, T z);
	vec(const vec& v);
	template<class T2>
	vec(const vec<T2, 3>&);
	template<uint a, uint b, uint c>
	vec(const base<T, a, b, c>& v);
	template<uint a, uint b>
	vec(T x, const base<T, a, b>& v);
	template<uint a, uint b>
	vec(const base<T, a, b>& v, T z);
	union {
		T data[3];
		struct { T x, y, z; };
		swizz<T, 0, 1> xy;
		swizz<T, 0, 2> xz;
		swizz<T, 1, 0> yx;
		swizz<T, 1, 2> yz;
		swizz<T, 2, 0> zx;
		swizz<T, 2, 1> zy;
		swizz<T, 0, 1, 2> xyz;
		swizz<T, 0, 2, 1> xzy;
		swizz<T, 1, 0, 2> yxz;
		swizz<T, 1, 2, 0> yzx;
		swizz<T, 2, 0, 1> zxy;
		swizz<T, 2, 1, 0> zyx;
	};
};

template<class T>
struct vec<T, 4> : base<T, 0, 1, 2, 3> {
	using base<T, 0, 1, 2, 3>::operator=;
	vec& operator=(const vec& v);
	vec();
	vec(T x);
	vec(T x, T y, T z, T w);
	vec(const vec& v);
	template<class T2>
	vec(const vec<T2, 4>&);
	template<uint a, uint b, uint c, uint d>
	vec(const base<T, a, b, c, d>& v);
	template<uint a, uint b>
	vec(T x, T y, const base<T, a, b>& v);
	template<uint a, uint b>
	vec(const base<T, a, b>& v, T z, T w);
	template<uint a, uint b>
	vec(T x, const base<T, a, b>& v, T w);
	template<uint a, uint b, uint c, uint d>
	vec(const base<T, a, b>& l, const base<T, c, d>& r);
	template<uint a, uint b, uint c>
	vec(const base<T, a, b, c>& v, T w);
	template<uint a, uint b, uint c>
	vec(T x, const base<T, a, b, c>& v);
	union {
		T data[4];
		struct { T x, y, z, w; };
		swizz<T, 0, 1> xy;
		swizz<T, 0, 2> xz;
		swizz<T, 0, 3> xw;
		swizz<T, 1, 0> yx;
		swizz<T, 1, 2> yz;
		swizz<T, 1, 3> yw;
		swizz<T, 2, 0> zx;
		swizz<T, 2, 1> zy;
		swizz<T, 2, 3> zw;
		swizz<T, 3, 0> wx;
		swizz<T, 3, 1> wy;
		swizz<T, 3, 2> wz;
		swizz<T, 0, 1, 2> xyz;
		swizz<T, 0, 1, 3> xyw;
		swizz<T, 0, 2, 1> xzy;
		swizz<T, 0, 2, 3> xzw;
		swizz<T, 0, 3, 1> xwy;
		swizz<T, 0, 3, 2> xwz;
		swizz<T, 1, 0, 2> yxz;
		swizz<T, 1, 0, 3> yxw;
		swizz<T, 1, 2, 0> yzx;
		swizz<T, 1, 2, 3> yzw;
		swizz<T, 1, 3, 0> ywx;
		swizz<T, 1, 3, 2> ywz;
		swizz<T, 2, 0, 1> zxy;
		swizz<T, 2, 0, 3> zxw;
		swizz<T, 2, 1, 0> zyx;
		swizz<T, 2, 1, 3> zyw;
		swizz<T, 2, 3, 0> zwx;
		swizz<T, 2, 3, 1> zwy;
		swizz<T, 3, 0, 1> wxy;
		swizz<T, 3, 0, 2> wxz;
		swizz<T, 3, 1, 0> wyx;
		swizz<T, 3, 1, 2> wyz;
		swizz<T, 3, 2, 0> wzx;
		swizz<T, 3, 2, 1> wzy;
		swizz<T, 0, 1, 2, 3> xyzw;
		swizz<T, 0, 1, 3, 2> xywz;
		swizz<T, 0, 2, 1, 3> xzyw;
		swizz<T, 0, 2, 3, 1> xzwy;
		swizz<T, 0, 3, 1, 2> xwyz;
		swizz<T, 0, 3, 2, 1> xwzy;
		swizz<T, 1, 0, 2, 3> yxzw;
		swizz<T, 1, 0, 3, 2> yxwz;
		swizz<T, 1, 2, 0, 3> yzxw;
		swizz<T, 1, 2, 3, 0> yzwx;
		swizz<T, 1, 3, 0, 2> ywxz;
		swizz<T, 1, 3, 2, 0> ywzx;
		swizz<T, 2, 0, 1, 3> zxyw;
		swizz<T, 2, 0, 3, 1> zxwy;
		swizz<T, 2, 1, 0, 3> zyxw;
		swizz<T, 2, 1, 3, 0> zywx;
		swizz<T, 2, 3, 0, 1> zwxy;
		swizz<T, 2, 3, 1, 0> zwyx;
		swizz<T, 3, 0, 1, 2> wxyz;
		swizz<T, 3, 0, 2, 1> wxzy;
		swizz<T, 3, 1, 0, 2> wyxz;
		swizz<T, 3, 1, 2, 0> wyzx;
		swizz<T, 3, 2, 0, 1> wzxy;
		swizz<T, 3, 2, 1, 0> wzyx;
	};
};


template<class T>
struct matrix2 {
	template<uint x, uint y, uint x1, uint y1>
	matrix2(const base<T, x, y>& a, const base<T, x1, y1>& b);
	matrix2();
	matrix2(T x);
	matrix2(T x, T y, T z, T w);
	matrix2(const matrix2& m);
	matrix2& operator = (const matrix2& m);
	union {
		T data[4];
		vec<T, 2> row[2];
		cvec<T, 2> col[2];
		dvec<T, 2> diag;
	};
	T det() const;
	matrix2 inv() const;
	matrix2 xpos() const;
	matrix2 operator *(const matrix2& r) const;
	template<uint x, uint y>
	vec<T, 2> operator *(const base<T, x, y>& v) const;
	matrix2& operator *=	(T s);
	matrix2& operator /=	(T s);
	matrix2  operator *	(T s) const;
	matrix2  operator /	(T s) const;
};
template<class T>
struct matrix4;

template<class T>
struct matrix3 {
	template<
		uint  x, uint  y, uint z,
		uint x1, uint y1, uint z1,
		uint x2, uint y2, uint z2>
		matrix3(const base<T, x, y, z>& a, const base<T, x1, y1, z1>& b, const base<T, x2, y2, z2>& c);
	matrix3();
	matrix3(T x);
	matrix3(T  x, T  y, T z, T x1, T y1, T z1, T x2, T y2, T z2);
	matrix3(const matrix3& m);

	matrix3& operator = (const matrix3& m);
	union {
		T data[9];
		vec<T, 3>  row[3];
		cvec<T, 3> col[3];
		dvec<T, 3> diag;
	};
	T det() const;
	matrix3 xpos() const;
	matrix3 operator * (const matrix3& r) const;
	template<uint x, uint y, uint z>
	vec<T, 3> operator *(const base<T, x, y, z>& v) const;
	T& operator()(uint r, uint c);
	T  operator()(uint r, uint c) const;
	matrix3& operator *=(T s);
	matrix3 operator *		(T s) const;
	matrix3& operator /=	(T s);
	matrix3 operator /		(T s) const;
	operator matrix4<T>() const;
};

template<class T>
struct matrix4 {
	template<
		uint  x, uint  y, uint  z, uint  w,
		uint x1, uint y1, uint z1, uint w1,
		uint x2, uint y2, uint z2, uint w2,
		uint x3, uint y3, uint z3, uint w3>
		matrix4(const base<T, x, y, z, w>& a,
			const base<T, x1, y1, z1, w1>& b,
			const base<T, x2, y2, z2, w2>& c,
			const base<T, x3, y3, z3, w3>& d);
	matrix4();
	matrix4(T x);
	matrix4(T  x, T  y, T  z, T w,
		T x1, T y1, T z1, T w1,
		T x2, T y2, T z2, T w2,
		T x3, T y3, T z3, T w3);
	matrix4(const matrix4& m);
	matrix4& operator = (const matrix4& m);

	union {
		T data[16];
		vec<T, 4>  row[4];
		cvec<T, 4> col[4];
		dvec<T, 4> diag;
	};
	T det() const;
	matrix4 inv() const;
	matrix4 xpos() const;
	matrix4 operator *(const matrix4& r) const;
	template<uint x, uint y, uint z, uint w>
	vec<T, 4> operator *(const base<T, x, y, z, w>& v) const;
	T& operator()(uint r, uint c);
	T  operator()(uint r, uint c) const;
	matrix4& operator *= (T s);
	matrix4& operator /=	(T s);
	matrix4 operator *		(T s) const;
	matrix4 operator /		(T s) const;
	operator matrix3<T>() const;
};
template<class T>
matrix3<T> rotx(T angle);
template<class T>
matrix3<T> roty(T angle);
template<class T>
matrix3<T> rotz(T angle);

template<class T>
std::ostream& operator << (std::ostream&, const matrix2<T>&);
template<class T>
std::ostream& operator << (std::ostream&, const matrix3<T>&);
template<class T>
std::ostream& operator << (std::ostream&, const matrix4<T>&);

matrix4<float> perspective(float fov, float aspect, float n, float f);
matrix4<float> ortho(float l, float r, float b, float t);
matrix4<float> ortho(float l, float r, float b, float t, float n, float f);
matrix4<float> view(const vec<float, 3>& p, const vec<float, 3>& r, const vec<float, 3>& u, const vec<float, 3>& d);

template<class T, uint x, uint y>
vec<T, 2> operator *(const base<T, x, y>& v, const matrix2<T>& m);
template<class T, uint x, uint y, uint z>
vec<T, 3> operator *(const base<T, x, y, z>& v, const matrix3<T>& m);
template<class T, uint x, uint y, uint z, uint w>
vec<T, 4> operator *(const base<T, x, y, z, w>& v, const matrix4<T>& m);

template<class T>
struct quaternion {
	union {
		T data[4];
		struct { T x, y, z, w; };
		struct { T i, j, k, s; };
		vec<T, 3> v;
		vec<T, 4> q;
	};
	template<uint a, uint b, uint c>
	quaternion(const base<T, a, b, c>& v, T w);
	quaternion();
	quaternion(T x, T y, T z, T w);
	quaternion(const vec<T, 3>& v, T w);
	quaternion(const quaternion& q);
	quaternion(const matrix3<T>&);
	quaternion(const matrix4<T>&);
	T len() const;
	T len2() const;
	quaternion& normalize();
	quaternion& operator=(const quaternion& q);
	quaternion  operator ~() const;
	quaternion  operator -() const;
	quaternion& operator += (const quaternion& q);
	quaternion& operator -= (const quaternion& q);
	quaternion  operator +  (const quaternion& q) const;
	quaternion  operator -  (const quaternion& q) const;
	quaternion& operator *= (T s);
	quaternion& operator /= (T s);
	quaternion  operator *  (float s) const;
	quaternion  operator /  (float s) const;
	quaternion  operator /  (const quaternion& q) const;
	quaternion  operator *= (const quaternion& q);
	quaternion  operator /= (const quaternion& q);
	quaternion  operator * (const quaternion& q) const;
	operator matrix3<T>() const;
	operator matrix4<T>() const;
	template<uint x, uint y, uint z>
	vec<T, 3> operator * (const base<T, x, y, z>& v) const;
};

template<class T>
inline std::ostream& operator << (std::ostream& s, const quaternion<T>& q)
{
	return s << q.q;
}
template<class T, uint x, uint y, uint z>
vec<T, 3> operator * (const base<T, x, y, z>& v, const quaternion<T>& q);
quaternion<float> axAng(float x, float y, float z, float w);
template<uint x, uint y, uint z>
quaternion<float> axAng(const base<float, x, y, z>& v, float w);
quaternion<float> axAng(const quaternion<float>& q);
template<class T>
T dot(const quaternion<T>& l, const quaternion<T>& r);

template<class T>
inline T dot(const quaternion<T>& l, const quaternion<T>& r)
{
	return dot(l.q, r.q);
}
inline float absl(float x) {
	static int abs;
	abs = *(int*)&x & 2147483647;
	return *(float*)&abs;
}

inline float cpysign(float x, float y) {
	static int sum;
	sum = *(int*)&x & 2147483648 |
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

inline bool xfstr::operator<(const xfstr& s) const
{
	return strcmp(data_, s.data_) < 0;;
}

inline bool xfstr::operator<=(const xfstr& s) const
{
	return strcmp(data_, s.data_) <= 0;;
}

inline bool xfstr::operator>(const xfstr& s) const
{
	return strcmp(data_, s.data_) > 0;;
}

inline bool xfstr::operator>=(const xfstr& s) const
{
	return strcmp(data_, s.data_) >= 0;;
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
	static char* end;
	n = strtol(data_, &end, 10);
	erase(data_, end);
	return *this;
}

inline xfstr& xfstr::operator>>(unsigned long& n)
{
	static char* end;
	n = strtoul(data_, &end, 10);
	erase(data_, end);
	return *this;
}

inline xfstr& xfstr::operator>>(int& n)
{
	static char* end;
	n = strtoul(data_, &end, 10);
	erase(data_, end);
	return *this;
}

inline xfstr& xfstr::operator>>(uint& n)
{
	static char* end;
	n = strtoul(data_, &end, 10);
	erase(data_, end);
	return *this;
}

inline xfstr& xfstr::operator>>(float& n)
{
	static char* end;
	n = strtof(data_, &end);
	erase(data_, end);
	return *this;
}

inline xfstr& xfstr::operator>>(double& n)
{
	static char* end;
	n = strtod(data_, &end);
	erase(data_, end);
	return *this;
}

inline xfstr& xfstr::read(const char* file)
{
	static char c;
	std::ifstream s(file);
	if (!s)
	{
		std::cout << "Cannot find file " << file << '\n';
		return *this;
	}
	size_ = 0;
	while (s.get(c)) *this += c;
	s.close();
	return *this;
}

inline std::istream& xfstr::getline(std::istream& s, char delim)
{
	clear();
	static char c;
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

inline const char* xfstr::c_str() const
{
	return data_;
}

inline xfstr::operator const char* () const
{
	return data_;
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

inline uint xfstr::count(const char* str) const
{
	static uint len, lim, c;
	len = strlen(str);
	if (size_ < len) return 0;
	lim = size_ - len + 1;
	c = 0;
	bool state = 1;
	for (uint i = 0; i < lim; ++i)
	{
		if (data_[i] == str[0])
		{
			for (uint j = 1; j < len; ++j)
			{
				if (data_[i + j] != str[j])
				{
					state = 0;
					break;
				}
			}
			if (state) ++c;
			state = 1;
		}
	}
	return c;
}

inline char* xfstr::find(const char* str, uint pos) const
{
	static uint len, lim;
	len = strlen(str);
	if (size_ < len) return 0;
	lim = size_ - len + 1;
	char* c = 0;
	for (uint i = 0; i < lim; ++i)
	{
		if (data_[i] == str[0])
		{
			c = data_ + i;
			for (uint j = 1; j < len; ++j)
			{
				if (data_[i + j] != str[j])
				{
					c = 0;
					break;
				}
			}
			if (c)
			{
				--pos;
				if (pos == 0) return c;
			}
		}
	}
	return c;
}

inline char* xfstr::find(const char* str, char* begin_, uint pos) const
{
	static uint len, lim, begin;
	len = strlen(str);
	begin = begin_ - data_;
	if (size_ - begin < len) return 0;
	lim = size_ - len + 1;
	char* c = 0;
	for (uint i = begin; i < lim; ++i)
	{
		if (data_[i] == str[0])
		{
			c = data_ + i;
			for (uint j = 1; j < len; ++j)
			{
				if (data_[i + j] != str[j])
				{
					c = 0;
					break;
				}
			}
			if (c)
			{
				--pos;
				if (pos == 0) return c;
			}
		}
	}
	return c;
}

inline char* xfstr::find(char c, size_t pos) const
{
	static char* i, * j;
	i = begin();
	j = end();
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
	static char* i, * j;
	i = begin();
	j = end();
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

inline xfstr xfstr::substr(const char* a, const char* b, uint pos)
{
	static char* i, * j;
	i = find(a, pos);
	j = find(b, pos) + strlen(b);
	return substr(i - data_, j - i);
}

inline xfstr xfstr::exbtwn(char a, char b) const
{
	static char* i, * j;
	i = find(a);
	j = find(b, ++i, end());
	return substr(i - data_, j - i);
}
inline xfstr xfstr::inbtwn(char a, char b) const
{
	static char* i, * j;
	i = find(a);
	j = find(b, i + 1, end());
	return substr(i - data_, ++j - i);
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

inline xfstr& xfstr::cls()
{
	if (empty()) return *this;
	while (*data_ == ' ' || *data_ == 9 || *data_ == '\n')
	{
		erase(data_);
		if (empty()) return *this;
	}
	while (*(data_ + size_ - 1) == ' ' || *(data_ + size_ - 1) == 9 || *(data_ + size_ - 1) == '\n')
	{
		erase(data_ + size_ - 1);
		if (empty()) return *this;
	}
	return *this;
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
	static char c;
	str.clear();
	while (s.get(c)) str += c;
	return s;
}

inline xfstr operator + (const char* c, const xfstr& s) {
	static uint len;
	len = strlen(c);
	xfstr re(len + s.size());
	memcpy(re.data(), c, len);
	memcpy(re.data() + len, s.data(), s.size());
	return re;
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
inline void xfvec<c>::reverse()
{
	uint size2 = size_ / 2;
	for (uint i = 0; i < size2; ++i)
	{
		c temp = data_[i];
		data_[i] = data_[size_ - i - 1];
		data_[size_ - i - 1] = temp;
	}
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
	v.size_ = 0;
	v.cap_ = 0;
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
	v.cap_ = 0;
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
inline const val& vref<key, val>::ref() const
{
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
inline xfvec<xfpair<key, val>>& xfmap<key, val>::container()
{
	return data;
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


template<class T, uint ...x>
inline base<T, x...>::operator vec<T, sizeof...(x)>() const
{
	return { *(T*)(this + x)... };
}

template<class T, uint ...x>
inline swizz<T, x...>& base<T, x...>::operator=(const base& v)
{
	((*(T*)(this + x) = *(T*)(&v + x)), ...);
	return *(swizz<T, x...>*)this;
}

template<class T, uint ...x>
template<uint ...y>
inline swizz<T, x...>& base<T, x...>::operator=(const base<T, y...>& v)
{
	if ((T*)this == (T*)&v) return operator=(vec<T, sizeof...(y)>(v));
	((*(T*)(this + x) = *(T*)(&v + y)), ...);
	return *(swizz<T, x...>*)this;
}

template<class T, uint ...x>
template<uint ...y>
inline swizz<T, x...>& base<T, x...>::operator+=(const base<T, y...>& v)
{
	if ((T*)this == (T*)&v) return operator+=(vec<T, sizeof...(y)>(v));
	((*(T*)(this + x) += *(T*)(&v + y)), ...);
	return *(swizz<T, x...>*)this;
}

template<class T, uint ...x>
template<uint ...y>
inline swizz<T, x...>& base<T, x...>::operator-=(const base<T, y...>& v)
{
	if ((T*)this == (T*)&v) return operator-=(vec<T, sizeof...(y)>(v));
	((*(T*)(this + x) -= *(T*)(&v + y)), ...);
	return *(swizz<T, x...>*)this;
}

template<class T, uint ...x>
template<uint ...y>
inline swizz<T, x...>& base<T, x...>::operator*=(const base<T, y...>& v)
{
	if ((T*)this == (T*)&v) return operator*=(vec<T, sizeof...(y)>(v));
	((*(T*)(this + x) *= *(T*)(&v + y)), ...);
	return *(swizz<T, x...>*)this;
}

template<class T, uint ...x>
template<uint ...y>
inline swizz<T, x...>& base<T, x...>::operator/=(const base<T, y...>& v)
{
	if ((T*)this == (T*)&v) return operator/=(vec<T, sizeof...(y)>(v));
	((*(T*)(this + x) /= *(T*)(&v + y)), ...);
	return *(swizz<T, x...>*)this;
}

template<class T, uint ...x>
template<uint ...y>
inline vec<T, sizeof...(x)> base<T, x...>::operator+(const base<T, y...>& v) const
{
	return { *(T*)(this + x) + *(T*)(&v + y)... };
}

template<class T, uint ...x>
template<uint ...y>
inline vec<T, sizeof...(x)> base<T, x...>::operator-(const base<T, y...>& v) const
{
	return { *(T*)(this + x) - *(T*)(&v + y)... };
}

template<class T, uint ...x>
template<uint ...y>
inline vec<T, sizeof...(x)> base<T, x...>::operator*(const base<T, y...>& v) const
{
	return { *(T*)(this + x) * *(T*)(&v + y)... };
}

template<class T, uint ...x>
template<uint ...y>
inline vec<T, sizeof...(x)> base<T, x...>::operator/(const base<T, y...>& v) const
{
	return { *(T*)(this + x) / *(T*)(&v + y)... };
}

template<class T, uint ...x>
template<uint ...y>
inline T base<T, x...>::operator^(const base<T, y...>& v) const
{
	return acosf(((*(T*)(this + x) * *(T*)(&v + y)) + ...)
		/ sqrt(((*(T*)(this + x) * *(T*)(this + x)) + ...))
		/ sqrt(((*(T*)(&v + y) * *(T*)(&v + y)) + ...)));
}

template<class T, uint ...x>
template<uint ...y>
inline vec<T, sizeof...(x)> base<T, x...>::operator%(const base<T, y...>& v) const
{
	return ~operator-(v);
}

template<class T, uint ...x>
inline swizz<T, x...>& base<T, x...>::operator=(T n)
{
	((*(T*)(this + x) = n), ...);
	return *(swizz<T, x...>*)this;
}

template<class T, uint ...x>
inline swizz<T, x...>& base<T, x...>::operator+=(T n)
{
	((*(T*)(this + x) += n), ...);
	return *(swizz<T, x...>*)this;
}

template<class T, uint ...x>
inline swizz<T, x...>& base<T, x...>::operator-=(T n)
{
	((*(T*)(this + x) -= n), ...);
	return *(swizz<T, x...>*)this;
}

template<class T, uint ...x>
inline swizz<T, x...>& base<T, x...>::operator*=(T n)
{
	((*(T*)(this + x) *= n), ...);
	return *(swizz<T, x...>*)this;
}

template<class T, uint ...x>
inline swizz<T, x...>& base<T, x...>::operator/=(T n)
{
	n = 1 / n;
	((*(T*)(this + x) *= n), ...);
	return *(swizz<T, x...>*)this;
}

template<class T, uint ...x>
inline vec<T, sizeof...(x)> base<T, x...>::operator+(T n) const
{
	return { *(T*)(this + x) + n... };
}

template<class T, uint ...x>
inline vec<T, sizeof...(x)> base<T, x...>::operator-(T n) const
{
	return { *(T*)(this + x) - n... };
}

template<class T, uint ...x>
inline vec<T, sizeof...(x)> base<T, x...>::operator*(T n) const
{
	return { *(T*)(this + x) * n... };
}

template<class T, uint ...x>
inline vec<T, sizeof...(x)> base<T, x...>::operator/(T n) const
{
	n = 1 / n;
	return { *(T*)(this + x) * n... };
}

template<class T, uint ...x>
inline vec<T, sizeof...(x)> base<T, x...>::norm() const
{
	T n = 1 / sqrt(((*(T*)(this + x) * *(T*)(this + x)) + ...));
	return { *(T*)(this + x) * n... };
}

template<class T, uint ...x>
inline vec<T, sizeof...(x)> base<T, x...>::operator-() const
{
	return { -*(T*)(this + x)... };
}

template<class T, uint ...x>
inline swizz<T, x...>& base<T, x...>::operator~()
{
	T n = 1 / sqrt(((*(T*)(this + x) * *(T*)(this + x)) + ...));
	((*(T*)(this + x) *= n), ...);
	return *(swizz<T, x...>*)this;
}

template<class T, uint ...x>
inline T base<T, x...>::len() const
{
	return sqrt(((*(T*)(this + x) * *(T*)(this + x)) + ...));
}

template<class T, uint ...x>
inline T base<T, x...>::operator!() const
{
	return ((*(T*)(this + x) * *(T*)(this + x)) + ...);
}

template<class T, uint ...x>
inline T& base<T, x...>::operator[](uint n) const
{
	return *(T*)(this + n);
}

template<class T, uint ...x>
template<uint ...y>
inline bool base<T, x...>::operator==(const base<T, y...>& v) const
{
	return ((is0(*(T*)(this + x) - *(T*)(&v + y))) && ...);
}

template<class T, uint ...x>
template<uint ...y>
inline bool base<T, x...>::operator!=(const base<T, y...>& v) const
{
	return !((is0(*(T*)(this + x) - *(T*)(&v + y))) && ...);
}

template<class T, uint ...x>
template<uint ...y>
inline bool base<T, x...>::operator<(const base<T, y...>& v) const
{
	vec<T, sizeof...(x)> u = { *(T*)(this + x) - *(T*)(&v + y)... };
	return is0(u.x) ? u.y < 0 : u.x < 0;
}

template<class T, uint ...x>
template<uint ...y>
inline bool base<T, x...>::operator<=(const base<T, y...>& v) const
{
	return operator<(v) || operator ==(v);
}


template<class T, uint ...x>
template<uint ...y>
inline bool base<T, x...>::operator>(const base<T, y...>& v) const
{
	vec<T, sizeof...(x)> u = { *(T*)(this + x) - *(T*)(&v + y)... };
	return is0(u.x) ? u.y > 0 : u.x > 0;
}

template<class T, uint ...x>
template<uint ...y>
inline bool base<T, x...>::operator>=(const base<T, y...>& v) const
{
	return operator>(v) || operator ==(v);
}

template<class T, uint...x>
inline vec<T, sizeof...(x)> operator+(T n, const base<T, x...>& v)
{
	return { n + *(T*)(&v + x)... };
}

template<class T, uint...x>
inline vec<T, sizeof...(x)> operator-(T n, const base<T, x...>& v)
{
	return { n - *(T*)(&v + x)... };
}

template<class T, uint...x>
inline vec<T, sizeof...(x)> operator*(T n, const base<T, x...>& v)
{
	return { n * *(T*)(&v + x)... };
}

template<class T, uint...x>
inline vec<T, sizeof...(x)> operator/(T n, const base<T, x...>& v)
{
	return { n / *(T*)(&v + x)... };
}

template<class T, uint...x>
inline std::ostream& operator<<(std::ostream& s, const base<T, x...>& v)
{
	((s << *(T*)(&v + x) << ' '), ...);
	return s << '\n';
}

template<class T, uint...x>
inline xfstr tostr(const base<T, x...>& v)
{
	xfstr re;
	((re += tostr(*(T*)(&v + x)) + ' '), ...);
	return re;
}

template<class T, uint...x, uint...y>
inline T dot(const base<T, x...>& l, const base<T, y...>& r)
{
	return ((*(T*)(&l + x) * *(T*)(&r + y)) + ...);
}

template<class T, uint x, uint y, uint z, uint x1, uint y1, uint z1>
inline vec<T, 3> cross(const base<T, x, y, z>& l, const base<T, x1, y1, z1>& r)
{
	return
	{
		*(T*)(&l + y) * *(T*)(&r + z1) - *(T*)(&l + z) * *(T*)(&r + y1),
		*(T*)(&l + z) * *(T*)(&r + x1) - *(T*)(&l + x) * *(T*)(&r + z1),
		*(T*)(&l + x) * *(T*)(&r + y1) - *(T*)(&l + y) * *(T*)(&r + x1)
	};
}

template<class T>
inline vec<T, 3> perp(const vec<T, 3>& v)
{
	uint c = !is0(v.x) + !is0(v.y) * 2 + !is0(v.z) * 4;
	switch (c) {
	case 1: return { 0, 1, 0 }; //x
	case 2: return { 0, 0, 1 }; //y
	case 4: return { 1, 0, 0 }; //z
	case 3: return { -v.y, v.x,  0 }; //xy
	case 5: return { v.z, 0, -v.x };  //xz
	case 6: return { 0, -v.z, v.y };  //yz
	case 7: return { -v.y * v.z, v.x * v.z, 0 }; //xyz
	default: return {};
	}
}

template<class T>
inline vec<T, 2> norm(T x, T y)
{
	T n = 1 / sqrt(x * x + y * y);
	return { x * n , y * n };
}

template<class T>
inline vec<T, 3> norm(T x, T y, T z)
{
	T n = 1 / sqrt(x * x + y * y + z * z);
	return { x * n , y * n, z * n };
}

template<class T>
inline vec<T, 4> norm(T x, T y, T z, T w)
{
	T n = 1 / sqrt(x * x + y * y + z * z + w * w);
	return { x * n , y * n, z * n, w * n };
}

template<class T, uint x>
inline T& swizz<T, x>::operator=(T f)
{
	return *(T*)(this + x) = f;
}

template<class T, uint x>
inline T& swizz<T, x>::operator+=(T f)
{
	return *(T*)(this + x) += f;
}

template<class T, uint x>
inline T& swizz<T, x>::operator-=(T f)
{
	return *(T*)(this + x) -= f;
}

template<class T, uint x>
inline T& swizz<T, x>::operator*=(T f)
{
	return *(T*)(this + x) *= f;
}

template<class T, uint x>
inline T& swizz<T, x>::operator/=(T f)
{
	return *(T*)(this + x) /= f;
}

template<class T, uint x>
inline swizz<T, x>::operator T& ()
{
	return *(T*)(this + x);
}

template<class T, uint x>
inline swizz<T, x>::operator T() const
{
	return *(T*)(this + x);
}

template<class T, uint x, uint y>
inline swizz<T, x, y>& swizz<T, x, y>::operator=(const swizz& v)
{
	*(T*)(this + x) = *(&v + x);
	*(T*)(this + y) = *(&v + y);
	return *this;
}

template<class T, uint x, uint y>
template<uint a, uint b>
inline swizz<T, x, y>& swizz<T, x, y>::operator=(const swizz<T, a, b>& v)
{
	if (this == &v) return operator=(vec2(v));
	*(T*)(this + x) = *(&v + a);
	*(T*)(this + y) = *(&v + b);
	return *this;
}

template<class T, uint x, uint y, uint z>
inline swizz<T, x, y, z>& swizz<T, x, y, z>::operator=(const swizz& v)
{
	*(T*)(this + x) = *(&v + x);
	*(T*)(this + y) = *(&v + y);
	*(T*)(this + z) = *(&v + z);
	return *this;
}

template<class T, uint x, uint y, uint z>
template<uint a, uint b, uint c>
inline swizz<T, x, y, z>& swizz<T, x, y, z>::operator=(const swizz<T, a, b, c>& v)
{
	if (this == &v) return operator=(vec3(v));
	*(T*)(this + x) = *(&v + a);
	*(T*)(this + y) = *(&v + b);
	*(T*)(this + z) = *(&v + c);
	return *this;
}

template<class T, uint x, uint y, uint z, uint w>
inline swizz<T, x, y, z, w>& swizz<T, x, y, z, w>::operator=(const swizz& v)
{
	*(T*)(this + x) = *(&v + x);
	*(T*)(this + y) = *(&v + y);
	*(T*)(this + z) = *(&v + z);
	*(T*)(this + w) = *(&v + w);
	return *this;
}

template<class T, uint x, uint y, uint z, uint w>
template<uint a, uint b, uint c, uint d>
inline swizz<T, x, y, z, w>& swizz<T, x, y, z, w>::operator=(const swizz<T, a, b, c, d>& v)
{
	if (this == &v) return operator=(vec4(v));
	*(T*)(this + x) = *(&v + a);
	*(T*)(this + y) = *(&v + b);
	*(T*)(this + z) = *(&v + c);
	*(T*)(this + w) = *(&v + d);
	return *this;
}


template<class T, uint n>
vec<T, n>& vec<T, n>::operator=(const vec& v)
{
	return (vec&)base::operator=(v);
}

template<class T, uint n>
inline vec<T, n>::vec()
{
}

template<class T>
inline vec<T, 2>& vec<T, 2>::operator=(const vec& v)
{
	x = v.x;
	y = v.y;
	return *this;
}

template<class T>
inline vec<T, 2>::vec()
	: data{}
{
}

template<class T>
inline vec<T, 2>::vec(T x)
	: data{ x, x }
{
}

template<class T>
inline vec<T, 2>::vec(T x, T y)
	: data{ x, y }
{
}

template<class T>
inline vec<T, 2>::vec(const vec& v)
	: data{ v.x, v.y }
{
}

template<class T>
template<class T2>
inline vec<T, 2>::vec(const vec<T2, 2>& v)
	: data{ T(v.x), T(v.y) }
{

}

template<class T>
template<uint a, uint b>
inline vec<T, 2>::vec(const base<T, a, b>& v)
	: data{ *(T*)(&v + a), *(T*)(&v + b) }
{
}

template<class T>
inline vec<T, 3>& vec<T, 3>::operator=(const vec& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}

template<class T>
inline vec<T, 3>::vec()
	: data{}
{
}

template<class T>
inline vec<T, 3>::vec(T x)
	: data{ x, x, x }
{
}

template<class T>
inline vec<T, 3>::vec(T x, T y, T z)
	: data{ x, y, z }
{
}

template<class T>
inline vec<T, 3>::vec(const vec& v)
	: data{ v.x, v.y, v.z }
{
}

template<class T>
template<class T2>
inline vec<T, 3>::vec(const vec<T2, 3>& v)
	: data{ T(v.x), T(v.y), T(v.z) }
{

}

template<class T>
template<uint a, uint b, uint c>
inline vec<T, 3>::vec(const base<T, a, b, c>& v)
	: data{ *(T*)(&v + a), *(T*)(&v + b), *(T*)(&v + c) }
{
}

template<class T>
template<uint a, uint b>
inline vec<T, 3>::vec(T x, const base<T, a, b>& v)
	: data{ x, *(T*)(&v + a), *(T*)(&v + b) }
{
}

template<class T>
template<uint a, uint b>
inline vec<T, 3>::vec(const base<T, a, b>& v, T z)
	: data{ *(T*)(&v + a), *(T*)(&v + b), z }
{
}

template<class T>
inline vec<T, 4>& vec<T, 4>::operator=(const vec& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
	return *this;
}

template<class T>
inline vec<T, 4>::vec()
	: data{}
{
}

template<class T>
inline vec<T, 4>::vec(T x)
	: data{ x, x, x, x }
{
}

template<class T>
inline vec<T, 4>::vec(T x, T y, T z, T w)
	: data{ x, y, z, w }
{
}

template<class T>
inline vec<T, 4>::vec(const vec& v)
	: data{ v.x, v.y, v.z, v.w }
{
}

template<class T>
template<class T2>
inline vec<T, 4>::vec(const vec<T2, 4>& v)
	: data{ T(v.x), T(v.y), T(v.z), T(v.w) }
{

}

template<class T>
template<uint a, uint b, uint c, uint d>
inline vec<T, 4>::vec(const base<T, a, b, c, d>& v)
	: data{ *(T*)(&v + a), *(T*)(&v + b),  *(T*)(&v + c), *(T*)(&v + d) }
{
}

template<class T>
template<uint a, uint b>
inline vec<T, 4>::vec(T x, T y, const base<T, a, b>& v)
	: data{ x, y, *(T*)(&v + a),*(T*)(&v + b) }
{
}

template<class T>
template<uint a, uint b>
inline vec<T, 4>::vec(const base<T, a, b>& v, T z, T w)
	: data{ *(T*)(&v + a),*(T*)(&v + b), z, w }
{
}

template<class T>
template<uint a, uint b>
inline vec<T, 4>::vec(T x, const base<T, a, b>& v, T w)
	: data{ x, *(T*)(&v + a),*(T*)(&v + b), w }
{
}

template<class T>
template<uint a, uint b, uint c, uint d>
inline vec<T, 4>::vec(const base<T, a, b>& l, const base<T, c, d>& r)
	: data{ *(T*)(&l + a),*(T*)(&l + b), *(T*)(&r + c), *(T*)(&r + d) }
{
}

template<class T>
template<uint a, uint b, uint c>
inline vec<T, 4>::vec(const base<T, a, b, c>& v, T w)
	: data{ *(T*)(&v + a), *(T*)(&v + b), *(T*)(&v + c), w }
{
}

template<class T>
template<uint a, uint b, uint c>
inline vec<T, 4>::vec(T x, const base<T, a, b, c>& v)
	: data{ x, *(T*)(&v + a), *(T*)(&v + b), *(T*)(&v + c) }
{
}



template<class T>
template<uint x, uint y, uint x1, uint y1>
inline matrix2<T>::matrix2(const base<T, x, y>& a, const base<T, x1, y1>& b)
	: data
{
	*(T*)(&a + x), *(T*)(&a + x1),
	*(T*)(&b + y), *(T*)(&b + y1)
}
{
}

template<class T>
inline matrix2<T>::matrix2()
	: data{ 1, 0, 0, 1 }
{
}

template<class T>
inline matrix2<T>::matrix2(T x)
	: data{ x, 0, 0, x }
{
}

template<class T>
inline matrix2<T>::matrix2(T x, T y, T z, T w)
	: data{ x, y, z, w }
{
}

template<class T>
inline matrix2<T>::matrix2(const matrix2& m)
	: data{ m.data[0], m.data[1], m.data[2], m.data[3] }
{
}


template<class T>
inline matrix2<T>& matrix2<T>::operator=(const matrix2& m)
{
	data[0] = m.data[0];
	data[1] = m.data[1];
	data[2] = m.data[2];
	data[3] = m.data[3];
	return *this;
}

template<class T>
inline T matrix2<T>::det() const
{
	return data[0] * data[3] - data[1] * data[2];
}

template<class T>
inline matrix2<T> matrix2<T>::inv() const
{
	T det = 1 / (data[0] * data[3] - data[1] * data[2]);
	return { det * data[3], -det * data[1], -det * data[2], det * data[0] };
}

template<class T>
inline matrix2<T> matrix2<T>::xpos() const
{
	return { data[0], data[2], data[1], data[3] };
}

template<class T>
inline matrix2<T> matrix2<T>::operator*(const matrix2& r) const
{
	return {
		data[0] * r.data[0] + data[1] * r.data[2],
		data[0] * r.data[1] + data[1] * r.data[3],
		data[2] * r.data[0] + data[3] * r.data[2],
		data[2] * r.data[1] + data[3] * r.data[3],
	};
}

template<class T>
template <uint x, uint y>
inline vec<T, 2> matrix2<T>::operator*(const base<T, x, y>& v) const
{
	return {
		*(T*)(&v + x) * data[0] + *(T*)(&v + y) * data[1],
		*(T*)(&v + x) * data[2] + *(T*)(&v + y) * data[3],
	};
}

template<class T>
inline matrix2<T>& matrix2<T>::operator*=(T s)
{
	data[0] *= s;
	data[1] *= s;
	data[2] *= s;
	data[3] *= s;
	return *this;
}

template<class T>
inline matrix2<T>& matrix2<T>::operator/=(T s)
{
	return operator*=(1 / s);
}

template<class T>
inline matrix2<T> matrix2<T>::operator*(T s) const
{
	return matrix2(*this) *= s;
}

template<class T>
inline matrix2<T> matrix2<T>::operator/(T s) const
{
	return matrix2(*this) *= (1 / s);
}


template<class T>
template <uint x, uint y, uint z, uint x1, uint y1, uint z1, uint x2, uint y2, uint z2>
inline matrix3<T>::matrix3(const base<T, x, y, z>& a, const base<T, x1, y1, z1>& b, const base<T, x2, y2, z2>& c)
	: data{ *(T*)(&a + x), *(T*)(&a + y), *(T*)(&a + z), *(T*)(&b + x1), *(T*)(&b + y1),
		*(T*)(&b + z1), *(T*)(&c + x2), *(T*)(&c + y2), *(T*)(&c + z2) }
{
}

template<class T>
inline  matrix3<T>::matrix3()
	: data{ 1, 0, 0, 0, 1, 0, 0, 0, 1 }
{
}

template<class T>
inline  matrix3<T>::matrix3(T x)
	: data{ x, 0, 0, 0, x, 0, 0, 0, x }
{
}

template<class T>
inline  matrix3<T>::matrix3(T x, T y, T z, T x1, T y1, T z1, T x2, T y2, T z2)
	: data{ x, y, z, x1, y1, z1, x2, y2, z2 }
{
}

template<class T>
inline  matrix3<T>::matrix3(const matrix3<T>& m)
	: data{ m.data[0], m.data[1], m.data[2], m.data[3], m.data[4], m.data[5],
		m.data[6], m.data[7], m.data[8] }
{
}

template<class T>
inline  matrix3<T>& matrix3<T>::operator=(const matrix3<T>& m)
{
	data[0] = m.data[0];
	data[1] = m.data[1];
	data[2] = m.data[2];
	data[3] = m.data[3];
	data[4] = m.data[4];
	data[5] = m.data[5];
	data[6] = m.data[6];
	data[7] = m.data[7];
	data[8] = m.data[8];
	return *this;
}

template<class T>
inline T matrix3<T>::det() const
{
	return data[0] * (data[4] * data[8] - data[5] * data[7])
		+ data[1] * (data[5] * data[6] - data[3] * data[8])
		+ data[2] * (data[3] * data[7] - data[4] * data[6]);
}

template<class T>
inline matrix3<T> matrix3<T>::xpos() const
{
	return { data[0], data[3], data[6], data[1], data[4], data[7], data[2],
		data[5], data[8] };
}

template<class T>
inline matrix3<T> matrix3<T>::operator*(const matrix3<T>& r) const
{
	return {
		data[0] * r.data[0] + data[1] * r.data[3] + data[2] * r.data[6],
		data[0] * r.data[1] + data[1] * r.data[4] + data[2] * r.data[7],
		data[0] * r.data[2] + data[1] * r.data[5] + data[2] * r.data[8],

		data[3] * r.data[0] + data[4] * r.data[3] + data[5] * r.data[6],
		data[3] * r.data[1] + data[4] * r.data[4] + data[5] * r.data[7],
		data[3] * r.data[2] + data[4] * r.data[5] + data[5] * r.data[8],

		data[6] * r.data[0] + data[7] * r.data[3] + data[8] * r.data[6],
		data[6] * r.data[1] + data[7] * r.data[4] + data[8] * r.data[7],
		data[6] * r.data[2] + data[7] * r.data[5] + data[8] * r.data[8],
	};
}

template<class T>
template <uint x, uint y, uint z>
inline vec<T, 3> matrix3<T>::operator*(const base<T, x, y, z>& v) const
{
	return {
		*(T*)(&v + x) * data[0] + *(T*)(&v + y) * data[1] + *(T*)(&v + z) * data[2],
		*(T*)(&v + x) * data[3] + *(T*)(&v + y) * data[4] + *(T*)(&v + z) * data[5],
		*(T*)(&v + x) * data[6] + *(T*)(&v + y) * data[7] + *(T*)(&v + z) * data[8],
	};
}

template<class T>
inline T& matrix3<T>::operator()(uint r, uint c)
{
	return *(data + 3 * r + c);
}

template<class T>
inline T matrix3<T>::operator()(uint r, uint c) const
{
	return *(data + 3 * r + c);
}

template<class T>
inline matrix3<T>& matrix3<T>::operator*=(T s)
{
	data[0] *= s;
	data[1] *= s;
	data[2] *= s;
	data[3] *= s;
	data[4] *= s;
	data[5] *= s;
	data[6] *= s;
	data[7] *= s;
	data[8] *= s;
	return *this;
}

template<class T>
inline matrix3<T> matrix3<T>::operator*(T s) const
{
	return matrix3<T>(*this) *= s;
}

template<class T>
inline matrix3<T>& matrix3<T>::operator/=(T s)
{
	return operator*=(1 / s);
}

template<class T>
inline matrix3<T> matrix3<T>::operator/(T s) const
{
	return matrix3<T>(*this) *= (1 / s);
}

template<class T>
inline matrix3<T>::operator matrix4<T>() const
{
	return
	{
		row[0].x, row[0].y, row[0].z, 0,
		row[1].x, row[1].y, row[1].z, 0,
		row[2].x, row[2].y, row[2].z, 0,
		0, 0, 0, 1,
	};
}


template<class T>
template <uint x, uint y, uint z, uint w, uint x1, uint y1, uint z1, uint w1, uint x2, uint y2, uint z2,
	uint w2, uint x3, uint y3, uint z3, uint w3>
	inline matrix4<T>::matrix4(const base<T, x, y, z, w>& a, const base<T, x1, y1, z1, w1>& b,
		const base<T, x2, y2, z2, w2>& c, const base<T, x3, y3, z3, w3>& d)
	: data
{
		*(T*)(&a + x), *(T*)(&a + y), *(T*)(&a + z), *(T*)(&a + w),
		*(T*)(&b + x1), *(T*)(&b + y1), *(T*)(&b + z1), *(T*)(&b + w1),
		*(T*)(&c + x2), *(T*)(&c + y2), *(T*)(&c + z2), *(T*)(&c + w2),
		*(T*)(&d + x3), *(T*)(&d + y3), *(T*)(&d + z3), *(T*)(&d + w3),
}
{
}

template<class T>
inline matrix4<T>::matrix4()
	: data{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 }
{
}
template<class T>
inline matrix4<T>::matrix4(T x)
	: data{ x, 0, 0, 0, 0, x, 0, 0, 0, 0, x, 0, 0, 0, 0, 1 }
{
}

template<class T>
inline matrix4<T>::matrix4(
	T x, T y, T z, T w, T x1, T y1, T z1, T w1, T x2, T y2, T z2, T w2, T x3, T y3, T z3, T w3)
	: data{ x, y, z, w, x1, y1, z1, w1, x2, y2, z2, w2, x3, y3, z3, w3 }
{
}

template<class T>
inline matrix4<T>::matrix4(const matrix4<T>& m)
	: data{ m.data[0], m.data[1], m.data[2], m.data[3], m.data[4], m.data[5],
		m.data[6], m.data[7], m.data[8], m.data[9], m.data[10], m.data[11],
		m.data[12], m.data[13], m.data[14], m.data[15] }
{
}

template<class T>
inline matrix4<T>& matrix4<T>::operator=(const matrix4<T>& m)
{
	data[0] = m.data[0];
	data[1] = m.data[1];
	data[2] = m.data[2];
	data[3] = m.data[3];
	data[4] = m.data[4];
	data[5] = m.data[5];
	data[6] = m.data[6];
	data[7] = m.data[7];
	data[8] = m.data[8];
	data[9] = m.data[9];
	data[10] = m.data[10];
	data[11] = m.data[11];
	data[12] = m.data[12];
	data[13] = m.data[13];
	data[14] = m.data[14];
	data[15] = m.data[15];
	return *this;
}

template<class T>
inline T matrix4<T>::det() const
{
	T det_08_09 = (data[8] * data[13] - data[9] * data[12]);
	T det_08_10 = (data[8] * data[14] - data[10] * data[12]);
	T det_08_11 = (data[8] * data[15] - data[11] * data[12]);
	T det_09_10 = (data[9] * data[14] - data[10] * data[13]);
	T det_09_11 = (data[9] * data[15] - data[11] * data[13]);
	T det_10_11 = (data[10] * data[15] - data[11] * data[14]);
	return data[0]
		* (data[5] * (det_10_11)-data[6] * (det_09_11)+data[7] * (det_09_10))
		- data[1]
		* (data[4] * (det_10_11)-data[6] * (det_08_11)+data[7] * (det_08_10))
		+ data[2]
		* (data[4] * (det_09_11)-data[5] * (det_08_11)+data[7] * (det_08_09))
		- data[3]
		* (data[4] * (det_09_10)-data[5] * (det_08_10)+data[6] * (det_08_09));
}

template<class T>
inline matrix4<T> matrix4<T>::inv() const
{
	T zw0 = data[10] * data[15] - data[11] * data[14];
	T yw0 = data[9] * data[15] - data[11] * data[13];
	T yz0 = data[9] * data[14] - data[10] * data[13];
	T xw0 = data[8] * data[15] - data[11] * data[12];
	T xz0 = data[8] * data[14] - data[10] * data[12];
	T xy0 = data[8] * data[13] - data[9] * data[12];

	T zw1 = data[3] * data[14] - data[2] * data[15];
	T yw1 = data[3] * data[13] - data[1] * data[15];
	T yz1 = data[2] * data[13] - data[1] * data[14];
	T xw1 = data[3] * data[12] - *(data + 0) * data[15];
	T xz1 = data[2] * data[12] - *(data + 0) * data[14];
	T xy1 = data[1] * data[12] - *(data + 0) * data[13];

	T zw2 = data[2] * data[7] - data[3] * data[6];
	T yw2 = data[1] * data[7] - data[3] * data[5];
	T yz2 = data[1] * data[6] - data[2] * data[5];
	T xw2 = data[0] * data[7] - data[3] * data[4];
	T xz2 = data[0] * data[6] - data[2] * data[4];
	T xy2 = data[0] * data[5] - data[1] * data[4];

	T zw3 = data[11] * data[6] - data[10] * data[7];
	T yw3 = data[11] * data[5] - data[9] * data[7];
	T yz3 = data[10] * data[5] - data[9] * data[6];
	T xw3 = data[11] * data[4] - data[8] * data[7];
	T xz3 = data[10] * data[4] - data[8] * data[6];
	T xy3 = data[9] * data[4] - data[8] * data[5];

	T x0 = data[5] * zw0 - data[6] * yw0 + data[7] * yz0;
	T y0 = data[4] * zw0 - data[6] * xw0 + data[7] * xz0;
	T z0 = data[4] * yw0 - data[5] * xw0 + data[7] * xy0;
	T w0 = data[4] * yz0 - data[5] * xz0 + data[6] * xy0;

	T x1 = data[9] * zw1 - data[10] * yw1 + data[11] * yz1;
	T y1 = data[8] * zw1 - data[10] * xw1 + data[11] * xz1;
	T z1 = data[8] * yw1 - data[9] * xw1 + data[11] * xy1;
	T w1 = data[8] * yz1 - data[9] * xz1 + data[10] * xy1;

	T x2 = data[13] * zw2 - data[14] * yw2 + data[15] * yz2;
	T y2 = data[12] * zw2 - data[14] * xw2 + data[15] * xz2;
	T z2 = data[12] * yw2 - data[13] * xw2 + data[15] * xy2;
	T w2 = data[12] * yz2 - data[13] * xz2 + data[14] * xy2;

	T x3 = data[1] * zw3 - data[2] * yw3 + data[3] * yz3;
	T y3 = data[0] * zw3 - data[2] * xw3 + data[3] * xz3;
	T z3 = data[0] * yw3 - data[1] * xw3 + data[3] * xy3;
	T w3 = data[0] * yz3 - data[1] * xz3 + data[2] * xy3;

	T det = 1 / (data[0] * x0 - data[1] * y0 + data[2] * z0 - data[3] * w0);
	return { det * x0, det * -x1, det * x2, det * -x3, det * -y0, det * y1, det * -y2, det * y3,
		det * z0, det * -z1, det * z2, det * -z3, det * -w0, det * w1, det * -w2, det * w3 };
}

template<class T>
inline matrix4<T> matrix4<T>::xpos() const
{
	return { data[0], data[4], data[8], data[12], data[1], data[5], data[9],
		data[13], data[2], data[6], data[10], data[14], data[3],
		data[7], data[11], data[15] };
}

template<class T>
inline matrix4<T> matrix4<T>::operator*(const matrix4<T>& r) const
{
	return { data[0] * r.data[0] + data[1] * r.data[4] + data[2] * r.data[8]
			+ data[3] * r.data[12],
		data[0] * r.data[1] + data[1] * r.data[5] + data[2] * r.data[9]
			+ data[3] * r.data[13],
		data[0] * r.data[2] + data[1] * r.data[6] + data[2] * r.data[10]
			+ data[3] * r.data[14],
		data[0] * r.data[3] + data[1] * r.data[7] + data[2] * r.data[11]
			+ data[3] * r.data[15],

		data[4] * r.data[0] + data[5] * r.data[4] + data[6] * r.data[8]
			+ data[7] * r.data[12],
		data[4] * r.data[1] + data[5] * r.data[5] + data[6] * r.data[9]
			+ data[7] * r.data[13],
		data[4] * r.data[2] + data[5] * r.data[6] + data[6] * r.data[10]
			+ data[7] * r.data[14],
		data[4] * r.data[3] + data[5] * r.data[7] + data[6] * r.data[11]
			+ data[7] * r.data[15],

		data[8] * r.data[0] + data[9] * r.data[4] + data[10] * r.data[8]
			+ data[11] * r.data[12],
		data[8] * r.data[1] + data[9] * r.data[5] + data[10] * r.data[9]
			+ data[11] * r.data[13],
		data[8] * r.data[2] + data[9] * r.data[6] + data[10] * r.data[10]
			+ data[11] * r.data[14],
		data[8] * r.data[3] + data[9] * r.data[7] + data[10] * r.data[11]
			+ data[11] * r.data[15],

		data[12] * r.data[0] + data[13] * r.data[4] + data[14] * r.data[8]
			+ data[15] * r.data[12],
		data[12] * r.data[1] + data[13] * r.data[5] + data[14] * r.data[9]
			+ data[15] * r.data[13],
		data[12] * r.data[2] + data[13] * r.data[6] + data[14] * r.data[10]
			+ data[15] * r.data[14],
		data[12] * r.data[3] + data[13] * r.data[7] + data[14] * r.data[11]
			+ data[15] * r.data[15] };
}

template<class T>
template <uint x, uint y, uint z, uint w>
inline vec<T, 4> matrix4<T>::operator*(const base<T, x, y, z, w>& v) const
{
	return { *(T*)(&v + x) * data[0] + *(T*)(&v + y) * data[1] + *(T*)(&v + z) * data[2]
			+ *(T*)(&v + w) * data[3],
		*(T*)(&v + x) * data[4] + *(T*)(&v + y) * data[5] + *(T*)(&v + z) * data[6]
			+ *(T*)(&v + w) * data[7],
		*(T*)(&v + x) * data[8] + *(T*)(&v + y) * data[9] + *(T*)(&v + z) * data[10]
			+ *(T*)(&v + w) * data[11],
		*(T*)(&v + x) * data[12] + *(T*)(&v + y) * data[13] + *(T*)(&v + z) * data[14]
			+ *(T*)(&v + w) * data[15] };
}

template<class T>
inline T& matrix4<T>::operator()(uint r, uint c)
{
	return *(data + 4 * r + c);
}

template<class T>
inline T matrix4<T>::operator()(uint r, uint c) const
{
	return *(data + 4 * r + c);
}

template<class T>
inline matrix4<T>& matrix4<T>::operator*=(T s)
{
	data[0] *= s;
	data[1] *= s;
	data[2] *= s;
	data[3] *= s;
	data[4] *= s;
	data[5] *= s;
	data[6] *= s;
	data[7] *= s;
	data[8] *= s;
	data[9] *= s;
	data[10] *= s;
	data[11] *= s;
	data[12] *= s;
	data[13] *= s;
	data[14] *= s;
	data[15] *= s;
	return *this;
}

template<class T>
inline matrix4<T>& matrix4<T>::operator/=(T s)
{
	return matrix4<T>::operator*=(1 / s);
}

template<class T>
inline matrix4<T> matrix4<T>::operator*(T s) const
{
	return matrix4<T>(*this) *= s;
}

template<class T>
inline matrix4<T> matrix4<T>::operator/(T s) const
{
	return matrix4<T>(*this) *= (1 / s);
}

template<class T>
matrix4<T>::operator matrix3<T>() const
{
	return
	{
		row[0].xyz,
		row[1].xyz,
		row[2].xyz
	};
}
template<class T>
inline matrix3<T> rotx(T angle)
{
	T c = cosf(angle), s = sinf(angle);
	return
	{
		1, 0, 0,
		0, c, -s,
		0, s, c
	};
}

template<class T>
inline matrix3<T> roty(T angle)
{
	T c = cosf(angle), s = sinf(angle);
	return
	{
		  c, 0, s,
		0, 1, 0,
		 -s, 0, c
	};
}

template<class T>
inline matrix3<T> rotz(T angle)
{
	T c = cosf(angle), s = sinf(angle);
	return
	{
		c, -s, 0,
		s, c, 0,
		0, 0, 1
	};
}

template<class T>
inline std::ostream& operator << (std::ostream& s, const matrix2<T>& m)
{
	return s << m.row[0] << m.row[1];
}
template<class T>
inline std::ostream& operator << (std::ostream& s, const matrix3<T>& m)
{
	return s << m.row[0] << m.row[1] << m.row[2];
}
template<class T>
inline std::ostream& operator << (std::ostream& s, const matrix4<T>& m)
{
	return s << m.row[0] << m.row[1] << m.row[2] << m.row[3];
}

inline matrix4<float> perspective(float fov, float aspect, float n, float f) {
	float tan = 1 / float(tanf(fov * ct::rad * 0.5f));
	float fn = 1 / (f - n);
	return{
		tan * aspect,	0,			0,		 0,
			0,		tan,			0,		 0,
			0,		0,		-fn * (f + n),	-1,
			0,		0,	 -2 * f * n * fn,	 0
	};
}

inline matrix4<float> ortho(float l, float r, float b, float t) {
	float rl = 1 / (r - l);
	float tb = 1 / (t - b);
	return {
		2 * rl,				0,			 0,		0,
			 0,		   2 * tb,			 0,		0,
			 0,				0,			 1,		0,
		-rl * (r + l), -tb * (t + b),			0,		1
	};
}

inline matrix4<float> ortho(float l, float r, float b, float t, float n, float f) {
	float rl = 1 / (r - l);
	float tb = 1 / (t - b);
	float fn = 1 / (f - n);
	return {
		2 * rl,			 0,			 0,		0,
			 0,		2 * tb,			 0,		0,
			 0,			 0,		2 * fn,		0,
		-rl * (r + l), -tb * (t + b), -fn * (f + n),	1
	};
}

inline matrix4<float> view(const vec<float, 3>& p, const vec<float, 3>& r, const vec<float, 3>& u, const vec<float, 3>& d) {
	return{
		r.x, u.x, d.x, 0,
		r.y, u.y, d.y, 0,
		r.z, u.z, d.z, 0,
		-dot(r, p), -dot(u, p), -dot(d, p), 1
	};
}


template<class T, uint x, uint y>
inline vec<T, 2> operator *(const base<T, x, y>& v, const matrix2<T>& m) {
	return {
		*(T*)(&v + x) * m.data[0] + *(T*)(&v + y) * m.data[2],
		*(T*)(&v + x) * m.data[1] + *(T*)(&v + y) * m.data[3],
	};
}

template<class T, uint x, uint y, uint z>
inline  vec<T, 3> operator *(const base<T, x, y, z>& v, const matrix3<T>& m) {
	return {
		*(T*)(&v + x) * m.data[0] + *(T*)(&v + y) * m.data[3] + *(T*)(&v + z) * m.data[6],
		*(T*)(&v + x) * m.data[1] + *(T*)(&v + y) * m.data[4] + *(T*)(&v + z) * m.data[7],
		*(T*)(&v + x) * m.data[2] + *(T*)(&v + y) * m.data[5] + *(T*)(&v + z) * m.data[8],
	};
}

template<class T, uint x, uint y, uint z, uint w>
inline vec<T, 4> operator *(const base<T, x, y, z, w>& v, const matrix4<T>& m) {
	return {
		*(T*)(&v + x) * m.data[0] + *(T*)(&v + y) * m.data[4] + *(T*)(&v + z) * m.data[8] + *(T*)(&v + w) * m.data[12],
		*(T*)(&v + x) * m.data[1] + *(T*)(&v + y) * m.data[5] + *(T*)(&v + z) * m.data[9] + *(T*)(&v + w) * m.data[13],
		*(T*)(&v + x) * m.data[2] + *(T*)(&v + y) * m.data[6] + *(T*)(&v + z) * m.data[10] + *(T*)(&v + w) * m.data[14],
		*(T*)(&v + x) * m.data[3] + *(T*)(&v + y) * m.data[7] + *(T*)(&v + z) * m.data[11] + *(T*)(&v + w) * m.data[15]
	};
}

template<class T, uint x, uint y, uint z>
inline vec<T, 3> operator * (const base<T, x, y, z>& v, const quaternion<T>& q) {
	T _x = *(T*)(&v + y) * q.k - *(T*)(&v + z) * q.j + *(T*)(&v + x) * q.s;
	T _y = *(T*)(&v + z) * q.i - *(T*)(&v + x) * q.k + *(T*)(&v + y) * q.s;
	T _z = *(T*)(&v + x) * q.j - *(T*)(&v + y) * q.i + *(T*)(&v + z) * q.s;
	T _w = *(T*)(&v + x) * q.i + *(T*)(&v + y) * q.j + *(T*)(&v + z) * q.k;
	return vec3(_y * q.k - _z * q.j + _x * q.s + q.i * _w,
		_z * q.i - _x * q.k + _y * q.s + q.j * _w,
		_x * q.j - _y * q.i + _z * q.s + q.k * _w);
}

template<class T>
template <uint a, uint b, uint c>
inline quaternion<T>::quaternion(const base<T, a, b, c>& v, T w)
	: data{ *(T*)(&v + a), *(T*)(&v + b), *(T*)(&v + c), w }
{
}

template<class T>
inline quaternion<T>::quaternion()
	: data{ 0, 0, 0, 1 }
{
}

template<class T>
inline quaternion<T>::quaternion(T x, T y, T z, T w)
	: data{ x, y, z, w }
{
}

template<class T>
inline quaternion<T>::quaternion(const vec<T, 3>& v, T w)
	: data{ v.x, v.y, v.z, w }
{
}

template<class T>
inline quaternion<T>::quaternion(const quaternion<T>& q)
	: data{ q.x, q.y, q.z, q.w }
{
}

template<class T>
inline quaternion<T>::quaternion(const matrix3<T>& m)
{
	float tr = m(0, 0) + m(1, 1) + m(2, 2);
	if (tr > 0.f) {
		float S = 0.5f / sqrt(tr + 1.f);
		w = 0.25f / S;
		x = (m(2, 1) - m(1, 2)) * S;
		y = (m(0, 2) - m(2, 0)) * S;
		z = (m(1, 0) - m(0, 1)) * S;
	}
	else if (m(0, 0) > m(1, 1) && m(0, 0) > m(2, 2)) {
		float S = 0.5f / sqrt(1.f + m(0, 0) - m(1, 1) - m(2, 2));
		w = (m(2, 1) - m(1, 2)) * S;
		x = 0.25f / S;
		y = (m(0, 1) + m(1, 0)) * S;
		z = (m(0, 2) + m(2, 0)) * S;
	}
	else if (m(1, 1) > m(2, 2)) {
		float S = 0.5f / sqrt(1.f + m(1, 1) - m(0, 0) - m(2, 2));
		w = (m(0, 2) - m(2, 0)) * S;
		x = (m(0, 1) + m(1, 0)) * S;
		y = 0.25f / S;
		z = (m(1, 2) + m(2, 1)) * S;
	}
	else {
		float S = 0.5f / sqrt(1.f + m(2, 2) - m(0, 0) - m(1, 1));
		w = (m(1, 0) - m(0, 1)) * S;
		x = (m(0, 2) + m(2, 0)) * S;
		y = (m(1, 2) + m(2, 1)) * S;
		z = 0.25f / S;
	}
}

template<class T>
inline quaternion<T>::quaternion(const matrix4<T>& m)
{
	float tr = m(0, 0) + m(1, 1) + m(2, 2);
	if (tr > 0.f) {
		float S = 0.5f / sqrt(tr + 1.f);
		w = 0.25f / S;
		x = (m(2, 1) - m(1, 2)) * S;
		y = (m(0, 2) - m(2, 0)) * S;
		z = (m(1, 0) - m(0, 1)) * S;
	}
	else if (m(0, 0) > m(1, 1) && m(0, 0) > m(2, 2)) {
		float S = 0.5f / sqrt(1.f + m(0, 0) - m(1, 1) - m(2, 2));
		w = (m(2, 1) - m(1, 2)) * S;
		x = 0.25f / S;
		y = (m(0, 1) + m(1, 0)) * S;
		z = (m(0, 2) + m(2, 0)) * S;
	}
	else if (m(1, 1) > m(2, 2)) {
		float S = 0.5f / sqrt(1.f + m(1, 1) - m(0, 0) - m(2, 2));
		w = (m(0, 2) - m(2, 0)) * S;
		x = (m(0, 1) + m(1, 0)) * S;
		y = 0.25f / S;
		z = (m(1, 2) + m(2, 1)) * S;
	}
	else {
		float S = 0.5f / sqrt(1.f + m(2, 2) - m(0, 0) - m(1, 1));
		w = (m(1, 0) - m(0, 1)) * S;
		x = (m(0, 2) + m(2, 0)) * S;
		y = (m(1, 2) + m(2, 1)) * S;
		z = 0.25f / S;
	}
}

template<class T>
inline T quaternion<T>::len() const
{
	return sqrtf(x * x + y * y + z * z + w * w);
}

template<class T>
inline T quaternion<T>::len2() const
{
	return x * x + y * y + z * z + w * w;
}

template<class T>
inline quaternion<T>& quaternion<T>::normalize()
{
	~q;
	return *this;
}

template<class T>
inline quaternion<T>& quaternion<T>::operator=(const quaternion<T>& q)
{
	x = q.x, y = q.y, z = q.z, w = q.w;
	return *this;
}

template<class T>
inline quaternion<T> quaternion<T>::operator~() const
{
	return { -x, -y, -z, w };
}

template<class T>
inline quaternion<T> quaternion<T>::operator-() const
{
	return { -x, -y, -z, -w };
}

template<class T>
inline quaternion<T>& quaternion<T>::operator+=(const quaternion<T>& q)
{
	x += q.x, y += q.y, z += q.z, w += q.w;
	return *this;
}

template<class T>
inline quaternion<T>& quaternion<T>::operator-=(const quaternion<T>& q)
{
	x -= q.x, y -= q.y, z -= q.z, w -= q.w;
	return *this;
}

template<class T>
inline quaternion<T> quaternion<T>::operator+(const quaternion<T>& q) const
{
	return quaternion<T>(*this) += q;
}

template<class T>
inline quaternion<T> quaternion<T>::operator-(const quaternion<T>& q) const
{
	return quaternion<T>(*this) -= q;
}

template<class T>
inline quaternion<T>& quaternion<T>::operator*=(T s)
{
	x *= s, y *= s, z *= s, w *= s;
	return *this;
}

template<class T>
inline quaternion<T>& quaternion<T>::operator/=(T s)
{
	s = 1 / s;
	x *= s, y *= s, z *= s, w *= s;
	return *this;
}

template<class T>
inline quaternion<T>  quaternion<T>::operator*(float s) const
{
	return { q.x * s, q.y * s, q.z * s, q.w * s };
}

template<class T>
inline quaternion<T>  quaternion<T>::operator/(float s) const
{
	s = 1 / s;
	return { q.x * s, q.y * s, q.z * s, q.w * s };
}

template<class T>
inline quaternion<T> operator*(float s, const quaternion<T>& q)
{
	return { q.x * s, q.y * s, q.z * s, q.w * s };
}

template<class T>
inline quaternion<T> operator/(float s, const quaternion<T>& q)
{
	s /= q.len2();
	return ~q *= s;
}

template<class T>
inline quaternion<T> quaternion<T>::operator/(const quaternion<T>& q) const
{
	return (*this * ~q) /= q.len2();
}

template<class T>
inline quaternion<T> quaternion<T>::operator*=(const quaternion<T>& q)
{
	return *this = *this * q;
}

template<class T>
inline quaternion<T> quaternion<T>::operator/=(const quaternion<T>& q)
{
	return *this = *this / q;
}

template<class T>
inline quaternion<T> quaternion<T>::operator*(const quaternion<T>& q) const
{
	return { s * q.i + i * q.s + j * q.k - k * q.j, s * q.j + j * q.s + k * q.i - i * q.k,
		s * q.k + k * q.s + i * q.j - j * q.i, s * q.s - i * q.i - j * q.j - k * q.k };
}

template<class T>
inline quaternion<T>::operator matrix3<T>() const
{
	T i2 = i + i, j2 = j + j, k2 = k + k;
	T ii = i * i2, ij = i * j2, ik = i * k2;
	T jj = j * j2, jk = j * k2, kk = k * k2;
	T si = s * i2, sj = s * j2, sk = s * k2;
	return { 1 - (jj + kk), ij - sk, ik + sj, ij + sk, 1 - (ii + kk), jk - si, ik - sj, jk + si,
		1 - (ii + jj) };
}

template<class T>
inline quaternion<T>::operator matrix4<T>() const
{
	T i2 = i + i, j2 = j + j, k2 = k + k;
	T ii = i * i2, ij = i * j2, ik = i * k2;
	T jj = j * j2, jk = j * k2, kk = k * k2;
	T si = s * i2, sj = s * j2, sk = s * k2;
	return { 1 - (jj + kk), ij - sk, ik + sj, 0, ij + sk, 1 - (ii + kk), jk - si, 0, ik - sj,
		jk + si, 1 - (ii + jj), 0, 0, 0, 0, 1 };
}

template<class T>
template<uint a, uint b, uint c>
inline vec<T, 3> quaternion<T>::operator *(const base<T, a, b, c>& v) const
{
	T _x = j * *(T*)(&v + c) - k * *(T*)(&v + b) + s * *(T*)(&v + a);
	T _y = k * *(T*)(&v + a) - i * *(T*)(&v + c) + s * *(T*)(&v + b);
	T _z = i * *(T*)(&v + b) - j * *(T*)(&v + a) + s * *(T*)(&v + c);
	T _w = i * *(T*)(&v + a) + j * *(T*)(&v + b) + k * *(T*)(&v + c);
	return { j * _z - k * _y + s * _x + i * _w, k * _x - i * _z + s * _y + j * _w,
		i * _y - j * _x + s * _z + k * _w };
}


inline quaternion<float> axAng(float x, float y, float z, float w)
{
	return { norm(x, y, z) *= sinf(w * 0.5f), cosf(w * 0.5f) };
}

inline quaternion<float> axAng(const quaternion<float>& q)
{
	return { q.v.norm() *= sinf(q.w * 0.5f), cosf(q.w * 0.5f) };
}

template<uint x, uint y, uint z>
inline quaternion<float> axAng(const base<float, x, y, z>& v, float w)
{
	return { v.norm() *= sinf(w * 0.5f), cosf(w * 0.5f) };
}

using mat2 = matrix2<float>;
using mat3 = matrix3<float>;
using mat4 = matrix4<float>;
using quat = quaternion<float>;
using umat3 = matrix3<uint>;
using namespace std;