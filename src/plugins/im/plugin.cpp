#include "plugin.h"

#include <QtCore/QtPlugin>

namespace Im
{
	Plugin::Plugin()
	{
		m_info->setAuthor("arturo182");
		m_info->setName(tr("Internet Messaging"));
		m_info->setWebsite("http://www.arturpacholec.pl/");
		m_info->setVersion("0.1");
	}

	Q_EXPORT_PLUGIN2(Im, Plugin)
}
