#include "mainwindow.h"

#include <tabs/tabmanager.h>
#include <core_constants.h>
#include <jsonsettings.h>

#include <QtGui/QApplication>
#include <QtCore/QDebug>

static const char settingsGroup[]    = "MainWindow";
static const char geometryKey[]      = "windowGeometry";
static const char hideOnStartupKey[] = "hideOnStartup";
static const char isToolWindowKey[]  = "isToolWindow";
static const char stateKey[]         = "windowState";

namespace Core
{
	MainWindow *MainWindow::m_instance = 0;

	MainWindow::MainWindow(QWidget *parent) :
		QMainWindow(parent),
		m_settings(0),
		m_profileManager(0),
		m_tabManager(new TabManager),
		m_tabWidget(new QTabWidget)
	{
		m_instance = this;
		m_tabManager->setTabWidget(m_tabWidget);

		connect(qApp, SIGNAL(aboutToQuit()), SLOT(aboutToClose()));

		setWindowTitle(QString("kitty.im v%1").arg(Constants::VERSION));
		setCentralWidget(m_tabWidget);
	}

	MainWindow::~MainWindow()
	{
		delete m_tabManager;
		m_tabManager = 0;

		delete m_tabWidget;
		m_tabWidget = 0;
	}

	void MainWindow::init()
	{
		if(!m_settings)
			return;

		readSettings();

		m_settings->beginGroup(settingsGroup);
		if(!m_settings->value(hideOnStartupKey).toBool())
			show();
		m_settings->endGroup();
	}

	void MainWindow::aboutToClose()
	{
		writeSettings();
	}

	void MainWindow::readSettings()
	{
		m_settings->beginGroup(settingsGroup);

		restoreGeometry(m_settings->value(geometryKey).toByteArray());
		restoreState(m_settings->value(stateKey).toByteArray());

		if(m_settings->value(isToolWindowKey, true).toBool())
			setWindowFlags(windowFlags() | Qt::Tool);

		m_settings->endGroup();
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
	}

	MainWindow *MainWindow::instance()
	{
		return m_instance;
	}
}
