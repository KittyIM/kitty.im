#ifndef CORE_IMODE_H
#define CORE_IMODE_H

#include <QtCore/QObject>
#include <QtGui/QIcon>

#include "../core_global.h"

namespace Core
{
	class CORE_EXPORT IMode : public QObject
	{
		Q_OBJECT

		public:
			IMode(const QString &id) :
				m_id(id),
				m_widget(0),
				m_enabled(true)
			{ }

			QString id() const { return m_id; }

			QString label() const { return m_label; }
			void setLabel(const QString &label)
			{
				if(label == m_label)
					return;

				m_label = label;
				emit labelChanged(label);
			}

			QIcon icon() const { return m_icon; }
			void setIcon(const QIcon &icon)
			{
				m_icon = icon;
				emit iconChanged(icon);
			}

			QWidget *widget() { return m_widget; }
			void setWidget(QWidget *widget) { m_widget = widget; }

			bool isEnabled() const { return m_enabled; }
			void setEnabled(const bool &enabled)
			{
				if(enabled == m_enabled)
					return;

				m_enabled = enabled;
				emit enabledChanged(enabled);
			}

		signals:
			void labelChanged(const QString &label);
			void iconChanged(const QIcon &icon);
			void enabledChanged(const bool &enabled);

		protected:
			QString m_label;
			QString m_id;
			QIcon m_icon;
			QWidget *m_widget;
			bool m_enabled;
	};
}

#endif // CORE_IMODE_H
