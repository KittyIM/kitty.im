#include "profilemanager.h"

#include "jsonsettings.h"

#include <QtCore/QCryptographicHash>
#include <QtCore/QDebug>
#include <QtCore/QDir>

namespace Core
{
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
		const QString settingsPath = profilePath(profileName) + "/settings.json";

		if(!QFile::exists(settingsPath))
			return false;

		const JsonSettings settings(settingsPath);
		QString password = settings.value("password").toString();

		return !password.isEmpty();
	}

	bool ProfileManager::checkPassword(const QString &profileName, const QString &password) const
	{
		if(!hasPassword(profileName))
			return true;

		const QString settingsPath = profilePath(profileName) + "/settings.json";

		const JsonSettings settings(settingsPath);
		QString actualPassword = settings.value("password").toString();
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
