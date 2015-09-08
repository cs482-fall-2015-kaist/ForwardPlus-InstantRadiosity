#ifndef MAIN_H
#define MAIN_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <cstring>

#include "tiny_obj_loader.h"

std::vector<tinyobj::shape_t> shapes;

struct	bBox
{
	glm::vec4	min;
	glm::vec4	max;
	glm::vec4	material;
};

typedef struct 
{
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texcoords;
	std::vector<unsigned short> indices;
    std::string texname;
    glm::vec3 color;
} mesh_t;

typedef struct 
{
	unsigned int vertex_array;
	unsigned int vbo_indices;
	unsigned int num_indices;
	unsigned int vbo_vertices;
	unsigned int vbo_normals;
	unsigned int vbo_texcoords;
    glm::vec3 color;
    std::string texname;
	bBox	 boundingBox;
} device_mesh_t;

typedef struct 
{
	unsigned int vertex_array;
	unsigned int vbo_indices;
	unsigned int num_indices;
	//Don't need these to get it working, but needed for deallocation
	unsigned int vbo_data;
} device_mesh2_t;

typedef struct 
{
	glm::vec3 pt;
	glm::vec2 texcoord;
} vertex2_t;

namespace mesh_attributes 
{
	enum 
	{
		POSITION,
		NORMAL,
        TEXCOORD
	};
}
namespace quad_attributes 
{
    enum 
	{
        POSITION,
        TEXCOORD
    };
}

enum Display 
{
    DISPLAY_DEPTH = 0,
    DISPLAY_NORMAL = 1,
    DISPLAY_POSITION = 2,
    DISPLAY_COLOR = 3,
    DISPLAY_TOTAL = 4,
    DISPLAY_LIGHTS = 5,
	DISPLAY_GLOWMASK = 6,
	DISPLAY_SHADOW = 7,
	DISPLAY_LPOS = 8
};

enum Render
{
    RENDER_CAMERA = 0,
    RENDER_LIGHT = 1
};

char* loadFile(char *fname, GLint &fSize);
void printShaderInfoLog(GLint shader);
void printLinkInfoLog(GLint prog);
void initShade();
void initPass();

void initMesh();
device_mesh_t uploadMesh(const mesh_t & mesh);

void display(void);
void keyboard(unsigned char, int, int);
void reshape(int, int);

//int main (int argc, char* argv[]);

void    initNoise();
void    initShader();
void    initFBO(int width, int height);
void    init();
void    initMesh();
void    initQuad();
void	initVPL ();

void	checkError (char * printString);

#endif
