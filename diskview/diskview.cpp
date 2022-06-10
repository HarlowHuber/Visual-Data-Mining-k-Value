#include "diskview.h"
#include <stdio.h>
#include <stdlib.h>

//***********************************************************************************************
//***********************************************************************************************

void diskview_t::fade_color(color_t& dest_src, const color_t& src, float src_alpha)
{
	dest_src.unpacked.r = (unsigned char)((1.0f - src_alpha) * (float)dest_src.unpacked.r + src_alpha * (float)src.unpacked.r);
	dest_src.unpacked.g = (unsigned char)((1.0f - src_alpha) * (float)dest_src.unpacked.g + src_alpha * (float)src.unpacked.g);
	dest_src.unpacked.b = (unsigned char)((1.0f - src_alpha) * (float)dest_src.unpacked.b + src_alpha * (float)src.unpacked.b);
}

//***********************************************************************************************
// Constructor
//***********************************************************************************************


diskview_t::diskview_t(void)
{

	display_done = NULL;

	gl_render_context = NULL;
	width = 10;
	height = 10;


	fovy = 45.0f;
	front = 0.1f;
	back = 100.0f;

	background[0].packed = 0x00000000;
	background[1].packed = 0xffffffff;

	showbbox = true;
	showvalbbox = true;
	showbush = false;
	showunivalbbox = false;

	showhchain = false;
	chainnb = -2;
	nbchain_selected = -2;
	hansel_aligned = true;

	mouse_dragging = false;
	mousex_drag_start = mousey_drag_start = 0;

	mousex = 0;
	mousey = 0;
}