#ifndef CORE_MODEMANAGER_H
#define CORE_MODEMANAGER_H

#include "../global.h"

class QSettings;

namespace Core
{
	class JsonSettings;
	class ModeWidget;
	class IMode;

	class CORE_EXPORT ModeManager : public QObject
	{
		Q_OBJECT

		public:
			static ModeManager *instance();

		public:
			ModeManager();
			~ModeManager();

			void addMode(IMode *mode);

			void readSettings(QSettings *settings);
			void writeSettings(QSettings *settings);

			IMode *currentMode();

			ModeWidget *modeWidget() { return m_modeWidget; }
			void setModeWidget(ModeWidget *modeWidget);

		signals:
			void currentModeChanged(IMode *mode);
			void modeAdded(const QString &id);
			void modeListChanged();

		private slots:
			void setCurrentIndex(const int &index);

		private:
			static ModeManager *m_instance;
			ModeWidget *m_modeWidget;
			QList<IMode*> m_modes;
	};
}

#endif // CORE_MODEMANAGER_H
