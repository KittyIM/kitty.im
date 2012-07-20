#include "profilemanager.h"

#include <argumentparser.h>
#include <jsonsettings.h>

#include <QtCore/QCryptographicHash>
#include <QtCore/QDebug>
#include <QtCore/QDir>

const char passwordKey[] = "password";

namespace Core
{
	ProfileManager::ProfileManager(const QString &profilePath) :
		m_profilePath(profilePath)
	{
	}

	QStringList ProfileManager::profiles() const
	{
		return QDir(m_profilePath).entryList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name);
	}

	QString ProfileManager::profileFromArgumentParser(ArgumentParser *argumentParser) const
	{
		if(count() == 0)
			return QString();

		//check for profile in arguments
		QString argumentProfile = argumentParser->value("profile");
		QString argumentPassword = argumentParser->value("password");
		if(!argumentProfile.isEmpty()) {
			if(!exists(argumentProfile))
				return QString();

			if(!checkPassword(argumentProfile, argumentPassword))
				return QString();

			return argumentProfile;
		}

		//maybe there's only one profile
		if(count() == 1) {
			QString onlyProfile = profiles().first();

			if(!checkPassword(onlyProfile, argumentPassword))
				return QString();

			return onlyProfile;
		}

		return QString();
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
		const QString settingsPath = profilePath(profileName) + "/settings.json";

		if(!QFile::exists(settingsPath))
			return false;

		const JsonSettings settings(settingsPath);
		QString password = settings.value(passwordKey).toString();

		return !password.isEmpty();
	}

	bool ProfileManager::checkPassword(const QString &profileName, const QString &password) const
	{
		if(!hasPassword(profileName))
			return true;

		const QString settingsPath = profilePath(profileName) + "/settings.json";

		const JsonSettings settings(settingsPath);
		QString actualPassword = settings.value(passwordKey).toString();
		QString passwordHash = QCryptographicHash::hash(password.toAscii(), QCryptographicHash::Sha1).toHex();

		return (passwordHash == actualPassword);
	}

	QString ProfileManager::profilePath(const QString &profileName = QString()) const
	{
		if(profileName.isEmpty())
			return m_profilePath;

		return QDir(m_profilePath).absoluteFilePath(profileName);
	}

}
