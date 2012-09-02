#include "iconmanager.h"

#include <icons/icontheme.h>

#include <QApplication>
#include <QSettings>
#include <QDebug>

const char appGroup[] = "App";
const char iconThemeKey[] = "iconTheme";

namespace Core
{
	IconManager *IconManager::m_instance = 0;

	IconManager::IconManager()
	{
		m_instance = this;
	}

	IconManager::~IconManager()
	{
		m_instance = 0;
	}

	QPixmap IconManager::icon(const QString &id)
	{
		return m_icons.value(id);
	}

	QStringList IconManager::allIds() const
	{
		QStringList ids = m_icons.keys();
		qSort(ids);

		return ids;
	}

	void IconManager::registerDefault(const QString &id, const QPixmap &icon)
	{
		m_defaults.insert(id, icon);
		m_icons.insert(id, icon);

		emit defaultRegistered(id);
	}

	void IconManager::loadDefaults()
	{
		m_icons.clear();
		m_icons = m_defaults;
	}

	void IconManager::loadTheme(const IconTheme &iconTheme)
	{
		loadDefaults();

		QHashIterator<QString, QString> it(iconTheme.icons());
		while(it.hasNext()) {
			it.next();

			m_icons.insert(it.key(), QPixmap(it.value()));
		}

		emit themeLoaded();
	}

	void IconManager::readSettings(QSettings *settings)
	{
		settings->beginGroup(appGroup);

		QString iconTheme = settings->value(iconThemeKey).toString();
		if(iconTheme.isEmpty()) {
			loadDefaults();
		} else {
			IconTheme theme(qApp->applicationDirPath() + "/themes/icons/" + iconTheme + "/theme.json");
			loadTheme(theme);
		}

		settings->endGroup();
	}

	IconManager *IconManager::instance()
	{
		return m_instance;
	}
}
