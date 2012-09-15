#include "mainwindow.h"

#include <settings/connectionsettings.h>
#include <settings/mainwindowsettings.h>
#include <settings/generalsettings.h>
#include <settings/settingsdialog.h>
#include <console/commandconsole.h>
#include <actions/actionmanager.h>
#include <console/consoledialog.h>
#include <console/debugconsole.h>
#include <console/iconconsole.h>
#include <modes/modemanager.h>
#include <icons/iconmanager.h>
#include <modes/modewidget.h>
#include <constants.h>
#include <trayicon.h>
#include <icore.h>

#include <QApplication>
#include <QSettings>
#include <QProcess>
#include <QDebug>

#ifdef Q_WS_WIN32
#include <qt_windows.h>
#endif

static const char settingsGroup[]			= "MainWindow";
static const char geometryKey[]				= "windowGeometry";
static const char hideOnStartupKey[]		= "hideOnStartup";
static const char toolWindowKey[]			= "isToolWindow";
static const char stateKey[]				= "windowState";
static const char alwaysOnTopKey[]			= "alwaysOnTop";
static const char autoHideTimeKey[]			= "autoHideTime";
static const char transparencyKey[]			= "transparency";
static const char dockingKey[]				= "Docking/enabled";
static const char dockingDistanceKey[]		= "Docking/distance";

namespace Core
{
	MainWindow *MainWindow::m_instance = 0;

	MainWindow::MainWindow(QSettings *settings, ProfileManager *profileManager) :
		m_iCore(new ICore()),
		m_settings(settings),
		m_profileManager(profileManager),
		m_actionManager(new ActionManager(this)),
		m_iconManager(new IconManager),
		m_modeManager(new ModeManager),
		m_modeWidget(new ModeWidget),
		m_trayIcon(new TrayIcon(m_actionManager, m_iconManager)),
		m_docking(false),
		m_dockingDistance(0)
	{
		m_instance = this;
		m_modeManager->setModeWidget(m_modeWidget);
		m_trayIcon->setToolTip(QString("lily.im v%1").arg(Constants::VERSION));
		m_autoHideTimer.setSingleShot(true);

		connect(qApp, SIGNAL(aboutToQuit()), SLOT(aboutToClose()));
		connect(&m_autoHideTimer, SIGNAL(timeout()), SLOT(hide()));

		setWindowTitle(QString("lily.im v%1").arg(Constants::VERSION));
		setCentralWidget(m_modeWidget);
	}

	MainWindow::~MainWindow()
	{
		delete m_actionManager;
		m_actionManager = 0;

		delete m_iconManager;
		m_iconManager = 0;

		delete m_modeManager;
		m_modeManager = 0;

		delete m_modeWidget;
		m_modeWidget = 0;

		delete m_trayIcon;
		m_trayIcon = 0;

		SettingsDialog::cleanup();
		ConsoleDialog::cleanup();
	}

	void MainWindow::init()
	{
		if(!m_settings)
			return;

		//icons
		m_iconManager->registerDefault(Constants::ICON_LILY, QPixmap(":/core/images/lily_48.png"));
		m_iconManager->registerDefault(Constants::ICON_SETTINGS, QPixmap(":/core/images/icons/wrench.png"));
		//m_iconManager->registerDefault(Constants::ICON_CLOSE, QPixmap(":/"));

		readSettings();

		m_settings->beginGroup(settingsGroup);
		if(!m_settings->value(hideOnStartupKey).toBool())
			show();
		m_settings->endGroup();

		//setting pages
		SettingsDialog::addPage(new SettingsPages::GeneralSettings());
		SettingsDialog::addPage(new SettingsPages::ConnectionSettings());
		SettingsDialog::addPage(new SettingsPages::MainWindowSettings());

		//consoles
		ConsoleDialog::addTab(new DebugConsole());
		ConsoleDialog::addTab(new CommandConsole());
		ConsoleDialog::addTab(new IconConsole(m_iconManager));

		//actions
		QAction *consoleAction = new QAction(tr("Console"), this);
		connect(consoleAction, SIGNAL(triggered()), SLOT(showConsoleDialog()));
		m_actionManager->registerAction(Constants::ACTION_CONSOLE, consoleAction);

		QAction *toggleAction = new QAction(tr("Show / Hide"), this);
		connect(toggleAction, SIGNAL(triggered()), SLOT(toggleWindow()));
		m_actionManager->registerAction(Constants::ACTION_TOGGLEMAIN, toggleAction);

		QAction *settingsAction = new QAction(tr("Settings"), this);
		settingsAction->setProperty("iconId", Constants::ICON_SETTINGS);
		connect(settingsAction, SIGNAL(triggered()), SLOT(showSettingsDialog()));
		m_actionManager->registerAction(Constants::ACTION_SETTINGS, settingsAction);

		QAction *aboutAction = new QAction(tr("About"), this);
		//aboutAction->setProperty("iconId", Constants::IMAGE_LILY48);
		m_actionManager->registerAction(Constants::ACTION_ABOUT, aboutAction);

		QAction *quitAction = new QAction(tr("Quit"), this);
		quitAction->setProperty("iconId", Constants::ICON_CLOSE);
		connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
		m_actionManager->registerAction(Constants::ACTION_QUIT, quitAction);

		//menus
		QMenu *mainMenu = new QMenu(this);
		m_actionManager->registerMenu(Constants::MENU_MAIN, mainMenu);

		QAction *mainMenuAction = mainMenu->menuAction();
		mainMenuAction->setText(tr("About"));
		//menuAction->setProperty("iconId", Constants::IMAGE_LILY48)
		m_actionManager->registerAction("Action.MainMenuAction", mainMenuAction);

		mainMenu->addAction(consoleAction);
		mainMenu->addAction(settingsAction);
		mainMenu->addAction(aboutAction);
		mainMenu->addAction(quitAction);

		//toolbars
		QToolBar *toolBar = m_actionManager->createToolBar(Constants::TOOLBAR_MAIN);
		toolBar->addAction(mainMenuAction);

		m_actionManager->createToolBar(Constants::TOOLBAR_PLUGINS);

		m_trayIcon->init();
	}

	bool MainWindow::isToolWindow() const
	{
		return (windowFlags() & Qt::Tool) == Qt::Tool;
	}

	void MainWindow::setToolWindow(const bool &toolWindow)
	{
		bool visible = isVisible();

		if(toolWindow) {
			setWindowFlags(windowFlags() | Qt::Tool);
		} else {
			setWindowFlags(windowFlags() & ~Qt::Tool);
		}

		setVisible(visible);
	}

	bool MainWindow::isAlwaysOnTop() const
	{
		return (windowFlags() & Qt::WindowStaysOnTopHint) == Qt::WindowStaysOnTopHint;
	}

	void MainWindow::setAlwaysOnTop(const bool &alwaysOnTop)
	{
		bool visible = isVisible();

		if(alwaysOnTop) {
			setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
		} else {
			setWindowFlags(windowFlags() & ~Qt::WindowStaysOnTopHint);
		}

		setVisible(visible);
	}

	int MainWindow::autoHideTime() const
	{
		return m_autoHideTimer.interval();
	}

	void MainWindow::setAutoHideTime(const int &msecs)
	{
		m_autoHideTimer.setInterval(msecs);
	}

	void MainWindow::leaveEvent(QEvent *event)
	{
		if(m_autoHideTimer.interval() > 0) {
			m_autoHideTimer.start();
		}
	}

	void MainWindow::enterEvent(QEvent *event)
	{
		m_autoHideTimer.stop();
	}

	void MainWindow::aboutToClose()
	{
		writeSettings();

		if(qApp->property("restart").toBool()) {
			QProcess::startDetached(qApp->applicationFilePath(), qApp->property("restartArguments").toStringList());
		}

		deleteLater();
	}

	void MainWindow::showConsoleDialog()
	{
		ICore::showConsoleDialog();
	}

	void MainWindow::showSettingsDialog()
	{
		ICore::showSettingsDialog();
	}

	void MainWindow::toggleWindow()
	{
		if(isVisible()) {
			if(isObscured()) {
				activateWindow();
				raise();
			} else {
				hide();
			}
		} else {
			show();
			activateWindow();
			raise();
		}
	}

	void MainWindow::readSettings()
	{
		m_settings->beginGroup(settingsGroup);

		restoreGeometry(m_settings->value(geometryKey).toByteArray());
		restoreState(m_settings->value(stateKey).toByteArray());
		setToolWindow(m_settings->value(toolWindowKey, true).toBool());
		setAlwaysOnTop(m_settings->value(alwaysOnTopKey).toBool());
		setAutoHideTime(m_settings->value(autoHideTimeKey).toInt());
		setWindowOpacity(m_settings->value(transparencyKey, 100).toInt() / 100.0);

		m_settings->endGroup();

		m_iconManager->readSettings(m_settings);
		m_modeManager->readSettings(m_settings);
		m_trayIcon->readSettings(m_settings);
	}

	void MainWindow::writeSettings()
	{
		if(!m_settings)
			return;

		m_settings->beginGroup(settingsGroup);
		m_settings->setValue(geometryKey, saveGeometry());
		m_settings->setValue(stateKey, saveState());
		m_settings->setValue(toolWindowKey, isToolWindow());
		m_settings->setValue(alwaysOnTopKey, isAlwaysOnTop());
		m_settings->setValue(autoHideTimeKey, autoHideTime());
		m_settings->setValue(transparencyKey, (int)(windowOpacity() * 100));
		m_settings->endGroup();

		m_modeManager->writeSettings(m_settings);
	}

	bool MainWindow::isObscured()
	{
#ifdef Q_WS_WIN32
		QList<HWND> visited;

		RECT rect;
		GetWindowRect(winId(), &rect);

		HWND hWnd = GetWindow(winId(), GW_HWNDPREV);
		while(hWnd) {
			if(visited.contains(hWnd)) {
				break;
			}

			visited.append(hWnd);

			if(IsWindowVisible(hWnd)) {
				RECT rect2;

				if(GetWindowRect(hWnd, &rect2)) {
					RECT intersect;

					if(IntersectRect(&intersect, &rect, &rect2)) {
						return true;
					}
				}
			}

			hWnd = GetWindow(hWnd, GW_HWNDPREV);
		}
#endif

		return false;
	}

	MainWindow *MainWindow::instance()
	{
		return m_instance;
	}
}
