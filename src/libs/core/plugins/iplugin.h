#ifndef CORE_IPLUGIN_H
#define CORE_IPLUGIN_H

#include <QtCore/QObject>

#include "../core_global.h"
#include "plugininfo.h"

namespace Core
{
	class CORE_EXPORT IPlugin : public QObject
	{
		Q_OBJECT

		public:
			IPlugin() :
				m_info(new PluginInfo(this))
			{ }

			virtual bool initialize(QString *errorString) = 0;
			virtual void pluginsInitialized() { }
			virtual void aboutToClose() {  }

			PluginInfo *info() const { return m_info; }

		protected:
			PluginInfo *m_info;
	};
}

#endif // CORE_IPLUGIN_H
