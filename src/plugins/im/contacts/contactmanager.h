#ifndef IM_CONTACTMANAGER_H
#define IM_CONTACTMANAGER_H

#include "../global.h"

namespace Im
{
	class IContact;

	class IM_EXPORT ContactManager : public QObject
	{
		Q_OBJECT

		public:
			ContactManager(QObject *parent = 0);

		private:
			QList<IContact*> m_contacts;
	};
}

#endif // IM_CONTACTMANAGER_H
