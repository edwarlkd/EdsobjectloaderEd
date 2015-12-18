#ifndef SO_STARTINGLINE_H
#define SO_STARTINGLINE_H

#include <vector>
#include <gsim/gs_color.h>
#include <gsim/gs_vec.h>
#include "ogl_tools.h"
#include <cmath>

# include <gsim/gs_mat.h>
# include <gsim/gs_light.h>
# include <gsim/gs_material.h>
# include <gsim/gs_array.h>
# include <gsim/gs_image.h>

class Startingline : public GlObjects
{
private:

	int _numpoints;         // saves the number of points
	const float pi = 3.1415926;

public:
	std::vector<GsVec>   P; // coordinates
	std::vector<GsColor> C; // colors

	GsArray<GsVec> Parray, N;
	GsArray<GsColor> Carray;

	GlShader _vsh, _fsh;
	GlProgram _prog;


	GsVec eval_bezier(float t, const std::vector<GsVec>& ctrlpnts);
	float factorialfunction(float);
	float cfunction(int, int);
	float bfunction(float);
	float countnumberi;
	float totalnumbern;

	GsArray<GsVec2> T;
	GlShader _vshgou, _fshgou, _vshphong, _fshphong; //vertex and fragment 
	GlProgram _proggouraud, _progphong; //program to use the data?
	GsMaterial _mtl;


	Startingline();
	~Startingline();

	void init();
	void build();
	void draw(const GsMat& tr, const GsMat& pr, const GsLight& l);

};



#endif