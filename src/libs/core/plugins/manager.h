#ifndef CORE_MANAGER_H
#define CORE_MANAGER_H

#include "../core_global.h"

#include <QtCore/QStringList>

namespace Core
{
	class JsonSettings;
	class IPlugin;

	class CORE_EXPORT PluginManager
	{
		public:
			PluginManager();

			void loadPlugins();

			bool hasNewPlugins() const;

			QList<IPlugin*> plugins() const;

			QStringList pluginPaths() const { return m_pluginPaths; }
			void setPluginPaths(const QStringList &pluginPaths) { m_pluginPaths = pluginPaths; }

			JsonSettings *pluginSettings() { return m_pluginSettings; }
			void setPluginSettings(JsonSettings *pluginSettings) { m_pluginSettings = pluginSettings; }

		private:
			QStringList m_pluginPaths;
			JsonSettings *m_pluginSettings;
			QList<IPlugin*> m_plugins;
	};
}

#endif // CORE_MANAGER_H
