/*! \file start_window.hpp
*
* \brief \n Фаил содержит описание стартового окна плагина ,  при запуске плагина в IDA ... \n
*
*	Описывает класс StartWindow
*	в этом классе содержатся формы для работы с
*	- setting_form		см \ref StartWindow::setting_form
*	- notepad_form		см \ref StartWindow::notepad_form
*	- binexport_form	см \ref StartWindow::binexport_form
*/

#pragma once
#include <QtWidgets/QtWidgets>

#include "first_window.hpp"
#include "notepad_window.hpp"
#include "binexport_class.hpp"
#include "ui_start_window.h"
#include "key_press_cmdline.h"
#include "function_utils.h"

// --- [ApiMonitorDoc] begin ---
// ВАЖНО:
// 1) start_window.hpp НЕ должен тянуть ida.hpp/loader.hpp и т.п. (чтобы не распухали зависимости UI).
// 2) Для вызова ApplyApiMonCommentsToImports нам достаточно forward declaration на apimon::DataBinDb,
//    а include "apimon_ida_apply.h" лучше делать в start_window.cpp.
// ---
namespace apimon { struct DataBinDb; }
// --- [ApiMonitorDoc] end ---

QT_BEGIN_NAMESPACE
class QLineEdit;
QT_END_NAMESPACE

/// \brief \n
/// Класс главного (__стартового__) окна плагина \n
/// Отображается при запуске, выполняет функции \ref ReadIdaDB...
///
/// в этом классе содержатся формы для работы с
/// - setting_form  см \ref StartWindow::setting_form
/// - notepad_form  см \ref StartWindow::notepad_form
/// - binexport_form см \ref StartWindow::binexport_form
///
/// \n\n
/// \ingroup VIEW_W UI_W
class StartWindow : public QWidget {
	Q_OBJECT

public:

	StartWindow(QWidget * parent = Q_NULLPTR);
	~StartWindow();

protected:
	// void keyPressEvent(QKeyEvent *event) override;

private:
	Ui::StartWindow ui;
	FirstWindow setting_form;
	NotepadWindow notepad_form;
	BinExportClass binexport_form;

	std::vector<func_t*> function_vector{};
	std::vector<std::string> string_vector{};
	int ReadIdaDB();

	// --- [ApiMonitorDoc] begin ---
	/// \brief Применить комментарии ApiMonitorDoc к импортам IDA (MVP).
	/// \details Реализация будет в start_window.cpp:
	///  - Загружаем/получаем apimon::DataBinDb (db)
	///  - Вызываем apimon_ida::ApplyApiMonCommentsToImports(db,...)
	void ApplyApiMonComments_Imports(const apimon::DataBinDb& db);

	/// \brief Применить комментарии ApiMonitorDoc к экспортируемым функциям (entry points).
	/// \details Реализация будет в start_window.cpp:
	///  - Вызываем apimon_ida::ApplyApiMonCommentsToExports(db,...)
	void ApplyApiMonComments_Exports(const apimon::DataBinDb& db);

	/// \brief Применить комментарии ApiMonitorDoc к call-сайтам, которые вызывают импорты.
	/// \details Реализация будет в start_window.cpp:
	///  - Вызываем apimon_ida::ApplyApiMonCommentsToImportCalls(db,...)
	void ApplyApiMonComments_ImportCalls(const apimon::DataBinDb& db);

	/// \brief Тестовый вызов "применить к импортам" без параметров.
	/// \details Удобно повесить на кнопку/меню/хоткей.
	void ApplyApiMonComments_Imports_FromLoadedDb();

	/// \brief Тестовый вызов "применить всё (imports/exports/calls)" без параметров.
	/// \details Внутри загрузка apimon_data.bin и вызовы ApplyApiMonComments_*.
	void ApplyApiMonComments_All_FromLoadedDb();
	// --- [ApiMonitorDoc] end ---

	QLineEdit* ui_CMDLine;

	private slots:

	void setting_form_show();
	void notepad_form_show();
	void binexport_form_show();

	void PressEnter();

	// --- [ApiMonitorDoc] begin ---
	/// \brief Slot: нажали кнопку/меню "Apply ApiMon (Imports)".
	/// \details В start_window.cpp привяжешь к ui-кнопке, когда покажешь её имя.
	void OnApplyApiMonImports();
	// --- [ApiMonitorDoc] end ---
};