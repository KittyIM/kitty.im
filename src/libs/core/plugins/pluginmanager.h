#ifndef CORE_PLUGINMANAGER_H
#define CORE_PLUGINMANAGER_H

#include "../core_global.h"

#include <QStringList>

namespace Core
{
	class JsonSettings;
	class PluginItem;

	class CORE_EXPORT PluginManager: public QObject
	{
		Q_OBJECT

		public:
			PluginManager(const QStringList &pluginPaths);

			void loadPlugins();

			bool scanForPlugins();

			QList<PluginItem*> plugins() const;

			QStringList pluginPaths() const { return m_pluginPaths; }

			JsonSettings *settings() { return m_settings; }
			void setSettings(JsonSettings *settings) { m_settings = settings; }

		public slots:
			void aboutToClose();

		signals:
			void pluginsInitialized();

		private:
			QStringList m_pluginPaths;
			JsonSettings *m_settings;
			QList<PluginItem*> m_plugins;
	};
}

#endif // CORE_PLUGINMANAGER_H
