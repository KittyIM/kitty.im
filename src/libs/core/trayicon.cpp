#include "trayicon.h"

#include <actions/actionmanager.h>
#include <icons/iconmanager.h>
#include <constants.h>

#include <QMenu>

namespace Core
{
	TrayIcon *TrayIcon::m_instance = 0;

	TrayIcon *TrayIcon::instance()
	{
		return m_instance;
	}

	TrayIcon::TrayIcon(ActionManager *actionManager, IconManager *iconManager, QObject *parent) :
		QObject(parent),
		m_actionManager(actionManager),
		m_iconManager(iconManager),
		m_trayIcon(new QSystemTrayIcon),
		m_blink(false)
	{
		m_instance = this;

		connect(&m_blinkTimer, SIGNAL(timeout()), SLOT(blinkIcon()));
		connect(&m_timeoutTimer, SIGNAL(timeout()), SLOT(stopBlinking()));
		connect(m_trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), SLOT(checkForClick(QSystemTrayIcon::ActivationReason)));
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
		m_trayIcon->setIcon(m_iconManager->icon(iconId));
	}

	void TrayIcon::setBlinkingIcon(const QString &iconId, const int &msecs, const int &timeout)
	{
		m_prevIconId = m_iconId;
		m_iconId = iconId;

		m_blinkTimer.start(msecs);
		if(timeout > 0)
			m_timeoutTimer.start(timeout);
	}

	void TrayIcon::readSettings(QSettings *settings)
	{
		m_trayIcon->show();
	}

	void TrayIcon::init()
	{
		setIcon(Constants::ICON_LILY);

		QMenu *trayMenu = new QMenu();
		trayMenu->addAction(m_actionManager->action(Constants::ACTION_TOGGLEMAIN));
		trayMenu->addAction(m_actionManager->action(Constants::ACTION_SETTINGS));
		trayMenu->addSeparator();
		trayMenu->addAction(m_actionManager->action(Constants::ACTION_QUIT));
		m_trayIcon->setContextMenu(trayMenu);

		m_actionManager->registerMenu(Constants::MENU_TRAY, trayMenu);
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
		m_trayIcon->setIcon(m_blink ? m_iconManager->icon(m_iconId) : QIcon());
		m_blink = !m_blink;
	}

	void TrayIcon::checkForClick(QSystemTrayIcon::ActivationReason reason)
	{
		if(reason == QSystemTrayIcon::Trigger)
			emit clicked();
	}
}
