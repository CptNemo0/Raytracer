#ifndef MESH_H
#define MESH_H
#include "raytracer_math.h"
#include "Triangle.h"
#include "Vertex.h"
#include "Texture.h"
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

        std::shared_ptr<Texture> texture;

		void SetMeshColors(const Color4& color0)
		{
			for (auto& vertex : vertices)
			{
				vertex.color = color0;
			}
		}

        virtual void Generate() = 0;

        void MakeNormals()  
           {  
               for (auto& vertex : vertices)  
               {  
                   vertex.normal = math::vec3(0.0f, 0.0f, 0.0f);  
               }  

               for (const auto& index : indices)  
               {  
                   const auto& v0 = vertices[index[0]].position;  
                   const auto& v1 = vertices[index[1]].position;  
                   const auto& v2 = vertices[index[2]].position;  

                   math::vec3 edge1 = v1 - v0;  
                   math::vec3 edge2 = v2 - v0;  
                   math::vec3 normal = math::normalized(math::cross(edge2, edge1));  

                   vertices[index[0]].normal += normal;  
                   vertices[index[1]].normal += normal;  
                   vertices[index[2]].normal += normal;  
               }  

               for (auto& vertex : vertices)  
               {  
                   math::normalize(vertex.normal);  
               }  
           };

        void SetTexture(std::shared_ptr<Texture> texture) 
        {
			this->texture = texture;
        }


    
    };
}

#endif // !MESH_H
