#include "modetabbar.h"

#include <modes/imode.h>

#include <QMouseEvent>
#include <QPainter>
#include <QDebug>

static const int tabPadding = 4;
static const int iconSize = 32;

namespace Core
{
	ModeTabBar::ModeTabBar(QWidget *parent) :
		QWidget(parent),
		m_currentIndex(0),
		m_hoverIndex(-1)
	{
		setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
		//setMinimumWidth(60);
		setMouseTracking(true);
	}

	void ModeTabBar::insertTab(const int &index, IMode *mode)
	{
		m_tabs.insert(index, mode);
		updateGeometry();
	}

	int ModeTabBar::count() const
	{
		return m_tabs.count();
	}

	QIcon ModeTabBar::tabIcon(const int &index) const
	{
		Q_ASSERT((index >= 0) && (index < count()));

		return m_tabs[index]->icon();
	}

	QString ModeTabBar::tabLabel(const int &index) const
	{
		Q_ASSERT((index >= 0) && (index < count()));

		return m_tabs[index]->label();
	}

	bool ModeTabBar::isTabEnabled(const int &index) const
	{
		Q_ASSERT((index >= 0) && (index < count()));

		return m_tabs[index]->isEnabled();
	}

	QRect ModeTabBar::tabRect(const int &index) const
	{
		QSize size = tabSizeHint();

		//shrink tabs if necessary
		if(size.height() * count() > height()) {
			size.setHeight(height() / count());
		}

		return QRect(0, index * size.height() + tabPadding, size.width(), size.height());
	}

	void ModeTabBar::paintEvent(QPaintEvent *event)
	{
		QPainter p(this);
		//p.translate(0, 2);

		QLinearGradient bgGrad(rect().topLeft(), rect().topRight());
		bgGrad.setColorAt(0.5, palette().color(QPalette::Window));
		bgGrad.setColorAt(1.0, palette().color(QPalette::Midlight));
		p.fillRect(rect(), bgGrad);

		p.setPen(palette().color(QPalette::Shadow));
		p.drawLine(width() - 1, 0, width() - 1, height());

		for(int i = 0; i < count(); ++i) {
			p.save();

			QFont labelFont = font();
			labelFont.setBold(true);
			p.setFont(labelFont);

			QRect rect = tabRect(i);

			int textHeight = p.fontMetrics().boundingRect(QRect(0, 0, width(), height()), 0, tabLabel(i)).height();
			QRect labelRect(QPoint(rect.left() + tabPadding, rect.bottom() - textHeight - tabPadding), QSize(rect.width() - (tabPadding * 2), textHeight));

			int iconSize = rect.height() - textHeight - (3 * tabPadding);
			QRect iconRect(QPoint((rect.width() - iconSize) / 2, rect.top() + tabPadding), QSize(iconSize, iconSize));

			bool isSelected = (i == m_currentIndex);
			bool isEnabled = isTabEnabled(i);
			bool isHovered = (i == m_hoverIndex);

			if(isSelected) {
				p.save();

				p.setPen(palette().color(QPalette::Shadow));
				p.drawLine(rect.topLeft(), rect.topRight());
				p.drawLine(rect.bottomLeft(), rect.bottomRight());

				p.fillRect(rect.adjusted(0, 0, -1, 0), QColor(0, 0, 0, 32));
				p.translate(rect.width() - 6, rect.top() + (rect.height() / 2) - 12);

				QPolygon arrowPoly;
				arrowPoly.append(QPoint(7, 0));
				arrowPoly.append(QPoint(7, 24));
				arrowPoly.append(QPoint(0, 12));

				p.translate(0, 1);
				p.setBrush(palette().color(QPalette::Shadow));
				p.setPen(palette().color(QPalette::Shadow));
				p.setRenderHint(QPainter::Antialiasing);
				p.drawPolygon(arrowPoly);

				p.translate(0, -1);
				p.setBrush(palette().color(QPalette::Light));
				p.drawPolygon(arrowPoly);

				p.restore();
			}

			if(isHovered && isEnabled) {
				p.fillRect(rect.adjusted(0, 0, -1, 0), QColor(0, 0, 0, 16));
			}

			if(!isEnabled)
				p.setOpacity(0.6);

			QPixmap icon = tabIcon(i).pixmap(iconSize, iconSize, isEnabled ? QIcon::Normal : QIcon::Disabled);

			p.drawPixmap(iconRect, icon);

			p.setPen(palette().color(QPalette::Text));
			p.drawText(labelRect, Qt::AlignCenter, tabLabel(i));
			p.restore();
		}
	}

	void ModeTabBar::mousePressEvent(QMouseEvent *event)
	{
		QPoint pressPos = event->pos();
		for(int i = 0; i < count(); ++i) {
			if(tabRect(i).contains(pressPos) && isTabEnabled(i)) {
				setCurrentIndex(i);
				break;
			}
		}
	}

	void ModeTabBar::mouseMoveEvent(QMouseEvent *event)
	{
		int hoverIndex = -1;

		QPoint pressPos = event->pos();
		for(int i = 0; i < count(); ++i) {
			if(tabRect(i).contains(pressPos)) {
				hoverIndex = i;
				break;
			}
		}

		if(hoverIndex == m_hoverIndex)
			return;

		m_hoverIndex = hoverIndex;
		update();
	}

	void ModeTabBar::leaveEvent(QEvent *event)
	{
		m_hoverIndex = -1;
		update();
	}

	QSize ModeTabBar::sizeHint() const
	{
		QSize size = tabSizeHint();

		return QSize(size.width(), size.height() * count());
	}

	QSize ModeTabBar::minimumSizeHint() const
	{
		QSize size = tabSizeHint();

		return QSize(size.width(), (size.height() - iconSize) * count());
	}

	QSize ModeTabBar::tabSizeHint() const
	{
		QFont labelFont = font();
		labelFont.setBold(true);

		QFontMetrics fm(labelFont);

		int maxWidth = minimumWidth();
		for(int i = 0; i < count(); ++i) {
			maxWidth = qMax(maxWidth, fm.width(tabLabel(i)) + 3 * tabPadding);
		}

		return QSize(maxWidth, iconSize + fm.height() + (3 * tabPadding));
	}

	void ModeTabBar::setCurrentIndex(const int &currentIndex)
	{
		if(currentIndex ==  m_currentIndex)
			return;

		m_currentIndex = currentIndex;
		update();
		emit currentIndexChanged(currentIndex);
	}

}
