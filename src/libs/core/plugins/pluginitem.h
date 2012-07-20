#ifndef CORE_PLUGINITEM_H
#define CORE_PLUGINITEM_H

#include "../core_global.h"

namespace Core
{
	class IPlugin;

	class CORE_EXPORT PluginItem : public QObject
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
				Unloaded
			};

		public:
			PluginItem(const QString &filePath);

			QString author() const;
			QString name() const;
			QString website() const;
			QString version() const;

			IPlugin *plugin() { return m_iplugin; }
			QString filePath() const { return m_filePath; }

			QString error() const { return m_error; }
			bool hasError() const { return !m_error.isEmpty(); }

			bool isEnabled() const { return m_enabled; }
			void setEnabled(const bool &enabled) { m_enabled = enabled; }

			State state() const { return m_state; }
			void setState(const State &destState);

		private:
			void loadPlugin();
			void initializePlugin();
			void runPlugin();
			void stopPlugin();
			void unloadPlugin();

		private:
			IPlugin *m_iplugin;
			QString m_filePath;
			QString m_error;
			bool m_enabled;
			State m_state;
	};
}

#endif // CORE_PLUGINITEM_H
