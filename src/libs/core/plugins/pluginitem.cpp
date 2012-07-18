#include "pluginitem.h"

#include <plugins/iplugin.h>
#include <QPluginLoader>

namespace Core
{
	PluginItem::PluginItem(const QString &filePath) :
		QObject(0),
		m_iplugin(0),
		m_filePath(filePath),
		m_state(Invalid)
	{
	}

	void PluginItem::setState(const State &destState)
	{
		if(hasError() || !m_enabled)
			return;

		switch(destState) {
			case Loaded:
				loadPlugin();
			break;

			case Initialized:
				initializePlugin();
			break;

			case Running:
				runPlugin();
			break;
		}
	}

	void PluginItem::loadPlugin()
	{
		if(hasError())
			return;

		QPluginLoader loader(m_filePath);

		if(!loader.load()) {
			m_error = loader.errorString();
			return;
		}

		IPlugin *plugin = qobject_cast<IPlugin*>(loader.instance());
		if(!plugin) {
			m_error = tr("Can't cast to IPlugin");
			loader.unload();
			return;
		}

		m_state = Loaded;
		m_iplugin = plugin;
	}

	void PluginItem::initializePlugin()
	{
		if(hasError() || !m_iplugin)
			return;

		QString errorString;
		if(!m_iplugin->initialize(&errorString)) {
			m_error = errorString;
			return;
		}

		m_state = Initialized;
	}

	void PluginItem::runPlugin()
	{
		if(hasError() || !m_iplugin)
			return;

		m_iplugin->pluginsInitialized();
		m_state = Running;
	}

	QString PluginItem::author() const
	{
		if(!m_iplugin || !m_iplugin->info())
			return "";

		return m_iplugin->info()->author();
	}

	QString PluginItem::name() const
	{
		if(!m_iplugin || !m_iplugin->info())
			return "";

		return m_iplugin->info()->name();
	}

	QString PluginItem::website() const
	{
		if(!m_iplugin || !m_iplugin->info())
			return "";

		return m_iplugin->info()->website();
	}

	QString PluginItem::version() const
	{
		if(!m_iplugin || !m_iplugin->info())
			return "";

		return m_iplugin->info()->version();
	}
}
