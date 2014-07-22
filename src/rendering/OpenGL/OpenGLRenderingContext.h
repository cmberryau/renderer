//
//  OpenGLRenderingContext.h
//  Renderer
//
//  Created by Christopher Berry on 05/07/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _opengl_renderingcontext_h
#define _opengl_renderingcontext_h

#include "rendering/RenderingContext.h"

namespace Renderer
{
	class OpenGLRenderingContext : public RenderingContext
	{
		public:
            static const int kNumSupportedOpenGLVersions;
            static const int kSupportedOpenGLVersions[9][2];
        
            static OpenGLRenderingContext * Create(Window * window,
			RenderingContextPrecision precision = FloatPrecision,
			int major_version = kSupportedOpenGLVersions[0][0],
            int minor_version = kSupportedOpenGLVersions[0][1]);			
			
			RenderingContextPrecision Precision();

            void BeginScene();
            void EndScene();

			~OpenGLRenderingContext();
        
		protected:
			OpenGLRenderingContext(RenderingContextType context_type,
								   RenderingContextPrecision context_precision);
        
   			SDL_GLContext _sdl_gl_context;
	};
}

#endif // #ifndef _opengl_renderingcontext_h