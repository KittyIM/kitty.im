#include "debugconsole.h"

#include <QTextBrowser>
#include <QGridLayout>
#include <QScrollBar>
#include <QDateTime>
#include <QDebug>

#include <core_constants.h>

namespace Core
{
	QTextBrowser *DebugConsole::m_debugText = 0;

	void DebugConsole::addMessage(QtMsgType type, const char *msg)
	{
		if(!m_debugText)
			return;

		QString color = "#ffffff";
		switch(type) {
			case QtDebugMsg:
				color = "#ccffcc";
			break;

			case QtWarningMsg:
				color = "#ffffcc";
			break;

			case QtCriticalMsg:
				color = "#ffcc99";
			break;

			case QtFatalMsg:
				color = "#ffcccc";
			break;
		}

		m_debugText->append(QString("<span style='background-color: %1;'>&nbsp;&nbsp;&nbsp;</span> <b>##%2</b> %3").arg(color).arg(QDateTime::currentDateTime().toString("hh:mm:ss")).arg(QString::fromLocal8Bit(msg).replace(" ", "&nbsp;")));

		const int scrollValue = m_debugText->verticalScrollBar()->value();
		const int scrollMax = m_debugText->verticalScrollBar()->maximum();
		if(scrollValue == scrollMax)
			m_debugText->verticalScrollBar()->setValue(scrollMax);
	}

	DebugConsole::DebugConsole() :
		IConsoleTab(Constants::CONSOLE_DEBUG)
	{
		setText(tr("Debug log"));

		m_debugText = new QTextBrowser();

		QGridLayout *layout = new QGridLayout(this);
		layout->setMargin(0);
		layout->addWidget(m_debugText);

		qInstallMsgHandler(addMessage);
	}

	DebugConsole::~DebugConsole()
	{
		qInstallMsgHandler(0);

		delete m_debugText;
		m_debugText = 0;
	}
}
