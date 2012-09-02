#ifndef CORE_SETTINGSPAGES_MAINWINDOWSETTINGS_H
#define CORE_SETTINGSPAGES_MAINWINDOWSETTINGS_H

#include "isettingspage.h"

#include <QWidget>

namespace Core
{
	namespace SettingsPages
	{
		namespace Ui { class MainWindowSettingsWidget; }
		class MainWindowSettingsWidget;

		class MainWindowSettings : public Core::ISettingsPage
		{
			Q_OBJECT

			public:
				MainWindowSettings();

				QWidget *createWidget();
				void apply();
				void finish();

			private:
				MainWindowSettingsWidget *m_widget;
		};

		class MainWindowSettingsWidget : public QWidget
		{
			Q_OBJECT

			public:
				MainWindowSettingsWidget();
				Ui::MainWindowSettingsWidget *ui;
		};
	}
}

#endif // CORE_SETTINGSPAGES_MAINWINDOWSETTINGS_H
