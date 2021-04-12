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

#define SOKOL_IMPL
#define SOKOL_GL_IMPL
#define SOKOL_D3D11
#include <sokol_gfx.h>
#include <util/sokol_gl.h>
#include <sokol_app.h>

#define TEXTURES_ENABLED 1
#define DEPTH_TEST_ENABLED 1 << 1
#define SCISSOR_TEST_ENABLED 1 << 2
#define CULLING_ENABLED 1 << 3
#define BLENDING_ENABLED 1 << 4
#define FOG_ENABLED 1 << 5
#define CLIPPING_PLANE_ENABLED 1 << 6
#define STENCIL_TEST_ENABLED 1 << 7
#define ALPHA_TEST_ENABLED 1 << 8
#define POLYGON_OFFSET_FILL_ENABLED 1 << 9

sg_pass_action clear_action;

struct {
	bool enabled;
	int size;
	int stride;
	uint8_t* ptr;
} color_pointer;

struct {
	bool enabled;
	int size;
	int stride;
	float* ptr;
} vertex_pointer;

struct {
	bool enabled;
	int size;
	int stride;
	float* ptr;
} texcoord_pointer;

struct 
{
	sg_cull_mode cull_mode;
	sg_blend_factor sfactor;
	sg_blend_factor dfactor;
	unsigned int render_flags;
} state;

int ( WINAPI * qwglDescribePixelFormat )( HDC, int, UINT, LPPIXELFORMATDESCRIPTOR );
BOOL ( WINAPI * qwglSetPixelFormat )( HDC, int, CONST PIXELFORMATDESCRIPTOR * );
BOOL ( WINAPI * qwglSwapBuffers )( HDC );

HGLRC ( WINAPI * qwglCreateContext )( HDC );
BOOL ( WINAPI * qwglDeleteContext )( HGLRC );
BOOL ( WINAPI * qwglMakeCurrent )( HDC, HGLRC );

void ( APIENTRY * qglAlphaFunc )( GLenum func, GLclampf ref );
void ( APIENTRY * qglArrayElement )( GLint i );
void ( APIENTRY * qglBegin )( GLenum mode );
void ( APIENTRY * qglBindTexture )( GLenum target, GLuint texture );
void ( APIENTRY * qglBlendFunc )( GLenum sfactor, GLenum dfactor );
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
void ( APIENTRY * qglLoadIdentity )( void );
void ( APIENTRY * qglLoadMatrixf )( const GLfloat *m );
void ( APIENTRY * qglMatrixMode )( GLenum mode );

void ( APIENTRY * qglOrtho )( GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar );
void ( APIENTRY * qglPopMatrix )( void );
void ( APIENTRY * qglPushMatrix )( void );
void ( APIENTRY * qglTexCoord2f )( GLfloat s, GLfloat t );
void ( APIENTRY * qglTexCoord2fv )( const GLfloat *v );
void ( APIENTRY * qglTexCoordPointer )( GLint size, GLenum type, GLsizei stride, const GLvoid *pointer );
void ( APIENTRY * qglTexEnvf )( GLenum target, GLenum pname, GLfloat param );
void ( APIENTRY * qglTexImage2D )( GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels );
void ( APIENTRY * qglTexParameterf )( GLenum target, GLenum pname, GLfloat param );
void ( APIENTRY * qglTexParameterfv )( GLenum target, GLenum pname, const GLfloat *params );
void ( APIENTRY * qglTranslatef )( GLfloat x, GLfloat y, GLfloat z );
void ( APIENTRY * qglVertexPointer )( GLint size, GLenum type, GLsizei stride, const GLvoid *pointer );
void ( APIENTRY * qglViewport )( GLint x, GLint y, GLsizei width, GLsizei height );

void glAlphaFunc_impl(GLenum func, GLclampf ref)
{
	glAlphaFunc(func, ref);
}

void glArrayElement_impl(GLint i)
{
	if (vertex_pointer.enabled)
	{
		int idx = i * vertex_pointer.stride;
		float x = vertex_pointer.ptr[idx];
		float y = vertex_pointer.ptr[idx + 1];
		float z = vertex_pointer.ptr[idx + 2];
		sgl_v3f(x, y, z);
	}

	if (color_pointer.enabled)
	{
		int idx = i * color_pointer.stride;
		uint8_t r = color_pointer.ptr[idx];
		uint8_t g = color_pointer.ptr[idx + 1];
		uint8_t b = color_pointer.ptr[idx + 2];
		uint8_t a = color_pointer.ptr[idx + 3];
		sgl_c4b(r, g, b, a);
	}

	if (texcoord_pointer.enabled)
	{
		int idx = i * texcoord_pointer.stride;
		float u = texcoord_pointer.ptr[idx];
		float v = texcoord_pointer.ptr[idx + 1];
		sgl_t2f(u, v);
	}

	glArrayElement(i);
}

sgl_pipeline current_pipeline;
void glBegin_impl(GLenum mode)
{
	switch (mode) {
	case GL_LINES:
		sgl_begin_lines();
		break;
	case GL_LINE_STRIP:
		sgl_begin_line_strip();
		break;
	case GL_LINE_LOOP:
	case GL_QUADS:
		sgl_begin_quads();
		break;
	case GL_POLYGON:
		sgl_begin_triangles();
		break;
	case GL_TRIANGLE_STRIP:
		sgl_begin_triangle_strip();
		break;
	case GL_POINTS:
		sgl_begin_points();
		break;
	}

	glBegin(mode);
}

void glBindTexture_impl(GLenum target, GLuint texture)
{ 
	glBindTexture(target, texture);
}

sg_blend_factor gl_to_sgl_blend_factor(GLenum factor) {
	sg_blend_factor result = SG_BLENDFACTOR_ONE;

	switch (factor) {
	case GL_SRC_ALPHA:
		result = SG_BLENDFACTOR_SRC_ALPHA;
		break;
	case GL_ONE_MINUS_SRC_ALPHA:
		result = SG_BLENDFACTOR_ONE_MINUS_SRC_ALPHA;
		break;
	case GL_DST_COLOR:
		result = SG_BLENDFACTOR_DST_COLOR;
		break;
	case GL_ONE_MINUS_SRC_COLOR:
		result = SG_BLENDFACTOR_ONE_MINUS_SRC_COLOR;
		break;
	case GL_ONE_MINUS_DST_ALPHA:
		result = SG_BLENDFACTOR_ONE_MINUS_DST_ALPHA;
		break;
	case GL_ZERO:
		result = SG_BLENDFACTOR_ZERO;
		break;
	case GL_ONE:
		result = SG_BLENDFACTOR_ONE;
		break;

	default:
		assert(0);
	}

	return result;
}

void glBlendFunc_impl(GLenum sfactor, GLenum dfactor)
{
	state.sfactor = gl_to_sgl_blend_factor(sfactor);
	state.dfactor = gl_to_sgl_blend_factor(dfactor);

	glBlendFunc(sfactor, dfactor);
}

void glClear_impl(GLbitfield mask)
{
	glClear(mask);
}

void glClearColor_impl(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
	clear_action.colors[0].val[0] = red;
	clear_action.colors[0].val[1] = blue;
	clear_action.colors[0].val[2] = green;
	clear_action.colors[0].val[3] = alpha;
	glClearColor(red, green, blue, alpha);
}

void glClearDepth_impl(GLclampd depth)
{
	clear_action.depth.val = depth;
	glClearDepth(depth);
}

void glClearIndex_impl(GLfloat c)
{
	glClearIndex(c);
}

void glClearStencil_impl(GLint s)
{
	clear_action.stencil.val = s;
	glClearStencil(s);
}

void glColor3f_impl(GLfloat red, GLfloat green, GLfloat blue)
{
	sgl_c3f(red, green, blue);
	glColor3f(red, green, blue);
}

void glColor3fv_impl(const GLfloat* v)
{
	sgl_c3f(v[0], v[1], v[2]);
	glColor3fv(v);
}

void glColor3ubv_impl(const GLubyte* v)
{
	sgl_c3b(v[0], v[1], v[2]);
	glColor3ubv(v);
}

void glColor4f_impl(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	sgl_c4f(red, green, blue, alpha);
	glColor4f(red, green, blue, alpha);
}

void glColor4ubv_impl(const GLubyte* v)
{
	sgl_c4b(v[0], v[1], v[2], v[3]);
	glColor4ubv(v);
}

void glColorMask_impl(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
	glColorMask(red, green, blue, alpha);
}

void glColorPointer_impl(GLint size, GLenum type, GLsizei stride, const GLvoid* pointer)
{
	color_pointer.size = size;
	color_pointer.stride = stride / sizeof(uint8_t);
	color_pointer.ptr = pointer;

	glColorPointer(size, type, stride, pointer);
}

void glVertexPointer_impl(GLint size, GLenum type, GLsizei stride, const GLvoid* pointer)
{
	vertex_pointer.size = size;
	vertex_pointer.stride = stride / sizeof(float);
	vertex_pointer.ptr = pointer;

	glVertexPointer(size, type, stride, pointer);
}

void glTexCoordPointer_impl(GLint size, GLenum type, GLsizei stride, const GLvoid* pointer)
{
	texcoord_pointer.size = size;
	texcoord_pointer.stride = stride / sizeof(float);
	texcoord_pointer.ptr = pointer;

	glTexCoordPointer(size, type, stride, pointer);
}

void glCullFace_impl(GLenum mode)
{
	switch (mode) {
	case GL_FRONT:
		state.cull_mode = SG_CULLMODE_FRONT;
		break;
	case GL_BACK:
		state.cull_mode = SG_CULLMODE_BACK;
		break;
	}

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
	unsigned int current_flag = 0;
	switch (cap) {
	case GL_TEXTURE_2D:
		current_flag = TEXTURES_ENABLED;
		break;
	case GL_DEPTH_TEST:
		current_flag = DEPTH_TEST_ENABLED;
		break;
	case GL_SCISSOR_TEST:
		current_flag = SCISSOR_TEST_ENABLED;
		break;
	case GL_CULL_FACE:
		current_flag = CULLING_ENABLED;
		break;
	case GL_BLEND:
		current_flag = BLENDING_ENABLED;
		break; 
	case GL_FOG:
		current_flag = FOG_ENABLED;
		break;
	case GL_CLIP_PLANE0:
		current_flag = CLIPPING_PLANE_ENABLED;
		break;
	case GL_STENCIL_TEST:
		current_flag = STENCIL_TEST_ENABLED;
		break;
	case GL_ALPHA_TEST:
		current_flag = ALPHA_TEST_ENABLED;
		break;
	case GL_POLYGON_OFFSET_FILL:
		current_flag = POLYGON_OFFSET_FILL_ENABLED;
		break;
	default:
		assert(0);
	}
	state.render_flags |= current_flag;
	glEnable(cap);
}

void glDisable_impl(GLenum cap)
{
	unsigned int current_flag = 0;
	switch (cap) {
	case GL_TEXTURE_2D:
		current_flag = TEXTURES_ENABLED;
		break;
	case GL_DEPTH_TEST:
		current_flag = DEPTH_TEST_ENABLED;
		break;
	case GL_SCISSOR_TEST:
		current_flag = SCISSOR_TEST_ENABLED;
		break;
	case GL_CULL_FACE:
		current_flag = CULLING_ENABLED;
		break;
	case GL_BLEND:
		current_flag = BLENDING_ENABLED;
		break;
	case GL_FOG:
		current_flag = FOG_ENABLED;
		break;
	case GL_CLIP_PLANE0:
		current_flag = CLIPPING_PLANE_ENABLED;
		break;
	case GL_STENCIL_TEST:
		current_flag = STENCIL_TEST_ENABLED;
		break;
	case GL_ALPHA_TEST:
		current_flag = ALPHA_TEST_ENABLED;
		break;
	case GL_POLYGON_OFFSET_FILL:
		current_flag = POLYGON_OFFSET_FILL_ENABLED;
		break;
	default:
		assert(0);
	}
	unsigned int mask = ~current_flag;
	state.render_flags &= mask;
	glDisable(cap);
}

void glEnableClientState_impl(GLenum _array)
{
	switch (_array) {
	case GL_COLOR_ARRAY:
		color_pointer.enabled = true;
		break;
	case GL_TEXTURE_COORD_ARRAY:
		texcoord_pointer.enabled = true;
		break;

	case GL_VERTEX_ARRAY:
		vertex_pointer.enabled = true;
		break;
	}
	glEnableClientState(_array);
}

void glDisableClientState_impl(GLenum _array)
{
	switch (_array) {
	case GL_COLOR_ARRAY:
		color_pointer.enabled = false;
		break;
	case GL_TEXTURE_COORD_ARRAY:
		texcoord_pointer.enabled = false;
		break;

	case GL_VERTEX_ARRAY:
		vertex_pointer.enabled = false;
		break;
	}
	glDisableClientState(_array);
}

void glEnd_impl(void)
{
	sgl_end();
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

void glLoadIdentity_impl(void)
{
	sgl_load_identity();
	glLoadIdentity();
}

void glLoadMatrixf_impl(const GLfloat* m)
{
	sgl_load_matrix(m);
	glLoadMatrixf(m);
}

void glMatrixMode_impl(GLenum mode)
{
	switch (mode) {
	case GL_PROJECTION:
		sgl_matrix_mode_projection();
		break;
	case GL_MODELVIEW:
		sgl_matrix_mode_modelview();
		break;
	}
	glMatrixMode(mode);
}

void glOrtho_impl(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar)
{
	sgl_ortho(left, right, bottom, top, zNear, zFar);
	glOrtho(left, right, bottom, top, zNear, zFar);
}

void glPopMatrix_impl(void)
{
	sgl_pop_matrix();
	glPopMatrix();
}

void glPushMatrix_impl(void)
{
	sgl_push_matrix();
	glPushMatrix();
}

void glTexCoord2f_impl(GLfloat s, GLfloat t)
{
	sgl_t2f(s, t);
	glTexCoord2f(s, t);
}

void glTexCoord2fv_impl(const GLfloat* v)
{
	sgl_t2f(v[0], v[1]);
	glTexCoord2fv(v);
}

void glTexEnvf_impl(GLenum target, GLenum pname, GLfloat param)
{
	glTexEnvf(target, pname, param);
}

void glTexImage2D_impl(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels)
{
	/*{
		sg_image_desc desc;
		memset(&desc, 0, sizeof(sg_image_desc));
		desc.pixel_format = SG_PIXELFORMAT_RGBA8;
		desc.min_filter = SG_FILTER_NEAREST_MIPMAP_LINEAR;
		desc.mag_filter = SG_FILTER_LINEAR;
		desc.wrap_u = SG_WRAP_REPEAT;
		desc.wrap_v = SG_WRAP_REPEAT;
		desc.width = width;
		desc.height = height;
		desc.content.subimage[0][0].ptr = pixels;
		desc.content.subimage[0][0].size = width * height * 4;
		sg_make_image(&desc);
	}*/

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

void glTranslatef_impl(GLfloat x, GLfloat y, GLfloat z)
{
	sgl_translate(x, y, z);
	glTranslatef(x, y, z);
}

void glViewport_impl(GLint x, GLint y, GLsizei width, GLsizei height)
{
	sgl_viewport(x, y, width, height, false);
	glViewport(x, y, width, height);
}

/*
** QGL_Shutdown
**
** Unloads the specified DLL then nulls out all the proc pointers.  This
** is only called during a hard shutdown of the OGL subsystem (e.g. vid_restart).
*/
void QGL_Shutdown( void ) {

	sgl_shutdown();
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
	qglBlendFunc                 = NULL;
	qglClear                     = NULL;
	qglClearColor                = NULL;
	qglClearDepth                = NULL;
	qglClearStencil              = NULL;
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
	qglLoadIdentity              = NULL;
	qglLoadMatrixf               = NULL;
	qglMatrixMode                = NULL;
	qglOrtho                     = NULL;
	qglPopMatrix                 = NULL;
	qglPushMatrix                = NULL;
	qglTexCoord2f                = NULL;
	qglTexCoord2fv               = NULL;
	qglTexCoordPointer           = NULL;
	qglTexEnvf                   = NULL;
	qglTexImage2D                = NULL;
	qglTexParameterf             = NULL;
	qglTexParameterfv            = NULL;
	qglTranslatef                = NULL;
	qglViewport                  = NULL;

	qwglCreateContext            = NULL;
	qwglDeleteContext            = NULL;
	qwglMakeCurrent              = NULL;

	qwglDescribePixelFormat      = NULL;
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
	{
		sg_desc desc;
		memset(&desc, 0, sizeof(desc));
		desc.d3d11_device = sapp_d3d11_get_device();
		desc.d3d11_device_context = sapp_d3d11_get_device_context();
		desc.d3d11_depth_stencil_view_cb = sapp_d3d11_get_depth_stencil_view;
		desc.d3d11_render_target_view_cb = sapp_d3d11_get_render_target_view;
		sg_setup(&desc);
		sgl_desc_t sgl_desc;
		memset(&sgl_desc, 0, sizeof(sgl_desc_t));
		sgl_setup(&sgl_desc);
	}

	{
		memset(&clear_action, 0, sizeof(sg_pass_action));
		clear_action.colors[0].action = SG_ACTION_CLEAR;
		clear_action.colors[0].val[0] = 0.f;
		clear_action.colors[0].val[1] = 0.f;
		clear_action.colors[0].val[2] = 0.f;
		clear_action.colors[0].val[3] = 1.f;
		clear_action.depth.action = SG_ACTION_CLEAR;
		clear_action.depth.val = 1.f;
		clear_action.stencil.action = SG_ACTION_CLEAR;
		clear_action.stencil.val = 0;
	}

	memset(&state, 0, sizeof(state));
	sgl_default_pipeline();

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
	qglBlendFunc                 = glBlendFunc_impl;
	qglClear                     = glClear_impl;
	qglClearColor                = glClearColor_impl;
	qglClearDepth                = glClearDepth_impl;
	qglClearStencil              = glClearStencil_impl;
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
	qglLoadIdentity              = glLoadIdentity_impl;
	qglLoadMatrixf               = glLoadMatrixf_impl;
	qglMatrixMode                = glMatrixMode_impl;
	qglOrtho                     = glOrtho_impl;
	qglPopMatrix                 = glPopMatrix_impl;
	qglPushMatrix                = glPushMatrix_impl;
	qglTexCoord2f                = glTexCoord2f_impl;
	qglTexCoord2fv               = glTexCoord2fv_impl;
	qglTexCoordPointer           = glTexCoordPointer_impl;
	qglTexEnvf                   = glTexEnvf_impl;
	qglTexImage2D                = glTexImage2D_impl;
	qglTexParameterf             = glTexParameterf_impl;
	qglTexParameterfv            = glTexParameterfv_impl;
	qglTranslatef                = glTranslatef_impl;
	qglVertexPointer             = glVertexPointer_impl;
	qglViewport                  = glViewport_impl;

	qwglCreateContext           = wglCreateContext;
	qwglDeleteContext           = wglDeleteContext;
	qwglMakeCurrent             = wglMakeCurrent;

	qwglDescribePixelFormat     = GPA("wglDescribePixelFormat");
	qwglSetPixelFormat          = GPA("wglSetPixelFormat");
	qwglSwapBuffers             = GPA("wglSwapBuffers");

	return qtrue;
}

#pragma warning (default : 4113 4133 4047 )



