#pragma once

//-----------Math helper--------------
#define PI 3.141592
#define RADIAN 0.0174532



inline double ConvertToRadian(double DegreeValue)
{
	double RadianValue = DegreeValue * (PI / 180.0);

	return RadianValue;
}