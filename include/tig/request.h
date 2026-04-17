/* Copyright (c) 2006-2026 Jonas Fonseca <jonas.fonseca@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef TIG_REQUEST_H
#define TIG_REQUEST_H

#include "tig/tig.h"

/*
 * User requests
 */

/* 视图名称中文映射 */
#define VIEW_REQ(id, name) REQ_(VIEW_##id, "显示" #name "视图")

#define REQ_INFO \
	REQ_GROUP("视图切换") \
	VIEW_INFO(VIEW_REQ), \
	\
	REQ_GROUP("视图操作") \
	REQ_(ENTER,		"进入并打开选中行"), \
	REQ_(BACK,		"返回上一个视图状态"), \
	REQ_(NEXT,		"移至下一项"), \
	REQ_(PREVIOUS,		"移至上一项"), \
	REQ_(PARENT,		"移至父级"), \
	REQ_(VIEW_NEXT,		"切换焦点到下一个视图"), \
	REQ_(REFRESH,		"重新加载并刷新视图"), \
	REQ_(MAXIMIZE,		"最大化当前视图"), \
	REQ_(VIEW_CLOSE,	"关闭当前视图"), \
	REQ_(VIEW_CLOSE_NO_QUIT,	"关闭当前视图但不退出"), \
	REQ_(QUIT,		"关闭所有视图并退出"), \
	\
	REQ_GROUP("视图专属操作") \
	REQ_(STATUS_UPDATE,	"暂存/取消暂存代码块或文件变更"), \
	REQ_(STATUS_REVERT,	"还原代码块或文件变更"), \
	REQ_(STATUS_MERGE,	"使用外部工具合并文件"), \
	REQ_(STAGE_UPDATE_LINE,	"暂存/取消暂存单行"), \
	REQ_(STAGE_UPDATE_PART, "暂存/取消暂存代码块部分"), \
	REQ_(STAGE_SPLIT_CHUNK,	"拆分当前diff代码块"), \
	\
	REQ_GROUP("光标导航") \
	REQ_(MOVE_UP,		"光标上移一行"), \
	REQ_(MOVE_DOWN,		"光标下移一行"), \
	REQ_(MOVE_PAGE_UP,	"光标上移一页"), \
	REQ_(MOVE_PAGE_DOWN,	"光标下移一页"), \
	REQ_(MOVE_HALF_PAGE_UP,	"光标上移半页"), \
	REQ_(MOVE_HALF_PAGE_DOWN,	"光标下移半页"), \
	REQ_(MOVE_FIRST_LINE,	"光标移至首行"), \
	REQ_(MOVE_LAST_LINE,	"光标移至末行"), \
	REQ_(MOVE_NEXT_MERGE,	"光标移至下一个合并提交"), \
	REQ_(MOVE_PREV_MERGE,	"光标移至上一个合并提交"), \
	\
	REQ_GROUP("滚动") \
	REQ_(SCROLL_LINE_UP,	"向上滚动一行"), \
	REQ_(SCROLL_LINE_DOWN,	"向下滚动一行"), \
	REQ_(SCROLL_PAGE_UP,	"向上滚动一页"), \
	REQ_(SCROLL_PAGE_DOWN,	"向下滚动一页"), \
	REQ_(SCROLL_HALF_PAGE_UP,	"向上滚动半页"), \
	REQ_(SCROLL_HALF_PAGE_DOWN,	"向下滚动半页"), \
	REQ_(SCROLL_FIRST_COL,	"滚动到首列"), \
	REQ_(SCROLL_LEFT,	"向左滚动两列"), \
	REQ_(SCROLL_RIGHT,	"向右滚动两列"), \
	\
	REQ_GROUP("搜索") \
	REQ_(SEARCH,		"搜索当前视图"), \
	REQ_(SEARCH_BACK,	"反向搜索当前视图"), \
	REQ_(FIND_NEXT,		"查找下一个匹配"), \
	REQ_(FIND_PREV,		"查找上一个匹配"), \
	\
	REQ_GROUP("其他") \
	REQ_(EDIT,		"在编辑器中打开"), \
	REQ_(PROMPT,		"打开命令提示符"), \
	REQ_(OPTIONS,		"打开选项菜单"), \
	REQ_(SCREEN_REDRAW,	"重绘屏幕"), \
	REQ_(STOP_LOADING,	"停止所有加载中的视图"), \
	REQ_(SHOW_VERSION,	"显示版本信息"), \
	REQ_(NONE,		"无操作")


/* User action requests. */
enum request {
#define REQ_GROUP(help)
#define REQ_(req, help) REQ_##req

	/* Offset all requests to avoid conflicts with ncurses getch values. */
	REQ_UNKNOWN = KEY_MAX + 1,
	REQ_OFFSET,
	REQ_INFO,

	/* Internal requests. */
	REQ_SCROLL_WHEEL_DOWN,
	REQ_SCROLL_WHEEL_UP,
	REQ_MOVE_WHEEL_DOWN,
	REQ_MOVE_WHEEL_UP,

	/* Start of the run request IDs */
	REQ_RUN_REQUESTS

#undef	REQ_GROUP
#undef	REQ_
};

struct request_info {
	enum request request;
	const char *name;
	int namelen;
	const char *help;
};

enum request get_request(const char *name);
const char *get_request_name(enum request request);
bool foreach_request(bool (*visitor)(void *data, const struct request_info *req_info, const char *group), void *data);

#endif
/* vim: set ts=8 sw=8 noexpandtab: */
