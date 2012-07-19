#include "modewidget.h"

#include <modes/modetabbar.h>
#include <modes/imode.h>

#include <QStackedLayout>
#include <QHBoxLayout>

namespace Core
{
	ModeWidget::ModeWidget(QWidget *parent) :
		QWidget(parent),
		m_tabBar(new ModeTabBar),
		m_stackedLayout(new QStackedLayout)
	{
		connect(m_tabBar, SIGNAL(currentIndexChanged(int)), m_stackedLayout, SLOT(setCurrentIndex(int)));

		QHBoxLayout *layout = new QHBoxLayout(this);
		layout->setMargin(0);
		layout->setSpacing(0);

		layout->addWidget(m_tabBar);
		layout->addLayout(m_stackedLayout);

		setLayout(layout);
	}

	void ModeWidget::insertMode(const int &index, IMode *mode)
	{
		m_tabBar->insertTab(index, mode);
		m_stackedLayout->insertWidget(index, mode->widget());
	}

	int ModeWidget::count() const
	{
		return m_tabBar->count();
	}

}
