#ifndef IM_ICONTACT_H
#define IM_ICONTACT_H

#include "../global.h"

#include <QHash>

namespace Im
{
	class IM_EXPORT IContact
	{
		public:
			IContact() { }

			virtual QVariant data(const QString &id, const QVariant &defaultValue = QVariant())
			{
				return m_data.value(id, defaultValue);
			}
			virtual void setData(const QString &id, const QVariant &value)
			{
				m_data.insert(id, value);
			}

		protected:
			QHash<QString, QVariant> m_data;
	};
}

#endif // IM_ICONTACT_H
