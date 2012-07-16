#include "mainwindow.h"

#include <tabs/tabmanager.h>
#include <core_constants.h>
#include <jsonsettings.h>

#include <QtGui/QApplication>
#include <QtCore/QDebug>
#include <QPushButton>

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
		readSettings();
	}

	void MainWindow::aboutToClose()
	{
		writeSettings();
	}

	void MainWindow::readSettings()
	{
		if(!m_settings)
			return;

		m_settings->beginGroup("MainWindow");

		restoreGeometry(m_settings->value("geometry").toByteArray());
		restoreState(m_settings->value("state").toByteArray());

		if(m_settings->value("tool").toBool())
			setWindowFlags(windowFlags() | Qt::Tool);

		m_settings->endGroup();
	}

	void MainWindow::writeSettings()
	{
		if(!m_settings)
			return;

		m_settings->beginGroup("MainWindow");
		m_settings->setValue("geometry", saveGeometry());
		m_settings->setValue("state", saveState());
		m_settings->setValue("tool", (windowFlags() & Qt::Tool) == Qt::Tool);
		m_settings->endGroup();
	}

	MainWindow *MainWindow::instance()
	{
		return m_instance;
	}
}
