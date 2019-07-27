﻿/**
 * File:   native_window.h
 * Author: AWTK Develop Team
 * Brief:  native window
 *
 * Copyright (c) 2019 - 2019  Guangzhou ZHIYUAN Electronics Co.,Ltd.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * License file for more details.
 *
 */

/**
 * History:
 * ================================================================
 * 2018-07-21 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#ifndef TK_NATIVE_WINDOW_H
#define TK_NATIVE_WINDOW_H

#include "tkc/str.h"
#include "tkc/value.h"
#include "tkc/object.h"
#include "base/widget.h"

BEGIN_C_DECLS

struct _native_window_t;
typedef struct _native_window_t native_window_t;

typedef canvas_t* (*native_window_get_canvas_t)(native_window_t* win);
typedef ret_t (*native_window_move_t)(native_window_t* win, xy_t x, xy_t y);
typedef ret_t (*native_window_resize_t)(native_window_t* win, wh_t w, wh_t h);

typedef struct _native_window_vtable_t {
  const char* type;
  native_window_move_t move;
  native_window_resize_t resize;
  native_window_get_canvas_t get_canvas;
} native_window_vtable_t;

/**
 * @class native_window_t
 * @parent object_t
 * 原生窗口。
 *
 */
struct _native_window_t {
  object_t object;

  void* handle;
  bool_t shared;
  rect_t dirty_rect;
  rect_t last_dirty_rect;
  const native_window_vtable_t* vt;

  rect_t rect;
  bool_t dirty;
};

/**
 * @method native_window_move
 * 移动窗口。
 *
 * @param {native_window_t*} win win对象。
 * @param {xy_t} x x坐标。
 * @param {xy_t} y y坐标。
 * @param {bool_t} force 无论是否shared都move。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t native_window_move(native_window_t* win, xy_t x, xy_t y, bool_t force);

/**
 * @method native_window_resize
 * 调整窗口大小。
 *
 * @param {native_window_t*} win win对象。
 * @param {wh_t} w 宽。
 * @param {wh_t} h 高。
 * @param {bool_t} force 无论是否shared都resize。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t native_window_resize(native_window_t* win, wh_t w, wh_t h, bool_t force);

/**
 * @method native_window_get_canvas
 * 获取canvas。
 *
 * @param {native_window_t*} win win对象。
 *
 * @return {canvas_t} 返回canvas对象。
 */
canvas_t* native_window_get_canvas(native_window_t* win);

/**
 * @method native_window_create
 * 创建win对象。
 * @param {const char*} params 参数。
 *
 * @return {native_window_t*} 返回win对象。
 */
native_window_t* native_window_create(widget_t* widget);

/**
 * @method native_window_invalidate
 * 请求重绘指定区域。
 * @param {native_window_t*} win win对象。
 * @param {rect_t*} r 重绘区域。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t native_window_invalidate(native_window_t* win, rect_t* r);

/*public for window manager only*/
rect_t native_window_calc_dirty_rect(native_window_t* win);
ret_t native_window_update_last_dirty_rect(native_window_t* win);
ret_t native_window_on_resized(native_window_t* win, wh_t w, wh_t h);

ret_t native_window_begin_frame(native_window_t* win, lcd_draw_mode_t mode);
ret_t native_window_paint(native_window_t* win, widget_t* widget);
ret_t native_window_end_frame(native_window_t* win);

#define NATIVE_WINDOW(win) ((native_window_t*)(win))

#define NATIVE_WINDOW_PROP_SIZE "size"
#define NATIVE_WINDOW_PROP_TITLE "title"
#define NATIVE_WINDOW_PROP_POSITION "position"

typedef enum _native_window_event_type_t {
  EVT_NATIVE_WINDOW_RESIZED = 0xff,
  EVT_NATIVE_WINDOW_DESTROY
} native_window_event_type_t;

END_C_DECLS

#endif /*TK_NATIVE_WINDOW_H*/