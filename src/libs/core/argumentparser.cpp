#include "argumentparser.h"

#include <QtCore/QStringList>

namespace Core
{
	ArgumentParser::ArgumentParser()
	{
	}

	void ArgumentParser::parseArguments(const QStringList &arguments)
	{
		clear();

		QListIterator<QString> it(arguments);

		//skip the first element (app path)
		it.next();

		while(it.hasNext()) {
			QString arg = it.next();

			if(arg.startsWith('-')) {
				if(it.hasNext()) {
					QString nextArg = it.peekNext();

					if(!nextArg.startsWith('-')) {
						insert(arg.mid(1), nextArg);
						continue;
					}
				}

				insert(arg.mid(1), "true");
			}
		}
	}

	QString ArgumentParser::asCommandLine() const
	{
		QString cmd;

		QMapIterator<QString, QString> it(*this);
		while(it.hasNext()) {
			it.next();

			cmd += "-" + it.key();

			if(it.value() != "true") {
				cmd += " ";

				if(it.value().contains(' ')) {
					cmd += "\"" + it.value() + "\"";
				} else {
					cmd += it.value();
				}

				if(it.hasNext()) {
					cmd += " ";
				}
			}
		}

		return cmd;
	}
}
