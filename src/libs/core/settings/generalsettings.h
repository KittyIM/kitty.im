#ifndef CORE_SETTINGSPAGES_GENERALSETTINGS_H
#define CORE_SETTINGSPAGES_GENERALSETTINGS_H

#include "isettingspage.h"

#include <QWidget>

namespace Core
{
	namespace SettingsPages
	{
		namespace Ui { class GeneralSettingsWidget; }
		class GeneralSettingsWidget;

		class GeneralSettings : public Core::ISettingsPage
		{
			Q_OBJECT

			public:
				GeneralSettings();

				QWidget *createWidget();
				void apply();
				void finish();

			private:
				GeneralSettingsWidget *m_widget;
		};

		class GeneralSettingsWidget : public QWidget
		{
			Q_OBJECT

			public:
				GeneralSettingsWidget();
				Ui::GeneralSettingsWidget *ui;
		};
	}
}

#endif // CORE_SETTINGSPAGES_GENERALSETTINGS_H
