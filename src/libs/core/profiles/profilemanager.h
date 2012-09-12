#ifndef CORE_PROFILEMANAGER_H
#define CORE_PROFILEMANAGER_H

#include "../global.h"

namespace Core
{
	class ArgumentParser;

	class CORE_EXPORT ProfileManager : public QObject
	{
		Q_OBJECT

		public:
			ProfileManager(const QString &profilePath);

			QStringList profiles() const;

			QString profileFromArgumentParser(ArgumentParser *argumentParser) const;

			int count() const;
			bool exists(const QString &profileName) const;

			bool hasPassword(const QString &profileName) const;
			bool checkPassword(const QString &profileName, const QString &password) const;

			QString profilePath(const QString &profileName) const;

		private:
			QString m_profilePath;
	};
}

#endif // CORE_PROFILEMANAGER_H
