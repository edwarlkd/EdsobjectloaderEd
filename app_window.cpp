
# include <iostream>
# include <gsim/gs.h>
# include "app_window.h"

AppWindow::AppWindow ( const char* label, int x, int y, int w, int h )
          :GlutWindow ( label, x, y, w, h )
 {
   initPrograms ();
   addMenuEntry ( "Option 0", evOption0 );
   addMenuEntry ( "Option 1", evOption1 );
   _viewaxis = true;
   _fovy = GS_TORAD(60.0f);
   _rotx = _roty = 0;
   _w = w;
   _h = h;
 }

void AppWindow::initPrograms ()
 {
   // Init my scene objects:
   _axis.init ();

   //Init Car 1//
   _model.init ();
   _Tire1.init();
   _Tire2.init();
   _Tire3.init();
   _Tire4.init();

   //Init Car 2//
   _model_1.init();
   _Tire1_1.init();
   _Tire1_2.init();
   _Tire1_3.init();
   _Tire1_4.init();



   _racingtrack.init();
   _groundworkoutside.init();
   _groundwork.init();
   _startingline.init();


   // set light:
   _light.set ( GsVec(0,0,10), GsColor(90,90,90,255), GsColor::white, GsColor::white );

   // Load demo model:
   loadModel ( 1 );
 }

static void printInfo ( GsModel& m )
 {
   std::cout<<"V:  "<<m.V.size()<<"\n";
   std::cout<<"F:  "<<m.F.size()<<"\n";
   std::cout<<"N:  "<<m.N.size()<<"\n";
   std::cout<<"M:  "<<m.M.size()<<"\n";
   std::cout<<"Fn: "<<m.Fn.size()<<"\n";
   std::cout<<"Fm: "<<m.Fm.size()<<"\n";
 }

void AppWindow::loadModel ( int model )
 {
	 float f;
	 //Car1//
	 GsString file;
	 GsString file2;
	 GsString file3;
	 GsString file4;
	 GsString file5;

	 //Car2//
	 GsString file1;
	 GsString file1_2;
	 GsString file1_3;
	 GsString file1_4;
	 GsString file1_5;

	//Load Car1//
	 f = 0.1f;
	 file = "../models/Car1/Body.obj"; file2 = "../models/Car1/Tire_1.obj"; file3 = "../models/Car1/Tire_2.obj"; file4 = "../models/Car1/Tire_3.obj"; file5 = "../models/Car1/Tire_4.obj";
	 file = "../models/Car2/Body2.obj"; file2 = "../models/Car2/Tire2_1.obj"; file3 = "../models/Car2/Tire2_2.obj"; file4 = "../models/Car2/Tire2_3.obj"; file5 = "../models/Car2/Tire2_4.obj";

	 std::cout << "Loading " << file << "...\n";
	 if (!_gsm.load(file)) std::cout << "Error!\n";
	 printInfo(_gsm);
	 _gsm.scale(f); // to fit our camera space

	 std::cout << "Loading " << file2 << "...\n";
	 if (!_gsm2.load(file2)) std::cout << "Error!\n";
	 printInfo(_gsm2);
	 _gsm2.scale(f); // to fit our camera space

	 std::cout << "Loading " << file3 << "...\n";
	 if (!_gsm3.load(file3)) std::cout << "Error!\n";
	 printInfo(_gsm3);
	 _gsm3.scale(f); // to fit our camera space

	 std::cout << "Loading " << file4 << "...\n";
	 if (!_gsm4.load(file4)) std::cout << "Error!\n";
	 printInfo(_gsm4);
	 _gsm4.scale(f); // to fit our camera space

	 std::cout << "Loading " << file5 << "...\n";
	 if (!_gsm5.load(file5)) std::cout << "Error!\n";
	 printInfo(_gsm5);
	 _gsm5.scale(f); // to fit our camera space
	 /////////////////////////////////////////////////////////////
	 //Load Car 2//
	 std::cout << "Loading " << file1 << "...\n";
	 if (!_gsm1.load(file1)) std::cout << "Error!\n";
	 printInfo(_gsm1);
	 _gsm1.scale(f); // to fit our camera space

	 std::cout << "Loading " << file1_2 << "...\n";
	 if (!_gsm1_2.load(file1_2)) std::cout << "Error!\n";
	 printInfo(_gsm1_2);
	 _gsm1_2.scale(f); // to fit our camera space

	 std::cout << "Loading " << file1_3 << "...\n";
	 if (!_gsm1_3.load(file1_3)) std::cout << "Error!\n";
	 printInfo(_gsm1_3);
	 _gsm1_3.scale(f); // to fit our camera space

	 std::cout << "Loading " << file1_4 << "...\n";
	 if (!_gsm1_4.load(file1_4)) std::cout << "Error!\n";
	 printInfo(_gsm1_4);
	 _gsm1_4.scale(f); // to fit our camera space

	 std::cout << "Loading " << file1_5 << "...\n";
	 if (!_gsm1_5.load(file1_5)) std::cout << "Error!\n";
	 printInfo(_gsm1_5);
	 _gsm1_5.scale(f); // to fit our camera space


	 //Build Car1//
	 _model.build(_gsm);
	 _Tire1.build(_gsm2);
	 _Tire2.build(_gsm3);
	 _Tire3.build(_gsm4);
	 _Tire4.build(_gsm5);

	 //Build Car2//
	 _model_1.build(_gsm1);
	 _Tire1_1.build(_gsm1_2);
	 _Tire1_2.build(_gsm1_3);
	 _Tire1_3.build(_gsm1_4);
	 _Tire1_4.build(_gsm1_5);

	 redraw();

 }

// mouse events are in window coordinates, but your 2D scene is in [0,1]x[0,1],
// so make here the conversion when needed
GsVec2 AppWindow::windowToScene ( const GsVec2& v )
 {
   // GsVec2 is a lighteweight class suitable to return by value:
   return GsVec2 ( (2.0f*(v.x/float(_w))) - 1.0f,
                    1.0f - (2.0f*(v.y/float(_h))) );
 }

// Called every time there is a window event
void AppWindow::glutKeyboard ( unsigned char key, int x, int y )
 {
   switch ( key )
    { case ' ': _viewaxis = !_viewaxis; redraw(); break;
	  case 27 : exit(1); // Esc was pressed
      case 's' : std::cout<<"Smoothing normals...\n";
                _gsm.smooth ( GS_TORAD(35) ); 
                 printInfo(_gsm);
                 _model.build(_gsm); 
                 redraw(); 
                 break;
      case 'f' : std::cout<<"Flat normals...\n";
                _gsm.flat();
                 printInfo(_gsm);
                 _model.build(_gsm); 
                 redraw(); 
                 break;
      case 'p' : if ( !_model.phong() )
                  { std::cout<<"Switching to phong shader...\n";
                    _model.phong(true);
                  }
                 redraw(); 
                 break;
      case 'g' : if ( _model.phong() )
                  { std::cout<<"Switching to gouraud shader...\n";
                    _model.phong(false);
                  }
                 redraw(); 
                 break;
      default : loadModel ( int(key-'0') );
                break;
	}
 }

void AppWindow::glutSpecial ( int key, int x, int y )
 {
   bool rd=true;
   const float incr=GS_TORAD(2.5f);
   const float incf=0.05f;
   switch ( key )
    { case GLUT_KEY_LEFT:      _roty-=incr; break;
      case GLUT_KEY_RIGHT:     _roty+=incr; break;
      case GLUT_KEY_UP:        _rotx+=incr; break;
      case GLUT_KEY_DOWN:      _rotx-=incr; break;
      case GLUT_KEY_PAGE_UP:   _fovy-=incf; break;
      case GLUT_KEY_PAGE_DOWN: _fovy+=incf; break;
      default: return; // return without rendering
	}
   if (rd) redraw(); // ask the window to be rendered when possible
 }

void AppWindow::glutMouse ( int b, int s, int x, int y )
 {
   // The mouse is not used in this example.
   // Recall that a mouse click in the screen corresponds
   // to a whole line traversing the 3D scene.
 }

void AppWindow::glutMotion ( int x, int y )
 {
 }

void AppWindow::glutMenu ( int m )
 {
   std::cout<<"Menu Event: "<<m<<std::endl;
 }

void AppWindow::glutReshape ( int w, int h )
 {
   // Define that OpenGL should use the whole window for rendering
   glViewport( 0, 0, w, h );
   _w=w; _h=h;
 }

// here we will redraw the scene according to the current state of the application.
void AppWindow::glutDisplay ()
 {
   // Clear the rendering window
   glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

   // Build a cross with some lines (if not built yet):
   if ( _axis.changed ) // needs update
    { _axis.build(1.0f); // axis has radius 1.0
    }

   if (buildonce)
   {
	   _racingtrack.build();
	   _groundworkoutside.build(_racingtrack.coordout);
	   _groundwork.build();
	   _startingline.build();
	   buildonce = false;
   }



   // Define our scene transformation:
   GsMat rx, ry, stransf;
   rx.rotx ( _rotx );
   ry.roty ( _roty );
   stransf = rx*ry; // set the scene transformation matrix

   // Define our projection transformation:
   // (see demo program in gltutors-projection.7z, we are replicating the same behavior here)
   GsMat camview, persp, sproj;

   GsVec eye(0,0,2), center(0,0,0), up(0,1,0);
   camview.lookat ( eye, center, up ); // set our 4x4 "camera" matrix

   float aspect=1.0f, znear=0.1f, zfar=50.0f;
   persp.perspective ( _fovy, aspect, znear, zfar ); // set our 4x4 perspective matrix

   // Our matrices are in "line-major" format, so vertices should be multiplied on the 
   // right side of a matrix multiplication, therefore in the expression below camview will
   // affect the vertex before persp, because v' = (persp*camview)*v = (persp)*(camview*v).
   sproj = persp * camview; // set final scene projection

   //  Note however that when the shader receives a matrix it will store it in column-major 
   //  format, what will cause our values to be transposed, and we will then have in our 
   //  shaders vectors on the left side of a multiplication to a matrix.

   // Draw:
   if ( _viewaxis ) _axis.draw ( stransf, sproj );
   

   _racingtrack.draw(stransf, sproj);
   _groundworkoutside.draw(stransf, sproj, _light);
   _groundwork.draw(stransf, sproj);
   _startingline.draw(stransf, sproj, _light);

   //Car1//
   _model.draw(stransf, sproj, _light);
   _Tire1.draw(stransf, sproj, _light);
   _Tire2.draw(stransf, sproj, _light);
   _Tire3.draw(stransf, sproj, _light);
   _Tire4.draw(stransf, sproj, _light);

   //Car2//

   // Swap buffers and draw:
   glFlush();         // flush the pipeline (usually not necessary)
   glutSwapBuffers(); // we were drawing to the back buffer, now bring it to the front
}


