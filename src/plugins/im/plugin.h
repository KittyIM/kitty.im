#ifndef IM_PLUGIN_H
#define IM_PLUGIN_H

#include <core/plugins/iplugin.h>

#include "im_global.h"

namespace Im
{
	class IM_EXPORT Plugin : public Core::IPlugin
	{
		Q_OBJECT

		public:
			Plugin();
	};
}

#endif // IM_PLUGIN_H
