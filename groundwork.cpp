#include "groundwork.h"

Groundwork::Groundwork()
{

}

Groundwork::~Groundwork()
{

}

void Groundwork::init()
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
	
	
	/*
	// Define buffers needed:
	set_program(prog);
	gen_vertex_arrays(1); // will use 1 vertex array
	gen_buffers(2);       // will use 2 buffers: one for coordinates and one for colors
	uniform_locations(2); // will send 2 variables: the 2 matrices below
	uniform_location(0, "vTransf");
	uniform_location(1, "vProj");
	*/
	
}

void Groundwork::build() // this is for inner 'green' field.
{
	//two big triangle to for a square of the field.
	Parray.push() = (GsVec(-3.0f, 0.1f, -4.0f));
	Parray.push() = (GsVec(-3.0f, 0.1f, 4.0f));
	Parray.push() = (GsVec(3.0f, 0.1f, -4.0f));

	Parray.push() = (GsVec(3.0f, 0.1f, -4.0f));
	Parray.push() = (GsVec(3.0f, 0.1f, 4.0f));
	Parray.push() = (GsVec(-3.0f, 0.1f, 4.0f));
	int countline = Parray.size();

	//ring for side.
	float len1 = 0.1; //let us set the default to be 0.5
	float radiust = 3.0f;
	int nfaces = 25;
	float angle, angle2, newX, newZ, newX1, newZ1;
	int Parraycounter = 0;
	float slice = 2 * pi / nfaces; //
	for (float i = 0; i <= nfaces / 2; i++)
	{	
		angle = slice * i;
		angle2 = slice * (i + 1);
		newX = (float)(0.0 + radiust * cos(angle));
		newZ = (float)(0.0 + radiust * sin(angle));
		newX1 = (float)(0.0 + radiust * cos(angle2));
		newZ1 = (float)(0.0 + radiust * sin(angle2));

		Parray.push() = (GsVec(0.0f, len1, 0.0f));
		Parray.push() = (GsVec(newX, len1, newZ)); //7th 
		Parray.push() = (GsVec(newX1, len1, newZ1));

	}
	int sizeofring = 0;
	int sizeafterfirstring = Parray.size();
	sizeofring = Parray.size() - countline;

	//shifting the 'half ring'
	GsMat result, rotation, translation;
	//	float rotationangle2 = (6 * pi / 7);
	translation.e14 = 0.0f; 
	translation.e24 = 0.0f;
	translation.e34 = 4.0f;
	result = translation;
	for (int i = countline; i < Parray.size(); i++)
	{
		Parray[i] = result*Parray[i];
	}

	//other side half-ring
	for (float i = 0; i <= nfaces / 2; i++)
	{
		angle = slice * i;
		angle2 = slice * (i + 1);
		newX = (float)(0.0 + radiust * cos(angle));
		newZ = (float)(0.0 + radiust * sin(angle));
		newX1 = (float)(0.0 + radiust * cos(angle2));
		newZ1 = (float)(0.0 + radiust * sin(angle2));

		Parray.push() = (GsVec(0.0f, len1, 0.0f));
		Parray.push() = (GsVec(-newX, len1, -newZ));
		Parray.push() = (GsVec(-newX1, len1, -newZ1));


	}
	int sizeofring2 = 0;
	sizeofring2 = Parray.size() - sizeafterfirstring;

	//shifintg the second 
	translation.e14 = 0.0f; //translation to next at the edge of the square
	translation.e24 = 0.0f;
	translation.e34 = -4.0f;
	result = translation;
	for (int i = sizeafterfirstring; i < Parray.size(); i++)
	{
		Parray[i] = result*Parray[i]; 
	}



	for (int i = 0; i < Parray.size(); i++)
	{
		Carray.push() = (GsColor::darkgreen);
	}


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

void Groundwork::draw(GsMat& tr, GsMat& pr)
{
		// Prepare program:
	glUseProgram(_prog.id);
	glUniformMatrix4fv(_prog.uniloc[0], 1, GL_FALSE, tr.e);
	glUniformMatrix4fv(_prog.uniloc[1], 1, GL_FALSE, pr.e);

	// Draw:
	glBindVertexArray(va[0]);
	glDrawArrays(GL_TRIANGLES, 0, _numpoints);
	glBindVertexArray(0); // break the existing vertex array object binding.

/*
	// Draw Lines:
	glUseProgram(prog);
	glBindVertexArray(va[0]);
	glBindBuffer(GL_ARRAY_BUFFER, buf[0]); // positions left handle
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, buf[1]); // colors
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_FALSE, 0, 0);
	glUniformMatrix4fv(uniloc[0], 1, GL_FALSE, tr.e);
	glUniformMatrix4fv(uniloc[1], 1, GL_FALSE, pr.e);

	glDrawArrays(GL_TRIANGLES, 0, _numpoints);
*/

}

