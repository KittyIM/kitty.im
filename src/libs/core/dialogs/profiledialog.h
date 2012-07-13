#ifndef CORE_PROFILEDIALOG_H
#define CORE_PROFILEDIALOG_H

#include "../core_global.h"

#include <QtGui/QDialog>

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
			explicit ProfileDialog(QWidget *parent = 0);
			~ProfileDialog();

			ProfileManager *profileManager() const { return m_profileManager; }
			void setProfileManager(ProfileManager *profileManager) { m_profileManager = profileManager; }

			QString profileName() const { return m_profileName; }

		protected:
			void showEvent(QShowEvent *event);

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
