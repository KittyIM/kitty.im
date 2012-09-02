#include "consoledialog.h"

#include <console/iconsoletab.h>
#include <icore.h>

#include <QDialogButtonBox>
#include <QApplication>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QSettings>
#include <QDebug>

static const char settingsGroup[]    = "ConsoleDialog";
static const char geometryKey[]      = "windowGeometry";

namespace Core
{
	ConsoleDialog *ConsoleDialog::m_instance = 0;
	QList<IConsoleTab*> ConsoleDialog::m_tabs;

	ConsoleDialog *ConsoleDialog::instance(QWidget *parent)
	{
		if(!m_instance)
			m_instance = new ConsoleDialog(parent);

		return m_instance;
	}

	void ConsoleDialog::addTab(IConsoleTab *tab)
	{
		m_tabs << tab;
	}

	void ConsoleDialog::cleanup()
	{
		qDeleteAll(m_tabs);
		m_tabs.clear();
	}

	ConsoleDialog::ConsoleDialog(QWidget *parent) :
		QDialog(parent),
		m_tabWidget(new QTabWidget)
	{
		setMinimumSize(400, 200);
		setWindowTitle(tr("Console"));

		connect(qApp, SIGNAL(aboutToQuit()), SLOT(reject()));

		foreach(IConsoleTab *tab, m_tabs) {
			m_tabWidget->addTab(tab, ICore::icon(tab->icon()), tab->text());
		}

		QDialogButtonBox *buttonBox = new QDialogButtonBox(this);
		buttonBox->setStandardButtons(QDialogButtonBox::Close);
		connect(buttonBox, SIGNAL(rejected()), SLOT(close()));

		QVBoxLayout *layout = new QVBoxLayout(this);
		layout->setMargin(3);
		layout->addWidget(m_tabWidget);
		layout->addWidget(buttonBox);
		setLayout(layout);

		readSettings();
	}

	ConsoleDialog::~ConsoleDialog()
	{
		writeSettings();

		//remove tab ownership so they don't get deleted with the tab widget
		foreach(IConsoleTab *tab, m_tabs)
			tab->setParent(0);

		delete m_tabWidget;
		m_tabWidget = 0;
	}

	void ConsoleDialog::done(int r)
	{
		QDialog::done(r);

		deleteLater();
		m_instance = 0;
	}

	void ConsoleDialog::keyPressEvent(QKeyEvent *event)
	{
		//pressing enter/return in a QDialog accepts it, don't do it
		switch(event->key()) {
			case Qt::Key_Return:
			case Qt::Key_Enter:
				event->ignore();
			break;

			default:
				QDialog::keyPressEvent(event);
		}
	}

	void ConsoleDialog::readSettings()
	{
		QSettings *settings = ICore::settings();

		settings->beginGroup(settingsGroup);
		restoreGeometry(settings->value(geometryKey).toByteArray());
		settings->endGroup();
	}

	void ConsoleDialog::writeSettings()
	{
		QSettings *settings = ICore::settings();

		settings->beginGroup(settingsGroup);
		settings->setValue(geometryKey, saveGeometry());
		settings->endGroup();
	}
}
