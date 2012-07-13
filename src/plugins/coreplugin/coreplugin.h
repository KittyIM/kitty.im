#ifndef CORE_COREPLUGIN_H
#define CORE_COREPLUGIN_H

#include <pluginsystem/iplugin.h>

#include "coreplugin_global.h"

namespace Core
{
	class COREPLUGIN_EXPORT CorePlugin : public PluginSystem::IPlugin
	{
		public:
			CorePlugin();

			QString name() const;
	};
}

#endif // CORE_COREPLUGIN_H
