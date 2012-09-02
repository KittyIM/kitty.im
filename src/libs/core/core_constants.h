#ifndef CORE_CONSTANTS_H
#define CORE_CONSTANTS_H

namespace Core
{
	namespace Constants
	{
		const char VERSION[]			= "0.0.1";

		//images
		const char IMAGE_KITTY48[]		= ":/core/images/kitty_48.png";
		const char IMAGE_KITYLOGO[]		= ":/core/images/logo.png";

		//icons
		const char ICON_KITTY[]			= "Icon.Kitty";
		const char ICON_SETTINGS[]		= "Icon.Settings";
		const char ICON_CLOSE[]			= "Icon.Close";

		//settings
		const char SETTINGS_GENERAL[]    = "Setting.General";
		const char SETTINGS_CONNECTION[] = "Setting.Connection";

		//toolbars
		const char TOOLBAR_MAIN[]		= "Toolbar.Main";
		const char TOOLBAR_PLUGINS[]	= "Toolbar.Plugins";

		//menus
		const char MENU_MAIN[]			= "Menu.Main";
		const char MENU_USER[]			= "Menu.User";
		const char MENU_TRAY[]			= "Menu.Tray";

		//actions
		const char ACTION_ABOUT[]		= "Action.About";
        const char ACTION_TOGGLEMAIN[]  = "Action.ToggleMainWindow";
		const char ACTION_CONSOLE[]		= "Action.Console";
		const char ACTION_SETTINGS[]	= "Action.Settings";
		const char ACTION_QUIT[]		= "Action.Quit";

		//consoles
		const char CONSOLE_ACTIONS[]	= "Console.Actions";
		const char CONSOLE_COMMAND[]	= "Console.Command";
		const char CONSOLE_DEBUG[]		= "Console.Debug";
		const char CONSOLE_ICONS[]		= "Console.Icons";
	}
}

#endif // CORE_CONSTANTS_H
