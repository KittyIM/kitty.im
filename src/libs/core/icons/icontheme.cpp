#include "icontheme.h"

#include <QVariant>
#include <QDebug>
#include <QFile>
#include <QDir>

#include <json.h>

namespace Core
{
	IconTheme::IconTheme(const QString &fileName)
	{
		QFile file(fileName);
		if(!file.exists())
			return;

		if(!file.open(QFile::ReadOnly))
			return;

		QDir fileDir(fileName);

		QString json = file.readAll();
		QVariantMap themeMap = Json::parse(json).toMap();

		QVariantMap infoMap = themeMap.value("info").toMap();
		m_author = infoMap.value("author").toString();
		m_name = infoMap.value("name").toString();
		m_version = infoMap.value("version").toString();

		QVariantMap iconsMap = themeMap.value("icons").toMap();
		QMapIterator<QString, QVariant> it(iconsMap);
		while(it.hasNext()) {
			it.next();

			const QString iconFile = it.value().toString();
			if(fileDir.exists(iconFile)) {
				m_icons.insert(it.key(), fileDir.absoluteFilePath(iconFile));
			}
		}

		file.close();
	}
}
