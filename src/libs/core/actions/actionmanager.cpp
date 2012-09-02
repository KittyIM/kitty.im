#include "actionmanager.h"

#include <QToolBar>
#include <QAction>
#include <QMenu>

#include <mainwindow.h>
#include <icore.h>

const char actionsGroup[] = "Actions";

namespace Core
{
	ActionManager *ActionManager::m_instance = 0;

	ActionManager::ActionManager(QMainWindow *mainWindow, QObject *parent) :
		QObject(parent),
		m_mainWindow(mainWindow)
	{
		m_instance = this;
	}

	ActionManager::~ActionManager()
	{
		qDeleteAll(m_actions);
		m_actions.clear();

		m_instance = 0;
	}

	QToolBar *ActionManager::createToolBar(const QString &id)
	{
		if(m_toolBars.contains(id))
			return m_toolBars.value(id);

		QToolBar *toolBar = new QToolBar();
		toolBar->setObjectName(id);
		toolBar->setFloatable(false);
		m_mainWindow->addToolBar(toolBar);

		m_toolBars.insert(id, toolBar);

		return toolBar;
	}

	void ActionManager::removeToolBar(const QString &id)
	{
		if(!m_toolBars.contains(id))
			return;

		//TODO
	}

	QToolBar *ActionManager::toolBar(const QString &id)
	{
		return m_toolBars.value(id);
	}

	void ActionManager::registerAction(const QString &id, QAction *action)
	{
		if(m_actions.contains(id))
			return;

		m_actions.insert(id, action);
		action->setIcon(ICore::icon(action->property("iconId").toString()));

		emit actionRegistered(id);
		emit actionListChanged();
	}

	void ActionManager::unregisterAction(const QString &id)
	{
		if(!m_actions.contains(id))
			return;

		//TODO
		//m_actions.remove(id);

		emit actionListChanged();
	}

	QAction *ActionManager::action(const QString &id)
	{
		return m_actions.value(id);
	}

	void ActionManager::registerMenu(const QString &id, QMenu *menu)
	{
		if(m_menus.contains(id))
			return;

		m_menus.insert(id, menu);

		emit menuRegistered(id);
		emit menuListChanged();
	}

	void ActionManager::unregisterMenu(const QString &id)
	{
		if(!m_menus.contains(id))
			return;

		//TODO

		emit menuListChanged();
	}

	QMenu *ActionManager::menu(const QString &id)
	{
		return m_menus.value(id);
	}

	QStringList ActionManager::toolBarIds() const
	{
		QStringList ids = m_toolBars.keys();
		qSort(ids);

		return ids;
	}

	QStringList ActionManager::menuIds() const
	{
		QStringList ids = m_menus.keys();
		qSort(ids);

		return ids;
	}

	QStringList ActionManager::actionIds() const
	{
		QStringList ids = m_actions.keys();
		qSort(ids);

		return ids;
	}

	void ActionManager::readSettings(JsonSettings *settings)
	{

	}

	void ActionManager::writeSettings(JsonSettings *settings)
	{

	}

	void ActionManager::refreshIcons()
	{
		QHashIterator<QString, QAction*> it(m_actions);
		while(it.hasNext()) {
			it.next();

			it.value()->setIcon(ICore::icon(it.value()->property("iconId").toString()));
		}
	}
}
