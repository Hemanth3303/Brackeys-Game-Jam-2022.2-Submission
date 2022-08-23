#include "simple_renderer2d.h"

void simple_renderer2d_init(Simple_Renderer2D* simple_renderer2d) {
	if(cc_deque_new(&simple_renderer2d->render_queue)!=CC_OK) {
		printf("Failed to init render queue\n");
	}
}

void simple_renderer2d_deinit(Simple_Renderer2D* simple_renderer2d) {
	cc_deque_destroy(simple_renderer2d->render_queue);
}

void simple_renderer2d_submit(Simple_Renderer2D* simple_renderer2d, Renderable2D *renderable) {
	if(cc_deque_add_last(simple_renderer2d->render_queue, renderable)!=CC_OK) {
		printf("Failed to add renderable to render queue\n");
	}
}

void simple_renderer2d_flush(Simple_Renderer2D* simple_renderer2d) {
	size_t render_queue_size=cc_deque_size(simple_renderer2d->render_queue);
	while(render_queue_size!=0) {
		Renderable2D renderable;
		void *ptr;
		cc_deque_remove_first(simple_renderer2d->render_queue, &ptr);
		render_queue_size=cc_deque_size(simple_renderer2d->render_queue);

		renderable=*((Renderable2D *)ptr);
		
		vertex_array_bind(renderable.vertex_array);
		index_buffer_bind(renderable.index_buffer);
		mat4 model_matrix;
		glm_mat4_identity(model_matrix);
		glm_translate(model_matrix, renderable.position);

		shader_enable(renderable.shader);
		shader_set_uniform_mat4f(renderable.shader, "model_matrix", model_matrix);
		texture_bind(&renderable.texture);
		glDrawElements(GL_TRIANGLES, renderable.index_buffer->count, GL_UNSIGNED_INT, NULL);
		shader_disable();

		index_buffer_unbind();
		vertex_array_unbind();

	}
}