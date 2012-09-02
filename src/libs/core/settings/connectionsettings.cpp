#include "connectionsettings.h"
#include "ui_connectionsettingswidget.h"

#include <core_constants.h>
#include <icore.h>

#include <QSettings>

const char connectionGroup[]			= "App/Connection";
const char sleepDisconnectKey[]		= "sleepDisconnect";
const char wakeupConnectKey[]		= "wakeupConnect";
const char autoReconnectKey[]		= "autoReconnect";
const char connectionProxyGroup[]	= "Proxy";

namespace Core
{
	namespace SettingsPages
	{
		ConnectionSettings::ConnectionSettings() :
			m_widget(0)
		{
			m_name = tr("Connection");
			m_id = Constants::SETTINGS_CONNECTION;
			m_parentId = Constants::SETTINGS_GENERAL;
		}

		QWidget *ConnectionSettings::createWidget()
		{
			m_widget = new ConnectionSettingsWidget();

			return m_widget;
		}

		void ConnectionSettings::apply()
		{
			QSettings *settings = ICore::settings();
			settings->beginGroup(connectionGroup);

			settings->endGroup();
		}

		void ConnectionSettings::finish()
		{
			if(!m_widget)
				return;

			delete m_widget;
			m_widget = 0;
		}

		ConnectionSettingsWidget::ConnectionSettingsWidget() :
			ui(new Ui::ConnectionSettingsWidget)
		{
			ui->setupUi(this);
		}

	}
}
