#include "opengl_pipeline.h"
#include "opengl_renderer.h"

#include <stdlib.h>
#include <assert.h>

mg_opengl_pipeline_t *mg_opengl_create_pipeline(mg_pipeline_create_info_t *create_info)
{
    mg_opengl_pipeline_t *pipeline = (mg_opengl_pipeline_t*)malloc(sizeof(mg_opengl_pipeline_t));

    uint32_t vertex_shader;
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &create_info->vertex_shader->code, NULL);
    glCompileShader(vertex_shader);
    
    uint32_t fragment_shader;
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &create_info->fragment_shader->code, NULL);
    glCompileShader(fragment_shader);

    pipeline->program_id = glCreateProgram();
    glAttachShader(pipeline->program_id, vertex_shader);
    glAttachShader(pipeline->program_id, fragment_shader);
    glLinkProgram(pipeline->program_id);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    glGenVertexArrays(1, &pipeline->vao_id);
    glBindVertexArray(pipeline->vao_id);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  

    glBindVertexArray(0);

    return pipeline;
}

void mg_opengl_destroy_pipeline(mg_opengl_pipeline_t *pipeline)
{
    glDeleteProgram(pipeline->program_id);
    glDeleteVertexArrays(1, &pipeline->vao_id);
    free(pipeline);
}

void mg_opengl_bind_pipeline(mg_opengl_pipeline_t *pipeline)
{
    glUseProgram(pipeline->program_id);
    glBindVertexArray(pipeline->vao_id);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}