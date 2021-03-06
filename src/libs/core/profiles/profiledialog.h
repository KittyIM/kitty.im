#ifndef CORE_PROFILEDIALOG_H
#define CORE_PROFILEDIALOG_H

#include "../global.h"

#include <QDialog>

class QTreeWidgetItem;

namespace Core
{
	namespace Ui
	{
		class ProfileDialog;
	}

	class ProfileManager;

	class CORE_EXPORT ProfileDialog : public QDialog
	{
		Q_OBJECT

		public:
			ProfileDialog(ProfileManager *profileManager, QWidget *parent = 0);
			~ProfileDialog();

			ProfileManager *profileManager() const { return m_profileManager; }

			QString profileName() const { return m_profileName; }

		protected:
			void showEvent(QShowEvent *event);
			void paintEvent(QPaintEvent *event);

		private slots:
			void updateControls(QTreeWidgetItem *item);
			void loginProfile();
			void deleteProfile();

		private:
			void updateProfiles();

		private:
			Ui::ProfileDialog *m_ui;
			ProfileManager *m_profileManager;
			QString m_profileName;
	};
}

#endif // CORE_PROFILEDIALOG_H
