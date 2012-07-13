#ifndef IPLUGIN_H
#define IPLUGIN_H

class QString;

namespace PluginSystem
{
	class IPlugin
	{
		public:
			virtual QString name() const = 0;
	};
}

#endif // IPLUGIN_H
