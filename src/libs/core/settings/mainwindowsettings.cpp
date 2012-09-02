#include "mainwindowsettings.h"
#include "ui_mainwindowsettingswidget.h"

#include <core_constants.h>
#include <mainwindow.h>
#include <icore.h>

#include <QSettings>

static const char settingsGroup[]			= "MainWindow";
static const char hideOnStartupKey[]		= "hideOnStartup";

namespace Core
{
	namespace SettingsPages
	{
		MainWindowSettings::MainWindowSettings() :
			m_widget(0)
		{
			m_name = tr("Main window");
			m_id = Constants::SETTINGS_MAINWINDOW;
			m_parentId = Constants::SETTINGS_GENERAL;
		}

		QWidget *MainWindowSettings::createWidget()
		{
			m_widget = new MainWindowSettingsWidget();

			MainWindow *mainWindow = MainWindow::instance();

			QSettings *settings = ICore::settings();
			settings->beginGroup(settingsGroup);

			m_widget->ui->hideOnStartupCheckBox->setChecked(settings->value(hideOnStartupKey).toBool());
			m_widget->ui->hideFromTaskbarCheckBox->setChecked(mainWindow->isToolWindow());
			m_widget->ui->alwaysOnTopCheckBox->setChecked(mainWindow->isAlwaysOnTop());
			m_widget->ui->autoHideSlider->setValue(mainWindow->autoHideTime() / 1000);
			m_widget->ui->transparencySlider->setValue(mainWindow->windowOpacity() * 100);
			m_widget->ui->dockToEdgesCheckBox->setChecked(mainWindow->isDocking());
			m_widget->ui->dockDistanceSpinBox->setValue(mainWindow->dockingDistance());

			settings->endGroup();

			return m_widget;

		}

		void MainWindowSettings::apply()
		{
			if(!m_widget)
				return;

			MainWindow *mainWindow = MainWindow::instance();

			QSettings *settings = ICore::settings();
			settings->beginGroup(settingsGroup);
			settings->setValue(hideOnStartupKey, m_widget->ui->hideOnStartupCheckBox->isChecked());

			mainWindow->setToolWindow(m_widget->ui->hideFromTaskbarCheckBox->isChecked());
			mainWindow->setAlwaysOnTop(m_widget->ui->alwaysOnTopCheckBox->isChecked());
			mainWindow->setAutoHideTime(m_widget->ui->autoHideSlider->value() * 1000);
			mainWindow->setWindowOpacity(m_widget->ui->transparencySlider->value() / 100.0);
			mainWindow->setDocking(m_widget->ui->dockToEdgesCheckBox->isChecked());
			mainWindow->setDockingDistance(m_widget->ui->dockDistanceSpinBox->value());

			settings->endGroup();
		}

		void MainWindowSettings::finish()
		{
			if(!m_widget)
				return;

			delete m_widget;
			m_widget = 0;
		}

		MainWindowSettingsWidget::MainWindowSettingsWidget() :
			ui(new Ui::MainWindowSettingsWidget)
		{
			ui->setupUi(this);
		}
	}
}
