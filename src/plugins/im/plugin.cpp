#include "plugin.h"

#include <QtCore/QTranslator>
#include <QtCore/QtPlugin>
#include <QtCore/QDebug>
#include <QtGui/QApplication>

namespace Im
{
	Plugin::Plugin()
	{
		m_info->setAuthor("arturo182");
		m_info->setName(tr("Internet Messaging"));
		m_info->setWebsite("http://www.arturpacholec.pl/");
		m_info->setVersion("0.1");
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
