#ifndef __DISKVIEW_MFC_H__
#define __DISKVIEW_MFC_H__

/*

  This is the definition of the view module MFC module, it could be (and maybe
  should be) replaced in the future by an other module using another system such
  wxWindows for example to assure portability ...

  since it is the only object of the library I export it all.
*/
#include <windows.h>
#include <glaux.h>	// PATH: $(SolutionDir)include/glaux.h
					// this file must be included, or else this project implementation will have to be re-written using functions in freegut or some other library
					// glaux.h is legacy code. the freeglut library is the modern alternative for OpenGL
					// here is a link to the only source code I could find: http://www.songho.ca/opengl/files/glaux.h

#include "diskview.h"   // conform to the diskview architeture and extends it
#include <nvboolfunc.h>  

class __declspec (dllexport) diskview_mfc_t : public diskview_t
{
private:

	void error_handler(diskview_enum_t msg, char* file, int line, bool iscritical = false);

	HDC output_dc;	// The output DC to use if own DC (not available using MFC)
	void compute_back_plane(void);

protected:

	nvboolfunc_t* boolfunc;	// the boolean function linked to

public:

	void diskview_t::invalidate_datas(void);

	void resetView(void);	//Reset the 3d view.

	//Draw a section of the disk.


			//For drawing the 3d view.
	void draw3dView(int size, nvboolfunc_t* boolfunc);
	//Draws a disk.
	void drawDisk(int num, float x, float y, float z, float rad, float rA, float h, int layer, nvboolfunc_t* boolfunc);

	//Draws a disk and draws data on the top and bottom of that disk.
	void drawDisk3dPlot(int num, float x, float y, float z, float rad, float rA, float h, int layer, nvboolfunc_t* boolfunc, int mid);

	//Draws a coompressed layer.
	void drawDiskCompressed(int num, float x, float y, float z, float rad, float rA, float h, int layer, nvboolfunc_t* boolfunc, int mid);

	//Draw the 'top' structure.
	void drawTop(int lyrs, float diff, int sides);
	
	void drawTop(int size, float diff, nvboolfunc_t* boolfunc);
	
	//Draw a top for 3d plotting.
	void drawTop3dPlot(int size, float diff, nvboolfunc_t* boolfunc);

	//Draw the top using compressed data.
	void drawTopCompressed(int size, float diff, nvboolfunc_t* boolfunc);

	//Given three points, calculate a normal vector and return it in unit status.
	void calcNormal(GLfloat[], GLfloat[], GLfloat[]);

	//Given a string color representation "lightgray".
	void setColors(char* c);

	//Given rgb values set the opengl material properties to this color.
	void setColors(float r, float g, float b);

	//Set colors based on the data at this node.
	void /*diskview_mfc_t::*/setColors(_generic_inode_t cur, color_t cNorm);


	// Canonical interface ...

	diskview_mfc_t(void);								// default constructor
	diskview_mfc_t(const diskview_mfc_t& src);	// copy constructor
	diskview_mfc_t& operator=(const diskview_mfc_t& src);	// copy operator
	~diskview_mfc_t(void);								// destructor

	//void invalidate_datas(void);						// function to be linked to the 
														// notify change event ...

	void paint(void);									// funtion used to draw itself
	void resize(long int x, long int y);				// reisze ...
	void destroy(void);

	// Managing methods

	void set_display_callback(void (*disp_callback) (void));
	void set_background_color(color_t& c0, color_t& c1);
	void set_frustrum(float _fovy, float _front, float _back);
	void get_disk_2dcoords(int x, int y, float& xpos, int& lvl);

	// MFC / WinAPI interface functions ...

private:

	bool setpxlformat(HDC hdc);							// set the pxl format for the window


	// MFC Dependant part :
public:

	bool init_view(HDC out_dc);
	void init_gl(void);
	void on_draw(HDC out_dc);
	void resize(HDC out_dc, long int x, long int y);

	// bool func management

	void set_boolfunc(nvboolfunc_t* func) { boolfunc = func; }
	void configure_boolfunc(bool _3d = false);
	void show_bbox(bool show = true) { showbbox = show; }
	bool get_bbox(void) { return showbbox; }

	void get_caption(char* buffer, int n);

	void do_bush_sort(int x, int y, unsigned int nFlags);
	void do_show_hansel(int x, int y, unsigned int nFlags);

	void do_move_one_dn(int x, int y, unsigned int nFlags);
	void do_move_one_up(int x, int y, unsigned int nFlags);
	bool do_move_one_over(int x, int y, unsigned int nFlags);
	void do_mode_hchain_dn(int x, int y, unsigned int nFlags);
	bool do_move_hchain_over(int x, int y, unsigned int nFlags);
	void do_mode_hchain_up(int x, int y, unsigned int nFlags);

	//Select an element with the mouse.
	void selectElement(int x, int y, unsigned int nFlags);
	//Monotonoly expand the data.
	void expand(int pos, int lvl);

	//Convert fake to real data.
	void convert(int pos, int lvl);

	//Check if a node is a violation of monotonicity.
	bool checkMonotViol(data_inode2d_t* d);
};



#endif
