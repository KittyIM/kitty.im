#ifndef CORE_PLUGININFO_H
#define CORE_PLUGININFO_H

#include "../core_global.h"

namespace Core
{
	class CORE_EXPORT PluginInfo : public QObject
	{
		Q_OBJECT

		public:
			PluginInfo(QObject *parent = 0) : QObject(parent)
			{ }

			QString name() const { return m_name; }
			void setName(const QString &name) { m_name = name; }

			QString version() const { return m_version; }
			void setVersion(const QString &version) { m_version = version; }

			QString author() const { return m_author; }
			void setAuthor(const QString &author) { m_author = author; }

			QString website() const { return m_website; }
			void setWebsite(const QString &website) { m_website = website; }

		private:
			QString m_name;
			QString m_version;
			QString m_author;
			QString m_website;
	};
}

#endif // CORE_PLUGININFO_H
