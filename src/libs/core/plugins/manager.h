#ifndef CORE_MANAGER_H
#define CORE_MANAGER_H

#include "../core_global.h"

#include <QtCore/QStringList>

namespace Core
{
	class IPlugin;

	class CORE_EXPORT PluginManager
	{
		public:
			PluginManager();

			void loadPlugins();

			QList<IPlugin*> plugins() const;

			QStringList pluginPaths() const { return m_pluginPaths; }
			void setPluginPaths(const QStringList &pluginPaths) { m_pluginPaths = pluginPaths; }

		private:
			QStringList m_pluginPaths;
			QList<IPlugin*> m_plugins;
	};
}

#endif // CORE_MANAGER_H
