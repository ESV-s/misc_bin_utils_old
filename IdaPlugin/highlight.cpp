#include "highlight.h"


static qstrvec_t *call_mnemonics = new qstrvec_t();

static int highlight2_enabled = 1;
static int highlight2_color = COLOR_CODNAME;

static const cfgopt_t g_opts[] =
{
	cfgopt_t("HIGHLIGHT2_ENABLED", &highlight2_enabled, 0, 1),
	cfgopt_t("HIGHLIGHT2_COLOR", &highlight2_color, COLOR_DEFAULT, COLOR_FG_MAX),
};



bool highlight_calls(qflow_chart_t * fc, int n, text_t & text)
{
	if (!highlight2_enabled || n >= fc->blocks.size())
		return false;

	gen_disasm_text(text, fc->blocks[n].start_ea, fc->blocks[n].end_ea, false);

	for (int i = 0; i < text.size(); i++)
	{
		ssize_t len = text[i].line.length();

		if (len > 2 && text[i].line[1] == COLOR_INSN)
		{
			const char* line = text[i].line.c_str();

			for (int j = 0; j < call_mnemonics->size(); j++)
			{
				const char* instr = call_mnemonics->at(j).c_str();
				ssize_t instr_len = call_mnemonics->at(j).length();

				if (instr_len + 2 < len &&
					!memcmp(instr, line + 2, instr_len) &&
					line[2 + instr_len] == COLOR_REGCMT)
				{
					text[i].line[1] = highlight2_color;
				}
			}
		}
	}

	return true;
}

ssize_t idaapi ui_cb(void * user_data, int code, va_list va)
{
	switch (code)
	{
	case ui_gen_idanode_text:
	{
		qflow_chart_t *fc = va_arg(va, qflow_chart_t *);
		int node = va_arg(va, int);
		text_t *text = va_arg(va, text_t *);
		return highlight_calls(fc, node, *text);
	}
	}
	return 0;
}

void get_call_instructions(void)
{
	if (call_mnemonics->size())
		return;
	// idp.hpp
	//#if !defined(NO_OBSOLETE_FUNCS) || defined(__DEFINE_PH__)
	//	idaman processor_t ida_export_data ph;   ///< current processor
	//	idaman asm_t ida_export_data ash;        ///< current assembler
	//#endif

	// need __DEFINE_PH__ in the settings project
	int instruc_count = ph.instruc_end - 1 - ph.instruc_start;

	for (int i = 0; i < instruc_count; i++)
	{
		if ((ph.instruc[i].feature & CF_CALL) == CF_CALL)
		{
			call_mnemonics->push_back(qstring(ph.instruc[i].name));
		}
	}

	//for (int i = 0; i < call_mnemonics->size(); i++)
	//{
	//	msg("Highlight instruction - %s\n", call_mnemonics->at(i).c_str());
	//}
}

void load_config()
{
	read_config_file("highlight2", g_opts, qnumber(g_opts));
}



bool check_highlight()
{
	if (!is_idaq())
		return false;
	load_config();

	get_call_instructions();

	hook_to_notification_point(HT_UI, ui_cb);

	msg("Highlight2 started\n");

	return true;
	
}

bool idaapi highlight_run()
{
	static const char form[] =
		"Highlight2 Settings\n"
		" <Enable plugin:C>>\n"
		" <Select color:b::40::>\n"
		"\n"
		"Hint: to change this permanently, edit highlight2.cfg.\n\n";

	static const char *items[] =
	{
		"COLOR_DEFAULT",
		"COLOR_REGCMT",
		"COLOR_RPTCMT",
		"COLOR_AUTOCMT",
		"COLOR_INSN",
		"COLOR_DATNAME",
		"COLOR_DNAME",
		"COLOR_DEMNAME",
		"COLOR_SYMBOL",
		"COLOR_CHAR",
		"COLOR_STRING",
		"COLOR_NUMBER",
		"COLOR_VOIDOP",
		"COLOR_CREF",
		"COLOR_DREF",
		"COLOR_CREFTAIL",
		"COLOR_DREFTAIL",
		"COLOR_ERROR",
		"COLOR_PREFIX",
		"COLOR_BINPREF",
		"COLOR_EXTRA",
		"COLOR_ALTOP",
		"COLOR_HIDNAME",
		"COLOR_LIBNAME",
		"COLOR_LOCNAME",
		"COLOR_CODNAME",
		"COLOR_ASMDIR",
		"COLOR_MACRO",
		"COLOR_DSTR",
		"COLOR_DCHAR",
		"COLOR_DNUM",
		"COLOR_KEYWORD",
		"COLOR_REG",
		"COLOR_IMPNAME",
		"COLOR_SEGNAME",
		"COLOR_UNKNAME",
		"COLOR_CNAME",
		"COLOR_UNAME",
		"COLOR_COLLAPSED",
		"COLOR_FG_MAX",
	};

	qstrvec_t list;
	for (int i = 0; i < qnumber(items); i++)
		list.push_back(items[i]);

	int sel = highlight2_color - 1;
	uval_t flags = highlight2_enabled;

	if (ask_form(form, &flags, &list, &sel) > 0)
	{
		highlight2_color = sel + 1;
		highlight2_enabled = flags;
	}

	return true;
}
