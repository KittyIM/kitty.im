#include "iconconsole.h"

#include <QGridLayout>
#include <QTreeWidget>
#include <QDebug>

#include <icons/iconmanager.h>
#include <constants.h>

namespace Core
{
	IconConsole::IconConsole(IconManager *iconManager) :
		IConsoleTab(Constants::CONSOLE_ICONS),
		m_iconManager(iconManager),
		m_iconTree(new QTreeWidget)
	{
		setText(tr("Icons"));

		m_iconTree->setHeaderHidden(true);
		m_iconTree->setIndentation(0);

		QGridLayout *layout = new QGridLayout(this);
		layout->setMargin(0);
		layout->addWidget(m_iconTree);
		setLayout(layout);

		refreshIcons();
	}

	IconConsole::~IconConsole()
	{
		delete m_iconTree;
		m_iconTree = 0;
	}

	void IconConsole::refreshIcons()
	{
		const QStringList iconIds = m_iconManager->allIds();

		m_iconTree->clear();

		foreach(const QString &iconId, iconIds) {
			QTreeWidgetItem *item = new QTreeWidgetItem(m_iconTree);
			item->setIcon(0, m_iconManager->icon(iconId));
			item->setText(0, iconId);
		}
	}
}
