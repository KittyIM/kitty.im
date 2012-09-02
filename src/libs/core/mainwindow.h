#ifndef CORE_MAINWINDOW_H
#define CORE_MAINWINDOW_H

#include "core_global.h"

#include <QMainWindow>

class QSettings;

namespace Core
{
	class ProfileManager;
	class ActionManager;
	class IconManager;
	class ModeManager;
	class ModeWidget;
	class ICore;

	class MainWindow : public QMainWindow
	{
		Q_OBJECT

		public:
			static MainWindow *instance();

		public:
			MainWindow(QSettings *settings, ProfileManager *profileManager);
			~MainWindow();

			void init();

			QSettings *settings() { return m_settings; }
			ProfileManager *profileManager() { return m_profileManager; }

		private slots:
			void aboutToClose();
			void showConsoleDialog();
			void showSettingsDialog();

		private:
			void readSettings();
			void writeSettings();

		private:
			static MainWindow *m_instance;
			ICore *m_iCore;
			QSettings *m_settings;
			ProfileManager *m_profileManager;
			ActionManager *m_actionManager;
			IconManager *m_iconManager;
			ModeManager *m_modeManager;
			ModeWidget *m_modeWidget;
	};

}

#endif // CORE_MAINWINDOW_H
