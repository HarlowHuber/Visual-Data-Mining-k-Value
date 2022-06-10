/* UPDATE 3 / 28 / 2022 - Harlow Huber
* The files belonging to the Visual Data Mining project are quite old and were built in Visual C++ 6.0 in, I presume, C++98.
* This project is being reimagined in Visual Studio 2022 in C++20. I do not know the format of the CHANGE LOG, so I will
* put my changes below.All functionality will remain the same, or exceedingly similar.
* All previous code comments will remain, for now, as a reference.
*
* BUG FIXES 4 / 8 / 2022 - HARLOW HUBER
*	all BOOLFUNC, INODE, AND DATA_INODE have been commented out for build purposes
*		this library and nvboolfunc have a circular dependency. remember this for future bugs
*		to build nvboolfunc, one must build diskview. however, diskview needs nvboolfunc. therefore,
*		comment out all "nvboolfunc code" in diskview to be able to built it. then build nvboolfunc
*	DLLMain commented out
*	in drawDiskCompressed, changed setColors(const char*) to setColors(char*) with const_cast<char*>
*	changed all "__FILE__" to "const_cast<char*>(__FILE__)"
*/

#include "diskview_mfc.h"
#include "stdio.h"
#include "glut.h"
#include <list>

//====GLOBALS====//

//Rotation angles and offsets for moving the camera.
GLdouble angleX, angleY = 0.0;
GLdouble distX, distY = 0.0;
GLdouble distZ = 5.0;

//Lighting parameters.
//Setup a light.
//Ambient ligthing shines everywhere equally.
//Diffuse comes from a direction but scatters in every direction.
//Specular comes and scatters in narrower directions.

GLfloat glfLightAmbient[] = { 0.0f,0.0f,0.0f,0.0f };
//R,G,B,Alpha
GLfloat glfLightDiffuse[] = { 1.0f, 1.0f, 1.0f, 0.0f };
GLfloat glfLightSpecular[] = { 0.0f, 0.0f, 0.0f, 0.0f };

// Define a directional light source.
GLfloat glfLightPosition[] = { 2.0f, 0.0f, 20.0f, 1.0f };

#define PI 3.14159265

//Amount to rotate picture with the keys.
#define ROT_ANGLE 10.0

//*****************************************************************************************//
// reload the datas and invalidate the view
//*****************************************************************************************//
void diskview_mfc_t::invalidate_datas(void)
{

}


//*****************************************************************************************//
// prepare the system for display....
//*****************************************************************************************//

void diskview_mfc_t::on_draw(HDC out_dc)
{
	output_dc = out_dc;

	paint();
}


//*****************************************************************************************//
// render the scene (diskview_t architecture ...
//*****************************************************************************************//


void diskview_mfc_t::paint(void)
{
	static double x = 0.0;



	if (!wglMakeCurrent(output_dc, gl_render_context))
	{
		error_handler(DISKVIEW_CONTEXT_ERROR, const_cast<char*>(__FILE__), __LINE__);
		return;
	}


	// lets put some render here ...


	//SEtup opengl.
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glShadeModel(GL_FLAT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// first draw the background (additional feedback may be needed ... )
/*	glDisable(GL_DEPTH_TEST | GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glBegin(GL_QUADS);
		glColor4ubv( (unsigned char *) &background[0]);
		glVertex3fv((float *) &back_plane[0]); glVertex3fv((float *) &back_plane[1]);
		glColor4ubv( (unsigned char *) &background[1]);
		glVertex3fv((float *) &back_plane[2]); glVertex3fv((float *) &back_plane[3]);
	glEnd();
*/




	if (boolfunc)
	{
		if (!boolfunc->is_3d() && !boolfunc->isMy3d())
		{
			//2d drawing.
			glDisable(GL_DEPTH_TEST);

			glDisable(GL_LIGHTING);
			glDisable(GL_LIGHT0);

			size_t s = boolfunc->get_size(), i;
			float yb, yt, x0, zd, sf, h, ydemi;
			color_t c;
			int xsize;
			float xinc = 0.0f;

			h = boolfunc->get_height();


			sf = (float)s;
			zd = -(front + back) / 2.0f;
			yb = -h * sf / 2.0f;


			// draw the disks

			glBegin(GL_QUADS);
			for (i = 0; i < s; i++)
			{
				yt = yb + h;
				x0 = -((float)(xsize = boolfunc->get_xsize(i))) / 2.0f;


				x0 += (!hansel_aligned || xsize & 1) ? xinc = 0.0f : xinc = 0.5f;

				c = boolfunc->get_disk_color(i);
				glColor4ubv(c.b8_array);
				glVertex3f(-x0 + xinc + xinc, yt, zd); glVertex3f(x0, yt, zd);
				glVertex3f(x0, yb, zd); glVertex3f(-x0 + xinc + xinc, yb, zd);
				yb += h;
			}
			glEnd();



			yb = -h * sf / 2.0f;
			ydemi = yb + h / 2.0f;
			for (i = 0; i < s; i++)
			{
				color_t c0, c1, cf, cd;
				generic_inode_t cur;


				xinc = (!hansel_aligned || boolfunc->get_xsize(i) & 1) ? 0.0f : 0.5f;

				yt = yb + h;
				cd = boolfunc->get_disk_color(i);
				//cd.upacked ^= 0xffffffff;
				c0 = boolfunc->get_val_color(i, false);
				c1 = boolfunc->get_val_color(i, true);
				cf.upacked = 0xff7f7f7f; // gray
				boolfunc->rewind(i);

				float hx0 = 0.0f, hyt = 0.0f, hyb = 0.0f, hzd = 0.0f;
				float hsx0 = 0.0f, hsyt = 0.0f, hsyb = 0.0f, hszd = 0.0f;


				while (cur.generic_pointer = boolfunc->get_next_inode(i))
				{
					color_t bit_color;


					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


					if (cur.inode2d->value) bit_color = c1;
					else bit_color = c0;


					if (cur.inode2d->is_fake) fade_color(bit_color, cf, 0.5f);

					glColor4ubv(bit_color.b8_array);

					x0 = (float)cur.inode2d->xpos + xinc;

					//Draws an element, black or white on the disks.
					glBegin(GL_QUADS);
					glVertex3f(x0 + 0.5f, yt, zd); glVertex3f(x0 - 0.5f, yt, zd);
					glVertex3f(x0 - 0.5f, yb, zd); glVertex3f(x0 + 0.5f, yb, zd);
					glEnd();

					if (showbush && cur.inode2d->nb_bush == 1)
					{
						glColor3f(1.0f, 0.0f, 0.0f);
						glBegin(GL_QUADS);
						glVertex3f(x0 + 0.5f, ydemi, zd); glVertex3f(x0 - 0.5f, ydemi, zd);
						glVertex3f(x0 - 0.5f, yb, zd); glVertex3f(x0 + 0.5f, yb, zd);
						glEnd();
					}

					if (showvalbbox)
					{
						//Box outlines.
						glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
						glBegin(GL_QUADS);
						glColor4ubv(cd.b8_array);
						glVertex3f(x0 + 0.5f, yt, zd); glVertex3f(x0 - 0.5f, yt, zd);
						glVertex3f(x0 - 0.5f, yb, zd); glVertex3f(x0 + 0.5f, yb, zd);
						glEnd();
						glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
					}

					if (showunivalbbox)
					{
						glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
						glBegin(GL_QUADS);
						glColor3f(0.0f, 1.0f, 1.0f);
						glVertex3f(x0 + 0.5f, yt, zd); glVertex3f(x0 - 0.5f, yt, zd);
						glVertex3f(x0 - 0.5f, yb, zd); glVertex3f(x0 + 0.5f, yb, zd);
						glEnd();
						glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
					}

					//To show data that is a violation of monotony.
					if (boolfunc->isMonotViol())
					{
						//These are the conditions for violating monotony.
						//LightGray above Dark Gray. lg>dg.
						//lg>dg  lg>b  w>dg   w>b.

						//Look at the element in the hansel chain above, and below.
						data_inode2d_t* dup = NULL;


						dup = cur.inode2d->chain_up;


						bool viol = false;

						//lg>dg
						if (dup != NULL && (dup->value == false && dup->is_fake == true && cur.inode2d->value == true && cur.inode2d->is_fake == true))
							viol = true;

						//lg>b
						if (dup != NULL && (dup->value == false && dup->is_fake == true && cur.inode2d->value == true && cur.inode2d->is_fake == false))
							viol = true;

						//w>dg
						if (dup != NULL && (dup->value == false && dup->is_fake == false && cur.inode2d->value == true && cur.inode2d->is_fake == true))
							viol = true;

						//w>b
						if (dup != NULL && (dup->value == false && dup->is_fake == false && cur.inode2d->value == true && cur.inode2d->is_fake == false))
							viol = true;

						if (viol == true)
						{
							glColor3f(1.0f, 0.0f, 0.0f);
							glBegin(GL_QUADS);
							glVertex3f(x0 + 0.5f, yt, zd); glVertex3f(x0 - 0.5f, yt, zd);
							glVertex3f(x0 - 0.5f, yb, zd); glVertex3f(x0 + 0.5f, yb, zd);
							glEnd();


							/*glColor3f(1.0f, 0.0f, 0.0f);
							glLineWidth(1.0);
							glBegin(GL_LINE_STRIP);
								glVertex3f(x0 + 0.5f, yt, zd);
								glVertex3f(x0 - 0.5f, yb, zd);
							glEnd();
							glBegin(GL_LINE_STRIP);
								glVertex3f(x0 - 0.5f, yt, zd);
								glVertex3f(x0 + 0.5f, yb, zd);
							glEnd();
							*/
						}

					}


					if (showhchain && cur.inode2d->chain_nb == chainnb)
					{
						hx0 = x0; hyt = yt; hyb = yb; hzd = zd;
					}

					if (nbchain_selected == cur.inode2d->chain_nb)
					{
						hsx0 = x0; hsyt = yt; hsyb = yb; hszd = zd;
					}


				}

				if (showhchain)
				{
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
					glBegin(GL_QUADS);
					glColor3f(1.0f, 0.0f, 0.0f);
					glVertex3f(hx0 + 0.5f, hyt, hzd); glVertex3f(hx0 - 0.5f, hyt, hzd);
					glVertex3f(hx0 - 0.5f, hyb, hzd); glVertex3f(hx0 + 0.5f, hyb, hzd);
					glEnd();
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				}

				// view the potential selected chain
				if (nbchain_selected > -1)
				{
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
					glBegin(GL_QUADS);
					glColor3f(1.0f, 1.0f, 0.0f);
					glVertex3f(hsx0 + 0.5f, hsyt, hszd); glVertex3f(hsx0 - 0.5f, hsyt, hszd);
					glVertex3f(hsx0 - 0.5f, hsyb, hszd); glVertex3f(hsx0 + 0.5f, hsyb, hszd);
					glEnd();
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				}

				ydemi += h;

				yb += h;
			}


			// draw the 2d bounding box

			if (showbbox)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				glBegin(GL_QUADS);
				yb = -h * sf / 2.0f;
				for (i = 0; i < s; i++)
				{
					yt = yb + h;
					x0 = -((float)(xsize = boolfunc->get_xsize(i))) / 2.0f;


					x0 += (!hansel_aligned || xsize & 1) ? xinc = 0.0f : xinc = 0.5f;

					c = boolfunc->get_disk_color(i);
					if (i != 0 && i != s - 1) c.upacked ^= 0xffffffff;
					else if (showhchain && chainnb == 0)
					{
						c.upacked = 0; c.unpacked.r = 255;
					}
					glColor4ubv(c.b8_array);
					glVertex3f(-x0 + xinc + xinc, yt, zd); glVertex3f(x0, yt, zd);
					glVertex3f(x0, yb, zd); glVertex3f(-x0 + xinc + xinc, yb, zd);
					yb += h;
				}
				glEnd();
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			}

		}
		else
		{
			//DRAW IN 3D!!!!

			//Get the disk parameters for size, sides.

			//Number of layers.
			size_t s = boolfunc->get_size();

			//Handle any key presses for rotation etc..
			switch (keyPressed)
			{
				//'a' and 'd' keys rotate, left and right (around the y axis).
				//TODO get VK_A to work instead of 65
				//D
			case 68:
				angleY += 1.0;
				if (angleY > 360.0)
					angleY = 0.0;
				break;
				//A
			case 65:
				angleY -= 1.0;
				if (angleY < 0.0)
					angleY = 360.0;
				break;
				//'w' and 's' rotate up and down (around x axis).
					//W
			case 87:
				angleX += 1.0;
				if (angleX > 360.0)
					angleX = 0.0;
				break;
				//S
			case 83:
				angleX -= 1.0;
				if (angleX < 0.0)
					angleX = 360.0;
				break;

				//Q moves x to left, E moves x to right.
				//Q
			case 81:
				distX += 0.2;
				break;
				//E
			case 69:
				distX -= 0.2;
				break;


				//R and F move y up and down.
				//R
			case 82:
				distY += 0.2;
				break;

				//F
			case 70:
				distY -= 0.2;
				break;

				//Z zooms in and X zooms out on z axis.
				//Z
			case 90:
				distZ -= 0.2;
				break;
				//X
			case 88:
				distZ += 0.2;
				break;

			default:
				break;
			}

			keyPressed = 0;




			//Setup Opengl for 3d drawing.	
			//For 3d depth drawing.
			glEnable(GL_DEPTH_TEST);
			glClearColor(0.2f, 0.2f, 0.2f, 1.0f);  	// clear background.
			glClearDepth(100.0);            // set depth buffer to the most distant value
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


			resetView();
			//Actual drawing.
			draw3dView(s, boolfunc);


		}
	}

	::SwapBuffers(output_dc);

	if (!wglMakeCurrent(NULL, NULL))
	{
		error_handler(DISKVIEW_CONTEXT_ERROR, const_cast<char*>(__FILE__), __LINE__);
		return;
	}


	// call the finishing callback if there is one, do nothing if not ...
	if (display_done != NULL) display_done();
}

/**********************************************************************8

	RESETVIEW

	Reset the 3d view.

************************************************************************/
void diskview_mfc_t::resetView()
{

	//Reset the matrix.
	glLoadIdentity();


	//Set up camera.
	gluLookAt(0.0, 1.0, 8.5, //eye viewpoint.  Location of the camera.     
		0.0, 0.0, 0.0,      //look at the center.
		0.0, 1.0, 0.0);      //orient Y as up.

	//Set up the lighting.

/*		glLightfv(GL_LIGHT0,GL_AMBIENT,glfLightAmbient);
		glLightfv(GL_LIGHT0,GL_DIFFUSE,glfLightDiffuse);
		glLightfv(GL_LIGHT0,GL_SPECULAR,glfLightSpecular);
		glLightfv(GL_LIGHT0,GL_POSITION,glfLightPosition);

		// Enable lighting in general.
		glEnable(GL_LIGHTING);
		// Enable the defined light source.
		glEnable(GL_LIGHT0);
*/
//Enable camera and light THEN roatate/transform so the light
//stays in one place.  behind the camera.  So it is always
//shinning on what you are looking at.

//Take into affect rotations and movements from the keys.
	glTranslated(distX, distY, distZ);
	glRotated(angleX, 1.0, 0.0, 0.0);
	glRotated(angleY, 0.0, 1.0, 0.0);

}


/**********************************************************************************************
***********************************************************************************************
***********************************************************************************************
*
*				DRAW3DVIEW
*
*	Draws a 3d view of the data.
*	there are three types of views. Normal, compressed, and 3dplot.
*
***********************************************************************************************
***********************************************************************************************
**********************************************************************************************/

void diskview_mfc_t::draw3dView(int size, nvboolfunc_t* boolfunc)
{
	//Boolfunc is the data we are drawing.  All layers and vectors.
	//Amount to shrink disks with each step.
	float diff = 0.25;

	//Decide which type of 3d view to draw.
	if (boolfunc->is3dPlot())
		drawTop3dPlot(size, diff, boolfunc);
	else if (boolfunc->isCompressed())
		drawTopCompressed(size, diff, boolfunc);
	else
		drawTop(size, diff, boolfunc);

}

/**********************************************************************************************
***********************************************************************************************
***********************************************************************************************
*
*				DRAWTOPCOMPRESSED
*
*	Draws a top for 3d plotting.
*	This will have fewer layers than a normal top since you draw on
*	the ends as well as the top and bottom of each disk.
*	Also, the data is compressed into groups for drawing.
*
***********************************************************************************************
***********************************************************************************************
**********************************************************************************************/

void diskview_mfc_t::drawTopCompressed(int size, float diff, nvboolfunc_t* boolfunc)
{

	//Height of a disk.
	float height = 0.2;

	//Number of layers to draw.
	int layers = size;

	//Counting.
	int i = 0;

	//Difference in size of each layer.
	float difference = diff;

	//The middle layer.
	int mid = (layers / 2);

	//Radius of the disk.
	float radius;

	//Offset to determine where disk is drawn, angle wise.
	float ang = 0.0;

	//Draw all the bottom layers.
	//These have two layers.
	//i on the bottom, and i++ on the side.

	//Which disk is being drawn.  First, second..
	int diskNum = 0;
	//Which disk the middle one is.
	int midDiskNum = 0;
	int disksNeeded = 0;
	int sides = 0;

	//Calculate the number of disks needed to draw.
	if (layers > 3)
	{
		disksNeeded = 1 + ((layers - 3) / 2);
		if (((layers - 3) % 2) != 0)
			disksNeeded++;
	}
	else
		disksNeeded = 1;




	//Draw the middle layer.

	ang = 0;

	//Draw the middle layer.
	//This disk has 3 drawing sides.
	i = mid;
	diskNum = (mid / 2) + 1;
	midDiskNum = diskNum;
	radius = (2.0 - ((1.0 * difference) * (float)(mid - i)));

	//This aligns the middle of the data position of the disks.
	//Rotate some more based on amount of data to draw.
	ang -= (360.0 / double(boolfunc->get_xsize(mid))) * (boolfunc->getDiskData(mid).dataList3d.size()) / 2.0;

	glPushMatrix();
	glRotatef(ang, 0.0, 1.0, 0.0);
	drawDiskCompressed(boolfunc->get_xsize(i), 0.0, ((float)diskNum * height), 0.0,
		radius, 0, height, i, boolfunc, mid);
	glPopMatrix();

	//Draw two layers at a time.
	for (i = mid - 2; i > -1; i -= 2)
	{
		//Draw bottom layers.

		diskNum--;
		//Rotate the drawing so that the first positions of disks line up.
		sides = boolfunc->get_xsize(i);

		ang = 0;

		//This aligns the 0 position of the disks.
		for (int l = 0; l < i - 1; l += 2)
			ang -= (360.0 / double(boolfunc->get_xsize(l)));

		//This aligns the middle of the data position of the disks.
		//Rotate some more based on amount of data to draw.
		ang -= (360.0 / double(boolfunc->get_xsize(i))) * (boolfunc->getDiskData(i).dataList3d.size()) / 2.0;



		//Radius of the disk.
		radius = (2.0 - ((1.0 * difference) * (float)(mid - i)));

		glPushMatrix();
		glRotatef(ang, 0.0, 1.0, 0.0);
		drawDiskCompressed(boolfunc->get_xsize(i), 0.0, float(diskNum) * height, 0.0,
			radius, 0, height, i, boolfunc, mid);
		glPopMatrix();


	}


	diskNum = midDiskNum;


	for (int l = mid + 2; l < layers; l += 2)
	{

		diskNum++;

		sides = boolfunc->get_xsize(l);

		ang = 0;
		//Top layers.
		for (int k = l - 2; k >= mid; k -= 2)
			ang -= (360.0 / double(boolfunc->get_xsize(k)));

		//This aligns the middle of the data position of the disks.
		//Rotate some more based on amount of data to draw.
		ang -= (360.0 / double(sides)) * (boolfunc->getDiskData(l).dataList3d.size()) / 2.0;



		radius = (2.0 + ((1.0 * difference) * (float)(mid - l)));
		glPushMatrix();
		glRotatef(ang, 0.0, 1.0, 0.0);
		drawDiskCompressed(boolfunc->get_xsize(l), 0.0, ((float)(diskNum)*height), 0.0,
			radius, 0, height, l, boolfunc, mid);
		glPopMatrix();


	}


}



/**********************************************************************************************
***********************************************************************************************
***********************************************************************************************
*
*				DRAWTOP3DPLOT
*
*	Draws a top for 3d plotting.
*	This will have fewer layers than a normal top since you draw on
*	the ends as well as the top and bottom of each disk.
*
*
***********************************************************************************************
***********************************************************************************************
**********************************************************************************************/

void diskview_mfc_t::drawTop3dPlot(int size, float diff, nvboolfunc_t* boolfunc)
{
	//Height of a disk.
	float height = 0.2;

	//Number of layers to draw.
	int layers = size;

	//Counting.
	int i = 0;

	//Difference in size of each layer.
	float difference = diff;

	//The middle layer.
	int mid = (layers / 2);

	//Radius of the disk.
	float radius;

	//Offset to determine where disk is drawn, angle wise.
	float ang = 0.0;

	//Draw all the bottom layers.
	//These have two layers.
	//i on the bottom, and i++ on the side.

	//Which disk is being drawn.  First, second..
	int diskNum = 0;
	//Which disk the middle one is.
	int midDiskNum = 0;
	int disksNeeded = 0;
	int sides = 0;

	//Calculate the number of disks needed to draw.
	if (layers > 3)
	{
		disksNeeded = 1 + ((layers - 3) / 2);
		if (((layers - 3) % 2) != 0)
			disksNeeded++;
	}
	else
		disksNeeded = 1;




	//Draw the middle layer.

	ang = 0;


	//Temp.
	difference = 0.05;


	//Draw the middle layer.
	//This disk has 3 drawing sides.
	i = mid;
	diskNum = (mid / 2) + 1;
	midDiskNum = diskNum;
	radius = (2.0 - ((1.0 * difference) * (float)(mid - i)));

	glPushMatrix();
	glRotatef(ang, 0.0, 1.0, 0.0);
	drawDisk3dPlot(boolfunc->get_xsize(i), 0.0, ((float)diskNum * height), 0.0,
		radius, 0, height, i, boolfunc, mid);
	glPopMatrix();






	//Draw two layers at a time.
	for (i = mid - 2; i > -1; i -= 2)
	{
		//Draw bottom layers.

		diskNum--;
		//Rotate the drawing so that the first positions of disks line up.
		sides = boolfunc->get_xsize(i);

		ang = 0;
		for (int l = 0; l < i - 2; l++)
			ang -= (360.0 / double(boolfunc->get_xsize(l)));


		//Radius of the disk.
		radius = (2.0 - ((1.0 * difference) * (float)(mid - i)));

		glPushMatrix();
		glRotatef(ang, 0.0, 1.0, 0.0);
		drawDisk3dPlot(boolfunc->get_xsize(mid), 0.0, float(diskNum) * height, 0.0,
			radius, 0, height, i, boolfunc, mid);
		glPopMatrix();


	}


	diskNum = midDiskNum;


	for (int l = mid + 2; l < layers + 1; l += 2)
	{
		ang -= (360.0 / double(boolfunc->get_xsize(l)));


		diskNum++;

		sides = boolfunc->get_xsize(l);
		ang = 0;
		//Top layers.
		for (int k = l + 1; k < layers + 1; k++)
			ang -= (360.0 / double(boolfunc->get_xsize(k)));

		//Top layers.
		ang = 0;
		radius = (2.0 + ((1.0 * difference) * (float)(mid - l)));
		glPushMatrix();
		glRotatef(ang, 0.0, 1.0, 0.0);
		drawDisk3dPlot(boolfunc->get_xsize(mid), 0.0, ((float)(diskNum)*height), 0.0,
			radius, 0, height, l, boolfunc, mid);
		glPopMatrix();


	}







}





/**********************************************************************************************
***********************************************************************************************
***********************************************************************************************
*
*				DRAWTOP
*
*	Draws the top.  Used when one disk == one layer.
*
*
***********************************************************************************************
***********************************************************************************************
**********************************************************************************************/


//Draws layers starting at the bottom.
void diskview_mfc_t::drawTop(int size, float diff, nvboolfunc_t* boolfunc)
{
	//Height of a disk.
	float height = 0.2;

	//Number of layers to draw.
	int layers = size;

	//Difference in size of each layer.
	float difference = diff;

	//The middle layer.
	int mid = (layers / 2);

	//Radius of the disk.
	float radius;

	//Offset to determine where disk is drawn, angle wise.
	float ang = 0.0;
	float midRadius = 2.0;

	int sides = 0;

	//Draw all the layers.
	for (int i = 0; i < size; i++)
	{



		//The amount of rotation, to make the 1s spots of the disks
		//line up is negative.  It is greatest at the center and
		//equal for tow equally distant layers.



		//Radius of the disk.
		//Top layers
		if (i > mid)
		{
			radius = fabs((2.0 + ((1.0 * difference) * (float)(mid - i))));
		}
		//Mid and bottom layers.

		else
		{
			radius = fabs((2.0 - ((1.0 * difference) * (float)(mid - i))));

		}

		/*
				This doesnt work but it makes an interesting shape so I saved it.
				:).

				if (i > mid)
				{
					radius = (1.5 + ((2.0 * difference)*(float)(mid - i)));
					ang = -((float)(size - i) * 20.0);
				}
				//Mid and bottom layers.
				else
				{
					radius = (1.5 - ((2.0 * difference)*(float)(mid - i)));
					ang = (float)(size - i) * 20.0;
				}

				//To rotate the drawing of the disks.
				glPushMatrix();
				glRotatef(ang,  1.0, 0.0, 0.0);
				//Get the lenght(number of sides disk should have).
				drawDisk(boolfunc->get_xsize(i), 0.0, ((float)i * height), 0.0,
					radius, ang, height, i, boolfunc);
				glPopMatrix();
		*/

		//Rotate the drawing so that the first positions of disks line up.
		sides = boolfunc->get_xsize(i);

		/*		ang = 0;
				if (i < mid)
				{
					for (int l = 0; l < i-1; l++)
						ang -= (360.0/double(boolfunc->get_xsize(l)));
				}
				else if (i == mid)
				{
					ang = 0;
				}
				else
				{

					for (int l = i+1; l < layers; l++)
						ang -= (360.0/double(boolfunc->get_xsize(l)));

				}

		*/
		ang = 0;
		glPushMatrix();
		glRotatef(ang, 0.0, 1.0, 0.0);
		//TODO change sides to size_t not int!
		drawDisk(sides, 0.0, ((float)i * height), 0.0,
			radius, 0, height, i, boolfunc);
		glPopMatrix();

	}


}


/**********************************************************************************************
***********************************************************************************************
***********************************************************************************************
*
*				CALCNORMAL
*
*	Calculate the normal vector from three input points,
*	In 3 arrays, each array is a point that has x,y,z.
*	Return an array of x,y,z comppnents, from 0.0 or 1.0 (unit vector);
*
*
***********************************************************************************************
***********************************************************************************************
**********************************************************************************************/

void diskview_mfc_t::calcNormal(GLfloat p1[3], GLfloat p2[3], GLfloat p3[3])
{


	//Output vector.
	GLfloat normVec[3] = { 0.0f };


	//Vector a is p2 - p1;
	GLfloat ax = p2[0] - p1[0];
	GLfloat ay = p2[1] - p1[1];
	GLfloat az = p2[2] - p1[2];

	//Vector b is p3 - p1;
	GLfloat bx = p3[0] - p1[0];
	GLfloat by = p3[1] - p1[1];
	GLfloat bz = p3[2] - p1[2];

	//Calc the normal, the cross product of a and b.
	normVec[0] = (ay * bz - az * by);
	normVec[1] = (az * bx - ax * bz);
	normVec[2] = (ax * by - ay * bx);

	//Turn it into a unit vector.
	for (int i = 0; i < 3; i++)
	{
		if (normVec[i] > 0.00000000000000000000001f)
			normVec[i] = 1.0f;
		else if (normVec[i] < -0.00000000000000000000001f)
			normVec[i] = -1.0f;
		else
			normVec[i] = 0.0f;
	}

	//Call glNormal to produce the normal vector.
	glNormal3d(normVec[0], normVec[1], normVec[2]);


}

/**********************************************************************************************
***********************************************************************************************
***********************************************************************************************
*
*					SETCOLORS
*
*	Set the open gl material properties to a color.
*
***********************************************************************************************
***********************************************************************************************
**********************************************************************************************/

void diskview_mfc_t::setColors(char* c)
{
	//Set colors based on word color.
	if (strcmp(c, "white") == 0)
		setColors(255.0, 255.0, 255.0);
	else if (strcmp(c, "lightgray") == 0)
		setColors(195.0, 195.0, 195.0);
	else if (strcmp(c, "darkgray") == 0)
		setColors(90.0, 90.0, 90.0);
	else if (strcmp(c, "black") == 0)
		setColors(0.0, 0.0, 0.0);
	else
		//Color not found.
		setColors(200.0, 150.0, 0.0);


}

void diskview_mfc_t::setColors(float red, float green, float blue)
{

	//Get a value >0.0 < 1.0 for each color since the colors are
	//storred as chars (0-255).

	GLfloat r = red / 255.0;
	GLfloat g = green / 255.0;
	GLfloat b = blue / 255.0;

	glColor3f(r, g, b);

	//Dont use ligthing for now.
	/*
	GLfloat materialDiffuse[]   = {r, g, b, 1.0f} ;
	GLfloat materialAmbient[]   = {r/4.0f, g/4.0f, b/4.0f, 1.0f} ;
	GLfloat materialSpecular[] = {r, g, b, 1.0f};
	GLfloat materialSe = 100;

	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular) ;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse) ;
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient) ;
	glMaterialf(GL_FRONT, GL_SHININESS, materialSe);
	*/

}

void diskview_mfc_t::setColors(_generic_inode_t cur, color_t cNorm)
{
	//Same as the other setColors but uses a reference to the current inode to
	//determine the appropriate color for a section.

	GLfloat r = 0.0;
	GLfloat g = 0.0;
	GLfloat b = 0.0;


	//If an inode was found and its value is false.
	if (cur.generic_pointer != NULL)
	{

		if (cur.inode2d->value)
		{
			//True data. (Black).
			if (cur.inode2d->is_fake)
			{
				//Fake black color. (Dark gay).
				r = 50.0;
				g = 50.0;
				b = 50.0;
			}
			else
			{
				//Black for true. Odd.
				r = 0.0;
				g = 0.0;
				b = 0.0;
			}
		}
		else if (!cur.inode2d->value)
		{
			//Data is false.(White)..
			if (cur.inode2d->is_fake)
			{
				//Fake white color. (light gray)
				r = 125.0;
				g = 125.0;
				b = 125.0;
			}
			else
			{
				//White for false? go figure.
				r = 255.0;
				g = 255.0;
				b = 255.0;
			}
		}
	}
	//Use the default disk color.
	else
	{
		r = cNorm.unpacked.r;
		g = cNorm.unpacked.g;
		b = cNorm.unpacked.b;
	}



	r /= 255.0;
	g /= 255.0;
	b /= 255.0;


	glColor3f(r, g, b);
}

















/**********************************************************************************************
***********************************************************************************************
***********************************************************************************************
*
*				DRAWDISK3DPLOT
*
*	Draws a disk with data on the top and bottom.
*
*	Here each disk represents 3 or 2 levels. 1 on the top, 1 on the side like normal,
*	and 1 on the bottom.
*	The only problem is that the top and bottom are broken into the same number of sections as
*	the sides.  This is too many so they arent all used.
*
*	Only the middle disk has 3 layers.  The rest have 2 because it is nice to be able
*	to see the data.
*
***********************************************************************************************
***********************************************************************************************
**********************************************************************************************/

void diskview_mfc_t::drawDisk3dPlot(int num, float x, float y, float z, float rad, float rA, float h, int layer, nvboolfunc_t* boolfunc, int mid)
{

	//Counting.
	int k = 0;

	//Sides.
	int n;
	//Centers and radius, also alignment angle.
	float cx, cy, cz, radius, rotAngle, height;

	//Number of slots/elements.
	n = num;
	//Center of the disk.
	cx = x;
	cy = y;
	cz = z;
	radius = rad;
	rotAngle = rA;
	//Thickness of this disk.
	height = h;

	//Color of this disk.
	color_t cNorm = boolfunc->get_disk_color(layer);

	//Arrays for calculating the normals.
	GLfloat norm1[3] = { 0.0f };
	GLfloat norm2[3] = { 0.0f };
	GLfloat norm3[3] = { 0.0f };

	//Array of vertexesfor the disk.
	//Hold x,y,z coords for the top ngon.
	GLfloat* vertx = new GLfloat[sizeof(GLfloat) * n];
	GLfloat* verty = new GLfloat[sizeof(GLfloat) * n];
	GLfloat* vertz = new GLfloat[sizeof(GLfloat) * n];

	double angle = rotAngle * PI;
	double angleInc = (2 * PI) / n;

	if (n < 3 || boolfunc->get_xsize(layer) < 3)
	{
		if (n == 0)
			return;

		_generic_inode_t cur;
		//See comments below.
		float offSet = (float)n / 2.0;
		float nodeToGet = (((float)0 - offSet) + 0.5f);

		cur.generic_pointer = boolfunc->get_inode(nodeToGet, layer);
		//Set the color for this section.
		setColors(cur, cNorm);
		glBegin(GL_QUADS);
		glVertex3f(cx - (radius / 4.0), cy - height, cz);
		glVertex3f(cx - (radius / 4.0), cy, cz);
		glVertex3f(cx + (radius / 4.0), cy, cz);
		glVertex3f(cx + (radius / 4.0), cy - height, cz);
		glEnd();


		if (showvalbbox)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			setColors(cNorm.unpacked.r, cNorm.unpacked.g, cNorm.unpacked.b);
			glLineWidth(2.0f);
			glBegin(GL_QUADS);
			glVertex3f(cx - (radius / 4.0), cy - height, cz);
			glVertex3f(cx - (radius / 4.0), cy, cz);
			glVertex3f(cx + (radius / 4.0), cy, cz);
			glVertex3f(cx + (radius / 4.0), cy - height, cz);
			glEnd();

			glLineWidth(1.0f);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		else if (showunivalbbox)
		{
			//Same box but use one color, not the disk color.

			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			setColors(0.0, 255.0, 255.0);
			glLineWidth(2.0f);
			glBegin(GL_QUADS);
			glVertex3f(cx - (radius / 4.0), cy - height, cz);
			glVertex3f(cx - (radius / 4.0), cy, cz);
			glVertex3f(cx + (radius / 4.0), cy, cz);
			glVertex3f(cx + (radius / 4.0), cy - height, cz);
			glEnd();

			glLineWidth(1.0f);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


		}


		//Draw a red stripe down the side of the first slot in a disk.

		if (boolfunc->isShowFirstPos())
		{
			setColors(255.0, 0.0, 0.0);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glLineWidth(10.0f);
			glBegin(GL_QUADS);
			glVertex3f(cx - (radius / 4.0), cy - height, cz);
			glVertex3f(cx - (radius / 4.0), cy, cz);
			glVertex3f(cx + (radius / 4.0), cy, cz);
			glVertex3f(cx + (radius / 4.0), cy - height, cz);
			glEnd();

			glLineWidth(1.0f);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}



		return;
	}



	//For pointer to disk data. 1s and 0s.  Used to get the values to plot.
	_generic_inode_t cur;

	//Calculate the vertexes.
	//The first way draws 'backwards'.
	//for (int i = 0; i < n; i++)
	for (int i = n - 1; i > -1; i--)
	{
		angle += angleInc;

		GLfloat vx, vy, vz;

		//This calculates the vertices for the top of the polygon.
		//The sides come down off of here in the -y direction.

		vx = radius * cos(angle) + cx;
		vy = cy;
		vz = radius * sin(angle) + cz;

		vertx[i] = vx;
		verty[i] = vy;
		vertz[i] = vz;

		//This array now holds all the vertexes. The polygons are drawn
		//from this.

	}

	//Draw the ngon, top.

	//Calculate the normal for this surface.
	//Get three points on the plane.
	norm1[0] = vertx[0];
	norm1[1] = verty[0];
	norm1[2] = vertz[0];

	//Negative because this polygon is upside down.
	norm2[0] = -vertx[1];
	norm2[1] = -verty[1];
	norm2[2] = -vertz[1];

	norm3[0] = vertx[2];
	norm3[1] = verty[2];
	norm3[2] = vertz[2];


	calcNormal(norm1, norm2, norm3);

	//Set disk color.
	setColors(cNorm.unpacked.r, cNorm.unpacked.g, cNorm.unpacked.b);

	//Wrap the polygon back together.
	vertx[n] = vertx[0];
	verty[n] = verty[0];
	vertz[n] = vertz[0];



	//Offset for the middle layer.
	float middleOffset = (float)(boolfunc->get_xsize(mid) - boolfunc->get_xsize(layer)) / 2.0;



	//The data that is being drawn.
	data_inode2d_t* d2d = NULL;
	if (layer >= mid)
	{
		boolfunc->rewind(layer + 1);
		d2d = (data_inode2d_t*)boolfunc->get_next_inode(layer + 1);
	}


	for (k = 0; k < n; k++)
	{

		//n is the number of slots/elements.

		//float offSet = (float)n /2.0;
		float offSet = (float)(boolfunc->get_xsize(layer + 1)) / 2.0;

		float nodeToGet = (((float)k - offSet) + 0.5f);

		int m = 0;

		//Distance to move elements from position 0.
		float move = 0;

		move = (float)(boolfunc->get_xsize(layer) - boolfunc->get_xsize(layer + 1)) / 2.0;
		m = (int)move + middleOffset;


		//Get a pointer to the inode here.  This contains the data about this entry.
		//And determines what color it should be when drawn.

		//If this disk is lower than mid, draw on side and bottom.
		//If it is mid do both sides.
		//If it is above mid draw on side and top.
		if (layer >= mid && k >= m)
		{
			//d2d = (data_inode2d_t *)boolfunc->get_next_inode(layer+1);
			d2d = (data_inode2d_t*)boolfunc->get_inode(nodeToGet - m, layer + 1);
			cur.generic_pointer = d2d;
		}
		else
			cur.generic_pointer = NULL;

		//Set the color for this section.
		setColors(cur, cNorm);
		//To show data that is a violation of monotony.
		if (boolfunc->isMonotViol())
			if (checkMonotViol(d2d))
				setColors(255, 0, 0);

		glBegin(GL_POLYGON);
		glVertex3f(cx, cy, cz);
		glVertex3f(vertx[k], verty[k], vertz[k]);
		//So the last point is the first one.
		if (k + 1 > n)
			glVertex3f(vertx[0], verty[0], vertz[0]);
		else
			glVertex3f(vertx[k + 1], verty[k + 1], vertz[k + 1]);
		glEnd();

		//Change the colors and draw an outline of the same polygon for a border.
		//If the correct box is selected on toolbar.
		//Just draw a line on the left side from the center.
		if (showvalbbox)
		{

			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			setColors(cNorm.unpacked.r, cNorm.unpacked.g, cNorm.unpacked.b);
			glLineWidth(2.0f);

			glBegin(GL_LINE_STRIP);
			glVertex3f(cx, cy, cz);
			glVertex3f(vertx[k], verty[k], vertz[k]);
			glEnd();

			glLineWidth(1.0f);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		else if (showunivalbbox)
		{
			//Same box but use one color, not the disk color.

			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			setColors(0.0, 255.0, 255.0);
			glLineWidth(2.0f);
			glBegin(GL_LINE_STRIP);
			glVertex3f(cx, cy, cz);
			glVertex3f(vertx[k], verty[k], vertz[k]);
			glEnd();

			glLineWidth(1.0f);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}



	}//Done with one section.

	//Draw the sides of the disk.
	//These come down from the top polygon in -y direction.

	boolfunc->rewind(layer);
	d2d = (data_inode2d_t*)boolfunc->get_next_inode(layer);

	for (k = 0; k < n; k++)
	{
		//So that index + 2 wraps around to 2, when index == n.
		int index = k;

		//Calculate the normal for this surface.
		norm1[0] = vertx[index];
		norm1[1] = verty[index];
		norm1[2] = vertz[index];

		index++;
		if (index >= n)
			index = 0;

		norm2[0] = vertx[index];
		norm2[1] = verty[index];
		norm2[2] = vertz[index];

		norm3[0] = vertx[index];
		norm3[1] = verty[index] - height;
		norm3[2] = vertz[index];

		calcNormal(norm1, norm2, norm3);

		//n is the number of slots/elements.
		float offSet = (float)(boolfunc->get_xsize(layer)) / 2.0;
		float nodeToGet = (((float)k - offSet) + 0.5f);

		//Get a pointer to the inode here.  This contains the data about this entry.
		//And determines what color it should be when drawn.


		//d2d = (data_inode2d_t *)boolfunc->get_next_inode(layer);
		if (k >= (int)middleOffset)
		{
			d2d = (data_inode2d_t*)boolfunc->get_inode(nodeToGet - middleOffset, layer);
			cur.generic_pointer = d2d;
		}
		else
			cur.generic_pointer = NULL;

		//Set the color for this section.
		setColors(cur, cNorm);
		//To show data that is a violation of monotony.
		if (boolfunc->isMonotViol())
			if (checkMonotViol(d2d))
				setColors(255, 0, 0);

		//Draw the side panel.
		glBegin(GL_QUADS);
		glVertex3f(vertx[k], verty[k] - height, vertz[k]);
		glVertex3f(vertx[k], verty[k], vertz[k]);
		glVertex3f(vertx[k + 1], verty[k + 1], vertz[k + 1]);
		glVertex3f(vertx[k + 1], verty[k + 1] - height, vertz[k + 1]);
		glEnd();

		//Change the colors and draw an outline of the same polygon for a border.
		//If the correct box is selected on toolbar.
		if (showvalbbox)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			setColors(cNorm.unpacked.r, cNorm.unpacked.g, cNorm.unpacked.b);
			glLineWidth(2.0f);

			glBegin(GL_QUADS);
			glVertex3f(vertx[k], verty[k] - height, vertz[k]);
			glVertex3f(vertx[k], verty[k], vertz[k]);
			glVertex3f(vertx[k + 1], verty[k + 1], vertz[k + 1]);
			glVertex3f(vertx[k + 1], verty[k + 1] - height, vertz[k + 1]);
			glEnd();

			glLineWidth(1.0f);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		else if (showunivalbbox)
		{
			//Same box but use one color, not the disk color.
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			setColors(0.0, 255.0, 255.0);
			glLineWidth(2.0f);

			glBegin(GL_QUADS);
			glVertex3f(vertx[k], verty[k] - height, vertz[k]);
			glVertex3f(vertx[k], verty[k], vertz[k]);
			glVertex3f(vertx[k + 1], verty[k + 1], vertz[k + 1]);
			glVertex3f(vertx[k + 1], verty[k + 1] - height, vertz[k + 1]);
			glEnd();

			glLineWidth(1.0f);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		//Draw a red stripe down the side of the first slot in a disk.
		if (k == 0 && boolfunc->isShowFirstPos())
		{
			setColors(255.0, 0.0, 0.0);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glLineWidth(10.0f);

			glBegin(GL_QUADS);
			glVertex3f(vertx[k], verty[k] - height, vertz[k]);
			glVertex3f(vertx[k], verty[k], vertz[k]);
			glVertex3f(vertx[k + 1], verty[k + 1], vertz[k + 1]);
			glVertex3f(vertx[k + 1], verty[k + 1] - height, vertz[k + 1]);
			glEnd();

			glLineWidth(1.0f);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}//Done drawing one section.

	//Draw the bottom polygon.
	//Calculate the normal for this surface.
	//Get thre points on the plane.

	norm1[0] = vertx[0];
	norm1[1] = verty[0];
	norm1[2] = vertz[0];

	norm2[0] = vertx[1];
	norm2[1] = verty[1];
	norm2[2] = vertz[1];

	norm3[0] = vertx[2];
	norm3[1] = verty[2];
	norm3[2] = vertz[2];

	calcNormal(norm1, norm2, norm3);

	//Change colors back to normal.
	setColors(cNorm.unpacked.r, cNorm.unpacked.g, cNorm.unpacked.b);

	if (layer <= mid)
	{
		boolfunc->rewind(layer - 1);
		d2d = (data_inode2d_t*)boolfunc->get_next_inode(layer - 1);
	}
	//Draw the bottom ngon.
	for (k = 0; k < n; k++)
	{

		//n is the number of slots/elements.
		float offSet = (float)(boolfunc->get_xsize(layer - 1)) / 2.0;
		float nodeToGet = (((float)k - offSet) + 0.5f);

		//Distance to move elements from position 0.
		float move = (float)(boolfunc->get_xsize(layer) - boolfunc->get_xsize(layer - 1)) / 2.0;

		int m = (int)move + middleOffset;

		//Get a pointer to the inode here.  This contains the data about this entry.
		//And determines what color it should be when drawn.
		if (layer <= mid && k >= m)
		{
			//d2d = (data_inode2d_t *)boolfunc->get_next_inode(layer-1);
			d2d = (data_inode2d_t*)boolfunc->get_inode(nodeToGet - m, layer - 1);
			cur.generic_pointer = d2d;
		}

		else
			cur.generic_pointer = NULL;

		//Set the color for this section.
		setColors(cur, cNorm);

		//To show data that is a violation of monotony.
		if (boolfunc->isMonotViol())
			if (checkMonotViol(d2d))
				setColors(255, 0, 0);

		glBegin(GL_POLYGON);
		glVertex3f(cx, cy - height, cz);
		glVertex3f(vertx[k], verty[k] - height, vertz[k]);
		//So the last point is the first one.
		if (k + 1 > n)
			glVertex3f(vertx[0], verty[0] - height, vertz[0]);
		else
			glVertex3f(vertx[k + 1], verty[k + 1] - height, vertz[k + 1]);
		glEnd();

		//Change the colors and draw an outline of the same polygon for a border.
		//If the correct box is selected on toolbar.
		//Just draw a line on the left side from the center.
		if (showvalbbox)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			setColors(cNorm.unpacked.r, cNorm.unpacked.g, cNorm.unpacked.b);
			glLineWidth(2.0f);

			glBegin(GL_LINE_STRIP);
			glVertex3f(cx, cy - height, cz);
			glVertex3f(vertx[k], verty[k] - height, vertz[k]);
			glEnd();

			glLineWidth(1.0f);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		else if (showunivalbbox)
		{
			//Same box but use one color, not the disk color.

			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			setColors(0.0, 255.0, 255.0);
			glLineWidth(2.0f);

			glBegin(GL_LINE_STRIP);
			glVertex3f(cx, cy - height, cz);
			glVertex3f(vertx[k], verty[k] - height, vertz[k]);
			glEnd();

			glLineWidth(1.0f);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}//Done drawing one section.

	//Cleanup.
	delete[] vertx;
	delete[] verty;
	delete[] vertz;

}





















/**********************************************************************************************
***********************************************************************************************
***********************************************************************************************
*
*				DRAWDISKCOMPRESSED
*
*	Draws a disk with data on the top and bottom.
*
*	Same as drawDisk3dPlot, but compresses the data.
*
*	A disk consists of a top ngon, a bottom ngon, and connecting side pieces.
*
***********************************************************************************************
***********************************************************************************************
**********************************************************************************************/

void diskview_mfc_t::drawDiskCompressed(int num, float x, float y, float z, float rad, float rA, float h, int layer, nvboolfunc_t* boolfunc, int mid)
{

	//Counting.
	int k = 0;

	//Sides.
	int n;
	//Centers and radius, also alignment angle.
	float cx, cy, cz, radius, rotAngle, height;

	//Number of slots/elements.
	n = num;
	//Center of the disk.
	cx = x;
	cy = y;
	cz = z;
	radius = rad;
	//Angle to start drawing.
	rotAngle = rA;
	//Thickness of this disk.
	height = h;

	//Color of this disk.  Same as the 2d disk.
	color_t cNorm = boolfunc->get_disk_color(layer);

	//Arrays for calculating the normals.
	GLfloat norm1[3] = { 0.0f };
	GLfloat norm2[3] = { 0.0f };
	GLfloat norm3[3] = { 0.0f };


	_generic_inode_t cur;
	float nodeToGet = 0;
	bool noData = false;
	bool noData1 = false;
	bool noData2 = false;


	//Array of vertexesfor the disk.
	//Hold x,y,z coords for the top ngon.
	GLfloat* vertx = new GLfloat[sizeof(GLfloat) * n];
	GLfloat* verty = new GLfloat[sizeof(GLfloat) * n];
	GLfloat* vertz = new GLfloat[sizeof(GLfloat) * n];

	double angle = rotAngle * PI;
	double angleInc = (2 * PI) / n;

	disk_data_t thisData;
	disk_data_t thisData1;
	disk_data_t thisData2;

	//Number of groups there are to draw for this layer.
	int numGroups = 0;

	//Iterator for the list elements. (Groups to draw).
	std::list<data3d>::const_iterator iter;
	std::list<data3d>::const_iterator iter1;
	std::list<data3d>::const_iterator iter2;

	//Offset the drawing of the top and bottom disk so they are centered
	//with comparison to the middle layer.
	float diskOffsetBottom = 0;
	float diskOffsetTop = 0;




	if (n < 3 || boolfunc->get_xsize(layer) < 3)
	{
		if (n == 0)
			return;

		_generic_inode_t cur;
		//See comments below.
		float offSet = (float)n / 2.0;
		float nodeToGet = (((float)0 - offSet) + 0.5f);

		cur.generic_pointer = boolfunc->get_inode(nodeToGet, layer);
		//Set the color for this section.
		setColors(cur, cNorm);
		glBegin(GL_QUADS);
		glVertex3f(cx - (radius / 4.0), cy - height, cz);
		glVertex3f(cx - (radius / 4.0), cy, cz);
		glVertex3f(cx + (radius / 4.0), cy, cz);
		glVertex3f(cx + (radius / 4.0), cy - height, cz);
		glEnd();

		if (showvalbbox)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			setColors(cNorm.unpacked.r, cNorm.unpacked.g, cNorm.unpacked.b);
			glLineWidth(2.0f);
			glBegin(GL_QUADS);
			glVertex3f(cx - (radius / 4.0), cy - height, cz);
			glVertex3f(cx - (radius / 4.0), cy, cz);
			glVertex3f(cx + (radius / 4.0), cy, cz);
			glVertex3f(cx + (radius / 4.0), cy - height, cz);
			glEnd();

			glLineWidth(1.0f);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		else if (showunivalbbox)
		{
			//Same box but use one color, not the disk color.

			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			setColors(0.0, 255.0, 255.0);
			glLineWidth(2.0f);
			glBegin(GL_QUADS);
			glVertex3f(cx - (radius / 4.0), cy - height, cz);
			glVertex3f(cx - (radius / 4.0), cy, cz);
			glVertex3f(cx + (radius / 4.0), cy, cz);
			glVertex3f(cx + (radius / 4.0), cy - height, cz);
			glEnd();

			glLineWidth(1.0f);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


		}


		//Draw a red stripe down the side of the first slot in a disk.

		if (boolfunc->isShowFirstPos())
		{
			setColors(255.0, 0.0, 0.0);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glLineWidth(10.0f);
			glBegin(GL_QUADS);
			glVertex3f(cx - (radius / 4.0), cy - height, cz);
			glVertex3f(cx - (radius / 4.0), cy, cz);
			glVertex3f(cx + (radius / 4.0), cy, cz);
			glVertex3f(cx + (radius / 4.0), cy - height, cz);
			glEnd();

			glLineWidth(1.0f);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}



		return;

	}


	//Offset for the middle layer.
//	float middleOffset = (float)(boolfunc->get_xsize(mid) - boolfunc->get_xsize(layer))/2.0;
	float middleOffset = 0;

	//Draw the sides of the disk.
	thisData1 = boolfunc->getDiskData(layer);
	iter1 = thisData1.dataList3d.begin();
	noData1 = false;
	numGroups = thisData1.dataList3d.size();




	//If this disk is lower than mid, draw on side and bottom.
	//If it is mid do both sides.
	//If it is above mid draw on side and top.
	if (layer >= mid)
	{
		//Get the data for this level.		
		thisData = boolfunc->getDiskData(layer + 1);
		iter = thisData.dataList3d.begin();


		noData = false;
		cur.generic_pointer = boolfunc->get_inode(nodeToGet, layer + 1);

		//Offset by middle layer/this layer /2.
		diskOffsetTop = (numGroups - (thisData.dataList3d.size() + 1)) / 2.0;
		if (diskOffsetTop < 0.0 || diskOffsetTop > boolfunc->get_xsize(layer + 1))
			diskOffsetTop = 0;
		//	diskOffsetTop = (boolfunc->get_xsize(layer+1) - boolfunc->get_xsize(layer))/2.0;	
		//	diskOffsetTop+=middleOffset;

	}
	else
	{
		//We arent drawing this level.
		noData = true;
		//iter = NULL;
		cur.generic_pointer = NULL;
	}


	if (layer <= mid)
	{
		thisData2 = boolfunc->getDiskData(layer - 1);
		iter2 = thisData2.dataList3d.begin();
		noData2 = false;
		cur.generic_pointer = boolfunc->get_inode(nodeToGet, layer - 1);
		diskOffsetBottom = fabs((numGroups - (thisData2.dataList3d.size() + 1)) / 2.0);
		if (diskOffsetBottom < 0.0 || diskOffsetBottom > boolfunc->get_xsize(layer - 1))
			diskOffsetBottom = 0;
		//diskOffsetBottom = (boolfunc->get_xsize(layer-1) - boolfunc->get_xsize(layer))/2.0;
		//diskOffsetBottom += middleOffset;

	}
	else
	{
		noData2 = true;
		//iter2 = NULL;
		cur.generic_pointer = NULL;
	}




	//Calculate the vertexes of the top ngon.
	//for (int i = 0; i < n; i++)
	for (int i = n - 1; i > -1; i--)
	{
		angle += angleInc;

		GLfloat vx, vy, vz;

		//This calculates the vertices for the top of the polygon.
		//The sides come down off of here in the -y direction.

		vx = radius * cos(angle) + cx;
		vy = cy;
		vz = radius * sin(angle) + cz;

		vertx[i] = vx;
		verty[i] = vy;
		vertz[i] = vz;

		//This array now holds all the vertexes. The polygons are drawn
		//from this.

	}

	//Draw the ngon, top.

	//Calculate the normal for this surface.
	//Get three points on the plane.
	norm1[0] = vertx[0];
	norm1[1] = verty[0];
	norm1[2] = vertz[0];

	//Negative because this polygon is upside down.
	norm2[0] = -vertx[1];
	norm2[1] = -verty[1];
	norm2[2] = -vertz[1];

	norm3[0] = vertx[2];
	norm3[1] = verty[2];
	norm3[2] = vertz[2];

	calcNormal(norm1, norm2, norm3);

	//Set disk color.
	setColors(cNorm.unpacked.r, cNorm.unpacked.g, cNorm.unpacked.b);

	//Wrap the polygon back together.
	vertx[n] = vertx[0];
	verty[n] = verty[0];
	vertz[n] = vertz[0];




	for (k = 0; k < n; k++)
	{
		//For each slot, get the next 3d data group that goes here.
		//If the end of the list is reached, draw all the rest as the disk color.

		//n is the number of slots/elements.
		float offSet = (float)n / 2.0;
		nodeToGet = (((float)k - offSet) + 0.5f);



		//Get a pointer to the inode here.  This contains the data about this entry.
		//And determines what color it should be when drawn.

		//Set the color for this section.
		if (noData == true || iter == thisData.dataList3d.end() || iter->bvList.size() == 0)
			setColors(cNorm.unpacked.r, cNorm.unpacked.g, cNorm.unpacked.b);
		else if (k >= diskOffsetTop)
		{
			if (iter->value == true && iter->madeUp != true)
				setColors(const_cast<char*>("black"));
			else if (iter->value == true && iter->madeUp == true)
				setColors(const_cast <char*>("darkgray"));
			else if (iter->value == false && iter->madeUp == true)
				setColors(const_cast <char*>("lightgray"));
			else if (iter->value == false && iter->madeUp != true)
				setColors(const_cast <char*>("white"));
		}

		glBegin(GL_POLYGON);
		glVertex3f(cx, cy, cz);
		glVertex3f(vertx[k], verty[k], vertz[k]);
		//So the last point is the first one.
		if (k + 1 > n)
			glVertex3f(vertx[0], verty[0], vertz[0]);
		else
			glVertex3f(vertx[k + 1], verty[k + 1], vertz[k + 1]);
		glEnd();

		//Change the colors and draw an outline of the same polygon for a border.
		//If the correct box is selected on toolbar.
		//Just draw a line on the left side from the center.
		if (showvalbbox)
		{

			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			setColors(cNorm.unpacked.r, cNorm.unpacked.g, cNorm.unpacked.b);
			glLineWidth(2.0f);

			glBegin(GL_LINE_STRIP);
			glVertex3f(cx, cy, cz);
			glVertex3f(vertx[k], verty[k], vertz[k]);
			glEnd();

			glLineWidth(1.0f);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		}
		else if (showunivalbbox)
		{
			//Same box but use one color, not the disk color.
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			setColors(0.0, 255.0, 255.0);
			glLineWidth(2.0f);

			glBegin(GL_LINE_STRIP);
			glVertex3f(cx, cy, cz);
			glVertex3f(vertx[k], verty[k], vertz[k]);
			glEnd();

			glLineWidth(1.0f);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

		//Get the next group.

		if (noData != true && iter != thisData.dataList3d.end() && k >= diskOffsetTop)
			iter++;

	}//Done drawing a section.



	//Draw the sides of the disk.
	//These come down from the top polygon in -y direction.
	for (k = 0; k < n; k++)
	{
		//So that index + 2 wraps around to 2, when index == n.
		int index = k;

		//Calculate the normal for this surface.
		norm1[0] = vertx[index];
		norm1[1] = verty[index];
		norm1[2] = vertz[index];

		index++;
		if (index >= n)
			index = 0;

		norm2[0] = vertx[index];
		norm2[1] = verty[index];
		norm2[2] = vertz[index];

		norm3[0] = vertx[index];
		norm3[1] = verty[index] - height;
		norm3[2] = vertz[index];

		calcNormal(norm1, norm2, norm3);

		//n is the number of slots/elements.
		float offSet = (float)n / 2.0;
		float nodeToGet = (((float)k - offSet) + 0.5f);

		//Get a pointer to the inode here.  This contains the data about this entry.
		cur.generic_pointer = boolfunc->get_inode(nodeToGet, layer);

		//Set the color for this section.
		if (noData1 == true || iter1 == thisData1.dataList3d.end() || iter1->bvList.size() == 0)
			setColors(cNorm.unpacked.r, cNorm.unpacked.g, cNorm.unpacked.b);
		else if (k >= middleOffset)
		{
			if (iter1->value == true && iter1->madeUp != true)
				setColors(const_cast<char*>("black"));
			else if (iter1->value == true && iter1->madeUp == true)
				setColors(const_cast<char*>("darkgray"));
			else if (iter1->value == false && iter1->madeUp == true)
				setColors(const_cast<char*>("lightgray"));
			else if (iter1->value == false && iter1->madeUp != true)
				setColors(const_cast<char*>("white"));
		}

		//Draw the side panel.
		glBegin(GL_QUADS);
		glVertex3f(vertx[k], verty[k] - height, vertz[k]);
		glVertex3f(vertx[k], verty[k], vertz[k]);
		glVertex3f(vertx[k + 1], verty[k + 1], vertz[k + 1]);
		glVertex3f(vertx[k + 1], verty[k + 1] - height, vertz[k + 1]);
		glEnd();

		//Change the colors and draw an outline of the same polygon for a border.
		//If the correct box is selected on toolbar.
		if (showvalbbox)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			setColors(cNorm.unpacked.r, cNorm.unpacked.g, cNorm.unpacked.b);
			glLineWidth(2.0f);

			glBegin(GL_QUADS);
			glVertex3f(vertx[k], verty[k] - height, vertz[k]);
			glVertex3f(vertx[k], verty[k], vertz[k]);
			glVertex3f(vertx[k + 1], verty[k + 1], vertz[k + 1]);
			glVertex3f(vertx[k + 1], verty[k + 1] - height, vertz[k + 1]);
			glEnd();

			glLineWidth(1.0f);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		else if (showunivalbbox)
		{
			//Same box but use one color, not the disk color.
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			setColors(0.0, 255.0, 255.0);
			glLineWidth(2.0f);

			glBegin(GL_QUADS);
			glVertex3f(vertx[k], verty[k] - height, vertz[k]);
			glVertex3f(vertx[k], verty[k], vertz[k]);
			glVertex3f(vertx[k + 1], verty[k + 1], vertz[k + 1]);
			glVertex3f(vertx[k + 1], verty[k + 1] - height, vertz[k + 1]);
			glEnd();

			glLineWidth(1.0f);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

		//Draw a red stripe down the side of the first slot in a disk.
		if (k == 0 && boolfunc->isShowFirstPos())
		{
			setColors(255.0, 0.0, 0.0);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glLineWidth(10.0f);

			glBegin(GL_QUADS);
			glVertex3f(vertx[k], verty[k] - height, vertz[k]);
			glVertex3f(vertx[k], verty[k], vertz[k]);
			glVertex3f(vertx[k + 1], verty[k + 1], vertz[k + 1]);
			glVertex3f(vertx[k + 1], verty[k + 1] - height, vertz[k + 1]);
			glEnd();

			glLineWidth(1.0f);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

		//Go to the next side.
		if (noData1 != true && iter1 != thisData1.dataList3d.end())
			iter1++;
	}//Done drawing one section.


	//Draw the bottom polygon.
	//Calculate the normal for this surface.
	//Get thre points on the plane.

	norm1[0] = vertx[0];
	norm1[1] = verty[0];
	norm1[2] = vertz[0];

	norm2[0] = vertx[1];
	norm2[1] = verty[1];
	norm2[2] = vertz[1];

	norm3[0] = vertx[2];
	norm3[1] = verty[2];
	norm3[2] = vertz[2];

	calcNormal(norm1, norm2, norm3);

	//Change colors back to normal.
	setColors(cNorm.unpacked.r, cNorm.unpacked.g, cNorm.unpacked.b);


	//Draw the bottom ngon.
	for (k = 0; k < n; k++)
	{
		//n is the number of slots/elements.
		float offSet = (float)n / 2.0;
		float nodeToGet = (((float)k - offSet) + 0.5f);

		//Set the color for this section.
		if (noData2 == true || iter2 == thisData2.dataList3d.end() || iter2->bvList.size() == 0)
			setColors(cNorm.unpacked.r, cNorm.unpacked.g, cNorm.unpacked.b);
		else if (k >= diskOffsetBottom)
		{
			if (iter2->value == true && iter2->madeUp != true)
				setColors(const_cast<char*>("black"));
			else if (iter2->value == true && iter2->madeUp == true)
				setColors(const_cast<char*>("darkgray"));
			else if (iter2->value == false && iter2->madeUp == true)
				setColors(const_cast<char*>("lightgray"));
			else if (iter2->value == false && iter2->madeUp != true)
				setColors(const_cast<char*>("white"));
		}

		glBegin(GL_POLYGON);
		glVertex3f(cx, cy - height, cz);
		glVertex3f(vertx[k], verty[k] - height, vertz[k]);
		//So the last point is the first one.
		if (k + 1 > n)
			glVertex3f(vertx[0], verty[0] - height, vertz[0]);
		else
			glVertex3f(vertx[k + 1], verty[k + 1] - height, vertz[k + 1]);
		glEnd();

		//Change the colors and draw an outline of the same polygon for a border.
		//If the correct box is selected on toolbar.
		//Just draw a line on the left side from the center.
		if (showvalbbox)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			setColors(cNorm.unpacked.r, cNorm.unpacked.g, cNorm.unpacked.b);
			glLineWidth(2.0f);

			glBegin(GL_LINE_STRIP);
			glVertex3f(cx, cy - height, cz);
			glVertex3f(vertx[k], verty[k] - height, vertz[k]);
			glEnd();

			glLineWidth(1.0f);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		else if (showunivalbbox)
		{
			//Same box but use one color, not the disk color.
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			setColors(0.0, 255.0, 255.0);
			glLineWidth(2.0f);

			glBegin(GL_LINE_STRIP);
			glVertex3f(cx, cy - height, cz);
			glVertex3f(vertx[k], verty[k] - height, vertz[k]);
			glEnd();

			glLineWidth(1.0f);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

		if (noData2 != true && iter2 != thisData2.dataList3d.end() && k >= diskOffsetBottom)
			iter2++;
	}//Done drawing one section.

		//Cleanup.
	delete[] vertx;
	delete[] verty;
	delete[] vertz;
}


















/**********************************************************************************************
***********************************************************************************************
***********************************************************************************************
*
*				DRAWDISK
*
*	USed to draw disks where one layer == one disk.
*
*
***********************************************************************************************
***********************************************************************************************
**********************************************************************************************/
//Draw a disk.
void diskview_mfc_t::drawDisk(int num, float x, float y, float z, float rad, float rA, float h, int layer, nvboolfunc_t* boolfunc)
{

	/*
		Formula for an ngon.  The top and bottom of the disk.

	void ngon(int n, float cx, float cy, float radius, float rotAngle)
	{ // assumes global Canvas object, cvs
	if(n < 3) return; // bad number of sides
	double angle = rotAngle * 3.14159265 / 180; // initial angle
	double angleInc = 2 * 3.14159265 /n; //angle increment
	cvs. moveTo(radius + cx, cy);
	for(int k = 0; k < n; k++) // repeat n times
	{
	angle += angleInc;
	cvs.lineTo(radius * cos(angle) + cx, radius * sin(angle) + cy);
	}
	}

	*/




	//Sides.
	int n;
	//Centers and radius, also alignment angle.
	float cx, cy, cz, radius, rotAngle, height;


	//Init.
	//Number of slots/elements.
	n = num;
	//Center of the disk.
	cx = x;
	cy = y;
	cz = z;
	radius = rad;
	rotAngle = rA;
	//Thickness of this disk.
	height = h;

	//Color of this disk.
	color_t cNorm = boolfunc->get_disk_color(layer);

	//Arrays for calculating the normals.
	GLfloat norm1[3] = { 0.0f };
	GLfloat norm2[3] = { 0.0f };
	GLfloat norm3[3] = { 0.0f };

	//Array of vertexesfor the disk.
	//Hold x,y,z coords for the top ngon.
	GLfloat* vertx = new GLfloat[sizeof(GLfloat) * n];
	GLfloat* verty = new GLfloat[sizeof(GLfloat) * n];
	GLfloat* vertz = new GLfloat[sizeof(GLfloat) * n];


	if (n < 3)
	{
		//Draw a 2d ploygon to show this level.
		//It has only one element.

		if (n == 0)
			return;

		_generic_inode_t cur;
		//See comments below.
		float offSet = (float)n / 2.0;
		float nodeToGet = (((float)0 - offSet) + 0.5f);

		cur.generic_pointer = boolfunc->get_inode(nodeToGet, layer);
		//Set the color for this section.
		setColors(cur, cNorm);
		glBegin(GL_QUADS);
		glVertex3f(cx - (radius / 4.0), cy - height, cz);
		glVertex3f(cx - (radius / 4.0), cy, cz);
		glVertex3f(cx + (radius / 4.0), cy, cz);
		glVertex3f(cx + (radius / 4.0), cy - height, cz);
		glEnd();

		if (showvalbbox)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			setColors(cNorm.unpacked.r, cNorm.unpacked.g, cNorm.unpacked.b);
			glLineWidth(2.0f);
			glBegin(GL_QUADS);
			glVertex3f(cx - (radius / 4.0), cy - height, cz);
			glVertex3f(cx - (radius / 4.0), cy, cz);
			glVertex3f(cx + (radius / 4.0), cy, cz);
			glVertex3f(cx + (radius / 4.0), cy - height, cz);
			glEnd();

			glLineWidth(1.0f);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		else if (showunivalbbox)
		{
			//Same box but use one color, not the disk color.

			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			setColors(0.0, 255.0, 255.0);
			glLineWidth(2.0f);
			glBegin(GL_QUADS);
			glVertex3f(cx - (radius / 4.0), cy - height, cz);
			glVertex3f(cx - (radius / 4.0), cy, cz);
			glVertex3f(cx + (radius / 4.0), cy, cz);
			glVertex3f(cx + (radius / 4.0), cy - height, cz);
			glEnd();

			glLineWidth(1.0f);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


		}


		//Draw a red stripe down the side of the first slot in a disk.

		if (boolfunc->isShowFirstPos())
		{
			setColors(255.0, 0.0, 0.0);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glLineWidth(10.0f);
			glBegin(GL_QUADS);
			glVertex3f(cx - (radius / 4.0), cy - height, cz);
			glVertex3f(cx - (radius / 4.0), cy, cz);
			glVertex3f(cx + (radius / 4.0), cy, cz);
			glVertex3f(cx + (radius / 4.0), cy - height, cz);
			glEnd();

			glLineWidth(1.0f);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}



		return;
	}




	double angle = rotAngle * PI;
	double angleInc = (2 * PI) / n;


	//For pointer to disk data. 1s and 0s.  Used to get the values to plot.
	_generic_inode_t cur;


	//Calculate the vertexes.
	//for (int i = 0; i < n; i++)
	for (int i = n - 1; i > -1; i--)
	{
		angle += angleInc;

		GLfloat vx, vy, vz;

		//This calculates the vertices for the top of the polygon.
		//The sides come down off of here in the -y direction.

		vx = radius * cos(angle) + cx;
		vy = cy;
		vz = radius * sin(angle) + cz;

		vertx[i] = vx;
		verty[i] = vy;
		vertz[i] = vz;

		//This array now holds all the vertexes. The polygons are drawn
		//from this.

	}

	//Draw the ngon, top.

	//Calculate the normal for this surface.
	//Get three points on the plane.
	norm1[0] = vertx[0];
	norm1[1] = verty[0];
	norm1[2] = vertz[0];

	//Negative because this polygon is upside down.
	norm2[0] = -vertx[1];
	norm2[1] = -verty[1];
	norm2[2] = -vertz[1];

	norm3[0] = vertx[2];
	norm3[1] = verty[2];
	norm3[2] = vertz[2];


	calcNormal(norm1, norm2, norm3);

	//Set disk color.
	setColors(cNorm.unpacked.r, cNorm.unpacked.g, cNorm.unpacked.b);

	glBegin(GL_POLYGON);
	for (int k = 0; k < n; k++)
		glVertex3f(vertx[k], verty[k], vertz[k]);
	glEnd();


	//Wrap the polygon back together.
	vertx[n] = vertx[0];
	verty[n] = verty[0];
	vertz[n] = vertz[0];




	//Draw the sides of the disk.
	//These come down from the top polygon in -y direction.
	for (int k = 0; k < n; k++)
	{
		//So that index + 2 wraps around to 2, when index == n.
		int index = k;

		//Calculate the normal for this surface.
		norm1[0] = vertx[index];
		norm1[1] = verty[index];
		norm1[2] = vertz[index];

		index++;
		if (index >= n)
			index = 0;

		norm2[0] = vertx[index];
		norm2[1] = verty[index];
		norm2[2] = vertz[index];

		norm3[0] = vertx[index];
		norm3[1] = verty[index] - height;
		norm3[2] = vertz[index];

		calcNormal(norm1, norm2, norm3);

		//Change the color of panels that are 1 values in the data.

		//Not used but an explanation of the program.
		//Go through each inode and get its value.
		//The value determines which slot it goes into.
		//when they are sorted as smallest to largest
		//Each layer is the number of 1s in the vector
		//so in this case 0001 is on the left, then 0010, then 0100, then 1000.
		//Will need to change for each different type of sorting.


		//Obsolete!
		//This works. colors every slot but not the right ones.
		//cur.generic_pointer = boolfunc->get_inode((((float) k  - 0.5f)/2.0f), layer);


		//Not used.
		//float xinc = (!hansel_aligned || boolfunc->get_xsize(i) & 1) ? 0.0f : 0.5f;

		//n is the number of slots/elements.
		float offSet = (float)n / 2.0;
		float nodeToGet = (((float)k - offSet) + 0.5f);

		//Get a pointer to the inode here.  This contains the data about this entry.
		//And determines what color it should be when drawn.
		cur.generic_pointer = boolfunc->get_inode(nodeToGet, layer);


		/*
				//Used to view all the inodes for this layer.
				boolfunc->rewind(layer);
				while (cur.generic_pointer = boolfunc->get_next_inode(layer))
				{
					float xp = cur.inode2d->xpos;
				}
		*/

		//If an inode was found and its value is false.

		//Set the color for this section.
		setColors(cur, cNorm);

		//To show data that is a violation of monotony.
		if (boolfunc->isMonotViol())
			if (checkMonotViol(cur.inode2d))
				setColors(255, 0, 0);


		//Draw the side panel.
		glBegin(GL_QUADS);
		glVertex3f(vertx[k], verty[k] - height, vertz[k]);
		glVertex3f(vertx[k], verty[k], vertz[k]);
		glVertex3f(vertx[k + 1], verty[k + 1], vertz[k + 1]);
		glVertex3f(vertx[k + 1], verty[k + 1] - height, vertz[k + 1]);
		glEnd();

		//Change the colors and draw an outline of the same polygon for a border.
		//If the correct box is selected on toolbar.
		if (showvalbbox)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			setColors(cNorm.unpacked.r, cNorm.unpacked.g, cNorm.unpacked.b);
			glLineWidth(2.0f);
			glBegin(GL_QUADS);
			glVertex3f(vertx[k], verty[k] - height, vertz[k]);
			glVertex3f(vertx[k], verty[k], vertz[k]);
			glVertex3f(vertx[k + 1], verty[k + 1], vertz[k + 1]);
			glVertex3f(vertx[k + 1], verty[k + 1] - height, vertz[k + 1]);
			glEnd();

			glLineWidth(1.0f);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		else if (showunivalbbox)
		{
			//Same box but use one color, not the disk color.

			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			setColors(0.0, 255.0, 255.0);
			glLineWidth(2.0f);
			glBegin(GL_QUADS);
			glVertex3f(vertx[k], verty[k] - height, vertz[k]);
			glVertex3f(vertx[k], verty[k], vertz[k]);
			glVertex3f(vertx[k + 1], verty[k + 1], vertz[k + 1]);
			glVertex3f(vertx[k + 1], verty[k + 1] - height, vertz[k + 1]);
			glEnd();

			glLineWidth(1.0f);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


		}


		//Draw a red stripe down the side of the first slot in a disk.

		if (k == 0 && boolfunc->isShowFirstPos())
		{
			setColors(255.0, 0.0, 0.0);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glLineWidth(10.0f);
			glBegin(GL_QUADS);
			glVertex3f(vertx[k], verty[k] - height, vertz[k]);
			glVertex3f(vertx[k], verty[k], vertz[k]);
			glVertex3f(vertx[k + 1], verty[k + 1], vertz[k + 1]);
			glVertex3f(vertx[k + 1], verty[k + 1] - height, vertz[k + 1]);
			glEnd();

			glLineWidth(1.0f);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

		//Go to the next side.		
	}


	//Draw the bottom polygon.
	//Calculate the normal for this surface.
	//Get thre points on the plane.

	norm1[0] = vertx[0];
	norm1[1] = verty[0];
	norm1[2] = vertz[0];

	norm2[0] = vertx[1];
	norm2[1] = verty[1];
	norm2[2] = vertz[1];

	norm3[0] = vertx[2];
	norm3[1] = verty[2];
	norm3[2] = vertz[2];


	//Calc the normal, the cross product of a and b.

	//glNormal3d( (ay*bz - az*by), -(az*bx - ax*bz), (ax*by - ay*bx) );
	calcNormal(norm1, norm2, norm3);

	//Change colors back to normal.
	setColors(cNorm.unpacked.r, cNorm.unpacked.g, cNorm.unpacked.b);


	//Draw the bottom ngon.
	glBegin(GL_POLYGON);
	for (int k = 0; k < n; k++)
		glVertex3f(vertx[k], verty[k] - height, vertz[k]);


	glEnd();

	//Cleanup.
	delete[] vertx;
	delete[] verty;
	delete[] vertz;

	return;
}


bool diskview_mfc_t::checkMonotViol(data_inode2d_t* d)
{

	//These are the conditions for violating monotony.
	//LightGray above Dark Gray. lg>dg.
	//lg>dg  lg>b  w>dg   w>b.

	if (d == NULL)
		return false;

	//Look at the element in the hansel chain above.
	data_inode2d_t* dup = NULL;
	dup = d->chain_up;

	bool viol = false;
	//lg>dg
	if (dup != NULL && (dup->value == false && dup->is_fake == true && d->value == true && d->is_fake == true))
		viol = true;

	//lg>b
	if (dup != NULL && (dup->value == false && dup->is_fake == true && d->value == true && d->is_fake == false))
		viol = true;

	//w>dg
	if (dup != NULL && (dup->value == false && dup->is_fake == false && d->value == true && d->is_fake == true))
		viol = true;

	//w>b
	if (dup != NULL && (dup->value == false && dup->is_fake == false && d->value == true && d->is_fake == false))
		viol = true;

	return viol;
}



//*****************************************************************************************//
// init functions ...
//*****************************************************************************************//

bool diskview_mfc_t::setpxlformat(HDC hdc)
{

	// We must set the pixel format of the window ... because of some
	// issue about the DC ... so we do it here ..

	PIXELFORMATDESCRIPTOR* ppfd;
	int pixelformat;

	PIXELFORMATDESCRIPTOR pfd = {
	sizeof(PIXELFORMATDESCRIPTOR),  //  size of this pfd 
	1,                     // version number 
	PFD_DRAW_TO_WINDOW |   // support window 
	PFD_SUPPORT_OPENGL |   // support OpenGL 
	PFD_GENERIC_FORMAT |
	PFD_DOUBLEBUFFER,      // double buffered 
	PFD_TYPE_RGBA,         // RGBA type 
	32,                    // 32-bit color depth 
	0, 0, 0, 0, 0, 0,      // color bits ignored 
	8,                     // no alpha buffer 
	0,                     // shift bit ignored 
	8,                     // no accumulation buffer 
	0, 0, 0, 0,            // accum bits ignored 
	64,                    // 64-bit z-buffer	 
	8,                     // stencil buffer 
	8,                     // auxiliary buffer 
	PFD_MAIN_PLANE,        // main layer 
	0,                     // reserved 
	0, 0, 0                // layer masks ignored 
	};


	ppfd = &pfd;


	if ((pixelformat = ChoosePixelFormat(hdc, ppfd)) == 0)
	{
		error_handler(DISKVIEW_GL_ERROR, const_cast<char*>(__FILE__), __LINE__);
		return false;
	}


	if (SetPixelFormat(hdc, pixelformat, ppfd) == FALSE)
	{
		error_handler(DISKVIEW_INIT_ERROR, const_cast<char*>(__FILE__), __LINE__);
		return false;
	}

	return true;

}

//*****************************************************************************************//
// init the view
//*****************************************************************************************//

bool diskview_mfc_t::init_view(HDC out_dc)
{

	output_dc = out_dc;

	setpxlformat(output_dc);

	if (!(gl_render_context = wglCreateContext(output_dc)))
	{
		error_handler(DISKVIEW_CONTEXT_ERROR, const_cast<char*>(__FILE__), __LINE__);
		return false;
	}



	// not here ...
	if (!wglMakeCurrent(output_dc, gl_render_context))
	{
		error_handler(DISKVIEW_CONTEXT_ERROR, const_cast<char*>(__FILE__), __LINE__);
		return false;
	}

	init_gl();

	if (!wglMakeCurrent(NULL, NULL))
	{
		error_handler(DISKVIEW_CONTEXT_ERROR, const_cast<char*>(__FILE__), __LINE__);
		return false;
	}


	return true;
}


//*****************************************************************************************//
// OpenGL View initialization (and configuration)
//*****************************************************************************************//

void diskview_mfc_t::init_gl(void)
{
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
}


//*****************************************************************************************//
// resize the display should be run from a WM_RESIZE event ...
//*****************************************************************************************//

void diskview_mfc_t::resize(HDC out_dc, long int x, long int y)
{

	if (x != 0 || y != 0)
	{


		if (!wglMakeCurrent(output_dc, gl_render_context))
		{
			error_handler(DISKVIEW_CONTEXT_ERROR, const_cast<char*>(__FILE__), __LINE__);
			return;
		}

		height = (y != 0) ? y : 1; // must not be 0 ...
		width = x;


		if (boolfunc) configure_boolfunc();
		else compute_back_plane();

		resize(x, y);

		if (!wglMakeCurrent(NULL, NULL))
		{
			error_handler(DISKVIEW_CONTEXT_ERROR, const_cast<char*>(__FILE__), __LINE__);
			return;
		}
	}
}

//*****************************************************************************************//
// resize the display should be run from a WM_RESIZE event ...
//*****************************************************************************************//


void diskview_mfc_t::resize(long int x, long int y)
{


	glViewport(0, 0, width, height);					// Reset The Current Viewport


	// it is not the better way to do this, but it is temporary ...

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	//glOrtho(-2.0, 2.0, -2.0, 2.0, -1.0, 1.0);

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(fovy, (GLfloat)width / (GLfloat)height, front, back);

	glMatrixMode(GL_MODELVIEW);						// Select The Modelview Matrix
	glLoadIdentity();							// Reset The Modelview Matrix



}

//*****************************************************************************************//
// destroy the context (used for destroying the windows mainly
//*****************************************************************************************//

void diskview_mfc_t::destroy(void)
{
	if (gl_render_context) ::wglDeleteContext(gl_render_context);
}

//*****************************************************************************************//
// configure the boolfunc display parameters
// if is in 3d set it to recalculate in 3d ... (not yet implemented)
//*****************************************************************************************//

void diskview_mfc_t::configure_boolfunc(bool _3d)
{
	if (!boolfunc) return;
	if (!_3d && !boolfunc->is_3d())
	{
		// we render the disk in 2d, so we choose to render it in the middle part
		// of the space  defined by (back + front) / 2
		// fact is that we have to get the max size on this middle space ...
		// for simple purpose, one value will be equal to 1.0f in coordinates
		// so that we could easyly center it ...
		float max_xsize;
		int c;

		max_xsize = (float)(((c = boolfunc->get_max_xsize()) & 1) ? c : c + 2);

		// given front and fovy, let's calculate back

		// here this 4 is strange but works, let it be ...
		back = (((float)height) * max_xsize) / (((float)width) * ((float)tan(fovy * M_PI / 360.0f))) + front;

		// now lets calculate the appropriate height of each disks

		boolfunc->set_height(max_xsize * ((float)height) / ((float)width * boolfunc->get_size()));

		// after defining front and back we redefine the back_plane coordinates

		compute_back_plane();

	}
	else {
		// not yet done ... do be seen.
	}
}

//*****************************************************************************************//
// recalculate the coordinates of the background plane
//*****************************************************************************************//


void diskview_mfc_t::compute_back_plane(void)
{
	back_plane[0].z = back_plane[1].z = back_plane[2].z = back_plane[3].z = -back - (front - back) * 0.01f;
	back_plane[0].y = back_plane[1].y = back * (float)tan(fovy * M_PI / 360.0f);
	back_plane[2].y = back_plane[3].y = -back_plane[1].y;
	back_plane[0].x = back_plane[3].x = ((float)width) * back_plane[0].y / ((float)height);
	back_plane[1].x = back_plane[2].x = -back_plane[0].x;

	screen_pos[1].y = -(screen_pos[0].y = (back + front) * (float)tan(fovy * M_PI / 360.0f) / 2.0f);
	screen_pos[0].x = -(screen_pos[1].x = ((float)width) * screen_pos[0].y / ((float)height));
}