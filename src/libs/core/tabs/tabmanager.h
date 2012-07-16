#ifndef CORE_TABMANAGER_H
#define CORE_TABMANAGER_H

#include "../core_global.h"

class QTabWidget;

namespace Core
{
	class CORE_EXPORT TabManager : public QObject
	{
		Q_OBJECT

		public:
			TabManager();

			QTabWidget *tabWidget() { return m_tabWidget; }
			void setTabWidget(QTabWidget *tabWidget) { m_tabWidget = tabWidget; }

		private:
			QTabWidget *m_tabWidget;
	};
}

#endif // CORE_TABMANAGER_H
