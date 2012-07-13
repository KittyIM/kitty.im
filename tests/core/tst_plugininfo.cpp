#include <QtCore/QString>
#include <QtTest>

#include <core/plugins/plugininfo.h>

class PluginInfoTest : public QObject
{
	Q_OBJECT

	private slots:
		void author();
		void website();
		void name();
		void version();
};

void PluginInfoTest::author()
{
	const QString author = "foo";

	Core::PluginInfo info;
	info.setAuthor(author);

	QCOMPARE(info.author(), author);
}

void PluginInfoTest::website()
{
	const QString website = "foo";

	Core::PluginInfo info;
	info.setWebsite(website);

	QCOMPARE(info.website(), website);
}

void PluginInfoTest::name()
{
	const QString name = "foo";

	Core::PluginInfo info;
	info.setName(name);

	QCOMPARE(info.name(), name);
}

void PluginInfoTest::version()
{
	const QString version = "foo";

	Core::PluginInfo info;
	info.setVersion(version);

	QCOMPARE(info.version(), version);
}

QTEST_APPLESS_MAIN(PluginInfoTest)

#include "tst_plugininfo.moc"
