#ifndef RESTERIZER_H
#define RESTERIZER_H

#include "Triangle.h"
#include "ColorBuffer.h"
#include "VertexProcessor.h"
#include "Mesh.h"
#include "Light.h"
#include "Texture.h"
#include <memory>
#include <algorithm>

class Rasterizer
{
public:
   Rasterizer(buffer::ColorBuffer& buffer, std::shared_ptr<VertexProcessor> processor) 
       : buffer_(buffer), vertexProcessor_(processor) {};

   void addProjectionMatrix(const math::mat4x4& projectionMatrix)
   {
       projectionMatrix_ = projectionMatrix;
   };

   void addLight(std::shared_ptr<Light> light)
   {
	   lights.push_back(light);
   };

   void setEyePosition(const math::vec3& eyePos)
   {
	   eyePosition_ = eyePos;
   };

   void rasterize()
   {
       if (triangles_) {
           triangles_->ToScreenCoordinates(buffer_.width_, buffer_.height_);
           triangles_->drawTriangle(buffer_, *vertexProcessor_);
       }
   };

   void rasterize(Triangle& triangle)
   {
       triangle.drawTriangle(buffer_, *vertexProcessor_);
   };

   void rasterizePixelLight(Triangle& triangle, const std::vector<std::shared_ptr<Light>>& lights, const std::vector<math::vec3>& pos, const std::vector<math::vec3>& normal)
   {
	   triangle.drawTrianglePixelLight(buffer_, vertexProcessor_, lights, pos, normal);
   }

   void rasterizePixelLightTextured(Triangle& triangle, const std::vector<std::shared_ptr<Light>>& lights, const std::vector<math::vec3>& pos, const std::vector<math::vec3>& normal)
   {
       triangle.drawTrianglePixelLightTextured(buffer_, vertexProcessor_, lights, pos, normal);
   }

   void rasterizeMesh(const mesh::Mesh& mesh)  
   {  
	   
      for (int i = 0; i < mesh.indices.size(); i++) {  
          math::vec3 v0 = mesh.vertices[mesh.indices[i][0]].position;  
          math::vec3 v1 = mesh.vertices[mesh.indices[i][1]].position;  
          math::vec3 v2 = mesh.vertices[mesh.indices[i][2]].position;  

          Triangle triangle(v0, v1, v2);
		   /*triangle.SetColors(mesh.vertices[mesh.indices[i][0]].color,
			   mesh.vertices[mesh.indices[i][1]].color,
			   mesh.vertices[mesh.indices[i][2]].color);*/
		   triangle.SetColors(Color4(255, 0, 0, 255),
			   Color4(0, 255, 0, 255),
			   Color4(0, 0, 255, 255));
          rasterize(triangle);  
      }  
   };

   void rasterizeTextured(Triangle& triangle)
   {
	   triangle.drawTriangleTextured(buffer_, vertexProcessor_);
   };

   void RasterizeMeshTextured(const mesh::Mesh& mesh)
   {
       if (mesh.texture != nullptr)
       {
		    vertexProcessor_->texture_ = mesh.texture;
            for (int i = 0; i < mesh.indices.size(); i++) 
            {
                Vertex v0 = mesh.vertices[mesh.indices[i][0]];
                Vertex v1 = mesh.vertices[mesh.indices[i][1]];
                Vertex v2 = mesh.vertices[mesh.indices[i][2]];

                Triangle triangle(v0, v1, v2);;
          
                triangle.drawTriangleTextured(buffer_, vertexProcessor_);
            }
       }
       else
       {
		   std::cout << "No texture set for the mesh." << std::endl;
       }
      
   }
   void RasterizeMeshVertexLightTextured(const mesh::Mesh& mesh)
   {
	   if (mesh.texture != nullptr)
	   {
           std::vector<math::vec3> vColors;
           vColors.reserve(mesh.vertices.size());

           math::mat4x4 normalMatrix = math::transposed(math::inverse(vertexProcessor_->modelMatrix_));

           for (const auto& vertex : mesh.vertices) {
               math::vec3 color = math::vec3(0.0f, 0.0f, 0.0f);
               math::vec3 worldPosition = vertexProcessor_->LocalToWorld(vertex.position);

               math::vec3 normal = vertex.normal;
               math::vec4 transformedNormal = math::transformed(normalMatrix, math::vec4(normal[0], normal[1], normal[2], 0.0f));
               normal = math::normalized(math::vec3(transformedNormal[0], transformedNormal[1], transformedNormal[2]));

               Fragment fragment0(worldPosition, normal);
               for (const auto& light : lights) {
                   color += (light->calculate(fragment0, eyePosition_));
               }

               color[0] = std::clamp(color[0], 0.0f, 255.0f);
               color[1] = std::clamp(color[1], 0.0f, 255.0f);
               color[2] = std::clamp(color[2], 0.0f, 255.0f);

               vColors.push_back(color);
           }

		   vertexProcessor_->texture_ = mesh.texture;
		   for (int i = 0; i < mesh.indices.size(); i++)
		   {
			   Vertex v0 = mesh.vertices[mesh.indices[i][0]];
			   Vertex v1 = mesh.vertices[mesh.indices[i][1]];
			   Vertex v2 = mesh.vertices[mesh.indices[i][2]];
			   Triangle triangle(v0, v1, v2);
			   triangle.SetColorsf(
				   vColors[mesh.indices[i][0]],
				   vColors[mesh.indices[i][1]],
				   vColors[mesh.indices[i][2]]);
			   
               rasterizeTextured(triangle);
		   }
	   }
	   else
	   {
		   std::cout << "No texture set for the mesh." << std::endl;
	   }
   }

   void RasterizeMeshPixelLight(const mesh::Mesh& mesh)  
   {  
      std::vector<math::vec3> vNormals;
	  std::vector<math::vec3> vPositions;
      vNormals.reserve(mesh.vertices.size()); 
	  vPositions.reserve(mesh.vertices.size());

	  math::mat4x4 normalMatrix = math::transposed(math::inverse(vertexProcessor_->modelMatrix_));


      for (const auto& vertex : mesh.vertices)  
      {  
          math::vec3 normal = vertex.normal;
		  math::vec4 normaled = math::transformed(normalMatrix, math::vec4(normal[0], normal[1], normal[2], 0.0f));
          normal = math::normalized(math::vec3(normaled[0], normaled[1], normaled[2]));
          vNormals.push_back(normal);  

		  auto local = math::vec4(vertex.position[0], vertex.position[1], vertex.position[2], 1.0f);
		  auto world = math::transformed(vertexProcessor_->modelMatrix_, local);
		  vPositions.push_back(math::vec3(world[0], world[1], world[2]));
      }  

      for (int i = 0; i < mesh.indices.size(); i++)  
      {  
          /*math::vec3 v0 = mesh.vertices[mesh.indices[i][0]].position;  
          math::vec3 v1 = mesh.vertices[mesh.indices[i][1]].position;  
          math::vec3 v2 = mesh.vertices[mesh.indices[i][2]].position;  

          Triangle triangle(v0, v1, v2); */ 
          Vertex v0 = mesh.vertices[mesh.indices[i][0]];
          Vertex v1 = mesh.vertices[mesh.indices[i][1]];
          Vertex v2 = mesh.vertices[mesh.indices[i][2]];

          Triangle triangle(v0, v1, v2);
          /*triangle.SetColors(Color4(255, 0, 0, 255),  
                             Color4(0, 255, 0, 255),  
                             Color4(0, 0, 255, 255));*/  

          std::vector<math::vec3> triangleNormals = {  
              vNormals[mesh.indices[i][0]],  
              vNormals[mesh.indices[i][1]],  
              vNormals[mesh.indices[i][2]]  
          };  
		  std::vector<math::vec3> trianglePositions = {
			  vPositions[mesh.indices[i][0]],
			  vPositions[mesh.indices[i][1]],
			  vPositions[mesh.indices[i][2]]
		  };

          rasterizePixelLight(triangle, lights, trianglePositions, triangleNormals);
      }  
   }

   void RasterizeMeshPixelLightTextured(const mesh::Mesh& mesh)
   {
       if (mesh.texture != nullptr)
       {
           std::vector<math::vec3> vNormals;
           std::vector<math::vec3> vPositions;
           vNormals.reserve(mesh.vertices.size());
           vPositions.reserve(mesh.vertices.size());

           math::mat4x4 normalMatrix = math::transposed(math::inverse(vertexProcessor_->modelMatrix_));

           vertexProcessor_->texture_ = mesh.texture;
           for (const auto& vertex : mesh.vertices)
           {
               math::vec3 normal = vertex.normal;
               math::vec4 normaled = math::transformed(normalMatrix, math::vec4(normal[0], normal[1], normal[2], 0.0f));
               normal = math::normalized(math::vec3(normaled[0], normaled[1], normaled[2]));
               vNormals.push_back(normal);

               auto local = math::vec4(vertex.position[0], vertex.position[1], vertex.position[2], 1.0f);
               auto world = math::transformed(vertexProcessor_->modelMatrix_, local);
               vPositions.push_back(math::vec3(world[0], world[1], world[2]));
           }

           for (int i = 0; i < mesh.indices.size(); i++)
           {
               /*math::vec3 v0 = mesh.vertices[mesh.indices[i][0]].position;
               math::vec3 v1 = mesh.vertices[mesh.indices[i][1]].position;
               math::vec3 v2 = mesh.vertices[mesh.indices[i][2]].position;

               Triangle triangle(v0, v1, v2); */
               Vertex v0 = mesh.vertices[mesh.indices[i][0]];
               Vertex v1 = mesh.vertices[mesh.indices[i][1]];
               Vertex v2 = mesh.vertices[mesh.indices[i][2]];

               Triangle triangle(v0, v1, v2);
               /*triangle.SetColors(Color4(255, 0, 0, 255),
                                  Color4(0, 255, 0, 255),
                                  Color4(0, 0, 255, 255));*/

               std::vector<math::vec3> triangleNormals = {
                   vNormals[mesh.indices[i][0]],
                   vNormals[mesh.indices[i][1]],
                   vNormals[mesh.indices[i][2]]
               };
               std::vector<math::vec3> trianglePositions = {
                   vPositions[mesh.indices[i][0]],
                   vPositions[mesh.indices[i][1]],
                   vPositions[mesh.indices[i][2]]
               };

               rasterizePixelLightTextured(triangle, lights, trianglePositions, triangleNormals);
           }
       }
       else
       {
           std::cout << "No texture set for the mesh." << std::endl;
       }
   }

   void RasterizeMeshVertexLight(const mesh::Mesh& mesh)  
     {  
        std::vector<math::vec3> vColors;  
        vColors.reserve(mesh.vertices.size());

        math::mat4x4 normalMatrix = math::transposed(math::inverse(vertexProcessor_->modelMatrix_));  

        for (const auto& vertex : mesh.vertices) {  
            math::vec3 color = math::vec3(0.0f, 0.0f, 0.0f);  
            math::vec3 worldPosition = vertexProcessor_->LocalToWorld(vertex.position);  

            math::vec3 normal = vertex.normal;  
            math::vec4 transformedNormal = math::transformed(normalMatrix, math::vec4(normal[0], normal[1], normal[2], 0.0f));  
            normal = math::normalized(math::vec3(transformedNormal[0], transformedNormal[1], transformedNormal[2]));  

            Fragment fragment0(worldPosition, normal);  
            for (const auto& light : lights) {  
                color += (light->calculate(fragment0, eyePosition_));  
            }  

            color[0] = std::clamp(color[0], 0.0f, 255.0f);  
            color[1] = std::clamp(color[1], 0.0f, 255.0f);  
            color[2] = std::clamp(color[2], 0.0f, 255.0f);  

            vColors.push_back(color);  
        }  

        for (int i = 0; i < mesh.indices.size(); i++) {  
            /*math::vec3 v0 = mesh.vertices[mesh.indices[i][0]].position;  
            math::vec3 v1 = mesh.vertices[mesh.indices[i][1]].position;  
            math::vec3 v2 = mesh.vertices[mesh.indices[i][2]].position;  

            Triangle triangle(v0, v1, v2);  */

			Vertex v0 = mesh.vertices[mesh.indices[i][0]];
			Vertex v1 = mesh.vertices[mesh.indices[i][1]];
			Vertex v2 = mesh.vertices[mesh.indices[i][2]];

			Triangle triangle(v0, v1, v2);

            triangle.SetColorsf(  
                vColors[mesh.indices[i][0]],  
                vColors[mesh.indices[i][1]],  
                vColors[mesh.indices[i][2]]);  
            rasterize(triangle);  
        }  
     }


   void ToScreenCoordinates(Triangle& triangle)
   {
       triangle.ToScreenCoordinates(buffer_.width_, buffer_.height_);
   }

private:
   buffer::ColorBuffer& buffer_;
   math::mat4x4 projectionMatrix_;
   std::shared_ptr<Triangle> triangles_;
   std::shared_ptr<VertexProcessor> vertexProcessor_;
   std::vector<std::shared_ptr<Light>> lights;
   math::vec3 eyePosition_;

};

#endif // !RESTERIZER_H