#ifndef CORE_MODEWIDGET_H
#define CORE_MODEWIDGET_H

#include <QtGui/QWidget>

class QStackedLayout;

namespace Core
{
	class ModeTabBar;
	class IMode;

	class ModeWidget : public QWidget
	{
		Q_OBJECT

		public:
			ModeWidget(QWidget *parent = 0);

			void insertMode(const int &index, IMode *mode);

			int count() const;

		private:
			ModeTabBar *m_tabBar;
			QStackedLayout* m_stackedLayout;
	};
}

#endif // CORE_MODEWIDGET_H
