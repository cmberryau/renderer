//
//  Object.cpp
//  Renderer
//
//  Created by Christopher Berry on 17/06/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "Object.h"

namespace Renderer
{
	void Object::AddMesh(Mesh * mesh)
	{
		if (mesh == nullptr)
			return;

		_mesh = mesh;
	}

	void Object::AddMeshRenderer(MeshRenderer * mesh_renderer)
	{
		if (mesh_renderer == nullptr)
			return;

		_mesh_renderer = mesh_renderer;
	}

	Object::Object() : _mesh(nullptr),
					   _mesh_renderer(nullptr)
    {
        
    }
    
    Object::~Object()
    {
		delete _mesh;
		delete _mesh_renderer;
    }
}