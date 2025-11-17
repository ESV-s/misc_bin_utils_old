#pragma once
#include <ida.hpp>
#include <idp.hpp>
#include <graph.hpp>
#include <loader.hpp>
#include <kernwin.hpp>



static bool highlight_calls(qflow_chart_t *fc, int n, text_t &text);

static ssize_t idaapi ui_cb(void *user_data, int code, va_list va);

static void get_call_instructions(void);

static void load_config();

bool check_highlight();

bool idaapi highlight_run();

