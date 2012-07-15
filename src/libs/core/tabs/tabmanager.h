#ifndef CORE_TABMANAGER_H
#define CORE_TABMANAGER_H

#include "../core_global.h"

namespace Core
{
	class CORE_EXPORT TabManager : public QObject
	{
		Q_OBJECT

		public:
			explicit TabManager(QObject *parent = 0);
	};
}

#endif // CORE_TABMANAGER_H
