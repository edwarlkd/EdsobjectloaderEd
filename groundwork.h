#ifndef SO_GROUNDWORK_H
#define SO_GROUNDWORK_H

#include <vector>
#include <gsim/gs_color.h>
#include <gsim/gs_vec.h>
#include "ogl_tools.h"
#include <cmath>
#include <gsim/gs_array.h>
//front wheel and barhandle

class Groundwork : public GlObjects
{
private:

	int _numpoints;         // saves the number of points
	const float pi = 3.1415926;

public:
	std::vector<GsVec>   P; // coordinates
	std::vector<GsColor> C; // colors

	GsArray<GsVec> Parray;
	GsArray<GsColor> Carray;

	GlShader _vsh, _fsh;
	GlProgram _prog;


	GsVec eval_bezier(float t, const std::vector<GsVec>& ctrlpnts);
	float factorialfunction(float);
	float cfunction(int, int);
	float bfunction(float);
	float countnumberi;
	float totalnumbern;

	Groundwork();
	~Groundwork();

	void init();
	void build();
	void draw(GsMat& tr, GsMat& pr);

};



#endif