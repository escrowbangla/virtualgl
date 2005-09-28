/* Copyright (C)2004 Landmark Graphics
 *
 * This library is free software and may be redistributed and/or modified under
 * the terms of the wxWindows Library License, Version 3 or (at your option)
 * any later version.  The full license is in the LICENSE.txt file included
 * with this distribution.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * wxWindows Library License for more details.
 */

// This is a container class which allows us to temporarily swap in a new
// drawable and then "pop the stack" after we're done with it.  It does nothing
// unless there is already a valid context established

#ifndef __TEMPCTX_H
#define __TEMPCTX_H

#define EXISTING_DRAWABLE (GLXDrawable)-1

#ifdef INFAKER
#include "faker-sym.h"
#define glXGetCurrentDisplay GetCurrentDisplay
#define glXGetCurrentDrawable GetCurrentDrawable
#define glXGetCurrentReadDrawable GetCurrentReadDrawable
#define glXMakeCurrent _glXMakeCurrent
#define glXMakeContextCurrent _glXMakeContextCurrent
#else
#ifdef USEGLP
#include <GL/glp.h>
#include "glpweak.h"
#endif
#include <GL/glx.h>
#endif

#ifdef USEGLP
#include "fakerconfig.h"
extern FakerConfig fconfig;
#endif

class tempctx
{
	public:

		tempctx(Display *dpy, GLXDrawable draw, GLXDrawable read,
			GLXContext ctx=glXGetCurrentContext(), bool glx11=false) :
			_dpy(glXGetCurrentDisplay()), _ctx(glXGetCurrentContext()),
			_read(glXGetCurrentReadDrawable()), _draw(glXGetCurrentDrawable()),
			_mc(false), _glx11(glx11)
		{
			if(!_ctx || (!_read && !_draw)) return;
			#ifdef USEGLP
			if(!fconfig.glp && (!dpy || !_dpy)) return;
			#else
			if(!dpy || !_dpy) return;
			#endif
			if(read==EXISTING_DRAWABLE) read=_read;
			if(draw==EXISTING_DRAWABLE) draw=_draw;
			if(_read!=read || _draw!=draw || _ctx!=ctx
			#ifdef USEGLP
			|| (!fconfig.glp && _dpy!=dpy)
			#else
			|| (_dpy!=dpy)
			#endif
			)
			{
				#ifdef USEGLP
				if(fconfig.glp) glPMakeContextCurrent(draw, read, ctx);
				else
				#endif
				{
					if(glx11) glXMakeCurrent(dpy, draw, ctx);
					else glXMakeContextCurrent(dpy, draw, read, ctx);
				}
				_mc=true;
			}
		}

		void restore(void)
		{
			if(_mc)
			{
				#ifdef USEGLP
				if(fconfig.glp) glPMakeContextCurrent(_draw, _read, _ctx);
				else
				#endif
				if(_dpy)
				{
					if(_glx11) glXMakeCurrent(_dpy, _draw, _ctx);
					else glXMakeContextCurrent(_dpy, _draw, _read, _ctx);
				}
			}
		}

		~tempctx(void)
		{
			restore();
		}

	private:

		Display *_dpy;
		GLXContext _ctx;
		GLXDrawable _read, _draw;
		bool _mc, _glx11;
};

#ifdef INFAKER
#undef glXGetCurrentDisplay
#undef glXGetCurrentDrawable
#undef glXGetCurrentReadDrawable
#undef glXMakeCurrent
#undef glXMakeContextCurrent
#endif

#endif // __TEMPCTX_H
