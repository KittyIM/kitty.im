#ifndef CORE_ICONTHEME_H
#define CORE_ICONTHEME_H

#include <QHash>

namespace Core
{
	class IconTheme
	{
		public:
			IconTheme(const QString &fileName);

			QString name() const { return m_name; }
			QString author() const { return m_author; }
			QString version() const { return m_version; }
			QHash<QString, QString> icons() const { return m_icons; }

		private:
			QHash<QString, QString> m_icons;
			QString m_name;
			QString m_author;
			QString m_version;
	};
}

#endif // CORE_ICONTHEME_H
