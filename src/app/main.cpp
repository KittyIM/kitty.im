#include <QtCore/QDebug>
#include <QtGui/QDesktopServices>
#include <QtGui/QApplication>

#include <core/profiles/profilemanager.h>
#include <core/dialogs/profiledialog.h>
#include <core/plugins/manager.h>
#include <core/plugins/iplugin.h>
#include <core/argumentparser.h>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QApplication::setApplicationName("kitty.im");
	QApplication::setOrganizationName("arturo182");

	Core::ArgumentParser parser;
	parser.parseArguments(app.arguments());

	qDebug() << parser.asCommandLine();

	QMapIterator<QString, QString> it(parser);
	while(it.hasNext()) {
		it.next();
		qDebug() << it.key() << "=" << it.value();
	}

	QString profilePath = QDesktopServices::storageLocation(QDesktopServices::DataLocation) + "/profiles";
	if(parser.contains("portable")) {
		profilePath = app.applicationDirPath() + "/profiles";
	}

	Core::ProfileManager profileMgr;
	profileMgr.setProfilePath(profilePath);

	qDebug() << profileMgr.profiles();

	QString profileToLoad;
	if(profileMgr.count() > 0) {
		QString argumentProfile = parser.value("profile");

		if(!argumentProfile.isEmpty()) {
			if(profileMgr.exists(argumentProfile)) {
				if(!profileMgr.hasPassword(argumentProfile) || profileMgr.checkPassword(argumentProfile, parser.value("password"))) {
					profileToLoad = argumentProfile;
				}
			} else if(profileMgr.count() == 1) {
				QString onlyProfile = profileMgr.profiles().first();
				if(!profileMgr.hasPassword(onlyProfile)) {
					profileToLoad = onlyProfile;
				}
			}
		}
	}

	if(profileToLoad.isEmpty()) {
		Core::ProfileDialog dlg;
		dlg.setProfileManager(&profileMgr);

		if(dlg.exec()) {
			qDebug() << "login" << dlg.profileName();
		} else {
			return 0;
		}
	} else {

	}

	/*QStringList pluginPaths;
	pluginPaths << app.applicationDirPath() + "/plugins";

	Core::PluginManager mgr;
	mgr.setPluginPaths(pluginPaths);
	mgr.loadPlugins();

	foreach(Core::IPlugin *plugin, mgr.plugins()) {
		qDebug() << plugin->info()->name();
	}*/

	return app.exec();
}
