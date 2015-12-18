
// Ensure the header file is included only once in multi-file projects
#ifndef APP_WINDOW_H
#define APP_WINDOW_H

# include <gsim/gs_color.h>
# include <gsim/gs_array.h>
# include <gsim/gs_light.h>
# include <gsim/gs_vec.h>
# include "ogl_tools.h"
# include "glut_window.h"
# include "so_axis.h"
# include "so_model.h"


# include "racingtrack.h"
# include "groundwork.h"
# include "groundworkoutside.h"
# include "startingline.h"



// The functionality of your application should be implemented inside AppWindow
class AppWindow : public GlutWindow
 { private :
    // OpenGL shaders and programs:
//    GlShader _vshflat, _fshflat, _vshgou, _fshgou, _vshphong, _fshphong;
  //  GlProgram _progflat, _proggou, _progphong;

    // My scene objects:
    SoAxis _axis;

	//Car Model 1//
	SoModel _model;
	SoModel _Tire1;
	SoModel _Tire2;
	SoModel _Tire3;
	SoModel _Tire4;
	///////////////

	//Car Model 2//
	SoModel _model_1;
	SoModel _Tire1_1;
	SoModel _Tire1_2;
	SoModel _Tire1_3;
	SoModel _Tire1_4;
	///////////////

	Racingtrack _racingtrack;
	Groundwork _groundwork;
	Groundworkoutside _groundworkoutside;
	Startingline _startingline;

	bool buildonce = true;

    // Scene data:
    bool  _viewaxis;
	//Car Model 1//
    GsModel _gsm;
	GsModel _gsm2;
	GsModel _gsm3;
	GsModel _gsm4;
	GsModel _gsm5;
	///////////////

	//Car Model 1//
	GsModel _gsm1;
	GsModel _gsm1_2;
	GsModel _gsm1_3;
	GsModel _gsm1_4;
	GsModel _gsm1_5;
	///////////////

    GsLight _light;
    
    // App data:
    enum MenuEv { evOption0, evOption1 };
    float _rotx, _roty, _fovy;
    int _w, _h;

   public :
    AppWindow ( const char* label, int x, int y, int w, int h );
    void initPrograms ();
    void loadModel ( int model );
    GsVec2 windowToScene ( const GsVec2& v );

   private : // functions derived from the base class
    virtual void glutMenu ( int m );
    virtual void glutKeyboard ( unsigned char key, int x, int y );
    virtual void glutSpecial ( int key, int x, int y );
    virtual void glutMouse ( int b, int s, int x, int y );
    virtual void glutMotion ( int x, int y );
    virtual void glutDisplay ();
    virtual void glutReshape ( int w, int h );
 };

#endif // APP_WINDOW_H
