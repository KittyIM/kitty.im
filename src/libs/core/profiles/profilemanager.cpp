#include "profilemanager.h"

#include <QtCore/QDir>

namespace Core
{
	ProfileManager::ProfileManager()
	{
	}

	QStringList ProfileManager::profiles() const
	{
		return QDir(m_profilePath).entryList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name);
	}

	int ProfileManager::count() const
	{
		return profiles().count();
	}

	bool ProfileManager::exists(const QString &profileName) const
	{
		return profiles().contains(profileName);
	}

	bool ProfileManager::hasPassword(const QString &profileName) const
	{
		return (profileName == "arturo182");
	}

	bool ProfileManager::checkPassword(const QString &profileName, const QString &password) const
	{
		if(!hasPassword(profileName))
			return true;

		return false;
	}
}
