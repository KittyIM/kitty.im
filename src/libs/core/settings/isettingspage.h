#ifndef CORE_ISETTINGSPAGE_H
#define CORE_ISETTINGSPAGE_H

#include "../global.h"

namespace Core
{
	class CORE_EXPORT ISettingsPage : public QObject
	{
		Q_OBJECT

		public:
			QString name() const { return m_name; }
			QString parentId() const { return m_parentId; }
			QString id() const { return m_id; }
			QString icon() const { return m_icon; }

			virtual QWidget *createWidget() = 0;
			virtual void apply() = 0;
			virtual void finish() = 0;

		protected:
			QString m_parentId;
			QString m_name;
			QString m_id;
			QString m_icon;
	};
}

#endif // CORE_ISETTINGSPAGE_H
