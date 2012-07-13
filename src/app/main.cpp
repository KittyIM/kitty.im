#include <QtGui/QApplication>

#include <pluginsystem/manager.h>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	PluginSystem::Manager mgr;


	return app.exec();
}
