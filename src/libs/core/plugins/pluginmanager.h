#ifndef CORE_PLUGINMANAGER_H
#define CORE_PLUGINMANAGER_H

#include "../core_global.h"

#include <QtCore/QStringList>

namespace Core
{
	class JsonSettings;
	class PluginItem;

	class CORE_EXPORT PluginManager
	{
		public:
			PluginManager();

			void loadPlugins();

			bool scanForPlugins();

			QList<PluginItem*> plugins() const;

			QStringList pluginPaths() const { return m_pluginPaths; }
			void setPluginPaths(const QStringList &pluginPaths) { m_pluginPaths = pluginPaths; }

			JsonSettings *settings() { return m_settings; }
			void setSettings(JsonSettings *settings) { m_settings = settings; }

		public slots:
			void aboutToClose();

		private:
			QStringList m_pluginPaths;
			JsonSettings *m_settings;
			QList<PluginItem*> m_plugins;
	};
}

#endif // CORE_PLUGINMANAGER_H
