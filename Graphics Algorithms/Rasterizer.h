#ifndef RESTERIZER_H
#define RESTERIZER_H

#include "Triangle.h"
#include "ColorBuffer.h"
#include "VertexProcessor.h"
#include "Mesh.h"
#include "Light.h"
#include <memory>
#include <algorithm>

class Rasterizer
{
public:
   Rasterizer(buffer::ColorBuffer& buffer, std::shared_ptr<VertexProcessor> processor) 
       : buffer_(buffer), vertexProcessor_(processor) {};

   void addTriangle(const Triangle& triangle)
   {
       triangles_ = std::make_shared<Triangle>(triangle);
   };

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

   void rasterizePixelLight(Triangle& triangle, std::vector<std::shared_ptr<Light>> lights, std::vector<math::vec3> normal) 
   {
	   triangle.drawTrianglePixelLight(buffer_, *vertexProcessor_, lights, normal);
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

   void ResterizeMeshPixelLight(const mesh::Mesh& mesh)
   {
	   for (int i = 0; i < mesh.indices.size(); i++) {
		   math::vec3 v0 = mesh.vertices[mesh.indices[i][0]].position;
		   math::vec3 v1 = mesh.vertices[mesh.indices[i][1]].position;
		   math::vec3 v2 = mesh.vertices[mesh.indices[i][2]].position;

		   math::vec3 normal = mesh.vertices[mesh.indices[i][0]].normal;
		   math::vec3 normal1 = mesh.vertices[mesh.indices[i][1]].normal;
		   math::vec3 normal2 = mesh.vertices[mesh.indices[i][2]].normal;

		   std::vector<math::vec3> normals;
		   normals.push_back(normal);
		   normals.push_back(normal1);
		   normals.push_back(normal2);

		   Triangle triangle(v0, v1, v2);
		   triangle.SetColors(Color4(255, 0, 0, 255),
			   Color4(0, 255, 0, 255),
			   Color4(0, 0, 255, 255));
		   rasterizePixelLight(triangle, lights, normals);
	   }
   };

   void RasterizeMeshLightVertex(const mesh::Mesh& mesh)
   {
       std::vector<math::vec3> vColors;
       vColors.reserve(mesh.indices.size());


       for (const auto& vertex : mesh.vertices) {
           /*math::vec3 color = math::vec3(
               static_cast<float>(vertex.color[0]),
               static_cast<float>(vertex.color[1]),
               static_cast<float>(vertex.color[2])
           );*/

		   math::vec3 color = math::vec3(0.0f, 0.0f, 0.0f);
           Fragment fragment0(vertex.position, vertex.normal);
           for (const auto& light : lights) {
               color += (light->calculate(fragment0, eyePosition_));
           }

           color[0] = std::clamp(color[0], 0.0f, 255.0f);
           color[1] = std::clamp(color[1], 0.0f, 255.0f);
           color[2] = std::clamp(color[2], 0.0f, 255.0f);

           vColors.push_back(color);
       }



       for (int i = 0; i < mesh.indices.size(); i++) {
           math::vec3 v0 = mesh.vertices[mesh.indices[i][0]].position;
           math::vec3 v1 = mesh.vertices[mesh.indices[i][1]].position;
           math::vec3 v2 = mesh.vertices[mesh.indices[i][2]].position;

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