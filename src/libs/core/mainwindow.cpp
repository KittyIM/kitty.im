#include "mainwindow.h"

#include <settings/connectionsettings.h>
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
#include <core_constants.h>
#include <icore.h>

#include <QApplication>
#include <QSettings>
#include <QProcess>
#include <QDebug>

static const char settingsGroup[]    = "MainWindow";
static const char geometryKey[]      = "windowGeometry";
static const char hideOnStartupKey[] = "hideOnStartup";
static const char isToolWindowKey[]  = "isToolWindow";
static const char stateKey[]         = "windowState";

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
		m_modeWidget(new ModeWidget)
	{
		m_instance = this;
		m_modeManager->setModeWidget(m_modeWidget);

		connect(qApp, SIGNAL(aboutToQuit()), SLOT(aboutToClose()));

		setWindowTitle(QString("kitty.im v%1").arg(Constants::VERSION));
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

		SettingsDialog::cleanup();
		ConsoleDialog::cleanup();
	}

	void MainWindow::init()
	{
		if(!m_settings)
			return;

		//icons
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

		//consoles
		ConsoleDialog::addTab(new DebugConsole());
		ConsoleDialog::addTab(new CommandConsole());
		ConsoleDialog::addTab(new IconConsole(m_iconManager));

		//toolbars
		QToolBar *toolBar = m_actionManager->createToolBar(Constants::TOOLBAR_MAIN);
		m_actionManager->createToolBar(Constants::TOOLBAR_PLUGINS);

		//actions
		QAction *consoleAction = new QAction(tr("Console"), this);
		connect(consoleAction, SIGNAL(triggered()), SLOT(showConsoleDialog()));
		m_actionManager->registerAction(Constants::ACTION_CONSOLE, consoleAction);

		QAction *settingsAction = new QAction(tr("Settings"), this);
		settingsAction->setProperty("iconId", Constants::ICON_SETTINGS);
		connect(settingsAction, SIGNAL(triggered()), SLOT(showSettingsDialog()));
		m_actionManager->registerAction(Constants::ACTION_SETTINGS, settingsAction);

		QAction *aboutAction = new QAction(tr("About"), this);
		//aboutAction->setProperty("iconId", Constants::IMAGE_KITTY48);
		m_actionManager->registerAction(Constants::ACTION_ABOUT, aboutAction);

		QAction *quitAction = new QAction(tr("Quit"), this);
		quitAction->setProperty("iconId", Constants::ICON_CLOSE);
		connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
		m_actionManager->registerAction(Constants::ACTION_QUIT, quitAction);

		//menus
		QMenu *mainMenu = new QMenu(this);

		QAction *mainMenuAction = mainMenu->menuAction();
		//menuAction->setProperty("iconId", Constants::IMAGE_KITTY48)
		m_actionManager->registerAction("Action.MainMenuAction", mainMenuAction);

		mainMenuAction->setText(tr("About"));
		mainMenu->addAction(consoleAction);
		mainMenu->addAction(settingsAction);
		mainMenu->addAction(aboutAction);
		mainMenu->addAction(quitAction);
		toolBar->addAction(mainMenuAction);
	}

	void MainWindow::aboutToClose()
	{
		writeSettings();

		if(qApp->property("restart").toBool()) {
			QProcess::startDetached(qApp->applicationFilePath(), qApp->property("restartArguments").toStringList());
		}
	}

	void MainWindow::showConsoleDialog()
	{
		ICore::showConsoleDialog(this);
	}

	void MainWindow::showSettingsDialog()
	{
		ICore::showSettingsDialog(this);
	}

	void MainWindow::readSettings()
	{
		m_settings->beginGroup(settingsGroup);

		restoreGeometry(m_settings->value(geometryKey).toByteArray());
		restoreState(m_settings->value(stateKey).toByteArray());

		if(m_settings->value(isToolWindowKey, true).toBool())
			setWindowFlags(windowFlags() | Qt::Tool);

		m_settings->endGroup();

		m_iconManager->readSettings(m_settings);
		m_modeManager->readSettings(m_settings);
	}

	void MainWindow::writeSettings()
	{
		if(!m_settings)
			return;

		m_settings->beginGroup(settingsGroup);
		m_settings->setValue(geometryKey, saveGeometry());
		m_settings->setValue(stateKey, saveState());
		m_settings->setValue(isToolWindowKey, (windowFlags() & Qt::Tool) == Qt::Tool);
		m_settings->endGroup();

		m_modeManager->writeSettings(m_settings);
	}

	MainWindow *MainWindow::instance()
	{
		return m_instance;
	}
}
