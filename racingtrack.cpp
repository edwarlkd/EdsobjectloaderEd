#include "racingtrack.h"

Racingtrack::Racingtrack()
{

}

Racingtrack::~Racingtrack()
{

}

void Racingtrack::init()
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

void Racingtrack::build()
{

	Parray.push() =(GsVec(-5.0f, 0.0f, -5.0f));
	Parray.push() = (GsVec(-5.0f, 0.0f, 5.0f));
	Parray.push() = (GsVec(5.0f, 0.0f, -5.0f));

	Parray.push() = (GsVec(5.0f, 0.0f, -5.0f));
	Parray.push() = (GsVec(5.0f, 0.0f, 5.0f));
	Parray.push() = (GsVec(-5.0f, 0.0f, 5.0f));
	
	coordout.push() = (Parray[2]) + GsVec(0.0f, 0.0f, 0.0f); //this will be sent to groundworkoutside
		
	int countline;
	countline = Parray.size();

	//ring for side.
	float len1 = 0.0; //let us set the default to be 0.5
	float radiust = 5.0f;
	int nfaces = 25;
	float angle, angle2, newX, newZ, newX1, newZ1;
	int Parraycounter = 0;
	float slice = 2 * pi / nfaces; // 3 to start, changes by 'q'
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

		int county = 6 + 1 + (i * 3);
		coordout.push() = (Parray[county]) + GsVec(0.0f, 0.0f, 0.0f);

	}

	int sizeofring = 0;
	int sizeafterfirstring = Parray.size();
	sizeofring = Parray.size() - countline;

	int sizeafterfirstringcoordout = coordout.size();

	//shifting the 'ring'
	GsMat result, rotation, translation;
	//	float rotationangle2 = (6 * pi / 7);
	translation.e14 = 0.0f; //translation for barbetweenhandle
	translation.e24 = 0.0f;
	translation.e34 = 5.0f;
	result = translation;
	for (int i = countline; i < Parray.size(); i++)
	{
		Parray[i] = result*Parray[i];
	}

	//	coordout.push_back(P[6]);
	//	coordout.push_back(P[8]);
	for (int i = 1; i < coordout.size(); i++)
	{
		coordout[i] = result*coordout[i];
	}

	//	coordout.push_back(P[0]);
	//	coordout.push_back(P[2]);


	//such order allows to go around 'O' track.
	//	coordout.push_back(P[6]);
	//	coordout.push_back(P[8]);

	//other size ring
	for (float i = 0; i <= nfaces / 2; i++)
	{
		angle = slice * i;
		angle2 = slice * (i + 1);
		newX = (float)(0.0 + radiust * cos(angle));
		newZ = (float)(0.0 + radiust * sin(angle));
		newX1 = (float)(0.0 + radiust * cos(angle2));
		newZ1 = (float)(0.0 + radiust * sin(angle2));

		////////////////////////////////////////////////////////////////////////
		//top 
		Parray.push() = (GsVec(0.0f, len1, 0.0f));
		Parray.push() = (GsVec(-newX, len1, -newZ));
		Parray.push() = (GsVec(-newX1, len1, -newZ1));

		int x = sizeafterfirstring + 1 + (i * 3);
		coordout.push() = (Parray[x]) + GsVec(0.0f, 0.0f, 0.0f);



	}
	int sizeofring2 = 0;
	sizeofring2 = Parray.size() - sizeafterfirstring;
	
	//shifintg the second 
	translation.e14 = 0.0f; //translation for barbetweenhandle
	translation.e24 = 0.0f;
	translation.e34 = -5.0f;
	result = translation;
	for (int i = sizeafterfirstring; i < Parray.size(); i++)
	{
		Parray[i] = result*Parray[i];
	}

	//coordout.push_back(P[0]);
	//	coordout.push_back(P[2]);
	//	coordout.push_back(P[P.size() - 1]);
	//	coordout.push_back(P[0]);
	//	coordout.push_back(P[2]);

	for (int i = sizeafterfirstringcoordout; i < coordout.size(); i++)
	{
		coordout[i] = result*coordout[i];       
	}
	
	for (int i = 0; i < Parray.size(); i++) Carray.push() = GsColor::black;

	


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

void Racingtrack::draw(GsMat& tr, GsMat& pr)
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

