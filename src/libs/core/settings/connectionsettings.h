#ifndef CORE_SETTINGSPAGES_CONNECTIONSETTINGS_H
#define CORE_SETTINGSPAGES_CONNECTIONSETTINGS_H

#include "isettingspage.h"

#include <QWidget>

namespace Core
{
	namespace SettingsPages
	{
		namespace Ui { class ConnectionSettingsWidget; }
		class ConnectionSettingsWidget;

		class ConnectionSettings : public ISettingsPage
		{
				Q_OBJECT

			public:
				ConnectionSettings();

				QWidget *createWidget();
				void apply();
				void finish();

			private:
				ConnectionSettingsWidget *m_widget;
		};

		class ConnectionSettingsWidget : public QWidget
		{
				Q_OBJECT

			public:
				ConnectionSettingsWidget();
				Ui::ConnectionSettingsWidget *ui;
		};
	}
}

#endif // CORE_SETTINGSPAGES_CONNECTIONSETTINGS_H
