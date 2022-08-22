#pragma once

#include "glad/glad.h"
#include "cglm/cglm.h"
#include "cc_deque.h"

#include "renderable2d.h"

typedef struct Simple_Renderer2D {
	CC_Deque *render_queue;
}Simple_Renderer2D;

void simple_renderer2d_init(Simple_Renderer2D* simple_renderer2d);
void simple_renderer2d_deinit(Simple_Renderer2D* simple_renderer2d);
void simple_renderer2d_submit(Simple_Renderer2D* simple_renderer2d, Renderable2D *renderable);
void simple_renderer2d_flush(Simple_Renderer2D* simple_renderer2d);