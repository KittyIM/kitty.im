#ifndef CORE_PROFILEMANAGER_H
#define CORE_PROFILEMANAGER_H

#include "../core_global.h"

namespace Core
{
	class CORE_EXPORT ProfileManager : public QObject
	{
		Q_OBJECT

		public:
			ProfileManager();

			QStringList profiles() const;

			int count() const;
			bool exists(const QString &profileName) const;

			bool hasPassword(const QString &profileName) const;
			bool checkPassword(const QString &profileName, const QString &password) const;

			QString profilePath() const { return m_profilePath; }
			void setProfilePath(const QString &profilePath) { m_profilePath = profilePath; }

		private:
			QString m_profilePath;
	};
}

#endif // CORE_PROFILEMANAGER_H
