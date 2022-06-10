#ifndef __DISKVIEW_H__
#define __DISKVIEW_H__


/*

  This DLL mainly define the main module of viewing of the Visual Data Mining
  As long as protability has been a concern, I use two classes, second herit
  from the first, first is an ABC

*/

#include <math.h>
#include <nvboolfunc.h>

#ifndef M_PI
#define M_PI 3.14159
#endif

#ifndef LINUX_COMPILE
#include <windows.h>
#endif

#include <gl/gl.h>
#include <gl/glu.h>


typedef enum
{
	DISKVIEW_MEMORY_ERROR,
	DISKVIEW_GL_ERROR,
	DISKVIEW_UNKNOWN_ERROR,
	DISKVIEW_INIT_ERROR,
	DISKVIEW_CONTEXT_ERROR
} diskview_enum_t;


// Strucure for vertexes, vectors etc ...

typedef struct __vertex_t
{
	float x;	// x coordinate
	float y;	// y coordinate
	float z;	// z coordinate
} vertex_t;

// This is the color manipulation union ... ABGR for windows ...
/*
typedef union __color_t
{
	struct __unpacked
	{
		unsigned char r; // Red component
		unsigned char g; // Green component
		unsigned char b; // Blue component
		unsigned char a; // Alpha component
	} unpacked;
	unsigned long int upacked;  // packed color
	long int packed;			  // packed color signed
	unsigned  char b8_array[4]; // array of component
} color_t;*/


class __declspec(dllexport) diskview_t
{
private:


protected:
	void (*display_done) (void);					// function to call whan
													// display is done ...

	virtual void error_handler(diskview_enum_t msg, char* file, int line,
		bool iscritical = false) = 0;

	HGLRC gl_render_context;  // render context
	long int width, height;  // pixel client state


	float fovy;				// used for perspective
	float front, back;		// used for perspective

	color_t background[2];  // background shading

	vertex_t back_plane[4]; // background plane coordinate 
							// 0 : rt, 1 : lt, 2 : lb, 3 : rb

	bool showbbox;			// show the bouding box or not
	virtual void compute_back_plane(void) = 0;
	bool showvalbbox;		// show the value disk colored bounding box
	bool showunivalbbox;    // show the unified color value bounding box

	bool showbush;			// display the selected bush or not

	UINT keyPressed;		//Key that has been pressed for rotating view.

	bool showhchain;		// display the selected hansel chain or not
	int chainnb;			// number of the selected hansel chain 
	int nbchain_selected;	// hansel chain currently moving

	int mousex, mousey;		// position of the mouse
	vertex_t screen_pos[2]; // screen parameters

	bool hansel_aligned;	// are the hansel chain to be vertically aligned ?

	bool mouse_dragging;	// is mouse currently draggin ?

	int mousex_drag_start, mousey_drag_start;  // begining position of the mouse dragging

public:

	// Canonical interface ...

	static void fade_color(color_t& dest_src, const color_t& src, float src_alpha);

	diskview_t(void); 									// default constructor
	diskview_t(const diskview_t& src) {}						// copy constructor
	virtual diskview_t& operator=(diskview_t& src) { return *this; }	// copy operator
	virtual ~diskview_t(void) {}							// destructor

	virtual void invalidate_datas(void) = 0;				// function to be linked to the 
															// notify change event ...

	virtual void paint(void) = 0;							// funtion used to draw itself
	//virtual void resize(long int x, long int y) = 0;		// resize function

	virtual void destroy(void) = 0;						// destroy contexts and GL objects



	// Managing methods

	virtual void set_display_callback(void (*disp_callback) (void)) = 0;
	virtual void set_background_color(color_t& c0, color_t& c1) = 0;
	virtual void set_frustrum(float _fovy, float _front, float _back) = 0;

	void show_bbox(bool show = true) { showbbox = show; }
	void show_valbbox(bool show = true) { showvalbbox = show; }

	bool get_showvalbox(void) { return showvalbbox; }
	bool get_bbox(void) { return showbbox; }

	void show_bush(bool show = true) { showbush = show; }
	bool get_showbush(void) { return showbush; }

	void show_univalbbox(bool show = true) { showunivalbbox = show; }
	bool get_univalbbox(void) { return showunivalbbox; }

	void show_hchain(bool show = true) { showhchain = show; }
	bool get_showhchain(void) { return showhchain; }

	void set_mousepos(int x, int y, unsigned int nflags) { mousex = x; mousey = y; }
	virtual void get_caption(char* buffer, int n) = 0;

	//For keyboard input.
	void set_key(UINT key) { keyPressed = key; }

	void get_disk_2dcoords(int x, int y, float& xpos, int& lvl);

	void set_hanselaligned(bool aligned) { hansel_aligned = aligned; }
	bool get_hanselaligned(void) { return hansel_aligned; }

	void reset_mousedragging(void) { mouse_dragging = false; }


};



#endif
