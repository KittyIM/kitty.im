#ifndef CORE_ICORE_H
#define CORE_ICORE_H

#include "global.h"

#include <QPixmap>

class QMainWindow;
class QSettings;
class QAction;

namespace Core
{
	class ProfileManager;
	class MainWindow;

	class CORE_EXPORT ICore : public QObject
	{
		Q_OBJECT

		public:
			static void initMainWindow(QSettings *settings, ProfileManager *profileManager);
			static void showConsoleDialog();
			static void showSettingsDialog(const QString &currentPage = QString());

			static QString uiLocale();
			static QSettings *settings();
			static QMainWindow *mainWindow();
			static QPixmap icon(const QString &id);
			static QAction *action(const QString &id);

			static void restart(const QStringList &arguments);

		private:
			static MainWindow *m_mainWindow;
	};
}

#endif // CORE_ICORE_H
