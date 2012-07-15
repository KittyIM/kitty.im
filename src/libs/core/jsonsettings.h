#ifndef CORE_JSONSETTINGS_H
#define CORE_JSONSETTINGS_H

#include <QtCore/QSettings>

namespace Core
{
	class JsonSettings: public QSettings
	{
		Q_OBJECT

		public:
			JsonSettings(const QString &fileName, QObject *parent = 0);

		public:
			static QSettings::Format format;

		private:
			static void readMap(SettingsMap &map, const QVariant &root, const QString &name);
			static void writeMap(QVariant &root, const QString &key, const QVariant &value);

			static bool jsonRead(QIODevice &device, SettingsMap &map);
			static bool jsonWrite(QIODevice &device, const SettingsMap &map);

			static QString variantToString(const QVariant &v);
			static QVariant stringToVariant(const QString &s);
			static QStringList splitArgs(const QString &s, int idx);

	};
}

#endif // CORE_JSONSETTINGS_H
