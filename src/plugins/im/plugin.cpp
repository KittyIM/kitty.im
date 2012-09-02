#include "plugin.h"

#include <core/icons/iconmanager.h>
#include <core/modes/modemanager.h>
#include <core/modes/imode.h>
#include <core/icore.h>

#include <QApplication>
#include <QPushButton>
#include <QTranslator>
#include <QTreeWidget>
#include <QtPlugin>
#include <QDebug>
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

		Core::IconManager *iconManager = Core::IconManager::instance();
		iconManager->registerDefault("Im.Mode", QPixmap(":/im/images/icons/mode.png"));

		const QString locale = Core::ICore::uiLocale();
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
		imMode->setIcon("Im.Mode");
		imMode->setWidget(treeWidget);
		modeManager->addMode(imMode);


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
