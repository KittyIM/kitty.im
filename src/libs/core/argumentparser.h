#ifndef CORE_ARGUMENTPARSER_H
#define CORE_ARGUMENTPARSER_H

#include <QMap>

#include "core_global.h"

namespace Core
{
	class CORE_EXPORT ArgumentParser : public QMap<QString, QString>
	{
		public:
			ArgumentParser();

			void parseArguments(const QStringList &arguments);
			QString asCommandLine() const;
	};
}

#endif // CORE_ARGUMENTPARSER_H
