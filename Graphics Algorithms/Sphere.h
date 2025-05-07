#ifndef SPHERE_H
#define SPHERE_H

#include "Mesh.h"
namespace mesh
{
    class Sphere : public Mesh
    {
    private:
	    const float radius_;
	    const uint32_t rings_;
	    const uint32_t sectors_;


    public:
	    Sphere(uint32_t rings, uint32_t sectors, float r)
		    : rings_(rings), sectors_(sectors), radius_(r)
	    {
		    vSize = (rings + 1) * (sectors + 1);
		    tSize = rings * sectors * 2;
		    vertices.resize(vSize);
		    indices.resize(tSize);
		    Generate();
	    }

        void Generate() override  
        {  
           size_t vertexIndex = 0;  
           size_t indexIndex = 0;  

           auto subsetp_u = 1.0f / static_cast<float>(rings_);
           auto subsetp_v = 1.0f / static_cast<float>(sectors_);

           for (uint32_t i = 0; i <= rings_; ++i)  
           {  
               float theta = i * math::pi / rings_;  
               float sinTheta = sin(theta);  
               float cosTheta = cos(theta);  

               for (uint32_t j = 0; j <= sectors_; ++j)  
               {  
                   float phi = j * 2 * math::pi / sectors_;
                   float sinPhi = sin(phi);  
                   float cosPhi = cos(phi);  

                   math::vec3 position(  
                       radius_ * sinTheta * cosPhi,  
                       radius_ * cosTheta,  
                       radius_ * sinTheta * sinPhi  
                   );  

                   math::vec3 normal = math::normalized(position);

                   math::vec2 uv(
					   subsetp_u * static_cast<float>(j),
					   subsetp_v * static_cast<float>(i)
                   );

                   Vertex& v = vertices[vertexIndex++];
                   v.position = position;
                   v.normal = normal;
                   v.uv = uv;
               }  
           }  

           for (uint32_t i = 0; i < rings_; ++i)  
           {  
               for (uint32_t j = 0; j < sectors_; ++j)  
               {  
                   uint32_t i1 = i * (sectors_ + 1) + j;  
                   uint32_t i2 = i1 + sectors_ + 1;  

                   indices[indexIndex++] = { i1, i2, i1 + 1 };  

                   indices[indexIndex++] = { i1 + 1, i2, i2 + 1 };  
               }  
           }  

	       //MakeNormals();

           for (auto& vertex : vertices)
           {
               vertex.normal = math::normalized(vertex.position);
           }
        }

		void SetColors(const Color4 color)
		{
			for (auto& vertex : vertices)
			{
				vertex.color = color;
			}
		}

    };

}


#endif // !SPHERE_H




