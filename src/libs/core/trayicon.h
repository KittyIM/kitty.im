#ifndef CORE_TRAYICON_H
#define CORE_TRAYICON_H

#include <QSystemTrayIcon>
#include <QTimer>

class QSettings;

namespace Core
{
    class ActionManager;
    class IconManager;

	class TrayIcon : public QObject
	{
		Q_OBJECT

		public:
			static TrayIcon *instance();

		public:
            TrayIcon(ActionManager *actionManager, IconManager *iconManager, QObject *parent = 0);
			~TrayIcon();

			void setIcon(const QString &iconId);
			void setBlinkingIcon(const QString &iconId, const int &msecs = 700, const int &timeout = -1);

			void readSettings(QSettings *settings);
            void init();

		public slots:
			void stopBlinking();
			void setToolTip(const QString &toolTip);

		signals:
			void clicked();

		private slots:
			void blinkIcon();
			void checkForClick(QSystemTrayIcon::ActivationReason reason);

		private:
			static TrayIcon *m_instance;
            ActionManager *m_actionManager;
            IconManager *m_iconManager;
			QSystemTrayIcon *m_trayIcon;
			QString m_iconId;
			QString m_prevIconId;
			QTimer m_blinkTimer;
			QTimer m_timeoutTimer;
			bool m_blink;
	};
}

#endif // CORE_TRAYICON_H
