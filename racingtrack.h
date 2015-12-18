#ifndef SO_RACINGTRACK_H
#define SO_RACINGTRACK_H

#include <vector>
#include <gsim/gs_color.h>
#include <gsim/gs_vec.h>
#include "ogl_tools.h"
#include <cmath>
#include <gsim/gs_array.h>

//front wheel and barhandle

class Racingtrack : public GlObjects
{
private:

	int _numpoints;         // saves the number of points
	const float pi = 3.1415926;

public:
	std::vector<GsVec>   P; // coordinates
	std::vector<GsColor> C; // colors

	GsArray<GsVec> Parray;
	GsArray<GsColor> Carray;
	GsArray<GsVec> coordout;

	GsVec eval_bezier(float t, const std::vector<GsVec>& ctrlpnts);
	float factorialfunction(float);
	float cfunction(int, int);
	float bfunction(float);
	float countnumberi;
	float totalnumbern;

	Racingtrack();
	~Racingtrack();

	void init();
	void build();
	void draw(GsMat& tr, GsMat& pr );


	GlShader _vsh, _fsh;
	GlProgram _prog;

};





#endif