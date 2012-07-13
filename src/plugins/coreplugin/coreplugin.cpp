#include "coreplugin.h"

#include <QtCore/QString>

namespace Core
{
	CorePlugin::CorePlugin()
	{
	}

	QString CorePlugin::name() const
	{
		return "CorePlugin";
	}
}
