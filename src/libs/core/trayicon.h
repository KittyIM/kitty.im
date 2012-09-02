#ifndef CORE_TRAYICON_H
#define CORE_TRAYICON_H

#include <QTimer>

class QSystemTrayIcon;

namespace Core
{
	class TrayIcon : public QObject
	{
		Q_OBJECT

		public:
			static TrayIcon *instance();

		public:
			TrayIcon(QObject *parent = 0);
			~TrayIcon();

			void setIcon(const QString &iconId);
			void setBlinkingIcon(const QString &iconId, const int &msecs = 300, const int &timeout = -1);

		public slots:
			void stopBlinking();
			void setToolTip(const QString &toolTip);

		signals:
			void clicked();

		private slots:
			void blinkIcon();

		private:
			static TrayIcon *m_instance;
			QSystemTrayIcon *m_trayIcon;
			QString m_iconId;
			QString m_prevIconId;
			QTimer m_blinkTimer;
			QTimer m_timeoutTimer;
			bool m_blink;
	};
}

#endif // CORE_TRAYICON_H
