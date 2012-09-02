#ifndef CORE_ICONSOLETAB_H
#define CORE_ICONSOLETAB_H

#include <QWidget>

namespace Core
{
	class IConsoleTab : public QWidget
	{
		Q_OBJECT

		public:
			IConsoleTab(const QString &id) :
				m_id(id)
			{ }

			QString id() const {return m_id; }

			QString text() const { return m_text; }
			void setText(const QString &text)
			{
				if(text == m_text)
					return;

				m_text = text;
				emit textChanged(text);
			}

			QString icon() const  {return m_icon; }
			void setIcon(const QString &icon)
			{
				if(icon == m_icon)
					return;

				m_icon = icon;
				emit iconChanged(icon);
			}

		signals:
			void textChanged(const QString &text);
			void iconChanged(const QString &icon);

		protected:
			QString m_id;
			QString m_text;
			QString m_icon;
	};
}

#endif // CORE_ICONSOLETAB_H
