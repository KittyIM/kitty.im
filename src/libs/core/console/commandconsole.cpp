#include "commandconsole.h"

#include <QTextDocument>
#include <QApplication>
#include <QTextBrowser>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QDebug>

#include <constants.h>
#include <icore.h>

namespace Core
{
	CommandConsole::CommandConsole() :
		IConsoleTab(Constants::CONSOLE_COMMAND),
		m_commandText(new QTextBrowser(this)),
		m_commandEdit(new QLineEdit(this))
	{
		setText(tr("Command line"));

		connect(m_commandEdit, SIGNAL(returnPressed()), SLOT(parseCommand()));

		QVBoxLayout *layout = new QVBoxLayout(this);
		layout->setMargin(0);
		layout->addWidget(m_commandText);
		layout->addWidget(m_commandEdit);
		setLayout(layout);
	}

	void CommandConsole::parseCommand()
	{
		QStringList cmd;
		const QStringList parts = m_commandEdit->text().split('"', QString::SkipEmptyParts);
		bool inQuotes = false;

		m_commandText->append("] " + Qt::escape(m_commandEdit->text()));

		foreach(const QString &part, parts) {
			if(inQuotes) {
				cmd << part;
			} else {
				cmd << part.split(' ', QString::SkipEmptyParts);
			}

			inQuotes = !inQuotes;
		}

		if(cmd[0] == "quit") {
			qApp->quit();
		} else if(cmd[0] == "restart") {
			ICore::restart((cmd.count() > 1) ? cmd[1].split(' ') : QStringList());
		} else if(cmd[0] == "help") {
			m_commandText->append(tr("Available commands:\nquit - quits lily.im\nrestart [arguments] - restarts lily.im with (optional) arguments\nhelp - displays this help"));
		} else {
			m_commandText->append(tr("Unknown command, use help to get list of available commands."));
		}

		m_commandEdit->clear();
	}
}
