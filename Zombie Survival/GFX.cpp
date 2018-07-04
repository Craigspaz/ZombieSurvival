#include "GFX.h"


GFX::GFX()
{
}


GFX::~GFX()
{
}

//void GFX::drawString(float x, float y, std::string text, float r, float g, float b)
//{
//	/const char* str = text.c_str();
//	//glPushMatrix();
//	glRasterPos2f(x, y);
//	glColor4f(r, g, b, 1.0);
//	glDisable(GL_TEXTURE);
//	glDisable(GL_TEXTURE_2D);
//	for (int i = 0; i < sizeof(str); i++)
//	{
//		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)str[i]);
//	}
//	glEnable(GL_TEXTURE_2D);
//	glEnable(GL_TEXTURE);
//	//glPopMatrix();
//}

void GFX::drawString(float x, float y, const char* text, float r, float g, float b)
{
	//glPushMatrix();
	int len;
	glRasterPos2f(x, y);
	glColor4f(r, g, b, 1.0);
	glDisable(GL_TEXTURE);
	glDisable(GL_TEXTURE_2D);
	len = strlen(text);
	for (int i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)text[i]);
	}
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE);
	//glPopMatrix();
}


void GFX::drawRect(float x, float y, float xx, float yy, GLuint texture)
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glPushMatrix();
	//glTranslatef(xx,yy,0);
	glBegin(GL_QUADS);

	glTexCoord2f(0, 0);
	glVertex2f(xx, yy);
	glTexCoord2f(0, 1);
	glVertex2f(xx, y + yy);
	glTexCoord2f(1, 1);
	glVertex2f(x + xx, y + yy);
	glTexCoord2f(1, 0);
	glVertex2f(x + xx, yy);

	glEnd();
	glPopMatrix();
}
void GFX::drawRect(float x, float y, float xx, float yy)
{
	glPushMatrix();
	//glTranslatef(xx,yy,0);
	glBegin(GL_QUADS);

	glVertex2f(xx, yy);
	glVertex2f(xx, y + yy);
	glVertex2f(x + xx, y + yy);
	glVertex2f(x + xx, yy);

	glEnd();
	glPopMatrix();
}
void GFX::drawLine(float x, float y, float xx, float yy, GLuint texture)
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glPushMatrix();
	glBegin(GL_LINES);
	glTexCoord2f(0, 0);
	glVertex2f(x, y);
	glTexCoord2f(1, 1);
	glVertex2f(xx, yy);
	glEnd();
	glPopMatrix();
}
void GFX::drawLine(float x, float y, float xx, float yy)
{
	glPushMatrix();
	glBegin(GL_LINES);
	glVertex2f(x, y);
	glVertex2f(xx, yy);
	glEnd();
	glPopMatrix();
}



void GFX::drawCircle(float x, float y, float r)
{
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++)
	{
		float degInRads = i * (3.14159265358979323846 / 180.0f);
		glVertex2f((cos(degInRads) * r) + x, (sin(degInRads) * r) + y);
	}
	glEnd();
	glPopMatrix();
}
void GFX::drawCircle(float x, float y,float r, GLuint texture)
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++)
	{
		float degInRads = i * (3.14159265358979323846 / 180.0f);
		if (i == 0)
		{
			glTexCoord2f(1, 1);
		}
		else if (i == 3.14159265358979323846/2.0f)
		{
			glTexCoord2f(0, 1);
		}
		else if (i == 3.14159265358979323846)
		{
			glTexCoord2f(0, 0);
		}
		else if (i == (3 * 3.14159265358979323846) / 4)
		{
			glTexCoord2f(1, 0);
		}
		glVertex2f((cos(degInRads) * r) + x, (sin(degInRads) * r) + y);
	}
	glEnd();
	glPopMatrix();
}