#ifndef MESH_H
#define MESH_H

#include "vertex.h"
#include <GL/glew.h>
#include "obj_loader.h"

class Mesh
{
public:
    Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
    Mesh(const std::string& fileName);
    void draw();
    ~Mesh();

private:
    enum {
        POSITION_VB,
        INDEX_VB,
        TEXCOORD_VB,
        NORMAL_VB,

        NUM_BUFFERS
    };

    void InitMesh(const IndexedModel& model);
    static void calcNormals(Vertex* vertices, unsigned int num_vertices,
            unsigned int* indices, unsigned int num_indices);

    GLuint m_vertexArrayObject;
    GLuint m_vertexArrayBuffers[NUM_BUFFERS];
    unsigned int m_drawCount; //stores how big it is, how much we want to draw
};

#endif // MESH_H
