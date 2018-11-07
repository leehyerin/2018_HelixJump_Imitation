#pragma once

//-----------Math helper--------------
#define PI 3.141592




double ConvertToRadian(double DegreeValue)
{
	double RadianValue = DegreeValue * (PI / 180.0);
	return RadianValue;
}