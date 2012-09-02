#include "trayicon.h"

#include <QSystemTrayIcon>

#include <icore.h>

namespace Core
{
	TrayIcon *TrayIcon::m_instance = 0;

	TrayIcon *TrayIcon::instance()
	{
		return m_instance;
	}

	TrayIcon::TrayIcon(QObject *parent) :
		QObject(parent),
		m_trayIcon(new QSystemTrayIcon),
		m_blink(false)
	{
		m_instance = this;

		connect(&m_blinkTimer, SIGNAL(timeout()), SLOT(blinkIcon()));
		connect(&m_timeoutTimer, SIGNAL(timeout()), SLOT(stopBlinking()));
	}

	TrayIcon::~TrayIcon()
	{
		delete m_trayIcon;
		m_trayIcon = 0;

		m_instance = 0;
	}

	void TrayIcon::setIcon(const QString &iconId)
	{
		m_iconId = iconId;
		m_trayIcon->setIcon(ICore::icon(iconId));

		if(!m_trayIcon->isVisible())
			m_trayIcon->show();
	}

	void TrayIcon::setBlinkingIcon(const QString &iconId, const int &msecs, const int &timeout)
	{
		m_prevIconId = m_iconId;
		m_iconId = iconId;

		m_blinkTimer.start(msecs);
		if(timeout > 0)
			m_timeoutTimer.start(timeout);
	}

	void TrayIcon::stopBlinking()
	{
		m_blinkTimer.stop();
		m_timeoutTimer.stop();
		setIcon(m_prevIconId);
	}

	void TrayIcon::setToolTip(const QString &toolTip)
	{
		m_trayIcon->setToolTip(toolTip);
	}

	void TrayIcon::blinkIcon()
	{
		m_trayIcon->setIcon(m_blink ? ICore::icon(m_iconId) : QIcon());
		m_blink = !m_blink;
	}
}
