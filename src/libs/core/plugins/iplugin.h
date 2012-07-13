#ifndef CORE_IPLUGIN_H
#define CORE_IPLUGIN_H

#include <QtCore/QObject>

#include "../core_global.h"
#include "plugininfo.h"

namespace Core
{
	class CORE_EXPORT IPlugin : public QObject
	{
		Q_OBJECT

		public:
			enum State
			{
				Invalid = 0,
				Loaded,
				Initialized,
				Running,
				Stopped,
				Deinitialized
			};

		public:
			IPlugin() :
				m_info(new PluginInfo(this)),
				m_state(Invalid)
			{ }

			PluginInfo *info() const { return m_info; }

			QString error() const { return m_error; }
			bool hasError() const { return !m_error.isEmpty(); }

			State state() const { return m_state; }
			void setState(const State &state) { m_state = state; }

		protected:
			PluginInfo *m_info;
			QString m_error;
			State m_state;
	};
}

#endif // CORE_IPLUGIN_H
