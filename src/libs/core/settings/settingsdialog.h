#ifndef CORE_SETTINGSDIALOG_H
#define CORE_SETTINGSDIALOG_H

#include "../core_global.h"

#include <QDialog>
#include <QHash>

class QTreeWidgetItem;
class QStackedLayout;
class QTreeWidget;
class QGroupBox;

namespace Core
{
	class ISettingsPage;

	class CORE_EXPORT SettingsDialog : public QDialog
	{
		Q_OBJECT

		public:
			static SettingsDialog *instance();
			static void addPage(ISettingsPage *page);
			static void cleanup();

			QString currentPage() const;
			void setCurrentPage(const QString &id);

		private slots:
			void changePage(QTreeWidgetItem *treeItem);
			void done(int r);
			void apply();

		private:
			SettingsDialog(QWidget *parent = 0);
			~SettingsDialog();

			void readSettings();
			void writeSettings();
			void preparePages();

		private:
			static SettingsDialog *m_instance;
			static QList<ISettingsPage*> m_pages;

		private:
			QHash<QString, ISettingsPage*> m_pageIds;
			QHash<QTreeWidgetItem*, ISettingsPage*> m_treeItems;
			QStackedLayout *m_stackedLayout;
			QGroupBox *m_pageGroupBox;
			QTreeWidget *m_categoryTree;
	};
}

#endif // CORE_SETTINGSDIALOG_H
