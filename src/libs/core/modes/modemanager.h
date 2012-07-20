#ifndef CORE_MODEMANAGER_H
#define CORE_MODEMANAGER_H

#include "../core_global.h"

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

			void addMode(IMode *mode);

			void readSettings(JsonSettings *settings);
			void writeSettings(JsonSettings *settings);

			IMode *currentMode();

			ModeWidget *modeWidget() { return m_modeWidget; }
			void setModeWidget(ModeWidget *modeWidget);

		signals:
			void currentModeChanged(IMode *mode);

		private slots:
			void setCurrentIndex(const int &index);

		private:
			static ModeManager *m_instance;
			ModeWidget *m_modeWidget;
			QList<IMode*> m_modes;
	};
}

#endif // CORE_MODEMANAGER_H
