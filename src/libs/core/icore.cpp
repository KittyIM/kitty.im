#include "icore.h"

#include <settings/settingsdialog.h>
#include <actions/actionmanager.h>
#include <console/consoledialog.h>
#include <icons/iconmanager.h>
#include <mainwindow.h>

#include <QApplication>
#include <QVariant>

namespace Core
{
	MainWindow *ICore::m_mainWindow = 0;

	void ICore::initMainWindow(QSettings *settings, ProfileManager *profileManager)
	{
		if(m_mainWindow)
			return;

		m_mainWindow = new MainWindow(settings, profileManager);
		m_mainWindow->init();
	}

	void ICore::showConsoleDialog()
	{
		ConsoleDialog::instance()->show();
	}

	void ICore::showSettingsDialog(const QString &currentPage)
	{
		SettingsDialog *dlg = SettingsDialog::instance();
		if(!currentPage.isEmpty())
			dlg->setCurrentPage(currentPage);
		dlg->show();
	}

	QString ICore::uiLocale()
	{
		return qApp->property("kittyim_locale").toString();
	}

	QSettings *ICore::settings()
	{
		return m_mainWindow->settings();
	}

	QMainWindow *ICore::mainWindow()
	{
		return m_mainWindow;
	}

	QPixmap ICore::icon(const QString &id)
	{
		if(!m_mainWindow)
			return QPixmap();

		return IconManager::instance()->icon(id);
	}

	QAction *ICore::action(const QString &id)
	{
		if(!m_mainWindow)
			return 0;

		return ActionManager::instance()->action(id);
	}

	void ICore::restart(const QStringList &arguments)
	{
		qApp->setProperty("restart", true);
		qApp->setProperty("restartArguments", arguments);
		qApp->quit();
	}

}
