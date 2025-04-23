#ifndef MESH_H
#define MESH_H
#include "raytracer_math.h"
#include "Triangle.h"
#include "Vertex.h"
#include <vector> 

namespace mesh
{
    class Mesh
    {
    public:
        int vSize = 1;
        int tSize = 1;
        std::vector<Vertex> vertices;
        std::vector<math::vec<3, int>> indices;

        virtual void Generate() = 0;
        void MakeNormals()  
           {  
               // Initialize all normals to zero  
               for (auto& vertex : vertices)  
               {  
                   vertex.normal = math::vec3(0.0f, 0.0f, 0.0f);  
               }  

               // Calculate normals for each triangle  
               for (const auto& index : indices)  
               {  
                   const auto& v0 = vertices[index[0]].position;  
                   const auto& v1 = vertices[index[1]].position;  
                   const auto& v2 = vertices[index[2]].position;  

                   // Compute the normal of the triangle  
                   math::vec3 edge1 = v1 - v0;  
                   math::vec3 edge2 = v2 - v0;  
                   math::vec3 normal = math::normalized(math::cross(edge1, edge2));  

                   // Add the normal to each vertex of the triangle  
                   vertices[index[0]].normal += normal;  
                   vertices[index[1]].normal += normal;  
                   vertices[index[2]].normal += normal;  
               }  

               // Normalize all vertex normals  
               for (auto& vertex : vertices)  
               {  
                   vertex.normal = math::normalized(vertex.normal);  
               }  
           };
    
    };
}

#endif // !MESH_H
