#ifndef CORE_MAINWINDOW_H
#define CORE_MAINWINDOW_H

#include "core_global.h"

#include <QMainWindow>
#include <QTimer>

class QSettings;

namespace Core
{
	class ProfileManager;
	class ActionManager;
	class IconManager;
	class ModeManager;
	class ModeWidget;
	class TrayIcon;
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

			bool isToolWindow() const;
			void setToolWindow(const bool &toolWindow);

			bool isAlwaysOnTop() const;
			void setAlwaysOnTop(const bool &alwaysOnTop);

			int autoHideTime() const;
			void setAutoHideTime(const int &msecs);

			bool isDocking() const	{ return m_docking; }
			void setDocking(const bool &docking) { m_docking = docking; }
			int dockingDistance() const	{ return m_dockingDistance; }
			void setDockingDistance(const int &px) { m_dockingDistance = px; }

		protected:
			void leaveEvent(QEvent *event);
			void enterEvent(QEvent *event);

		private slots:
			void aboutToClose();
			void showConsoleDialog();
			void showSettingsDialog();
            void toggleWindow();

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
            TrayIcon *m_trayIcon;
			QTimer m_autoHideTimer;
			bool m_docking; //TODO
			int m_dockingDistance;
	};

}

#endif // CORE_MAINWINDOW_H
