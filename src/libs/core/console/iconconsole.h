#ifndef CORE_ICONCONSOLE_H
#define CORE_ICONCONSOLE_H

#include <console/iconsoletab.h>

class QTreeWidget;

namespace Core
{
	class IconManager;

	class IconConsole : public IConsoleTab
	{
		public:
			IconConsole(IconManager *iconManager);
			~IconConsole();

			void refreshIcons();

		private:
			IconManager *m_iconManager;
			QTreeWidget *m_iconTree;
	};
}

#endif // CORE_ICONSCONSOLE_H
