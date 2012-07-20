#include "actionmanager.h"

const char actionsGroup[] = "Actions";

namespace Core
{
	ActionManager *ActionManager::m_instance = 0;

	ActionManager::ActionManager(QObject *parent) :
		QObject(parent)
	{
		m_instance = this;
	}

	void ActionManager::readSettings(JsonSettings *settings)
	{

	}

	void ActionManager::writeSettings(JsonSettings *settings)
	{

	}
}
