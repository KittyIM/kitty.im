#ifndef CORE_ICONMANAGER_H
#define CORE_ICONMANAGER_H

#include "../global.h"

#include <QPixmap>
#include <QHash>

class QSettings;

namespace Core
{
	class IconTheme;

	class CORE_EXPORT IconManager : public QObject
	{
		Q_OBJECT

		public:
			static IconManager *instance();

		public:
			IconManager();
			~IconManager();

			QPixmap icon(const QString &id);
			QStringList allIds() const;
			bool contains(const QString &id) const { return m_icons.contains(id); }

			void registerDefault(const QString &id, const QPixmap &icon);
			void loadDefaults();
			void loadTheme(const IconTheme &iconTheme);
			void readSettings(QSettings *settings);

		signals:
			void defaultRegistered(const QString &id);
			void themeLoaded();

		private:
			static IconManager *m_instance;
			QHash<QString, QPixmap> m_icons;
			QHash<QString, QPixmap> m_defaults;
	};
}

#endif // CORE_ICONMANAGER_H
