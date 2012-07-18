#ifndef CORE_IPLUGIN_H
#define CORE_IPLUGIN_H

#include <QtCore/QObject>

#include "../core_global.h"

namespace Core
{
	class CORE_EXPORT IPlugin : public QObject
	{
		Q_OBJECT

		public:
			IPlugin() { }

			virtual QString name() const = 0;
			virtual QString version() const = 0;
			virtual QString author() const = 0;
			virtual QString website() const = 0;

			virtual bool initialize(QString *errorString) = 0;
			virtual void pluginsInitialized() { }
			virtual void aboutToClose() { }
	};
}

#endif // CORE_IPLUGIN_H
