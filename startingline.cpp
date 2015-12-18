#include "startingline.h"

Startingline::Startingline()
{

}

Startingline::~Startingline()
{

}

void Startingline::init()
{
	// Build program:
	_vsh.load_and_compile(GL_VERTEX_SHADER, "../vsh_mcol_flat.glsl");
	_fsh.load_and_compile(GL_FRAGMENT_SHADER, "../fsh_flat.glsl");
	_prog.init_and_link(_vsh, _fsh);

	// Define buffers needed:
	gen_vertex_arrays(1); // will use 1 vertex array
	gen_buffers(2);       // will use 2 buffers: one for coordinates and one for colors
	_prog.uniform_locations(2); // will send 2 variables: the 2 matrices below
	_prog.uniform_location(0, "vTransf");
	_prog.uniform_location(1, "vProj");
}

void Startingline::build() // 
{
	Parray.push() = GsVec(-1.0f, 0.1f, -0.2f);
	Parray.push() = GsVec(1.0f, 0.1f, -0.2f);
	Parray.push() = GsVec(-1.0f, 0.1f, 0.2f);
	
	Parray.push() = GsVec(1.0f, 0.1f, 0.2f);
	Parray.push() = GsVec(1.0f, 0.1f, -0.2f);
	Parray.push() = GsVec(-1.0f, 0.1f, 0.2f);

	//shifting
	GsMat result, rotation, translation;
	//	float rotationangle2 = (6 * pi / 7);
	translation.e14 = -4.0f; //translation for barbetweenhandle
	translation.e24 = 0.0f;
	translation.e34 = 0.0f;
	result = translation;
	for (int i = 0; i < Parray.size(); i++)
	{
		Parray[i] = result*Parray[i];
	}

	/*	coordinates for the starting line:
	Parray[0] = -5, 0.1, -0.2
	Parray[1] = -3, 0.1, -0.2
	Parray[2] = -5, 0.1, 0.2
	Parray[3] = -3, 0.1, 0.2
	Parray[4] = -3, 0.1, -0.2
	Parray[5] = -5, 0.1, 0.2
	*/

	
	float genius = Parray.size() / 6;
	for (int i = 0; i < (genius); i++)
	{
		float me = i;
		T.push() = (GsVec2(me / genius, 0))* -1;
		T.push() = (GsVec2((me + 1) / genius, 0))* -1;
		T.push() = (GsVec2(me / genius, 1))* -1;

		T.push() = (GsVec2(me / genius, 1))* -1;
		T.push() = (GsVec2((me + 1) / genius, 1))*-1;
		T.push() = (GsVec2((me + 1) / genius, 0))*-1;
	}

	for (int i = 0; i < Parray.size(); i++)
	{
		std::cout << "Parray[" << i << "] = " << Parray[i] << "\n";
	}

	Carray.size(Parray.size()); Carray.setall(GsColor::white);

	// send data to OpenGL buffers:
	glBindVertexArray(va[0]);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, buf[0]);
	glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float)*Parray.size(), Parray.pt(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, buf[1]);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(gsbyte)*Carray.size(), Carray.pt(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_FALSE, 0, 0);

	glBindVertexArray(0); // break the existing vertex array object binding.

						  // save size so that we can free our buffers and later draw the OpenGL arrays:
	_numpoints = Parray.size();

	// free non-needed memory:
	Parray.capacity(0); Carray.capacity(0);



}

void Startingline::draw(const GsMat& tr, const GsMat& pr, const GsLight& l)
{
	// Prepare program:
	glUseProgram(_prog.id);
	glUniformMatrix4fv(_prog.uniloc[0], 1, GL_FALSE, tr.e);
	glUniformMatrix4fv(_prog.uniloc[1], 1, GL_FALSE, pr.e);

	// Draw:
	glBindVertexArray(va[0]);
	glDrawArrays(GL_TRIANGLES, 0, _numpoints);
	glBindVertexArray(0); // break the existing vertex array object binding.

}

