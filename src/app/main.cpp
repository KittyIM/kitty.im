#include <QDesktopServices>
#include <QApplication>
#include <QMainWindow>
#include <QTranslator>
#include <QDebug>

#include <core/profiles/profilemanager.h>
#include <core/settings/settingsdialog.h>
#include <core/profiles/profiledialog.h>
#include <core/plugins/pluginmanager.h>
#include <core/console/consoledialog.h>
#include <core/plugins/pluginitem.h>
#include <core/plugins/iplugin.h>
#include <core/argumentparser.h>
#include <core/jsonsettings.h>
#include <core/icore.h>

static const char appGroup[] = "App";
static const char languageKey[] = "language";

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	app.setQuitOnLastWindowClosed(false);
	QApplication::setApplicationName("kitty.im");
	QApplication::setOrganizationName("arturo182");

	Core::ArgumentParser argumentParser;
	argumentParser.parseArguments(app.arguments());

	//profile
    QString profilePath = QDesktopServices::storageLocation(QDesktopServices::DataLocation) + "/profiles";
	if(argumentParser.contains("portable")) {
		profilePath = app.applicationDirPath() + "/profiles";
	}

	Core::ProfileManager profileManager(profilePath);

	QString profileName = profileManager.profileFromArgumentParser(&argumentParser);
	if(profileName.isEmpty()) {
		Core::ProfileDialog dlg(&profileManager);

		if(dlg.exec()) {
			profileName = dlg.profileName();
		} else {
			return 0;
		}
	}

	//settings
    const QString settingsPath = profileManager.profilePath(profileName) + "/settings.json";
	Core::JsonSettings settings(settingsPath);

	//translation
	QTranslator translator;
	QTranslator qtTranslator;
	QStringList uiLanguages = QLocale::system().uiLanguages();

	settings.beginGroup(appGroup);
	const QString language = settings.value(languageKey).toString();
	if(!language.isEmpty())
		uiLanguages.prepend(language);
	settings.endGroup();

	const QString translationPath = app.applicationDirPath() + "/translations";
	foreach(QString locale, uiLanguages) {
		locale.replace('-', '_');

		if(translator.load("kittyim_" + locale, translationPath)) {
			const QString qtTrFile = "qt_" + locale;

			if(qtTranslator.load(qtTrFile, translationPath)) {
				app.installTranslator(&translator);
				app.installTranslator(&qtTranslator);
				app.setProperty("kittyim_locale", locale);

				break;
			}

			translator.load(QString());
		} else if((locale == "C") || locale.startsWith("en")) {
			break;
		}
	}

	//mainwindow
    Core::ICore::initMainWindow(&settings, &profileManager);

	//plugins
    QStringList pluginPaths;
	pluginPaths << app.applicationDirPath() + "/plugins";

	Core::PluginManager pluginManager(pluginPaths);
	pluginManager.setSettings(&settings);

	if(pluginManager.scanForPlugins()) {
		//show plugindialog here
		qDebug() << "bloody new plugins";
	}

	pluginManager.loadPlugins();

	foreach(Core::PluginItem *plugin, pluginManager.plugins()) {
		qDebug() << plugin->name();
	}

	if(argumentParser.contains("debug")) {
		Core::ICore::showConsoleDialog();
	}

	return app.exec();
}
