#ifndef CORE_CONSOLEDIALOG_H
#define CORE_CONSOLEDIALOG_H

#include "../core_global.h"

#include <QDialog>
#include <QMap>

class QTabWidget;

namespace Core
{
	class IConsoleTab;

	class CORE_EXPORT ConsoleDialog : public QDialog
	{
		Q_OBJECT

		public:
			static ConsoleDialog *instance(QWidget *parent = 0);
			static void addTab(IConsoleTab *tab);
			static void cleanup();

		public:
			ConsoleDialog(QWidget *parent = 0);
			~ConsoleDialog();

		public slots:
			void done(int r);

		protected:
			void keyPressEvent(QKeyEvent *event);

		private:
			void readSettings();
			void writeSettings();

		private:
			static ConsoleDialog *m_instance;
			static QList<IConsoleTab*> m_tabs;

		private:
			QTabWidget *m_tabWidget;
	};
}

#endif // CORE_CONSOLEDIALOG_H
