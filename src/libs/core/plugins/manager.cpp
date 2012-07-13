#include "manager.h"

#include "iplugin.h"

#include <QtCore/QPluginLoader>
#include <QtCore/QDebug>
#include <QtCore/QDir>

namespace Core
{
	PluginManager::PluginManager()
	{
	}

	void PluginManager::loadPlugins()
	{
		foreach(const QString &pluginPath, m_pluginPaths) {
			foreach(const QString &fileName, QDir(pluginPath).entryList()) {
				if(QLibrary::isLibrary(fileName)) {
					QPluginLoader loader(pluginPath + "/" + fileName);

					if(!loader.load()) {
						qDebug() << loader.errorString();
						continue;
					}

					IPlugin *plugin = qobject_cast<IPlugin*>(loader.instance());
					if(!plugin) {
						qDebug() << "Can't cast to IPlugin";
						continue;
					}

					m_plugins.append(plugin);
				}
			}
		}
	}

	QList<IPlugin *> PluginManager::plugins() const
	{
		return m_plugins;
	}

}
