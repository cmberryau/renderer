//
//  ApplicationFactory.cpp
//  Renderer
//
//  Created by Christopher Berry on 16/09/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "ApplicationFactory.hpp"
#include "ApplicationXML.hpp"
#include "objects/ObjectFactory.hpp"

#ifdef EMSCRIPTEN
#include "application/EmscriptenApplication.hpp"
#endif

namespace Renderer
{
	std::shared_ptr<Application> ApplicationFactory::FromFile(const std::string & file_path)
    {
        std::string window_name("Renderer");
        
        // temporary code		
		auto window = std::make_shared<Window>(640, 480, window_name);
#ifndef EMSCRIPTEN
        auto rendering_context = std::make_shared<OpenGLRenderingContext>(*window);
#else
		auto rendering_context = std::make_shared<OpenGLESRenderingContext>(*window);
#endif
        auto event_listener = std::make_shared<EventListener>();
        
#ifdef EMSCRIPTEN
        auto app = std::make_shared<EmscriptenApplication>(window, rendering_context, event_listener);
#else
		auto app = std::make_shared<Application>(window, rendering_context, event_listener);
#endif     

        auto content = IO::ReadFile(file_path);
        
        rapidxml::xml_document<> doc;
        doc.parse<0>(&content[0]);

		std::vector<std::unique_ptr<Object>> objects;

        auto root_node = doc.first_node(ApplicationXML::kApplicationTag.c_str());
        if(root_node)
        {
            for(auto scene_node = root_node->first_node(ApplicationXML::kSceneTag.c_str());
				scene_node; scene_node = scene_node->next_sibling())
            {
                for(auto object_node = scene_node->first_node(ApplicationXML::kObjectTag.c_str());
					object_node; object_node = object_node->next_sibling())
                {
					ProcessObjectXMLNode(object_node, objects);
                }
            }
        }
        
		return app;
	}

	// processes an xml node that refers to an object
	void ApplicationFactory::ProcessObjectXMLNode(rapidxml::xml_node<> * object_node,
												  std::vector<std::unique_ptr<Object>> & objects)
	{
        auto object_ptr = ObjectFactory::ObjectFromXMLNode(object_node);

		// add it to the vector of objects
		objects.push_back(std::move(object_ptr));

		// process any child objects
		for (auto child_node = object_node->first_node(ApplicationXML::kObjectTag.c_str());
			child_node; child_node = child_node->next_sibling())
		{
			ProcessObjectXMLNode(child_node, objects);
		}
	}
}