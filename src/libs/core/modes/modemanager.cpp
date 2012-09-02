#include "modemanager.h"

#include <QTabWidget>
#include <QDebug>
#include <QList>

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

	ModeManager::~ModeManager()
	{
		qDeleteAll(m_modes);
		m_modes.clear();

		m_instance = 0;
	}

	void ModeManager::addMode(IMode *mode)
	{
		if(!m_modeWidget)
			return;

		int index = m_modes.count();

		m_modes.insert(index, mode);
		m_modeWidget->insertMode(index, mode);

		emit modeAdded(mode->id());
		emit modeListChanged();
	}

	void ModeManager::readSettings(QSettings *settings)
	{
		settings->beginGroup(modesGroup);
		settings->endGroup();
	}

	void ModeManager::writeSettings(QSettings *settings)
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
