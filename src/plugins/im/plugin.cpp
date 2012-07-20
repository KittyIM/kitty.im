#include "plugin.h"

#include <core/modes/modemanager.h>
#include <core/modes/imode.h>
#include <core/mainwindow.h>

#include <QtCore/QTranslator>
#include <QtCore/QtPlugin>
#include <QtCore/QDebug>
#include <QtGui/QApplication>
#include <QtGui/QPushButton>
#include <QTreeWidget>
#include <QLabel>

namespace Im
{
	Plugin::Plugin()
	{
	}

	QString Plugin::name() const
	{
		return tr("Instant Messaging");
	}

	QString Plugin::version() const
	{
		return "0.0.1";
	}

	QString Plugin::author() const
	{
		return "arturo182";
	}

	QString Plugin::website() const
	{
		return "http://www.arturpacholec.pl/";
	}

	bool Plugin::initialize(QString *errorString)
	{
		//qDebug() << "Im::initialize";

		//TODO
		const QString locale = Core::MainWindow::instance()->uiLocale();
		if(!locale.isEmpty()) {
			QTranslator *translator = new QTranslator(this);
			const QString translationPath = qApp->applicationDirPath() + "/translations";
			const QString fileName = "im_" + locale;

			if(translator->load(fileName, translationPath))
				qApp->installTranslator(translator);
		}

		Core::ModeManager *modeManager = Core::ModeManager::instance();

		QPushButton *quitButton = new QPushButton();
		quitButton->setText("quit");
		connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));

		QTreeWidget *treeWidget = new QTreeWidget();
		treeWidget->setFrameStyle(QFrame::NoFrame);

		Core::IMode *imMode = new Core::IMode("Mode.Im");
		imMode->setLabel("IM");
		imMode->setIcon(QIcon("E:/Pictures/Ikony/Pastel/32/user-comment.png"));
		imMode->setWidget(treeWidget);
		modeManager->addMode(imMode);

		Core::IMode *emailMode = new Core::IMode("Mode.Email");
		emailMode->setLabel("Email");
		emailMode->setEnabled(false);
		emailMode->setIcon(QIcon("E:/Pictures/Ikony/Pastel/32/email.png"));
		emailMode->setWidget(new QLabel);
		modeManager->addMode(emailMode);

		Core::IMode *twitterMode = new Core::IMode("Mode.Twitter");
		twitterMode->setLabel("Twitter");
		twitterMode->setIcon(QIcon("C:/Users/arturo182/Downloads/twitter.png"));
		twitterMode->setWidget(quitButton);
		modeManager->addMode(twitterMode);

		Core::IMode *facebookMode = new Core::IMode("Mode.Facebook");
		facebookMode->setLabel("Facebook");
		facebookMode->setIcon(QIcon("C:/Users/arturo182/Downloads/facebook.png"));
		facebookMode->setWidget(new QLabel("Facebook!"));
		modeManager->addMode(facebookMode);

		return true;
	}

	void Plugin::pluginsInitialized()
	{
		//qDebug() << "Im::pluginInitialized";
	}

	void Plugin::aboutToClose()
	{
		qDebug() << "Im::aboutToClose";
	}

	Q_EXPORT_PLUGIN2(Im, Plugin)
}
