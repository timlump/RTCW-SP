/*
===========================================================================

Return to Castle Wolfenstein single player GPL Source Code
Copyright (C) 1999-2010 id Software LLC, a ZeniMax Media company. 

This file is part of the Return to Castle Wolfenstein single player GPL Source Code (RTCW SP Source Code).  

RTCW SP Source Code is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

RTCW SP Source Code is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with RTCW SP Source Code.  If not, see <http://www.gnu.org/licenses/>.

In addition, the RTCW SP Source Code is also subject to certain additional terms. You should have received a copy of these additional terms immediately following the terms and conditions of the GNU General Public License which accompanied the RTCW SP Source Code.  If not, please request a copy in writing from id Software at the address below.

If you have questions concerning this license or the applicable additional terms, you may contact in writing id Software LLC, c/o ZeniMax Media Inc., Suite 120, Rockville, Maryland 20850 USA.

===========================================================================
*/

/*
** QGL_WIN.C
**
** This file implements the operating system binding of GL to QGL function
** pointers.  When doing a port of Quake3 you must implement the following
** two functions:
**
** QGL_Init() - loads libraries, assigns function pointers, etc.
** QGL_Shutdown() - unloads libraries, NULLs function pointers
*/
#include <float.h>
#include "../renderer/tr_local.h"
#include "glw_win.h"

int ( WINAPI * qwglChoosePixelFormat )( HDC, CONST PIXELFORMATDESCRIPTOR * );
int ( WINAPI * qwglDescribePixelFormat )( HDC, int, UINT, LPPIXELFORMATDESCRIPTOR );
int ( WINAPI * qwglGetPixelFormat )( HDC );
BOOL ( WINAPI * qwglSetPixelFormat )( HDC, int, CONST PIXELFORMATDESCRIPTOR * );
BOOL ( WINAPI * qwglSwapBuffers )( HDC );

BOOL ( WINAPI * qwglCopyContext )( HGLRC, HGLRC, UINT );
HGLRC ( WINAPI * qwglCreateContext )( HDC );
HGLRC ( WINAPI * qwglCreateLayerContext )( HDC, int );
BOOL ( WINAPI * qwglDeleteContext )( HGLRC );
HGLRC ( WINAPI * qwglGetCurrentContext )( VOID );
HDC ( WINAPI * qwglGetCurrentDC )( VOID );
PROC ( WINAPI * qwglGetProcAddress )( LPCSTR );
BOOL ( WINAPI * qwglMakeCurrent )( HDC, HGLRC );
BOOL ( WINAPI * qwglShareLists )( HGLRC, HGLRC );
BOOL ( WINAPI * qwglUseFontBitmaps )( HDC, DWORD, DWORD, DWORD );

BOOL ( WINAPI * qwglUseFontOutlines )( HDC, DWORD, DWORD, DWORD, FLOAT,
				FLOAT, int, LPGLYPHMETRICSFLOAT );

BOOL ( WINAPI * qwglDescribeLayerPlane )( HDC, int, int, UINT,
				LPLAYERPLANEDESCRIPTOR );
int ( WINAPI * qwglSetLayerPaletteEntries )( HDC, int, int, int,
											 CONST COLORREF * );
int ( WINAPI * qwglGetLayerPaletteEntries )( HDC, int, int, int,
			   COLORREF * );
BOOL ( WINAPI * qwglRealizeLayerPalette )( HDC, int, BOOL );
BOOL ( WINAPI * qwglSwapLayerBuffers )( HDC, UINT );

void ( APIENTRY * qglAlphaFunc )( GLenum func, GLclampf ref );
void ( APIENTRY * qglArrayElement )( GLint i );
void ( APIENTRY * qglBegin )( GLenum mode );
void ( APIENTRY * qglBindTexture )( GLenum target, GLuint texture );
void ( APIENTRY * qglBitmap )( GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, const GLubyte *bitmap );
void ( APIENTRY * qglBlendFunc )( GLenum sfactor, GLenum dfactor );
void ( APIENTRY * qglCallList )( GLuint list );
void ( APIENTRY * qglCallLists )( GLsizei n, GLenum type, const GLvoid *lists );
void ( APIENTRY * qglClear )( GLbitfield mask );
void ( APIENTRY * qglClearColor )( GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha );
void ( APIENTRY * qglClearDepth )( GLclampd depth );
void ( APIENTRY * qglClearStencil )( GLint s );
void ( APIENTRY * qglClipPlane )( GLenum plane, const GLdouble *equation );
void ( APIENTRY * qglColor3f )( GLfloat red, GLfloat green, GLfloat blue );
void ( APIENTRY * qglColor3fv )( const GLfloat *v );
void ( APIENTRY * qglColor4f )( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha );
void ( APIENTRY * qglColor4ubv )( const GLubyte *v );
void ( APIENTRY * qglColorMask )( GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha );
void ( APIENTRY * qglColorPointer )( GLint size, GLenum type, GLsizei stride, const GLvoid *pointer );
void ( APIENTRY * qglCullFace )( GLenum mode );
void ( APIENTRY * qglDeleteTextures )( GLsizei n, const GLuint *textures );
void ( APIENTRY * qglDepthFunc )( GLenum func );
void ( APIENTRY * qglDepthMask )( GLboolean flag );
void ( APIENTRY * qglDepthRange )( GLclampd zNear, GLclampd zFar );
void ( APIENTRY * qglDisable )( GLenum cap );
void ( APIENTRY * qglDisableClientState )( GLenum array );
void ( APIENTRY * qglDrawBuffer )( GLenum mode );
void ( APIENTRY * qglDrawElements )( GLenum mode, GLsizei count, GLenum type, const GLvoid *indices );
void ( APIENTRY * qglEnable )( GLenum cap );
void ( APIENTRY * qglEnableClientState )( GLenum array );
void ( APIENTRY * qglEnd )( void );
void ( APIENTRY * qglFinish )( void );
void ( APIENTRY * qglFogf )( GLenum pname, GLfloat param );
void ( APIENTRY * qglFogfv )( GLenum pname, const GLfloat *params );
void ( APIENTRY * qglFogi )( GLenum pname, GLint param );
GLenum ( APIENTRY * qglGetError )( void );
void ( APIENTRY * qglGetFloatv )( GLenum pname, GLfloat *params );
void ( APIENTRY * qglGetIntegerv )( GLenum pname, GLint *params );
const GLubyte * ( APIENTRY * qglGetString )(GLenum name);
void ( APIENTRY * qglHint )( GLenum target, GLenum mode );
void ( APIENTRY * qglLineWidth )( GLfloat width );
void ( APIENTRY * qglLoadIdentity )( void );
void ( APIENTRY * qglLoadMatrixf )( const GLfloat *m );
void ( APIENTRY * qglMatrixMode )( GLenum mode );

void ( APIENTRY * qglNormalPointer )( GLenum type, GLsizei stride, const GLvoid *pointer );
void ( APIENTRY * qglOrtho )( GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar );
void ( APIENTRY * qglPointSize )( GLfloat size );
void ( APIENTRY * qglPolygonMode )( GLenum face, GLenum mode );
void ( APIENTRY * qglPolygonOffset )( GLfloat factor, GLfloat units );
void ( APIENTRY * qglPopMatrix )( void );
void ( APIENTRY * qglPushMatrix )( void );
void ( APIENTRY * qglRasterPos3fv )( const GLfloat *v );
void ( APIENTRY * qglReadPixels )( GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels );
void ( APIENTRY * qglScissor )( GLint x, GLint y, GLsizei width, GLsizei height );
void ( APIENTRY * qglShadeModel )( GLenum mode );
void ( APIENTRY * qglStencilFunc )( GLenum func, GLint ref, GLuint mask );
void ( APIENTRY * qglStencilMask )( GLuint mask );
void ( APIENTRY * qglStencilOp )( GLenum fail, GLenum zfail, GLenum zpass );
void ( APIENTRY * qglTexCoord2f )( GLfloat s, GLfloat t );
void ( APIENTRY * qglTexCoord2fv )( const GLfloat *v );
void ( APIENTRY * qglTexCoordPointer )( GLint size, GLenum type, GLsizei stride, const GLvoid *pointer );
void ( APIENTRY * qglTexEnvf )( GLenum target, GLenum pname, GLfloat param );
void ( APIENTRY * qglTexImage2D )( GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels );
void ( APIENTRY * qglTexParameterf )( GLenum target, GLenum pname, GLfloat param );
void ( APIENTRY * qglTexParameterfv )( GLenum target, GLenum pname, const GLfloat *params );
void ( APIENTRY * qglTexSubImage2D )( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels );
void ( APIENTRY * qglTranslatef )( GLfloat x, GLfloat y, GLfloat z );
void ( APIENTRY * qglVertex2f )( GLfloat x, GLfloat y );
void ( APIENTRY * qglVertex3f )( GLfloat x, GLfloat y, GLfloat z );
void ( APIENTRY * qglVertex3fv )( const GLfloat *v );
void ( APIENTRY * qglVertexPointer )( GLint size, GLenum type, GLsizei stride, const GLvoid *pointer );
void ( APIENTRY * qglViewport )( GLint x, GLint y, GLsizei width, GLsizei height );

void glAlphaFunc_impl(GLenum func, GLclampf ref)
{
	glAlphaFunc(func, ref);
}

void glArrayElement_impl(GLint i)
{
	glArrayElement(i);
}

void glBegin_impl(GLenum mode)
{
	glBegin(mode);
}

void glBindTexture_impl(GLenum target, GLuint texture)
{
	glBindTexture(target, texture);
}

void glBitmap_impl(GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, const GLubyte* bitmap)
{
	glBitmap(width, height, xorig, yorig, xmove, ymove, bitmap);
}

void glBlendFunc_impl(GLenum sfactor, GLenum dfactor)
{
	glBlendFunc(sfactor, dfactor);
}

void glCallList_impl(GLuint list)
{
	glCallList(list);
}

void glCallLists_impl(GLsizei n, GLenum type, const GLvoid* lists)
{
	glCallLists(n, type, lists);
}

void glClear_impl(GLbitfield mask)
{
	glClear(mask);
}

void glClearColor_impl(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
	glClearColor(red, green, blue, alpha);
}

void glClearDepth_impl(GLclampd depth)
{
	glClearDepth(depth);
}

void glClearIndex_impl(GLfloat c)
{
	glClearIndex(c);
}

void glClearStencil_impl(GLint s)
{
	glClearStencil(s);
}

void glClipPlane_impl(GLenum plane, const GLdouble* equation)
{
	glClipPlane(plane, equation);
}

void glColor3f_impl(GLfloat red, GLfloat green, GLfloat blue)
{
	glColor3f(red, green, blue);
}

void glColor3fv_impl(const GLfloat* v)
{
	glColor3fv(v);
}

void glColor3ubv_impl(const GLubyte* v)
{
	glColor3ubv(v);
}

void glColor4f_impl(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	glColor4f(red, green, blue, alpha);
}

void glColor4ubv_impl(const GLubyte* v)
{
	glColor4ubv(v);
}

void glColorMask_impl(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
	glColorMask(red, green, blue, alpha);
}

void glColorPointer_impl(GLint size, GLenum type, GLsizei stride, const GLvoid* pointer)
{
	glColorPointer(size, type, stride, pointer);
}

void glCullFace_impl(GLenum mode)
{
	glCullFace(mode);
}

void glDeleteTextures_impl(GLsizei n, const GLuint* textures)
{
	glDeleteTextures(n, textures);
}

void glDepthFunc_impl(GLenum func)
{
	glDepthFunc(func);
}

void glDepthMask_impl(GLboolean flag)
{
	glDepthMask(flag);
}

void glDepthRange_impl(GLclampd zNear, GLclampd zFar)
{
	glDepthRange(zNear, zFar);
}

void glDisable_impl(GLenum cap)
{
	glDisable(cap);
}

void glDisableClientState_impl(GLenum _array)
{
	glDisableClientState(_array);
}

void glDrawBuffer_impl(GLenum mode)
{
	glDrawBuffer(mode);
}

void glDrawElements_impl(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices)
{
	glDrawElements(mode, count, type, indices);
}

void glEnable_impl(GLenum cap)
{
	glEnable(cap);
}

void glEnableClientState_impl(GLenum _array)
{
	glEnableClientState(_array);
}

void glEnd_impl(void)
{
	glEnd();
}

void glFinish_impl(void)
{
	glFinish();
}

void glFogf_impl(GLenum pname, GLfloat param)
{
	glFogf(pname, param);
}

void glFogfv_impl(GLenum pname, const GLfloat* params)
{
	glFogfv(pname, params);
}

void glFogi_impl(GLenum pname, GLint param)
{
	glFogi(pname, param);
}

GLenum glGetError_impl(void)
{
	return glGetError();
}

void glGetFloatv_impl(GLenum pname, GLfloat* params)
{
	glGetFloatv(pname, params);
}

void glGetIntegerv_impl(GLenum pname, GLint* params)
{
	glGetIntegerv(pname, params);
}

const GLubyte* glGetString_impl(GLenum name)
{
	return glGetString(name);
}

void glHint_impl(GLenum target, GLenum mode)
{
	glHint(target, mode);
}

void glLineWidth_impl(GLfloat width)
{
	glLineWidth(width);
}

void glLoadIdentity_impl(void)
{
	glLoadIdentity();
}

void glLoadMatrixf_impl(const GLfloat* m)
{
	glLoadMatrixf(m);
}

void glMatrixMode_impl(GLenum mode)
{
	glMatrixMode(mode);
}

void glNormalPointer_impl(GLenum type, GLsizei stride, const GLvoid* pointer)
{
	glNormalPointer(type, stride, pointer);
}

void glOrtho_impl(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar)
{
	glOrtho(left, right, bottom, top, zNear, zFar);
}

void glPointSize_impl(GLfloat size)
{
	glPointSize(size);
}

void glPolygonMode_impl(GLenum face, GLenum mode)
{
	glPolygonMode(face, mode);
}

void glPolygonOffset_impl(GLfloat factor, GLfloat units)
{
	glPolygonOffset(factor, units);
}

void glPopMatrix_impl(void)
{
	glPopMatrix();
}

void glPushMatrix_impl(void)
{
	glPushMatrix();
}

void glRasterPos3fv_impl(const GLfloat* v)
{
	glRasterPos3fv(v);
}

void glReadPixels_impl(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* pixels)
{
	glReadPixels(x, y, width, height, format, type, pixels);
}

void glScissor_impl(GLint x, GLint y, GLsizei width, GLsizei height)
{
	glScissor(x, y, width, height);
}

void glShadeModel_impl(GLenum mode)
{
	glShadeModel(mode);
}

void glStencilFunc_impl(GLenum func, GLint ref, GLuint mask)
{
	glStencilFunc(func, ref, mask);
}

void glStencilMask_impl(GLuint mask)
{
	glStencilMask(mask);
}

void glStencilOp_impl(GLenum fail, GLenum zfail, GLenum zpass)
{
	glStencilOp(fail, zfail, zpass);
}

void glTexCoord2f_impl(GLfloat s, GLfloat t)
{
	glTexCoord2f(s, t);
}

void glTexCoord2fv_impl(const GLfloat* v)
{
	glTexCoord3fv(v);
}

void glTexCoordPointer_impl(GLint size, GLenum type, GLsizei stride, const GLvoid* pointer)
{
	glTexCoordPointer(size, type, stride, pointer);
}

void glTexEnvf_impl(GLenum target, GLenum pname, GLfloat param)
{
	glTexEnvf(target, pname, param);
}

void glTexImage2D_impl(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels)
{
	glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
}

void glTexParameterf_impl(GLenum target, GLenum pname, GLfloat param)
{
	glTexParameterf(target, pname, param);
}

void glTexParameterfv_impl(GLenum target, GLenum pname, const GLfloat* params)
{
	glTexParameterfv(target, pname, params);
}

void glTexSubImage2D_impl(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels)
{
	glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
}

void glTranslatef_impl(GLfloat x, GLfloat y, GLfloat z)
{
	glTranslatef(x, y, z);
}

void glVertex2f_impl(GLfloat x, GLfloat y)
{
	glVertex2f(x, y);
}

void glVertex3f_impl(GLfloat x, GLfloat y, GLfloat z)
{
	glVertex3f(x, y, z);
}

void glVertex3fv_impl(const GLfloat* v)
{
	glVertex3fv(v);
}

void glVertexPointer_impl(GLint size, GLenum type, GLsizei stride, const GLvoid* pointer)
{
	glVertexPointer(size, type, stride, pointer);
}

void glViewport_impl(GLint x, GLint y, GLsizei width, GLsizei height)
{
	glViewport(x, y, width, height);
}

/*
** QGL_Shutdown
**
** Unloads the specified DLL then nulls out all the proc pointers.  This
** is only called during a hard shutdown of the OGL subsystem (e.g. vid_restart).
*/
void QGL_Shutdown( void ) {
	ri.Printf( PRINT_ALL, "...shutting down QGL\n" );

	if ( glw_state.hinstOpenGL ) {
		ri.Printf( PRINT_ALL, "...unloading OpenGL DLL\n" );
		FreeLibrary( glw_state.hinstOpenGL );
	}

	glw_state.hinstOpenGL = NULL;

	qglAlphaFunc                 = NULL;
	qglArrayElement              = NULL;
	qglBegin                     = NULL;
	qglBindTexture               = NULL;
	qglBitmap                    = NULL;
	qglBlendFunc                 = NULL;
	qglCallList                  = NULL;
	qglCallLists                 = NULL;
	qglClear                     = NULL;
	qglClearColor                = NULL;
	qglClearDepth                = NULL;
	qglClearStencil              = NULL;
	qglClipPlane                 = NULL;
	qglColor3f                   = NULL;
	qglColor3fv                  = NULL;
	qglColor4f                   = NULL;
	qglColor4ubv                 = NULL;
	qglColorMask                 = NULL;
	qglColorPointer              = NULL;
	qglCullFace                  = NULL;
	qglDeleteTextures            = NULL;
	qglDepthFunc                 = NULL;
	qglDepthMask                 = NULL;
	qglDepthRange                = NULL;
	qglDisable                   = NULL;
	qglDisableClientState        = NULL;
	qglDrawBuffer                = NULL;
	qglDrawElements              = NULL;
	qglEnable                    = NULL;
	qglEnableClientState         = NULL;
	qglEnd                       = NULL;
	qglFinish                    = NULL;
	qglFogf                      = NULL;
	qglFogfv                     = NULL;
	qglFogi                      = NULL;
	qglGetError                  = NULL;
	qglGetFloatv                 = NULL;
	qglGetIntegerv               = NULL;
	qglGetString                 = NULL;
	qglHint                      = NULL;
	qglLineWidth                 = NULL;
	qglLoadIdentity              = NULL;
	qglLoadMatrixf               = NULL;
	qglMatrixMode                = NULL;
	qglNormalPointer             = NULL;
	qglOrtho                     = NULL;
	qglPointSize                 = NULL;
	qglPolygonMode               = NULL;
	qglPolygonOffset             = NULL;
	qglPopMatrix                 = NULL;
	qglPushMatrix                = NULL;
	qglRasterPos3fv              = NULL;
	qglReadPixels                = NULL;
	qglScissor                   = NULL;
	qglShadeModel                = NULL;
	qglStencilFunc               = NULL;
	qglStencilMask               = NULL;
	qglStencilOp                 = NULL;
	qglTexCoord2f                = NULL;
	qglTexCoord2fv               = NULL;
	qglTexCoordPointer           = NULL;
	qglTexEnvf                   = NULL;
	qglTexImage2D                = NULL;
	qglTexParameterf             = NULL;
	qglTexParameterfv            = NULL;
	qglTexSubImage2D             = NULL;
	qglTranslatef                = NULL;
	qglVertex3f                  = NULL;
	qglVertex3fv                 = NULL;
	qglVertexPointer             = NULL;
	qglViewport                  = NULL;

	qwglCopyContext              = NULL;
	qwglCreateContext            = NULL;
	qwglCreateLayerContext       = NULL;
	qwglDeleteContext            = NULL;
	qwglDescribeLayerPlane       = NULL;
	qwglGetCurrentContext        = NULL;
	qwglGetCurrentDC             = NULL;
	qwglGetLayerPaletteEntries   = NULL;
	qwglGetProcAddress           = NULL;
	qwglMakeCurrent              = NULL;
	qwglRealizeLayerPalette      = NULL;
	qwglSetLayerPaletteEntries   = NULL;
	qwglShareLists               = NULL;
	qwglSwapLayerBuffers         = NULL;
	qwglUseFontBitmaps           = NULL;
	qwglUseFontOutlines          = NULL;

	qwglChoosePixelFormat        = NULL;
	qwglDescribePixelFormat      = NULL;
	qwglGetPixelFormat           = NULL;
	qwglSetPixelFormat           = NULL;
	qwglSwapBuffers              = NULL;
}

#define GR_NUM_BOARDS 0x0f

#   pragma warning (disable : 4113 4133 4047 )
#   define GPA( a ) GetProcAddress( glw_state.hinstOpenGL, a )

/*
** QGL_Init
**
** This is responsible for binding our qgl function pointers to
** the appropriate GL stuff.  In Windows this means doing a
** LoadLibrary and a bunch of calls to GetProcAddress.  On other
** operating systems we need to do the right thing, whatever that
** might be.
*/
qboolean QGL_Init( const char *dllname ) {
	char systemDir[1024];
	char libName[1024];

	GetSystemDirectory( systemDir, sizeof( systemDir ) );

	assert( glw_state.hinstOpenGL == 0 );

	ri.Printf( PRINT_ALL, "...initializing QGL\n" );

	// NOTE: this assumes that 'dllname' is lower case (and it should be)!
	if ( dllname[0] != '!' && strstr( "dllname", ".dll" ) == NULL ) {
		Com_sprintf( libName, sizeof( libName ), "%s\\%s", systemDir, dllname );
	} else
	{
		Q_strncpyz( libName, dllname, sizeof( libName ) );
	}

	ri.Printf( PRINT_ALL, "...calling LoadLibrary( '%s.dll' ): ", libName );

	if ( ( glw_state.hinstOpenGL = LoadLibrary( dllname ) ) == 0 ) {
		ri.Printf( PRINT_ALL, "failed\n" );
		return qfalse;
	}
	ri.Printf( PRINT_ALL, "succeeded\n" );

	qglAlphaFunc                 = glAlphaFunc_impl;
	qglArrayElement              = glArrayElement_impl;
	qglBegin                     = glBegin_impl;
	qglBindTexture               = glBindTexture_impl;
	qglBitmap                    = glBitmap_impl;
	qglBlendFunc                 = glBlendFunc_impl;
	qglCallList                  = glCallList_impl;
	qglCallLists                 = glCallLists_impl;
	qglClear                     = glClear_impl;
	qglClearColor                = glClearColor_impl;
	qglClearDepth                = glClearDepth_impl;
	qglClearStencil              = glClearStencil_impl;
	qglClipPlane                 = glClipPlane_impl;
	qglColor3f                   = glColor3f_impl;
	qglColor3fv                  = glColor3fv_impl;
	qglColor4f                   = glColor4f_impl;
	qglColor4ubv                 = glColor4ubv_impl;
	qglColorMask                 = glColorMask_impl;
	qglColorPointer              = glColorPointer_impl;
	qglCullFace                  = glCullFace_impl;
	qglDeleteTextures            = glDeleteTextures_impl;
	qglDepthFunc                 = glDepthFunc_impl;
	qglDepthMask                 = glDepthMask_impl;
	qglDepthRange                = glDepthRange_impl;
	qglDisable                   = glDisable_impl;
	qglDisableClientState        = glDisableClientState_impl;
	qglDrawBuffer                = glDrawBuffer_impl;
	qglDrawElements              = glDrawElements_impl;
	qglEnable                    = glEnable_impl;
	qglEnableClientState         = glEnableClientState_impl;
	qglEnd                       = glEnd_impl;
	qglFinish                    = glFinish_impl;
	qglFogf                      = glFogf_impl;
	qglFogfv                     = glFogfv_impl;
	qglFogi                      = glFogi_impl;
	qglGetError                  = glGetError_impl;
	qglGetFloatv                 = glGetFloatv_impl;
	qglGetIntegerv               = glGetIntegerv_impl;
	qglGetString                 = glGetString_impl;
	qglHint                      = glHint_impl;
	qglLineWidth                 = glLineWidth_impl;
	qglLoadIdentity              = glLoadIdentity_impl;
	qglLoadMatrixf               = glLoadMatrixf_impl;
	qglMatrixMode                = glMatrixMode_impl;
	qglNormalPointer             = glNormalPointer_impl;
	qglOrtho                     = glOrtho_impl;
	qglPointSize                 = glPointSize_impl;
	qglPolygonMode               = glPolygonMode_impl;
	qglPolygonOffset             = glPolygonOffset_impl;
	qglPopMatrix                 = glPopMatrix_impl;
	qglPushMatrix                = glPushMatrix_impl;
	qglRasterPos3fv              = glRasterPos3fv_impl;
	qglReadPixels                = glReadPixels_impl;
	qglScissor                   = glScissor_impl;
	qglShadeModel                = glShadeModel_impl;
	qglStencilFunc               = glStencilFunc_impl;
	qglStencilMask               = glStencilMask_impl;
	qglStencilOp                 = glStencilOp_impl;
	qglTexCoord2f                = glTexCoord2f_impl;
	qglTexCoord2fv               = glTexCoord2fv_impl;
	qglTexCoordPointer           = glTexCoordPointer_impl;
	qglTexEnvf                   = glTexEnvf_impl;
	qglTexImage2D                = glTexImage2D_impl;
	qglTexParameterf             = glTexParameterf_impl;
	qglTexParameterfv            = glTexParameterfv_impl;
	qglTexSubImage2D             = glTexSubImage2D_impl;
	qglTranslatef                = glTranslatef_impl;
	qglVertex2f                  = glVertex2f_impl;
	qglVertex3f                  = glVertex3f_impl;
	qglVertex3fv                 = glVertex3fv_impl;
	qglVertexPointer             = glVertexPointer_impl;
	qglViewport                  = glViewport_impl;

	qwglCopyContext             = wglCopyContext;
	qwglCreateContext           = wglCreateContext;
	qwglCreateLayerContext      = wglCreateLayerContext;
	qwglDeleteContext           = wglDeleteContext;
	qwglDescribeLayerPlane      = wglDescribeLayerPlane;
	qwglGetCurrentContext       = wglGetCurrentContext;
	qwglGetCurrentDC            = wglGetCurrentDC;
	qwglGetLayerPaletteEntries  = wglGetLayerPaletteEntries;
	qwglGetProcAddress          = wglGetProcAddress;
	qwglMakeCurrent             = wglMakeCurrent;
	qwglRealizeLayerPalette     = wglRealizeLayerPalette;
	qwglSetLayerPaletteEntries  = wglSetLayerPaletteEntries;
	qwglShareLists              = wglShareLists;
	qwglSwapLayerBuffers        = wglSwapLayerBuffers;
	qwglUseFontBitmaps          = wglUseFontBitmapsA;
	qwglUseFontOutlines         = wglUseFontOutlinesA;

	qwglChoosePixelFormat       = GPA("wglChoosePixelFormat");
	qwglDescribePixelFormat     = GPA("wglDescribePixelFormat");
	qwglGetPixelFormat          = GPA("wglGetPixelFormat");
	qwglSetPixelFormat          = GPA("wglSetPixelFormat");
	qwglSwapBuffers             = GPA("wglSwapBuffers");

	return qtrue;
}

#pragma warning (default : 4113 4133 4047 )



