#include <QtCore/QTranslator>
#include <QtCore/QDebug>
#include <QtGui/QDesktopServices>
#include <QtGui/QApplication>

#include <core/profiles/profilemanager.h>
#include <core/profiles/profiledialog.h>
#include <core/plugins/pluginmanager.h>
#include <core/plugins/pluginitem.h>
#include <core/plugins/iplugin.h>
#include <core/argumentparser.h>
#include <core/jsonsettings.h>
#include <core/mainwindow.h>

static const char appGroup[] = "App";
static const char languageKey[] = "language";

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QApplication::setApplicationName("kitty.im");
	QApplication::setOrganizationName("arturo182");

	Core::ArgumentParser argumentParser;
	argumentParser.parseArguments(app.arguments());

	//profile
	QString profilePath = QDesktopServices::storageLocation(QDesktopServices::DataLocation) + "/profiles";
	if(argumentParser.contains("portable")) {
		profilePath = app.applicationDirPath() + "/profiles";
	}

	Core::ProfileManager profileManager;
	profileManager.setProfilePath(profilePath);

	QString profileName;
	if(profileManager.count() > 0) {
		QString argumentProfile = argumentParser.value("profile");

		if(!argumentProfile.isEmpty()) {
			if(profileManager.exists(argumentProfile)) {
				if(!profileManager.hasPassword(argumentProfile) ||
					profileManager.checkPassword(argumentProfile, argumentParser.value("password"))
				) {
					profileName = argumentProfile;
				}
			}
		} else if(profileManager.count() == 1) {
			QString onlyProfile = profileManager.profiles().first();

			if(!profileManager.hasPassword(onlyProfile)) {
				profileName = onlyProfile;
			}
		}
	}

	if(profileName.isEmpty()) {
		Core::ProfileDialog dlg;
		dlg.setProfileManager(&profileManager);

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
	Core::MainWindow mainWindow;
	mainWindow.setSettings(&settings);
	mainWindow.setProfileManager(&profileManager);
	mainWindow.init();

	//plugins
	QStringList pluginPaths;
	pluginPaths << app.applicationDirPath() + "/plugins";

	Core::PluginManager pluginManager;
	pluginManager.setPluginPaths(pluginPaths);
	pluginManager.setSettings(&settings);

	if(pluginManager.scanForPlugins()) {
		//show plugindialog here
		qDebug() << "bloody new plugins";
	}

	pluginManager.loadPlugins();

	foreach(Core::PluginItem *plugin, pluginManager.plugins()) {
		qDebug() << plugin->name();
	}

	return app.exec();
}
