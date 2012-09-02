#ifndef CORE_MODETABBAR_H
#define CORE_MODETABBAR_H

#include <QWidget>

namespace Core
{
	class IMode;

	class ModeTabBar : public QWidget
	{
		Q_OBJECT

		public:
			explicit ModeTabBar(QWidget *parent = 0);

			void insertTab(const int &index, IMode *mode);

			int count() const;
			QString tabIcon(const int &index) const;
			QString tabLabel(const int &index) const;
			bool isTabEnabled(const int &index) const;
			QRect tabRect(const int &index) const;

			QSize sizeHint() const;
			QSize minimumSizeHint() const;

			void setCurrentIndex(const int &currentIndex);
			int currentIndex() const { return m_currentIndex; }

		signals:
			void currentIndexChanged(const int &index);

		protected:
			void paintEvent(QPaintEvent *event);
			void mousePressEvent(QMouseEvent *event);
			void mouseMoveEvent(QMouseEvent *event);
			void leaveEvent(QEvent *event);

		private:
			QSize tabSizeHint() const;

		private:
			QList<IMode*> m_tabs;
			int m_currentIndex;
			int m_hoverIndex;
	};
}

#endif // CORE_MODETABBAR_H
