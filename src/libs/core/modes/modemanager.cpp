#include "modemanager.h"

#include <QtCore/QDebug>
#include <QtCore/QList>
#include <QtGui/QTabWidget>

#include <modes/modewidget.h>
#include <jsonsettings.h>
#include <modes/imode.h>
#include <mainwindow.h>

static const char modesGroup[] = "Modes";

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
		settings->beginGroup(modesGroup);
		settings->endGroup();
	}

	void ModeManager::writeSettings(JsonSettings *settings)
	{
		settings->beginGroup(modesGroup);
		settings->endGroup();
	}

	IMode *ModeManager::currentMode()
	{
		const int idx = m_modeWidget->currentIndex();

		if(idx < 0)
			return 0;

		return m_modes[idx];
	}

	void ModeManager::setModeWidget(ModeWidget *modeWidget)
	{
		 m_modeWidget = modeWidget;
		 connect(m_modeWidget, SIGNAL(currentIndexChanged(int)), SLOT(setCurrentIndex(int)));
	}

	void ModeManager::setCurrentIndex(const int &index)
	{
		if((index < 0) || (index > m_modes.count() - 1))
			return;

		emit currentModeChanged(m_modes[index]);
	}

	ModeManager *ModeManager::instance()
	{
		return m_instance;
	}
}
