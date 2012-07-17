#include "manager.h"

#include <plugins/iplugin.h>
#include <jsonsettings.h>

#include <QtCore/QPluginLoader>
#include <QtCore/QDebug>
#include <QtCore/QDir>

static const char pluginsGroup[] = "plugins";
static const char fileNameKey[]  = "fileName";
static const char isEnabledKey[] = "isEnabled";

namespace Core
{
	PluginManager::PluginManager() :
		m_pluginSettings(0)
	{
	}

	void PluginManager::loadPlugins()
	{
		//create plugin list
		QMap<QString, bool> pluginStates;
		int count = m_pluginSettings->beginReadArray(pluginsGroup);
		for(int i = 0; i < count; ++i) {
			m_pluginSettings->setArrayIndex(i);

			QString fileName = m_pluginSettings->value(fileNameKey).toString();
			bool isEnabled = m_pluginSettings->value(isEnabledKey).toBool();

			pluginStates.insert(fileName, isEnabled);
		}
		m_pluginSettings->endArray();

		//load plugins
		foreach(const QString &pluginPath, m_pluginPaths) {
			foreach(const QFileInfo &fileInfo, QDir(pluginPath).entryInfoList(QDir::Files)) {
				if(QLibrary::isLibrary(fileInfo.absoluteFilePath()) && pluginStates.value(fileInfo.completeBaseName())) {
					QPluginLoader loader(fileInfo.absoluteFilePath());

					if(!loader.load()) {
						qDebug() << loader.errorString();
						continue;
					}

					IPlugin *plugin = qobject_cast<IPlugin*>(loader.instance());
					if(!plugin) {
						qDebug() << "Can't cast to IPlugin";
						loader.unload();
						continue;
					}

					m_plugins.append(plugin);
				}
			}
		}
	}

	bool PluginManager::hasNewPlugins() const
	{
		if(!m_pluginSettings)
			return false;

		//create plugin list
		QStringList pluginFiles;
		foreach(const QString &pluginPath, m_pluginPaths) {
			foreach(const QFileInfo &fileInfo, QDir(pluginPath).entryInfoList(QDir::Files)) {
				if(QLibrary::isLibrary(fileInfo.absoluteFilePath())) {
					pluginFiles << fileInfo.completeBaseName();
				}
			}
		}

		//remove known plugins
		int count = m_pluginSettings->beginReadArray(pluginsGroup);
		for(int i = 0; i < count; ++i) {
			m_pluginSettings->setArrayIndex(i);

			QString fileName = m_pluginSettings->value(fileNameKey).toString();
			pluginFiles.removeAll(fileName);
		}
		m_pluginSettings->endArray();

		return (pluginFiles.count() > 0);
	}

	QList<IPlugin *> PluginManager::plugins() const
	{
		return m_plugins;
	}

}
