/*! \file main.cpp
*
* \brief \n Главный файл плагина \n
*/

/*
Это пример модуля плагина. Он демонстрирует, как создать собственное окно и заполнить его виджетами Qt.

	Примечание: мы не рекомендуем использовать этот плагин и виджеты Qt из C++.
	Такие плагины будут зависеть от точной версии библиотек Qt
	и компилятора C++, используемого для их сборки. Hex-Rays может в любое время изменить как библиотеки Qt, так и компилятор C++,
	используемый для сборки IDA, без предварительного предупреждения. Во-вторых, IDA использует собственную сборку библиотек Qt с пространством имен.
	Пожалуйста, рассмотрите возможность использования PyQt для создания виджетов Qt, он более надежен и не страдает от этих проблем.
*/

#pragma once

#include <QtWidgets/QtWidgets>

#include <QtCore\QString>
#include <QtCore/qdir.h>

#include <ida.hpp>
#include <idp.hpp>
#include <loader.hpp>
#include <kernwin.hpp>
#include <frame.hpp>

#include "myactions.h"
#include "pe_heders.h"
#include "start_window.hpp"
#include "highlight.h"
#include <search.hpp>

#include <ua.hpp>
#include "settings.h"
#include "db_connection.hpp"

#include <bytes.hpp>
#include <graph.hpp>

#include "exporter.h"

/// \addtogroup PLUGINS_W
	///@{
	/// \name Описание Действий пунктов меню
	/// используется в см. \ref ui_callback в свиче ui_populating_widget_popup для регистрации пунктов меню \n
	/// и в \ref plugin_ctx_t::plugin_ctx_t для регистрации деиствий выполняемых пунктом меню 
	    ///@{
#define ABOUT_ALL_FUNCTIONS_VIEW_A "Ida View A: Get Info about All Function"		///< Выполняется для получения информации о всех функциях из View A
#define ABOUT_THIS_FUNCTION_VIEW_A "Ida View A: Get Info about This Function"		///< Выполняется для получения информации о текущей функции из View A
#define ACTION3_NAME "Part 3"														///< назначить деиствие и переименовать согласно деиствию
#define ACTION4_NAME "Part 4"														///< назначить деиствие и переименовать согласно деиствию
		///@}

#ifdef _DEBUG
///  переменная предназначена для вывода сообщении в режиме отладки ...
bool mdbg = TRUE;
#else
///  переменная предназначена для вывода сообщении в режиме отладки ...
bool mdbg = FALSE;
#endif


/// Вектор имён фаилов из ApiMonitorDoc папки ...
extern vector<std::string> files_list;
//--------------------------------------------------------------------------

static const unsigned char bbb_icon[] = {
	0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A, 0x00, 0x00, 0x00, 0x0D, 0x49, 0x48, 0x44, 0x52,
	0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x08, 0x06, 0x00, 0x00, 0x00, 0x1F, 0xF3, 0xFF,
	0x61, 0x00, 0x00, 0x00, 0x7D, 0x49, 0x44, 0x41, 0x54, 0x78, 0xDA, 0x63, 0x64, 0xC0, 0x0E, 0xFE,
	0xE3, 0x10, 0x67, 0x24, 0x28, 0x00, 0xD2, 0xFC, 0xF3, 0xAF, 0x36, 0x56, 0xDD, 0xEC, 0xCC, 0x57,
	0x31, 0xF4, 0x20, 0x73, 0xC0, 0xB6, 0xE2, 0xD2, 0x8C, 0x66, 0x08, 0x5C, 0x2F, 0x8A, 0x01, 0x84,
	0x34, 0x63, 0x73, 0x09, 0x23, 0xA9, 0x9A, 0xD1, 0x0D, 0x61, 0x44, 0xD7, 0xCC, 0xCF, 0x02, 0x71,
	0xE2, 0xC7, 0x3F, 0xA8, 0x06, 0x62, 0x13, 0x07, 0x19, 0x42, 0x7D, 0x03, 0x48, 0xF5, 0xC6, 0x20,
	0x34, 0x00, 0xE4, 0x57, 0x74, 0xFF, 0xE3, 0x92, 0x83, 0x19, 0xC0, 0x40, 0x8C, 0x21, 0xD8, 0x34,
	0x33, 0x40, 0xA3, 0x91, 0x01, 0x97, 0x21, 0xC8, 0x00, 0x9B, 0x66, 0x38, 0x01, 0x33, 0x00, 0x44,
	0x50, 0x92, 0x94, 0xB1, 0xBA, 0x04, 0x8B, 0x66, 0x9C, 0x99, 0x09, 0xC5, 0x10, 0x1C, 0xE2, 0x18,
	0xEA, 0x01, 0xA3, 0x65, 0x55, 0x0B, 0x33, 0x14, 0x07, 0x63, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45,
	0x4E, 0x44, 0xAE, 0x42, 0x60, 0x82
};

/// Перечисление для передачи зарегистрированного деиствия в  \ref act_handler_t : public action_handler_t
///
/// см \ref act_handler_t::activate
enum MakeFuncForMenuItem
{
	GET_INFO_ABOUT_ALL_FUNCTIONS_VIEW_A = 1,  ///< согласовано с \ref ABOUT_ALL_FUNCTIONS_VIEW_A и \ref ah1
	GET_INFO_ABOUT_THIS_FUNCTION_VIEW_A,      ///< согласовано с \ref ABOUT_THIS_FUNCTION_VIEW_A и \ref ah2
	ACTION_3_NAME,
	ACTION_4_NAME
};


/// \brief \n  Класс контекста плагина наследуемый от \ref plugmod_t и \ref event_listener_t (idp.hpp)\n
/// Устанавливает дополнительные (вспомогательные) функции для плагина в виде: \n
/// - 1 слушателей событий #hook_event_listener
/// - 2 условий запуска #run
/// - 3 обратного вызова для обработки событий #on_event ,\n\n
///   в третьем случае код события зависит от группы событий, к которой прикреплен callback
struct plugin_ctx_t : public plugmod_t, public event_listener_t
{
	bool     hooked = false; // установка слушателя клавиатуры
	TWidget* widget = nullptr;

	plugin_ctx_t();
	~plugin_ctx_t();

	virtual bool idaapi    run(size_t) override;
	virtual ssize_t idaapi on_event(ssize_t code, va_list va) override;

	// установка слушателя клавиатуры и работа с пунктами меню
	void desc_notification(const char* notification_name, TWidget* view) const;
	void desc_mouse_event(const view_mouse_event_t* event) const;
};

void plugin_ctx_t::desc_notification(const char* notification_name, TWidget* view) const
{
	qstring buffer;
	get_widget_title(&buffer, view);
	//if (hooked)
	//{
	//	msg("Received notification from view %s: \"%s\"\n",
	//		buffer.c_str(),
	//		notification_name);
	//}
}

void plugin_ctx_t::desc_mouse_event(const view_mouse_event_t* event) const
{
	int                     px = event->x;
	int                     py = event->y;
	int                     state = event->state;
	qstring                 over_txt;
	const selection_item_t* item = event->location.item;

	if (event->rtype != TCCRT_FLAT && item != NULL) // если вид не плоский (flat) - например в виде графика
	{
		if (item->is_node) // если мышь на ноде
			over_txt.sprnt("node %d", item->node);
		else // если на ребре соединяющем 2 ноды
			// item->elp.e.src  от какои ноды
			// item->elp.e.dst  к какои ноде идет соединяющее ребро
			over_txt.sprnt("edge %d -> %d", item->elp.e.src, item->elp.e.dst);
	}
	else
	{
		over_txt = "(nothing)";
	}

	msg("Parameters MY : x:%d, y:%d, state:%d, over:%s\n", px, py, state, over_txt.c_str());
}

//---------------------------------------------------------------------------
// Callback for ui notifications

/// \brief \n Обратный вызов,зарегистрированный и  предоставляемый функцией hook_to_notification_point().\n
///
/// Плагин может подключиться к точке уведомления и получать уведомления обо всех основных событиях в IDA.\n
/// Функция обратного вызова будет вызываться для каждого события.
/// \n
/// \param ud  user_data данные, передаваемые при вызове hook_to_notification_point()
/// \param notification_code  processor_t::event_t или ::ui_notification_t или debugger_t::event_t, в зависимости от типа хука
/// \param va дополнительные параметры, передаваемые вместе с уведомлением. см. описания event для получения информации
/// \return  0 ok, событие должно быть обработано дальше\n
///    !=0 событие заблокировано и должно быть отброшено.\n\n
/// в случае процессорных модулей возвращаемое значение используется в качестве возвращаемого значения processor_t::notify()
static ssize_t idaapi ui_callback(void* ud, int notification_code, va_list va)
{
	switch (notification_code)
	{
	case ui_populating_widget_popup:
		{
			TWidget*   widget = va_arg(va, TWidget *);
			const auto v_type = get_widget_type(widget);

			// выполняем динамическое добавление пунктов в выпадающее меню для выбранного view программы

			if (v_type == BWN_DISASM) // если это ида вью А
			{
				TPopupMenu* p = va_arg(va, TPopupMenu *);
				auto*       plgmod = static_cast<plugin_ctx_t*>(ud);
				plgmod->desc_notification("view_popup", widget);

				attach_action_to_popup(widget, p, "-"); // ← разделитель
				attach_action_to_popup(widget, p, ABOUT_ALL_FUNCTIONS_VIEW_A, "BB Actions/");
				attach_action_to_popup(widget, p, ABOUT_THIS_FUNCTION_VIEW_A, "BB Actions/");
				attach_action_to_popup(widget, p, "-"); // ← разделитель
			}

			if (v_type == BWN_OUTPUT) // если это окно вывода
			{
				TPopupMenu* p = va_arg(va, TPopupMenu *);
				auto*       plgmod = static_cast<plugin_ctx_t*>(ud);
				plgmod->desc_notification("view_popup", widget);

				attach_action_to_popup(widget, p, "-"); // ← разделитель
				attach_action_to_popup(widget, p, ACTION3_NAME, "BB Actions/");
				attach_action_to_popup(widget, p, ACTION4_NAME, "BB Actions/");
				attach_action_to_popup(widget, p, "-"); // ← разделитель
			}
			break;
		}
	}

	return 0;
}

//--------------------------------------------------------------------------
struct act_handler_t : public action_handler_t
{
	int value;

	act_handler_t(int _value)
		: value(_value)
	{
	}

	virtual int idaapi activate(action_activation_ctx_t*) override
	{
		switch (value)
		{
		case GET_INFO_ABOUT_ALL_FUNCTIONS_VIEW_A:
			msg("User GET_INFO_ABOUT_ALL menu item is called\n");
			break;
		case GET_INFO_ABOUT_THIS_FUNCTION_VIEW_A:
			msg("User GET_INFO_ABOUT_FUNC menu item is called\n");
			break;
			// ACTION_3_NAME
		case ACTION_3_NAME:
			msg("User ACTION_3_NAME menu item is called\n");
			break;
		case ACTION_4_NAME:
			msg("User ACTION_4_NAME menu item is called\n");
			break;
		default:
			msg("        ERROR BB : User UNKNOWN menu item is called\n");
			break;
		}
		return true;
	}

	virtual action_state_t idaapi update(action_update_ctx_t*) override
	{
		return AST_ENABLE_ALWAYS;
	}
};

/// \name Значения Действий пунктов меню
/// функции устанавливающие значение передаваемое обработчику выбранной акции в выпадающем меню ... см. \ref act_handler_t : public action_handler_t \n
/// при нажатии на пункт меню это значение попадает в act_handler_t : public action_handler_t \n
/// используется в \ref plugin_ctx_t::plugin_ctx_t для задания значения , которое будет отдавать тот или иной пункт меню в обработчик \n
/// и обрабатывается свичем согласно \ref MakeFuncForMenuItem \n
/// 
	///@{
static act_handler_t ah1(1);		///< соответствует \ref GET_INFO_ABOUT_ALL_FUNCTIONS_VIEW_A - 1
static act_handler_t ah2(2);		///< и тд ... - 2
static act_handler_t ah3(3);		///< и тд ... - 3
static act_handler_t ah4(4);		///< и тд ... - 4
	///@}


/// \brief \n Обратный вызов для обработки событий. Код события зависит от группы событий, к которой прикреплен callback\n
/// \n
/// \param code код события которое прослушивается
/// \param va
/// \return 0
ssize_t idaapi plugin_ctx_t::on_event(ssize_t code, va_list va)
{
	TWidget* view = va_arg(va, TWidget *);

	if (code == ui_widget_visible)
	{
		TWidget* l_widget = va_arg(va, TWidget *);
		if (l_widget == widget)
		{
			QWidget* w = (QWidget*)widget;

			auto* start_window = new StartWindow(w);
			start_window->show();
		}
#pragma region Тестовый
		ea_t minEA = inf_get_min_ea();
		ea_t maxEA = inf_get_max_ea();

		// ea_t eee = get_screen_ea();
		const size_t functions_count = get_func_qty();
#pragma endregion Тестовый

		// получить путь до плагина !!!
		qstring plugin_path;
		{
			char    path[MAX_PATH];
			HMODULE hm = nullptr;

			if (GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
			                      GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, "", &hm) == 0)
			{
				return false;
			}

			if (GetModuleFileName(hm, path, sizeof(path)) == 0)
			{
				return false;
			}

			plugin_path.append(path);
			plugin_path.resize(plugin_path.rfind('\\', 0) + 1);
		}

		// покажем количество фаилов в векторе  - то что есть в папке monitor_api_files
		if (mdbg) { msg("\n\t\tVector files Api directory has %d files ...\n\n", files_list.size()); }
	}
	else if (code == ui_widget_invisible)
	{
		TWidget* l_widget = va_arg(va, TWidget *);
		if (l_widget == widget)
		{
			// user defined widget is closed, destroy its controls (to be implemented)
			msg("BlaBlaBla widget is closed\n");
			widget = nullptr;
		}
	}
	//else if (code == view_activated)
	//{
	//	desc_notification("view_activated", view);
	//}
	//else if (code == view_deactivated)
	//{
	//	desc_notification("view_deactivated", view);
	//}
	//else if (code == view_keydown)
	//{
	//	desc_notification("view_keydown", view);
	//	int key = va_arg(va, int);
	//	int state = va_arg(va, int);
	//	msg("Parameters: Key:%d(\'%c\') State:%d\n", key, key, state);
	//}

	//else if (code == view_click || code == view_dblclick)
	//{
	//	desc_notification(code == view_click ? "view_click" : "view_dblclick", view);

	//	int cx, cy;
	//	get_cursor(&cx, &cy);
	//	if (hooked)
	//	{
	//		msg("Cursor position:(%d, %d)\n", cx, cy);
	//		desc_mouse_event(va_arg(va, view_mouse_event_t*));
	//	}

	//}
	//else if (code == view_curpos)
	//{
	//	desc_notification("view_curpos", view);
	//	if (is_idaview(view))
	//	{
	//		auto addr = get_screen_ea();
	//		_RPT1(0, "Address = %llx\n", addr);
	//		char buf[MAXSTR];
	//		ea2str(buf, sizeof(buf), get_screen_ea());
	//		msg("New address: %s\n", buf);
	//	}
	//}
	//else if (code == view_mouse_over)
	//{
	//	desc_notification("view_mouse_over", view);
	//	desc_mouse_event(va_arg(va, view_mouse_event_t*));
	//}
	return 0;
}

plugin_ctx_t::plugin_ctx_t()
{
	// Вспомогательная функция для подключения слушателей событий.
	hook_event_listener(HT_UI, this);

	// Регистрация действий меню
	int icon_id = load_custom_icon(bbb_icon, sizeof(bbb_icon), "png");

	const action_desc_t actions[] =
	{
#define ROW(name, label, handler, tooltip) ACTION_DESC_LITERAL_PLUGMOD(name, label, handler, this, NULL, tooltip, icon_id)

		// зададим имена пунктам в выпадающих меню и назначим функции для выбранного пункта

		ROW(ABOUT_ALL_FUNCTIONS_VIEW_A, "-  BB first menu item ", &ah1, " Get info about all functions ..."),
		ROW(ABOUT_THIS_FUNCTION_VIEW_A, "-  BB second menu item", &ah2, " Get info about this functions ..."),
		ROW(ACTION3_NAME, "-  BB third menu item ", &ah3, " Tooltip for part 3 ..."),
		ROW(ACTION4_NAME, "-  BB fourth menu item", &ah4, " Tooltip for part 4 ..."),
#undef ROW
	};

	// зарегистрируем действия пунктов меню
	for (size_t i = 0, n = qnumber(actions); i < n; ++i)
	{
		register_action(actions[i]);
	}
}

plugin_ctx_t::~plugin_ctx_t()
{
	Settings::shutdown(); // ← один раз на выгрузке

	// слушатели клавиш и пункты меню
	unhook_from_notification_point(HT_VIEW, ui_callback, this);
	unhook_from_notification_point(HT_UI, ui_callback, this);
	// слушатели удаляются автоматически при выгрузке модуля-владельца
	widget = nullptr;
}


/// \brief \n Вызвать плагин. см. procmod_t
/// \return
bool idaapi plugin_ctx_t::run(size_t)
{
	TWidget* g_widget = find_widget("Bla Bla Bla");
	if (g_widget == nullptr)
	{
		// нужно ли очищать панель вывода от текста ...
		const auto output_cleaning = Settings::getPrintInfoOutputCleaning();
		if (output_cleaning)
		{
			msg_clear();
		}
		// получим значение  - фиксировано расположение окна плагина или нет ...
		const auto fixed = Settings::getFixedLocation();
		if (fixed)
		{
			// сначала поставим курсор на первый вид - чтоб плагин всегда открывался в нужном расположении ...
			const auto form = find_widget("IDA View-A");
			activate_widget(form, true);
		}

		widget = create_empty_widget("Bla Bla Bla");
		display_widget(widget, WOPN_DP_TAB);
		/* set callback for view notifications */
		if (!hooked)
		{
			// Вспомогательная функция для подключения слушателей событий.
			hook_event_listener(HT_VIEW, this);
			// Регистрация обратного вызова для класса событий в IDA
			hook_to_notification_point(HT_UI, ui_callback, this);
			hooked = true;
			msg("BB Plugin: installed view notification hook.\n");
		}
	}
	else
	{
		close_widget(g_widget, WCLS_SAVE);
		widget = nullptr; // make lint happy
	}

	return true;
}

//--------------------------------------------------------------------------


/// \brief \n Инициализировать плагин - возвращает указатель на plugmod_t ...\n\n
///
/// Описанные в данной функции события происходят при запуске Ida\n
/// когда она проверяет и загружает плагины перед их использованием ...
/// \return
static plugmod_t*idaapi init()
{
	if (!is_idaq())
		return nullptr;

	Settings::init(); // ← обязательно: загрузить/создать дефолты

	get_current_plugin_directory();
	const std::string API_MONITOR_FOLDER = "\\ApiMonitorDoc";
	get_collection_api_files(PLUGIN_CURRENT_DIRECTORY + API_MONITOR_FOLDER);

	auto sql_instance_name = Settings::getMSSQLInstance();
	if (!sql_instance_name.isEmpty())
	{
		DBConnection tmp(nullptr);
		tmp.TryConnect(sql_instance_name);
	}

	msg("\n\n\n\************************************************\n\n\n"
	    "When the BlaBlaBla plugin is called, depending on the size of the file being examined,\n"
	    "it may take some time for it to read the Ida database ..."
	    "\n\n\n\************************************************\n\n\n");

	return new plugin_ctx_t;
}

//--------------------------------------------------------------------------
static const char comment[] = "This is a BlaBlaBla plugin.";
static const char help[] =
	"A BlaBlaBla plugin module\n";

//--------------------------------------------------------------------------
// This is the preferred name of the plugin module in the menu system
// The preferred name may be overridden in plugins.cfg file
// 
static const char wanted_name[] = "BlaBlaBla";

// This is the preferred hotkey for the plugin module
// The preferred hotkey may be overridden in plugins.cfg file
// 
static const char wanted_hotkey[] = "Shift+Alt+B";

//--------------------------------------------------------------------------
//
//      PLUGIN DESCRIPTION BLOCK
//
//--------------------------------------------------------------------------
plugin_t PLUGIN =
{
	IDP_INTERFACE_VERSION,
	PLUGIN_MULTI, // The plugin can work with multiple idbs in parallel
	init,         // initialize
	nullptr,
	nullptr,
	comment,
	help,          // multiline help about the plugin
	wanted_name,   // the preferred short name of the plugin
	wanted_hotkey, // the preferred hotkey to run the plugin
};
///@}
