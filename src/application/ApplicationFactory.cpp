//
//  ApplicationFactory.cpp
//  Renderer
//
//  Created by Christopher Berry on 16/09/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "ApplicationFactory.hpp"
#include "utility/rapidxml/rapidxml.hpp"

#ifdef EMSCRIPTEN
#include "application/EmscriptenApplication.hpp"
#endif

namespace Renderer
{
	std::shared_ptr<Application> ApplicationFactory::FromFile(const std::string & file_path)
    {
        std::string content = IO::ReadFile(file_path);
        
        rapidxml::xml_document<> xml_doc;
        xml_doc.parse<0>(&content[0]);
        
        for(rapidxml::xml_node<> * node = xml_doc.first_node();
            node; node = node->next_sibling())
        {
            std::cout << node->name();
        }
        
        std::string window_name("Renderer");
        
        // temporary code
        std::shared_ptr<Window> window(new Window(640, 480, window_name));
#ifndef EMSCRIPTEN
        std::shared_ptr<RenderingContext> rendering_context(new OpenGLRenderingContext(*window));
#else
        std::shared_ptr<RenderingContext> rendering_context(new OpenGLESRenderingContext(*window));
#endif
        std::shared_ptr<EventListener> event_listener(new EventListener());
        
#ifdef EMSCRIPTEN
        std::shared_ptr<Application> app(new EmscriptenApplication(window, rendering_context, event_listener));
#else
        std::shared_ptr<Application> app(new Application(window, rendering_context, event_listener));
#endif
        
		return app;
	}
}