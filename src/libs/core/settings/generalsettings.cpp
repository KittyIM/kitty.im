#include "generalsettings.h"
#include "ui_generalsettingswidget.h"

#include <core_constants.h>
#include <icore.h>

#include <QPushButton>
#include <QFileInfo>
#include <QSettings>
#include <QDebug>
#include <QDir>

static const char settingsGroup[] = "App";
static const char languageKey[] = "language";

namespace Core
{
	namespace SettingsPages
	{
		GeneralSettings::GeneralSettings() :
			m_widget(0)
		{
			m_name = tr("Settings");
			m_icon = Constants::ICON_SETTINGS;
			m_id = Constants::SETTINGS_GENERAL;
		}

		QWidget *GeneralSettings::createWidget()
		{
			m_widget = new GeneralSettingsWidget();

			QSettings *settings = ICore::settings();
			settings->beginGroup(settingsGroup);

			const QString currentLocale = settings->value(languageKey).toString();

			m_widget->ui->languageComboBox->addItem(tr("System"), QString());
			m_widget->ui->languageComboBox->addItem("English", "C");

			if(currentLocale == "C")
				m_widget->ui->languageComboBox->setCurrentIndex(m_widget->ui->languageComboBox->count() - 1);

			const QString translationPath = qApp->applicationDirPath() + "/translations";
			const QFileInfoList translationFiles = QDir(translationPath).entryInfoList(QStringList() << "kittyim_*.qm");

			foreach(const QFileInfo &fileInfo, translationFiles) {
				const QString locale = fileInfo.baseName().remove("kittyim_");

				m_widget->ui->languageComboBox->addItem(QLocale::languageToString(QLocale(locale).language()), locale);
				if(locale == currentLocale) {
					m_widget->ui->languageComboBox->setCurrentIndex(m_widget->ui->languageComboBox->count() - 1);
				}
			}

			settings->endGroup();

			return m_widget;
		}

		void GeneralSettings::apply()
		{
			if(!m_widget)
				return;

			QSettings *settings = ICore::settings();
			settings->beginGroup(settingsGroup);

			//language
			const int languageIdx = m_widget->ui->languageComboBox->currentIndex();
			QString locale = m_widget->ui->languageComboBox->itemData(languageIdx).toString();
			if(locale.isEmpty()) {
				settings->remove(languageKey);
			} else {
				settings->setValue(languageKey, locale);
			}

			settings->endGroup();
		}

		void GeneralSettings::finish()
		{
			if(!m_widget)
				return;

			delete m_widget;
			m_widget = 0;
		}

		GeneralSettingsWidget::GeneralSettingsWidget() :
			ui(new Ui::GeneralSettingsWidget)
		{
			ui->setupUi(this);
		}
	}
}
