#ifndef CORE_ACTIONMANAGER_H
#define CORE_ACTIONMANAGER_H

#include "../global.h"

#include <QToolBar>
#include <QAction>
#include <QDebug>
#include <QHash>
#include <QMenu>

class QToolBar;

namespace Core
{
	class JsonSettings;

	class CORE_EXPORT ActionManager : public QObject
	{
		Q_OBJECT

		public:
			static ActionManager *instance() { return m_instance; }

		public:
			ActionManager(QMainWindow *mainWindow, QObject *parent = 0);
			~ActionManager();

			QToolBar *createToolBar(const QString &id);
			void removeToolBar(const QString &id);
			QToolBar *toolBar(const QString &id);

			void registerAction(const QString &id, QAction *action);
			void unregisterAction(const QString &id);
			QAction *action(const QString &id);

			void registerMenu(const QString &id, QMenu *menu);
			void unregisterMenu(const QString &id);
			QMenu *menu(const QString &id);

			QStringList toolBarIds() const;
			QStringList menuIds() const;
			QStringList actionIds() const;

			void readSettings(JsonSettings *settings);
			void writeSettings(JsonSettings *settings);

		public slots:
			void refreshIcons();

		signals:
			void actionRegistered(const QString &id);
			void actionListChanged();
			void menuRegistered(const QString &id);
			void menuListChanged();

		private:
			static ActionManager *m_instance;

		private:
			QHash<QString, QAction*> m_actions;
			QHash<QString, QMenu*> m_menus;
			QHash<QString, QToolBar*> m_toolBars;
			QMainWindow *m_mainWindow;
	};
}

#endif // CORE_ACTIONMANAGER_H
