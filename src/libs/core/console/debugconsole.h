#ifndef CORE_DEBUGCONSOLE_H
#define CORE_DEBUGCONSOLE_H

#include <console/iconsoletab.h>

class QTextBrowser;

namespace Core
{
	class DebugConsole : public IConsoleTab
	{
		public:
			static void addMessage(QtMsgType type, const char *msg);

		public:
			DebugConsole();
			~DebugConsole();

		private:
			static QTextBrowser *m_debugText;
	};
}

#endif // CORE_DEBUGCONSOLE_H
