#ifndef __ZXINGWRITER_H__
#define __ZXINGWRITER_H__

#include <string>
#include <vector>

using namespace std;

class dPoint
{
public:
	double x;
	double y;
	bool flag;

public:
	dPoint() : x(0), y(0), flag(false) {}
};

vector<dPoint> __stdcall Border(const double d_width, const double d_height, const std::string text, const std::string type);

#endif
