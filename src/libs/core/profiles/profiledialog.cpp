#include "profiledialog.h"
#include "ui_profiledialog.h"

#include <QInputDialog>
#include <QMessageBox>
#include <QPainter>
#include <QDebug>
#include <QDir>

#include <profiles/profilemanager.h>
#include <3rdparty/qtwin/qtwin.h>
#include <utils/utils.h>
#include <constants.h>

namespace Core
{
	ProfileDialog::ProfileDialog(ProfileManager *profileManager, QWidget *parent) :
		QDialog(parent),
		m_ui(new Ui::ProfileDialog),
		m_profileManager(profileManager)
	{
		m_ui->setupUi(this);
		m_ui->passwordEdit->hide();
		m_ui->passwordLabel->hide();

		if(QtWin::isCompositionEnabled()) {
			QtWin::extendFrameIntoClientArea(this);
			setContentsMargins(0, 0, 0, 0);
		}
	}

	ProfileDialog::~ProfileDialog()
	{
		delete m_ui;
	}

	void ProfileDialog::showEvent(QShowEvent *event)
	{
		m_ui->versionLabel->setText(QString("kitty.im v%1").arg(Constants::VERSION));

		updateProfiles();
	}

	void ProfileDialog::paintEvent(QPaintEvent *event)
	{
#ifdef Q_WS_WIN32
		if(QtWin::isCompositionEnabled()) {
			QPainter p(this);
			p.setPen(palette().midlight().color());
			p.setBrush(palette().window());
			p.drawRoundedRect(m_ui->profilesGroupBox->geometry(), 2, 2);
		}
#endif
	}

	void ProfileDialog::updateControls(QTreeWidgetItem *item)
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

	void ProfileDialog::loginProfile()
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

			QString profilePath = m_profileManager->profilePath(profileName);
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

	void ProfileDialog::deleteProfile()
	{
		if(m_ui->passwordEdit->isVisible() && m_ui->passwordEdit->text().isEmpty()) {
			m_ui->passwordEdit->setFocus();
			return;
		}

		QTreeWidgetItem *profileItem = m_ui->profileTree->currentItem();
		if(!profileItem || !m_profileManager)
			return;

		const QString profileName = profileItem->text(0);
		if(!m_profileManager->checkPassword(profileName, m_ui->passwordEdit->text())) {
			QMessageBox::warning(this, tr("Wrong password"), tr("The password you entered is wrong"));

			m_ui->passwordEdit->selectAll();
			m_ui->passwordEdit->setFocus();

			return;
		}

		int result = QMessageBox::question(this, tr("Are you sure?"), QString(tr("Do you really want to delete profile \"%1\"?").arg(profileName)), QMessageBox::Yes, QMessageBox::No);
		if(result == QMessageBox::Yes) {
			Utils::rmPath(m_profileManager->profilePath(profileName));
			updateProfiles();
		}
	}

	void ProfileDialog::updateProfiles()
	{
		if(!m_profileManager)
			return;

		m_ui->profileTree->clear();

		foreach(const QString &profileName, m_profileManager->profiles()) {
			QTreeWidgetItem *profileItem = new QTreeWidgetItem(m_ui->profileTree);
			profileItem->setText(0, profileName);

			QString avatarPath = m_profileManager->profilePath(profileName) + "/avatar.png";
			profileItem->setIcon(0, QIcon(QFile::exists(avatarPath) ? avatarPath :  Constants::IMAGE_KITTY48));
		}

		QTreeWidgetItem *addProfileItem = new QTreeWidgetItem(m_ui->profileTree);
		addProfileItem->setText(0, tr("Add profile..."));
		addProfileItem->setIcon(0, QIcon(Constants::IMAGE_KITTY48));
		addProfileItem->setData(0, Qt::UserRole, true);
	}
}
