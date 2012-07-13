#include "profiledialog.h"
#include "ui_profiledialog.h"

#include <QtCore/QDebug>
#include <QtGui/QInputDialog>
#include <QtGui/QMessageBox>

#include <profiles/profilemanager.h>
#include <QDir>

namespace Core
{
	ProfileDialog::ProfileDialog(QWidget *parent) :
		QDialog(parent),
		m_ui(new Ui::ProfileDialog),
		m_profileManager(0)
	{
		m_ui->setupUi(this);
		m_ui->passwordEdit->hide();
		m_ui->passwordLabel->hide();
	}

	ProfileDialog::~ProfileDialog()
	{
		delete m_ui;
	}

	void ProfileDialog::showEvent(QShowEvent *event)
	{
		updateProfiles();
	}
}

void Core::ProfileDialog::updateControls(QTreeWidgetItem *item)
{
	m_ui->passwordEdit->clear();
	m_ui->passwordEdit->hide();
	m_ui->passwordLabel->hide();

	m_ui->loginButton->setEnabled(false);
	m_ui->deleteButton->setEnabled(false);

	if(!item || item->data(0, Qt::UserRole).toBool() || !m_profileManager)
		return;

	bool hasPassword = m_profileManager->hasPassword(item->text(0));
	m_ui->passwordEdit->setVisible(hasPassword);
	m_ui->passwordLabel->setVisible(hasPassword);

	m_ui->loginButton->setEnabled(true);
	m_ui->deleteButton->setEnabled(true);
}

void Core::ProfileDialog::loginProfile()
{
	if(m_ui->passwordEdit->isVisible() && m_ui->passwordEdit->text().isEmpty()) {
		m_ui->passwordEdit->setFocus();
		return;
	}

	QTreeWidgetItem *profileItem = m_ui->profileTree->currentItem();
	if(!profileItem || !m_profileManager)
		return;

	//create new profile
	if(profileItem->data(0, Qt::UserRole).toBool()) {
		QString profileName = QInputDialog::getText(this, tr("Profile name"), tr("Enter name for the new profile"));
		if(profileName.isEmpty())
			return;

		QString profilePath = m_profileManager->profilePath() + "/" + profileName;
		if(QDir(profilePath).exists()) {
			QMessageBox::warning(this, tr("Profile creation failed"), tr("Profile already exists."));
			return;
		}

		if(!QDir(profilePath).mkpath(".")) {
			QMessageBox::warning(this, tr("Profile creation failed"), tr("There was a problem creating your profile."));
			return;
		}

		updateProfiles();

		return;
	}

	//check for password
	QString profileName = profileItem->text(0);
	if(!m_profileManager->checkPassword(profileName, m_ui->passwordEdit->text())) {
		QMessageBox::warning(this, tr("Wrong password"), tr("The password you entered is wrong"));

		m_ui->passwordEdit->selectAll();
		m_ui->passwordEdit->setFocus();

		return;
	}

	//login
	m_profileName = profileName;
	accept();
}

void Core::ProfileDialog::deleteProfile()
{

}

void Core::ProfileDialog::updateProfiles()
{
	if(!m_profileManager)
		return;

	m_ui->profileTree->clear();

	foreach(const QString &profileName, m_profileManager->profiles()) {
		QTreeWidgetItem *profileItem = new QTreeWidgetItem(m_ui->profileTree);
		profileItem->setText(0, profileName);
		profileItem->setIcon(0, QIcon(":/core/images/icons/kitty_48.png"));
	}

	QTreeWidgetItem *addProfileItem = new QTreeWidgetItem(m_ui->profileTree);
	addProfileItem->setText(0, tr("Add profile..."));
	addProfileItem->setIcon(0, QIcon(":/core/images/icons/kitty_48.png"));
	addProfileItem->setData(0, Qt::UserRole, true);
}
