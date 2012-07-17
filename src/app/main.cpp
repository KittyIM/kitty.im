#include <QtCore/QDebug>
#include <QtGui/QDesktopServices>
#include <QtGui/QApplication>

#include <core/profiles/profilemanager.h>
#include <core/profiles/profiledialog.h>
#include <core/plugins/manager.h>
#include <core/plugins/iplugin.h>
#include <core/argumentparser.h>
#include <core/jsonsettings.h>
#include <core/mainwindow.h>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QApplication::setApplicationName("kitty.im");
	QApplication::setOrganizationName("arturo182");

	Core::ArgumentParser parser;
	parser.parseArguments(app.arguments());

	QString profilePath = QDesktopServices::storageLocation(QDesktopServices::DataLocation) + "/profiles";
	if(parser.contains("portable")) {
		profilePath = app.applicationDirPath() + "/profiles";
	}

	Core::ProfileManager profileManager;
	profileManager.setProfilePath(profilePath);

	QString profileName;
	if(profileManager.count() > 0) {
		QString argumentProfile = parser.value("profile");

		if(!argumentProfile.isEmpty()) {
			if(profileManager.exists(argumentProfile)) {
				if(!profileManager.hasPassword(argumentProfile) ||
					profileManager.checkPassword(argumentProfile, parser.value("password"))
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

	const QString settingsPath = profileManager.profilePath(profileName) + "/settings.json";
	Core::JsonSettings settings(settingsPath);

	Core::MainWindow mainWindow;
	mainWindow.setSettings(&settings);
	mainWindow.setProfileManager(&profileManager);

	mainWindow.init();

	QStringList pluginPaths;
	pluginPaths << app.applicationDirPath() + "/plugins";

	const QString pluginSettingsPath = profileManager.profilePath(profileName) + "/plugins.json";
	Core::JsonSettings pluginSettings(pluginSettingsPath);

	Core::PluginManager mgr;
	mgr.setPluginPaths(pluginPaths);
	mgr.setPluginSettings(&pluginSettings);

	if(mgr.hasNewPlugins()) {
		qDebug() << "bloody new plugins";
	}

	mgr.loadPlugins();

	foreach(Core::IPlugin *plugin, mgr.plugins()) {
		qDebug() << plugin->info()->name();
	}

	return app.exec();
}
