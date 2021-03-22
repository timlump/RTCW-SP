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
** QGL.H
*/

#ifndef __QGL_H__
#define __QGL_H__


#pragma warning (disable: 4201)
#pragma warning (disable: 4214)
#pragma warning (disable: 4514)
#pragma warning (disable: 4032)
#pragma warning (disable: 4201)
#pragma warning (disable: 4214)

#include <windows.h>
#include <GL/GL.h>
//#include <angle_gl.h>

typedef double GLclampd;
#define GL_LINE                           0x1B01
#define GL_FILL                           0x1B02
#define GL_RGB5                           0x8050
#define GL_CLAMP                          0x2900
#define GL_EYE_PLANE                      0x2502
#define GL_POLYGON                        0x0009

#ifndef APIENTRY
#define APIENTRY
#endif
#ifndef WINAPI
#define WINAPI
#endif


//===========================================================================

// TTimo: FIXME
// linux needs those prototypes
// GL_VERSION_1_2 is defined after #include <gl.h>
#if !defined( GL_VERSION_1_2 ) || defined( __linux__ )
typedef void ( APIENTRY * PFNGLMULTITEXCOORD1DARBPROC )( GLenum target, GLdouble s );
typedef void ( APIENTRY * PFNGLMULTITEXCOORD1DVARBPROC )( GLenum target, const GLdouble *v );
typedef void ( APIENTRY * PFNGLMULTITEXCOORD1FARBPROC )( GLenum target, GLfloat s );
typedef void ( APIENTRY * PFNGLMULTITEXCOORD1FVARBPROC )( GLenum target, const GLfloat *v );
typedef void ( APIENTRY * PFNGLMULTITEXCOORD1IARBPROC )( GLenum target, GLint s );
typedef void ( APIENTRY * PFNGLMULTITEXCOORD1IVARBPROC )( GLenum target, const GLint *v );
typedef void ( APIENTRY * PFNGLMULTITEXCOORD1SARBPROC )( GLenum target, GLshort s );
typedef void ( APIENTRY * PFNGLMULTITEXCOORD1SVARBPROC )( GLenum target, const GLshort *v );
typedef void ( APIENTRY * PFNGLMULTITEXCOORD2DARBPROC )( GLenum target, GLdouble s, GLdouble t );
typedef void ( APIENTRY * PFNGLMULTITEXCOORD2DVARBPROC )( GLenum target, const GLdouble *v );
typedef void ( APIENTRY * PFNGLMULTITEXCOORD2FARBPROC )( GLenum target, GLfloat s, GLfloat t );
typedef void ( APIENTRY * PFNGLMULTITEXCOORD2FVARBPROC )( GLenum target, const GLfloat *v );
typedef void ( APIENTRY * PFNGLMULTITEXCOORD2IARBPROC )( GLenum target, GLint s, GLint t );
typedef void ( APIENTRY * PFNGLMULTITEXCOORD2IVARBPROC )( GLenum target, const GLint *v );
typedef void ( APIENTRY * PFNGLMULTITEXCOORD2SARBPROC )( GLenum target, GLshort s, GLshort t );
typedef void ( APIENTRY * PFNGLMULTITEXCOORD2SVARBPROC )( GLenum target, const GLshort *v );
typedef void ( APIENTRY * PFNGLMULTITEXCOORD3DARBPROC )( GLenum target, GLdouble s, GLdouble t, GLdouble r );
typedef void ( APIENTRY * PFNGLMULTITEXCOORD3DVARBPROC )( GLenum target, const GLdouble *v );
typedef void ( APIENTRY * PFNGLMULTITEXCOORD3FARBPROC )( GLenum target, GLfloat s, GLfloat t, GLfloat r );
typedef void ( APIENTRY * PFNGLMULTITEXCOORD3FVARBPROC )( GLenum target, const GLfloat *v );
typedef void ( APIENTRY * PFNGLMULTITEXCOORD3IARBPROC )( GLenum target, GLint s, GLint t, GLint r );
typedef void ( APIENTRY * PFNGLMULTITEXCOORD3IVARBPROC )( GLenum target, const GLint *v );
typedef void ( APIENTRY * PFNGLMULTITEXCOORD3SARBPROC )( GLenum target, GLshort s, GLshort t, GLshort r );
typedef void ( APIENTRY * PFNGLMULTITEXCOORD3SVARBPROC )( GLenum target, const GLshort *v );
typedef void ( APIENTRY * PFNGLMULTITEXCOORD4DARBPROC )( GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q );
typedef void ( APIENTRY * PFNGLMULTITEXCOORD4DVARBPROC )( GLenum target, const GLdouble *v );
typedef void ( APIENTRY * PFNGLMULTITEXCOORD4FARBPROC )( GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q );
typedef void ( APIENTRY * PFNGLMULTITEXCOORD4FVARBPROC )( GLenum target, const GLfloat *v );
typedef void ( APIENTRY * PFNGLMULTITEXCOORD4IARBPROC )( GLenum target, GLint s, GLint t, GLint r, GLint q );
typedef void ( APIENTRY * PFNGLMULTITEXCOORD4IVARBPROC )( GLenum target, const GLint *v );
typedef void ( APIENTRY * PFNGLMULTITEXCOORD4SARBPROC )( GLenum target, GLshort s, GLshort t, GLshort r, GLshort q );
typedef void ( APIENTRY * PFNGLMULTITEXCOORD4SVARBPROC )( GLenum target, const GLshort *v );
typedef void ( APIENTRY * PFNGLACTIVETEXTUREARBPROC )( GLenum target );
typedef void ( APIENTRY * PFNGLCLIENTACTIVETEXTUREARBPROC )( GLenum target );
#endif

//===========================================================================
// 
// windows systems use a function pointer for each call so we can load minidrivers

extern void ( APIENTRY * qglAlphaFunc )( GLenum func, GLclampf ref );
extern void ( APIENTRY * qglArrayElement )( GLint i );
extern void ( APIENTRY * qglBegin )( GLenum mode );
extern void ( APIENTRY * qglBindTexture )( GLenum target, GLuint texture );
extern void ( APIENTRY * qglBitmap )( GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, const GLubyte *bitmap );
extern void ( APIENTRY * qglBlendFunc )( GLenum sfactor, GLenum dfactor );
extern void ( APIENTRY * qglCallList )( GLuint list );
extern void ( APIENTRY * qglCallLists )( GLsizei n, GLenum type, const GLvoid *lists );
extern void ( APIENTRY * qglClear )( GLbitfield mask );
extern void ( APIENTRY * qglClearColor )( GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha );
extern void ( APIENTRY * qglClearDepth )( GLclampd depth );
extern void ( APIENTRY * qglClearIndex )( GLfloat c );
extern void ( APIENTRY * qglClearStencil )( GLint s );
extern void ( APIENTRY * qglClipPlane )( GLenum plane, const GLdouble *equation );
extern void ( APIENTRY * qglColor3f )( GLfloat red, GLfloat green, GLfloat blue );
extern void ( APIENTRY * qglColor3fv )( const GLfloat *v );
extern void ( APIENTRY * qglColor3ubv )( const GLubyte *v );
extern void ( APIENTRY * qglColor4f )( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha );
extern void (APIENTRY* qglColor4ubv)(const GLubyte* v);
extern void ( APIENTRY * qglColorMask )( GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha );
extern void ( APIENTRY * qglColorPointer )( GLint size, GLenum type, GLsizei stride, const GLvoid *pointer );
extern void ( APIENTRY * qglCullFace )( GLenum mode );
extern void ( APIENTRY * qglDeleteTextures )( GLsizei n, const GLuint *textures );
extern void ( APIENTRY * qglDepthFunc )( GLenum func );
extern void ( APIENTRY * qglDepthMask )( GLboolean flag );
extern void ( APIENTRY * qglDepthRange )( GLclampd zNear, GLclampd zFar );
extern void ( APIENTRY * qglDisable )( GLenum cap );
extern void ( APIENTRY * qglDisableClientState )( GLenum array );
extern void ( APIENTRY * qglDrawBuffer )( GLenum mode );
extern void ( APIENTRY * qglDrawElements )( GLenum mode, GLsizei count, GLenum type, const GLvoid *indices );
extern void ( APIENTRY * qglEnable )( GLenum cap );
extern void ( APIENTRY * qglEnableClientState )( GLenum array );
extern void ( APIENTRY * qglEnd )( void );
extern void ( APIENTRY * qglFinish )( void );
extern void ( APIENTRY * qglFogf )( GLenum pname, GLfloat param );
extern void ( APIENTRY * qglFogfv )( GLenum pname, const GLfloat *params );
extern void ( APIENTRY * qglFogi )( GLenum pname, GLint param );
extern GLenum ( APIENTRY * qglGetError )( void );
extern void ( APIENTRY * qglGetFloatv )( GLenum pname, GLfloat *params );
extern void ( APIENTRY * qglGetIntegerv )( GLenum pname, GLint *params );
extern const GLubyte * ( APIENTRY * qglGetString )(GLenum name);
extern void ( APIENTRY * qglHint )( GLenum target, GLenum mode );
extern void ( APIENTRY * qglLineWidth )( GLfloat width );
extern void ( APIENTRY * qglLoadIdentity )( void );
extern void ( APIENTRY * qglLoadMatrixf )( const GLfloat *m );
extern void ( APIENTRY * qglMatrixMode )( GLenum mode );
extern void ( APIENTRY * qglNormalPointer )( GLenum type, GLsizei stride, const GLvoid *pointer );
extern void ( APIENTRY * qglOrtho )( GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar );
extern void ( APIENTRY * qglPointSize )( GLfloat size );
extern void ( APIENTRY * qglPolygonMode )( GLenum face, GLenum mode );
extern void ( APIENTRY * qglPolygonOffset )( GLfloat factor, GLfloat units );
extern void ( APIENTRY * qglPopMatrix )( void );
extern void ( APIENTRY * qglPushMatrix )( void );
extern void ( APIENTRY * qglRasterPos3fv )( const GLfloat *v );
extern void ( APIENTRY * qglReadPixels )( GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels );
extern void ( APIENTRY * qglScissor )( GLint x, GLint y, GLsizei width, GLsizei height );
extern void ( APIENTRY * qglShadeModel )( GLenum mode );
extern void ( APIENTRY * qglStencilFunc )( GLenum func, GLint ref, GLuint mask );
extern void ( APIENTRY * qglStencilMask )( GLuint mask );
extern void ( APIENTRY * qglStencilOp )( GLenum fail, GLenum zfail, GLenum zpass );
extern void ( APIENTRY * qglTexCoord2f )( GLfloat s, GLfloat t );
extern void ( APIENTRY * qglTexCoord2fv )( const GLfloat *v );
extern void ( APIENTRY * qglTexCoordPointer )( GLint size, GLenum type, GLsizei stride, const GLvoid *pointer );
extern void ( APIENTRY * qglTexEnvf )( GLenum target, GLenum pname, GLfloat param );
extern void ( APIENTRY * qglTexImage2D )( GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels );
extern void ( APIENTRY * qglTexParameterf )( GLenum target, GLenum pname, GLfloat param );
extern void ( APIENTRY * qglTexParameterfv )( GLenum target, GLenum pname, const GLfloat *params );
extern void ( APIENTRY * qglTexSubImage2D )( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels );
extern void ( APIENTRY * qglTranslatef )( GLfloat x, GLfloat y, GLfloat z );
extern void ( APIENTRY * qglVertex2f )( GLfloat x, GLfloat y );
extern void ( APIENTRY * qglVertex3f )( GLfloat x, GLfloat y, GLfloat z );
extern void ( APIENTRY * qglVertex3fv )( const GLfloat *v );
extern void ( APIENTRY * qglVertexPointer )( GLint size, GLenum type, GLsizei stride, const GLvoid *pointer );
extern void ( APIENTRY * qglViewport )( GLint x, GLint y, GLsizei width, GLsizei height );

extern int ( WINAPI * qwglChoosePixelFormat )( HDC, CONST PIXELFORMATDESCRIPTOR * );
extern int ( WINAPI * qwglDescribePixelFormat )( HDC, int, UINT, LPPIXELFORMATDESCRIPTOR );
extern int ( WINAPI * qwglGetPixelFormat )( HDC );
extern BOOL ( WINAPI * qwglSetPixelFormat )( HDC, int, CONST PIXELFORMATDESCRIPTOR * );
extern BOOL ( WINAPI * qwglSwapBuffers )( HDC );

extern HGLRC ( WINAPI * qwglCreateContext )( HDC );
extern BOOL ( WINAPI * qwglDeleteContext )( HGLRC );
extern BOOL ( WINAPI * qwglMakeCurrent )( HDC, HGLRC );

extern BOOL ( WINAPI * qwglUseFontOutlines )( HDC, DWORD, DWORD, DWORD, FLOAT,
					   FLOAT, int, LPGLYPHMETRICSFLOAT );

extern BOOL ( WINAPI * qwglDescribeLayerPlane )( HDC, int, int, UINT,
					   LPLAYERPLANEDESCRIPTOR );
extern int ( WINAPI * qwglSetLayerPaletteEntries )( HDC, int, int, int,
													CONST COLORREF * );
extern int ( WINAPI * qwglGetLayerPaletteEntries )( HDC, int, int, int,
					  COLORREF * );
extern BOOL ( WINAPI * qwglRealizeLayerPalette )( HDC, int, BOOL );
extern BOOL ( WINAPI * qwglSwapLayerBuffers )( HDC, UINT );


#endif  // _WIN32 && __linux__
