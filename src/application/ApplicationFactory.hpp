//
//  ApplicationFactory.hpp
//  Renderer
//
//  Created by Christopher Berry on 16/09/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _application_factory_h
#define _application_factory_h

#include "Application.hpp"

#include <string>

namespace Renderer
{
	class ApplicationFactory
	{
		public:
			static Application FromFile(const std::string & file_path);

		private:
			explicit ApplicationFactory();
			~ApplicationFactory();
	};
}

#endif // _application_factory_h