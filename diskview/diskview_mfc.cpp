/* UPDATE 3 / 28 / 2022 - Harlow Huber
* The files belonging to the Visual Data Mining project are quite old and were built in Visual C++ 6.0 in, I presume, C++98.
* This project is being reimagined in Visual Studio 2022 in C++20. I do not know the format of the CHANGE LOG, so I will
* put my changes below.All functionality will remain the same, or exceedingly similar.
* All previous code comments will remain, for now, as a reference.
*
* BUG FIXES 4 / 5 / 2022 - HARLOW HUBER
*	all BOOLFUNC, INODE, AND DATA_INODE have been commented out for build purposes
*		this library and nvboolfunc have a circular dependency. remember this for future bugs
*		to build nvboolfunc, one must build diskview. however, diskview needs nvboolfunc. therefore, 
*		comment out all "nvboolfunc code" in diskview to be able to built it. then build nvboolfunc
*	DLLMain commented out
*/

/*
	Definition of the constructor/destructor and managing functions
*/

#include "diskview_mfc.h"
#include <stdio.h>

//***********************************************************************************************
// DLL architecture ...
//***********************************************************************************************
// at this point just do nothing ... see further ...

/*int WINAPI DllMain(HINSTANCE hInstance, DWORD fdwReason, PVOID pvReserved)
{
	return TRUE;
}*/


//***********************************************************************************************
// Default constructor ... initialize to NULL mainly ... and some others ..
//***********************************************************************************************

diskview_mfc_t::diskview_mfc_t(void) :
	output_dc(NULL), boolfunc(NULL)
{
	display_done = NULL;

	background[0].packed = 0x00000000;			// black
	background[1].upacked = 0xffffffff; // white

	back_plane[0].x = back_plane[1].x = back_plane[2].x = back_plane[3].x = 0.0f;
	back_plane[0].y = back_plane[1].y = back_plane[2].y = back_plane[3].y = 0.0f;
	back_plane[0].z = back_plane[1].z = back_plane[2].z = back_plane[3].z = 0.0f;

	fovy = 45.0f;
	front = 0.1f;
	back = 100.0f;

	showbbox = true;
}

//***********************************************************************************************
// Copy constructor, do not recreate an other boolfunc
//***********************************************************************************************

diskview_mfc_t::diskview_mfc_t(const diskview_mfc_t& src)
{
	display_done = src.display_done;
	output_dc = src.output_dc;
	background[0] = src.background[0];
	background[1] = src.background[1];
	fovy = src.fovy; front = src.front; back = src.back;
	//boolfunc = src.boolfunc;
}

//***********************************************************************************************
// Copy operator ... do not recreate any other boolfunc
//***********************************************************************************************

diskview_mfc_t& diskview_mfc_t::operator=(const diskview_mfc_t& src)
{
	display_done = src.display_done;
	output_dc = src.output_dc;
	background[0] = src.background[0];
	background[1] = src.background[1];
	fovy = src.fovy; front = src.front; back = src.back;
	//boolfunc = src.boolfunc;
	return *this;
}

//***********************************************************************************************
// Destructor ...
//***********************************************************************************************

diskview_mfc_t::~diskview_mfc_t(void)
{

}


//***********************************************************************************************
// Set and managing functions
// disp_func : function to be called at the end
//***********************************************************************************************

void diskview_mfc_t::set_display_callback(void (*disp_func)(void))
{
	display_done = disp_func;
}


//***********************************************************************************************
// set_background_color
// Set the background shading colors
// c0 up color
// c1 down color
//***********************************************************************************************

void diskview_mfc_t::set_background_color(color_t& c0, color_t& c1)
{
	background[0] = c0;
	background[1] = c1;
}

//***********************************************************************************************
// set_frustrum
// Set the frustrum parameters, used to view the scene, do not call gluPerspective
//  _fovy : vertical angle
//  _front : front coordinate
//  _back : back coordinate
//***********************************************************************************************

void diskview_mfc_t::set_frustrum(float _fovy, float _front, float _back)
{
	fovy = _fovy; front = _front; back = _back;
}

//***********************************************************************************************
// error_handler
// Open an error message box for the user
// msg : the enum corresponding to the error
// file : set this to __FILE__
// line : set this to __LINE__
// iscritical : if true, then exit
//***********************************************************************************************

void diskview_mfc_t::error_handler(diskview_enum_t msg, char* file, int line, bool iscritical)
{
	char buffer[256];
	switch (msg)
	{
	case DISKVIEW_MEMORY_ERROR:
		sprintf_s(buffer, "%s:%d Memory allocation error, not enougth memory ?", file, line);
		break;

	case DISKVIEW_GL_ERROR:
		sprintf_s(buffer, "%s:%d OpenGL error ... try to reboot or to reinstall the driver ...", file, line);
		break;

	case DISKVIEW_INIT_ERROR:
		sprintf_s(buffer, "%s:%d Initialization error, your graphic card may not support this mode", file, line);
		break;

	case DISKVIEW_CONTEXT_ERROR:
		sprintf_s(buffer, "%s:%d Context creation error, try to reboot or to reinstall the GL driver ...", file, line);
		break;


	case DISKVIEW_UNKNOWN_ERROR:
		sprintf_s(buffer, "%s:%d Unknown error ... ?!", file, line);
		break;

	default:
		break;
	}

	LPCWSTR ws = L"Diskview error :";
	LPCWSTR buff_L[256];
	::MessageBox(NULL, buff_L[0], ws, MB_OK | MB_ICONERROR);
	if (iscritical) exit(msg);

}


//***********************************************************************************************
// set the caption of the tool tip, or help
//***********************************************************************************************
void diskview_mfc_t::get_caption(char* buffer, int n)
{
	/*
	//My Changes.
	//Took this out for now becuase it seemed useless and
	//crashed the program.  Maybe I'll fix it later.
	//Routinely.
	//LR

	float x;
	int lvl;
	char * bitv;
	bit_vector_t v;
	bool r;

	get_disk_2dcoords(mousex, mousey, x, lvl);
	if (boolfunc->get_vectdata(x, lvl, v, r))
	{
		bitv = v.get_string();
		sprintf(buffer, "level %d vector %s=%c", lvl, bitv, (r)? '1' : '0');
//		delete[](bitv);
	} else {
		sprintf(buffer, "no data level height is %d", lvl);
	}

  */
}

//***********************************************************************************************
// Do the bush sort at a given point
//***********************************************************************************************

void diskview_mfc_t::do_bush_sort(int mousex, int mousey, unsigned int nFlags)
{
	float x;
	int lvl;

	get_disk_2dcoords(mousex, mousey, x, lvl);

	boolfunc->bush_sort(lvl, x);

}

//***********************************************************************************************
// Convert the screen coordinates into disk coordinates usable by the boolfunc object
//***********************************************************************************************

void diskview_mfc_t::get_disk_2dcoords(int x, int y, float& xpos, int& lvl)
{
	/*
		x = ((float)mousex)*(screen_pos[1].x - screen_pos[0].x) / ((float)width) + screen_pos[0].x;
		y = (screen_pos[0].y - screen_pos[1].y)*((float)(height - mousey)) / ((float)height) + screen_pos[1].y;
		yr = y /boolfunc->get_height();
		yr = (float) ((fabs(yr - floor(yr)) < 0.5f) ? floor(yr) : ceil(yr));
		lvl = ((int)yr) + (int)(boolfunc->get_size()>>1);
	*/

	float yf, yr;

	xpos = ((float)x) * (screen_pos[1].x - screen_pos[0].x) / ((float)width) + screen_pos[0].x;
	yf = (screen_pos[0].y - screen_pos[1].y) * ((float)(height - y)) / ((float)height) + screen_pos[1].y;
	yr = yf / boolfunc->get_height();
	yr = (float)((fabs(yr - floor(yr)) < 0.5f) ? floor(yr) : ceil(yr));
	lvl = ((int)yr) + (int)(boolfunc->get_size() >> 1);
}

//***********************************************************************************************
// Select the hansel chain to view, does not change the showhchain var
//***********************************************************************************************

void diskview_mfc_t::do_show_hansel(int x, int y, unsigned int nFlags)
{
	float xpos;
	int lvl;
	data_inode2d_t* inode = NULL;

	get_disk_2dcoords(x, y, xpos, lvl);

	inode = boolfunc->get_inode(xpos, lvl);
	if (inode)
	{
		if (inode->chain_nb != -1) chainnb = inode->chain_nb;
	}
}

//***********************************************************************************************
// functions used to move the inode (only one by one)
// init function
//***********************************************************************************************

void diskview_mfc_t::do_move_one_dn(int x, int y, unsigned int nFlags)
{
	if (boolfunc)
	{
		mouse_dragging = true;
		mousex_drag_start = x;
		mousey_drag_start = y;
	}
}

//***********************************************************************************************
// functions used to move the inode (only one by one)
// moving (over) function
//***********************************************************************************************

bool diskview_mfc_t::do_move_one_over(int x, int y, unsigned int nFlags)
{
	if (mouse_dragging)
	{
		float x1, x2;
		int lvl, lvl_dummy;
		mousex = x;
		mousey = y;

		//		float i, dir;
		bool r = false;

		get_disk_2dcoords(mousex_drag_start, mousey_drag_start, x1, lvl);
		get_disk_2dcoords(x, y, x2, lvl_dummy);


		if (fabs(x1 - x2) > 0.0)
		{
			mousex_drag_start = x;
			//return boolfunc->simple_swap(x1, x2, lvl);
			/*
						dir = (x1 < x2) ? 1.0f : 1.0f;
						for (i = x1; dir * i + dir <= dir * x2; i += dir)
						{
							r |= boolfunc->simple_swap(i , i + dir, lvl);

						}
			*/
			return r;
		}
	}
	return false;
}

//***********************************************************************************************
// function used to move the inode (only one by one)
// finishing function
//***********************************************************************************************

void diskview_mfc_t::do_move_one_up(int x, int y, unsigned int nFlags)
{
	nbchain_selected = -2;
	mouse_dragging = false;
}

//***********************************************************************************************
// select the chain to move
//***********************************************************************************************

void diskview_mfc_t::do_mode_hchain_dn(int x, int y, unsigned int nFlags)
{
	if (boolfunc)
	{

		float xpos;
		int lvl;
		data_inode2d_t* inode = NULL;

		get_disk_2dcoords(x, y, xpos, lvl);

		inode = boolfunc->get_inode(xpos, lvl);
		if (inode)
		{
			if (inode->chain_nb != -1) nbchain_selected = inode->chain_nb;
		}

		mouse_dragging = true;
		mousex_drag_start = x;
		mousey_drag_start = y;
	}
}


//***********************************************************************************************
// move function of the chain.
//***********************************************************************************************

bool diskview_mfc_t::do_move_hchain_over(int x, int y, unsigned int nFlags)
{
	if (mouse_dragging)
	{
		float x1, x2;
		int lvl, lvl_dummy;
		mousex = x;
		mousey = y;

		get_disk_2dcoords(mousex_drag_start, mousey_drag_start, x1, lvl);
		get_disk_2dcoords(x, y, x2, lvl_dummy);

		if (fabs(x1 - x2) > 0.0)
		{
			mousex_drag_start = x;
			return boolfunc->hchain_move(x1, x2, lvl);
		}
	}
	return false;
}

//Called when the user clicks a single element and monotMode is true.
//This means the user wants to monotonoly expand the data from the node 
//selected.

//Clicking on a white element expands all those below it, by turning them white.
//It follows the hansel chain.

//Black goes up from the current element and changes those to black.

//Is used in 2d mode.

void diskview_mfc_t::selectElement(int x, int y, unsigned int nFlags)
{
	if (boolfunc)
	{

		int mx = 0;
		int my = 0;
		float xpos;
		int lvl;

		mx = x;
		my = y;


		get_disk_2dcoords(mx, my, xpos, lvl);

		//Expand the chosen element.
		if (boolfunc->isMonot())
			expand(xpos, lvl);
		else if (boolfunc->isConvert())
			convert(xpos, lvl);

	}
}


//This function does the 2d expanding.

void diskview_mfc_t::expand(int pos, int lvl)
{

	//Get the indoe at this postion and level.
	float np;
	if (pos > 0)
		np = (float)pos + 0.5;
	else
		np = (float)pos - 0.5;

	data_inode2d_t* d2d = (data_inode2d_t*)boolfunc->get_inode(np, lvl);

	if (!d2d)
		return;

	if (d2d->value == true && d2d->is_fake != true)
	{
		//If it is black go up.

			//Go up chain and change all to black.
		d2d = d2d->chain_up;
		while (d2d != NULL)
		{
			d2d->value = true;
			d2d->is_fake = false;
			d2d = d2d->chain_up;

		}


	}
	else if (d2d->value == false && d2d->is_fake != true)
	{
		//If it is white go down.

			//Go down chain and turn all to white.
		d2d = d2d->chain_dn;
		while (d2d != NULL)
		{
			d2d->value = false;
			d2d->is_fake = false;
			d2d = d2d->chain_dn;
		}
	}
	//Else do nothing.
	else
		return;


	paint();
}


//This converts the element clicked on.
//Dark gray goes to black and light gray goes to white.
void diskview_mfc_t::convert(int pos, int lvl)
{

	//Get the indoe at this postion and level.
	float np;
	if (pos > 0)
		np = (float)pos + 0.5;
	else
		np = (float)pos - 0.5;

	data_inode2d_t* d2d = (data_inode2d_t*)boolfunc->get_inode(np, lvl);

	if (!d2d)
		return;

	//Convert to not fake.
	d2d->is_fake = false;


	paint();
}