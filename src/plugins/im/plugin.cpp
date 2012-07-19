#include "plugin.h"

#include <core/modes/modemanager.h>
#include <core/modes/imode.h>

#include <QtCore/QTranslator>
#include <QtCore/QtPlugin>
#include <QtCore/QDebug>
#include <QtGui/QApplication>
#include <QtGui/QPushButton>
#include <QTreeWidget>

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
		qDebug() << "Im::initialize";

		//TODO
		const QString locale = qApp->property("kittyim_locale").toString();
		if(!locale.isEmpty()) {
			QTranslator *translator = new QTranslator(this);
			const QString translationPath = qApp->applicationDirPath() + "/translations";
			const QString fileName = "im_" + locale;

			if(translator->load(fileName, translationPath))
				qApp->installTranslator(translator);
		}

		return true;
	}

	void Plugin::pluginsInitialized()
	{
		qDebug() << "Im::pluginInitialized";
	}

	void Plugin::aboutToClose()
	{
		qDebug() << "Im::aboutToClose";
	}

	Q_EXPORT_PLUGIN2(Im, Plugin)
}
