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

int ( WINAPI * qwglSwapIntervalEXT )( int interval );
BOOL ( WINAPI * qwglGetDeviceGammaRamp3DFX )( HDC, LPVOID );
BOOL ( WINAPI * qwglSetDeviceGammaRamp3DFX )( HDC, LPVOID );

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

void glBegin_impl(GLenum mode)
{
	glBegin(mode);
}

void glEnd_impl()
{
	glEnd();
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

	qglAlphaFunc                 = glAlphaFunc;
	qglArrayElement              = glArrayElement;
	qglBegin                     = glBegin_impl;
	qglBindTexture               = glBindTexture;
	qglBitmap                    = glBitmap;
	qglBlendFunc                 = glBlendFunc;
	qglCallList                  = glCallList;
	qglCallLists                 = glCallLists;
	qglClear                     = glClear;
	qglClearColor                = glClearColor;
	qglClearDepth                = glClearDepth;
	qglClearStencil              = glClearStencil;
	qglClipPlane                 = glClipPlane;
	qglColor3f                   = glColor3f;
	qglColor3fv                  = glColor3fv;
	qglColor4f                   = glColor4f;
	qglColor4ubv                 = glColor4ubv;
	qglColorMask                 = glColorMask;
	qglColorPointer              = glColorPointer;
	qglCullFace                  = glCullFace;
	qglDeleteTextures            = glDeleteTextures;
	qglDepthFunc                 = glDepthFunc;
	qglDepthMask                 = glDepthMask;
	qglDepthRange                = glDepthRange;
	qglDisable                   = glDisable;
	qglDisableClientState        = glDisableClientState;
	qglDrawBuffer                = glDrawBuffer;
	qglDrawElements              = glDrawElements;
	qglEnable                    = glEnable;
	qglEnableClientState         = glEnableClientState;
	qglEnd                       = glEnd_impl;
	qglFinish                    = glFinish;
	qglFogf                      = glFogf;
	qglFogfv                     = glFogfv;
	qglFogi                      = glFogi;
	qglGetError                  = ( GLenum ( __stdcall * )(void) )glGetError;
	qglGetFloatv                 = glGetFloatv;
	qglGetIntegerv               = glGetIntegerv;
	qglGetString                 = glGetString;
	qglHint                      = glHint;
	qglLineWidth                 = glLineWidth;
	qglLoadIdentity              = glLoadIdentity;
	qglLoadMatrixf               = glLoadMatrixf;
	qglMatrixMode                = glMatrixMode;
	qglNormalPointer             = glNormalPointer;
	qglOrtho                     = glOrtho;
	qglPointSize                 = glPointSize;
	qglPolygonMode               = glPolygonMode;
	qglPolygonOffset             = glPolygonOffset;
	qglPopMatrix                 = glPopMatrix;
	qglPushMatrix                = glPushMatrix;
	qglRasterPos3fv              = glRasterPos3fv;
	qglReadPixels                = glReadPixels;
	qglScissor                   = glScissor;
	qglShadeModel                = glShadeModel;
	qglStencilFunc               = glStencilFunc;
	qglStencilMask               = glStencilMask;
	qglStencilOp                 = glStencilOp;
	qglTexCoord2f                = glTexCoord2f;
	qglTexCoord2fv               = glTexCoord2fv;
	qglTexCoordPointer           = glTexCoordPointer;
	qglTexEnvf                   = glTexEnvf;
	qglTexImage2D                = glTexImage2D;
	qglTexParameterf             = glTexParameterf;
	qglTexParameterfv            = glTexParameterfv;
	qglTexSubImage2D             = glTexSubImage2D;
	qglTranslatef                = glTranslatef;
	qglVertex2f                  = glVertex2f;
	qglVertex3f                  = glVertex3f;
	qglVertex3fv                 = glVertex3fv;
	qglVertexPointer             = glVertexPointer;
	qglViewport                  = glViewport;

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

	qwglSwapIntervalEXT         = 0;
	qglActiveTextureARB         = 0;
	qglClientActiveTextureARB   = 0;
	qglMultiTexCoord2fARB       = 0;
	qglLockArraysEXT            = 0;
	qglUnlockArraysEXT          = 0;

	qglPNTrianglesiATI          = 0;    // ATI truform
	qglPNTrianglesfATI          = 0;    // ATI truform

	qwglGetDeviceGammaRamp3DFX  = NULL;
	qwglSetDeviceGammaRamp3DFX  = NULL;

	return qtrue;
}

#pragma warning (default : 4113 4133 4047 )



