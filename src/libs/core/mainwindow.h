#ifndef CORE_MAINWINDOW_H
#define CORE_MAINWINDOW_H

#include "core_global.h"

#include <QtGui/QMainWindow>

namespace Core
{
	class ProfileManager;
	class JsonSettings;
	class ModeManager;
	class ModeWidget;

	class CORE_EXPORT MainWindow : public QMainWindow
	{
		Q_OBJECT

		public:
			static MainWindow *instance();

		public:
			explicit MainWindow(QWidget *parent = 0);
			~MainWindow();

			void init();

			void setSettings(JsonSettings *settings) { m_settings = settings; }
			JsonSettings *settings() { return m_settings; }

			void setProfileManager(ProfileManager *profileManager) { m_profileManager = profileManager; }
			ProfileManager *profileManager() { return m_profileManager; }

		private slots:
			void aboutToClose();

		private:
			void readSettings();
			void writeSettings();

		private:
			static MainWindow *m_instance;
			JsonSettings *m_settings;
			ProfileManager *m_profileManager;
			ModeManager *m_modeManager;
			ModeWidget *m_modeWidget;
	};

}

#endif // CORE_MAINWINDOW_H
