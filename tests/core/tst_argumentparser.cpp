#include <QtCore/QString>
#include <QtTest>

#include <core/argumentparser.h>

class ArgumentParserTest : public QObject
{
	Q_OBJECT

	public slots:
		void parseArguments();
};

void ArgumentParserTest::parseArguments()
{
	const QStringList args = QStringList() << "-foo" << "bar" << "-bool";

	Core::ArgumentParser parser;
	parser.parseArguments(args);

	QCOMPARE(parser.count(), 2);
	QVERIFY(parser.contains("foo"));
	QVERIFY(parser.contains("bool"));
	QCOMPARE(parser.value("foo"), "bar");
	QCOMPARE(parser.value("foo"), "bar");
	QCOMPARE(parser.value("bool"), "true");

}

QTEST_APPLESS_MAIN(ArgumentParserTest)

#include "tst_argumentparser.moc"
