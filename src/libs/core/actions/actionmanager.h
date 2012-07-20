#ifndef CORE_ACTIONMANAGER_H
#define CORE_ACTIONMANAGER_H

#include "../core_global.h"

#include <QtCore/QMap>

namespace Core
{
	class JsonSettings;
	class Action;

	class CORE_EXPORT ActionManager : public QObject
	{
		Q_OBJECT

		public:
			static ActionManager *instance() { return m_instance; }

		public:
			ActionManager(QObject *parent = 0);

			void readSettings(JsonSettings *settings);
			void writeSettings(JsonSettings *settings);

		private:
			static ActionManager *m_instance;

		private:
			QMap<QString, Action*> m_actions;
	};
}

#endif // CORE_ACTIONMANAGER_H
