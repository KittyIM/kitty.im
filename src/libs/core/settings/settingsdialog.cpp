#include "settingsdialog.h"

#include <settings/isettingspage.h>
#include <icons/iconmanager.h>
#include <icore.h>

#include <QDialogButtonBox>
#include <QStackedLayout>
#include <QApplication>
#include <QGridLayout>
#include <QPushButton>
#include <QTreeWidget>
#include <QGroupBox>
#include <QSettings>
#include <QDebug>

static const char settingsGroup[]    = "SettingsDialog";
static const char geometryKey[]      = "windowGeometry";

namespace Core
{
	SettingsDialog *SettingsDialog::m_instance = 0;
	QList<ISettingsPage*> SettingsDialog::m_pages;

	SettingsDialog::SettingsDialog(QWidget *parent) :
		QDialog(parent),
		m_stackedLayout(new QStackedLayout),
		m_pageGroupBox(new QGroupBox),
		m_categoryTree(new QTreeWidget)
	{
		setMinimumSize(400, 200);
		setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
		setWindowTitle(tr("Settings"));

		connect(qApp, SIGNAL(aboutToQuit()), SLOT(reject()));

		QGridLayout *layout = new QGridLayout(this);
		layout->setMargin(6);
		layout->setSpacing(6);

		//category tree
		m_categoryTree->setMinimumWidth(180);
		m_categoryTree->setMaximumWidth(180);
		m_categoryTree->setHeaderHidden(true);
		connect(m_categoryTree, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)), SLOT(changePage(QTreeWidgetItem*)));
		layout->addWidget(m_categoryTree, 0, 0, 1, 1);

		//groupbox
		m_pageGroupBox->setObjectName("pageGroupBox");
		m_pageGroupBox->setStyleSheet("#pageGroupBox { font-weight: bold; }");
		m_pageGroupBox->setLayout(m_stackedLayout);
		layout->addWidget(m_pageGroupBox, 0, 1, 1, 1);

		//button box
		QDialogButtonBox *buttonBox = new QDialogButtonBox(this);
		QPushButton *okButton = buttonBox->addButton(QDialogButtonBox::Ok);
		connect(okButton, SIGNAL(clicked()), SLOT(accept()));

		QPushButton *cancelButton = buttonBox->addButton(QDialogButtonBox::Cancel);
		connect(cancelButton, SIGNAL(clicked()), SLOT(reject()));

		QPushButton *applyButton = buttonBox->addButton(QDialogButtonBox::Apply);
		connect(applyButton, SIGNAL(clicked()), SLOT(apply()));

		layout->addWidget(buttonBox, 1, 0, 1, 2);
		setLayout(layout);

		readSettings();
		preparePages();
	}

	SettingsDialog::~SettingsDialog()
	{
		writeSettings();

		delete m_categoryTree;
		m_categoryTree = 0;

		delete m_stackedLayout;
		m_stackedLayout = 0;

		delete m_pageGroupBox;
		m_pageGroupBox = 0;
	}

	void SettingsDialog::readSettings()
	{
		QSettings *settings = ICore::settings();
		settings->beginGroup(settingsGroup);
		restoreGeometry(settings->value(geometryKey).toByteArray());
		settings->endGroup();
	}

	void SettingsDialog::writeSettings()
	{
		QSettings *settings = ICore::settings();
		settings->beginGroup(settingsGroup);
		settings->setValue(geometryKey, saveGeometry());
		settings->endGroup();
	}

	void SettingsDialog::preparePages()
	{
		IconManager *iconManager = IconManager::instance();
		foreach(ISettingsPage *page, m_pages) {
			m_pageIds.insert(page->id(), page);
		}

		//category tree
		foreach(ISettingsPage *page, m_pages) {
			QTreeWidgetItem *treeItem = new QTreeWidgetItem();
			treeItem->setText(0, page->name());
			treeItem->setIcon(0, iconManager->icon(page->icon()));
			treeItem->setData(0, Qt::UserRole, -1);

			if(page->parentId().isEmpty()) {
				m_categoryTree->addTopLevelItem(treeItem);
			} else {
				ISettingsPage *parentPage = m_pageIds.value(page->parentId());
				if(!parentPage)
					continue;

				QTreeWidgetItem *parentItem = m_treeItems.key(parentPage);
				if(!parentItem)
					continue;

				parentItem->addChild(treeItem);
			}

			m_treeItems.insert(treeItem, page);
		}

		if(m_categoryTree->topLevelItemCount() > 0)
			changePage(m_categoryTree->topLevelItem(0));

		m_categoryTree->expandAll();
	}

	QString SettingsDialog::currentPage() const
	{
		QTreeWidgetItem *currentItem = m_categoryTree->currentItem();
		if(!currentItem)
			return QString();

		ISettingsPage *currentPage = m_treeItems.value(currentItem);
		if(!currentPage)
			return QString();

		return currentPage->id();
	}

	void SettingsDialog::setCurrentPage(const QString &id)
	{
		ISettingsPage *page = m_pageIds.value(id);
		if(!page)
			return;

		QTreeWidgetItem *treeItem = m_treeItems.key(page);
		if(!treeItem)
			return;

		m_categoryTree->setCurrentItem(treeItem);
	}

	void SettingsDialog::changePage(QTreeWidgetItem *treeItem)
	{
		if(!treeItem)
			return;

		ISettingsPage *page = m_treeItems.value(treeItem);
		if(!page)
			return;

		int idx = treeItem->data(0, Qt::UserRole).toInt();
		if(idx == -1) {
			idx = m_stackedLayout->addWidget(page->createWidget());
			treeItem->setData(0, Qt::UserRole, idx);
		}

		m_stackedLayout->setCurrentIndex(idx);
		m_pageGroupBox->setTitle(page->name());
	}

	void SettingsDialog::done(int r)
	{
		if(r == QDialog::Accepted)
			apply();

		foreach(ISettingsPage *page, m_pages)
			page->finish();

		QDialog::done(r);

		m_instance = 0;
		deleteLater();
	}

	void SettingsDialog::apply()
	{
		foreach(ISettingsPage *page, m_pages)
			page->apply();
	}

	SettingsDialog *SettingsDialog::instance()
	{
		if(!m_instance)
			m_instance = new SettingsDialog();

		return m_instance;
	}

	void SettingsDialog::addPage(ISettingsPage *page)
	{
		m_pages << page;
	}

	void SettingsDialog::cleanup()
	{
		qDeleteAll(m_pages);
		m_pages.clear();
	}
}
