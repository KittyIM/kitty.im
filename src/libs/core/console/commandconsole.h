#ifndef CORE_COMMANDCONSOLE_H
#define CORE_COMMANDCONSOLE_H

#include <console/iconsoletab.h>

class QTextBrowser;
class QLineEdit;

namespace Core
{
	class CommandConsole : public IConsoleTab
	{
        Q_OBJECT

		public:
            CommandConsole();

        private slots:
            void parseCommand();

		private:
            QTextBrowser *m_commandText;
			QLineEdit *m_commandEdit;
	};
}

#endif // CORE_COMMANDCONSOLE_H
