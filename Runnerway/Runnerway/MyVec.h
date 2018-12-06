#pragma once

struct MyVec
{
	double x, y, z;
};

inline MyVec operator +(MyVec &a, MyVec &b)
{
	MyVec val;

	val.x = a.x + b.x;
	val.y = a.y + b.y;
	val.z = a.z + b.z;

	return val;
}

inline MyVec operator *(MyVec &a, double m)
{
	MyVec val;

	val.x = a.x * m;
	val.y = a.y * m;
	val.z = a.z * m;

	return val;
}