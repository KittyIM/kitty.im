#include "pluginmanager.h"

#include <plugins/pluginitem.h>
#include <plugins/iplugin.h>
#include <jsonsettings.h>

#include <QtCore/QPluginLoader>
#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtGui/QApplication>

static const char pluginsGroup[] = "Plugins";

namespace Core
{
	PluginManager::PluginManager(const QStringList &pluginPaths) :
		m_pluginPaths(pluginPaths),
		m_settings(0)
	{
		connect(qApp, SIGNAL(aboutToQuit()), SLOT(aboutToClose()));
	}

	void PluginManager::loadPlugins()
	{
		foreach(PluginItem *plugin, m_plugins) {
			plugin->setState(PluginItem::Loaded);
		}

		foreach(PluginItem *plugin, m_plugins) {
			plugin->setState(PluginItem::Initialized);
		}

		emit pluginsInitialized();

		foreach(PluginItem *plugin, m_plugins) {
			plugin->setState(PluginItem::Running);
		}
	}

	bool PluginManager::scanForPlugins()
	{
		if(!m_settings)
			return false;

		QMap<QString, bool> knownPlugins;
		m_settings->beginGroup(pluginsGroup);
		foreach(const QString &pluginName, m_settings->childKeys()) {
			bool isEnabled = m_settings->value(pluginName).toBool();
			knownPlugins.insert(pluginName, isEnabled);
		}
		m_settings->endGroup();

		bool unknownPlugins = false;
		foreach(const QString &pluginPath, m_pluginPaths) {
			foreach(const QFileInfo &fileInfo, QDir(pluginPath).entryInfoList(QDir::Files)) {
				QString filePath = fileInfo.absoluteFilePath();

				if(QLibrary::isLibrary(filePath)) {
					QString fileName = fileInfo.completeBaseName();

					PluginItem *pluginItem = new PluginItem(filePath);

					if(knownPlugins.contains(fileName)) {
						pluginItem->setEnabled(knownPlugins.value(fileName));
					} else {
						unknownPlugins = true;
					}

					m_plugins << pluginItem;
				}
			}
		}

		return unknownPlugins;
	}

	QList<PluginItem*> PluginManager::plugins() const
	{
		return m_plugins;
	}

	void PluginManager::aboutToClose()
	{
		foreach(PluginItem *plugin, m_plugins) {
			plugin->setState(PluginItem::Stopped);
		}
	}

}
