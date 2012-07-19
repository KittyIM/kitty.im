#include "modemanager.h"

#include <QtCore/QDebug>
#include <QtCore/QList>
#include <QtGui/QTabWidget>

#include <modes/modewidget.h>
#include <jsonsettings.h>
#include <modes/imode.h>

static const char tabsGroup[] = "Tabs";

namespace Core
{
	ModeManager *ModeManager::m_instance = 0;

	ModeManager::ModeManager() :
		QObject(0),
		m_modeWidget(0)
	{
		m_instance = this;
	}

	void ModeManager::addMode(IMode *mode)
	{
		if(!m_modeWidget)
			return;

		int index = m_modes.count();

		m_modes.insert(index, mode);
		m_modeWidget->insertMode(index, mode);
	}

	void ModeManager::readSettings(JsonSettings *settings)
	{
		settings->beginGroup(tabsGroup);
		settings->endGroup();
	}

	void ModeManager::writeSettings(JsonSettings *settings)
	{
		settings->beginGroup(tabsGroup);
		settings->endGroup();
	}

	void ModeManager::analyze()
	{
		for(int i = 0; i < m_modeWidget->count(); ++i) {
			//qDebug() << i << m_modeWidget->widget(i)->windowTitle();
		}
	}

	ModeManager *ModeManager::instance()
	{
		return m_instance;
	}
}
