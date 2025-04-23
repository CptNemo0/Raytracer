#ifndef RESTERIZER_H
#define RESTERIZER_H

#include "Triangle.h"
#include "ColorBuffer.h"
#include "VertexProcessor.h"
#include "Mesh.h"
#include <memory>

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
		   /*triangle.SetColors(Color4(255, 0, 0, 255),
			   Color4(255, 0, 0, 255),
			   Color4(255, 0, 0, 255));*/
		   rasterize(triangle);
	   }
   };

   void ToScreenCoordinates(Triangle& triangle)
   {
       triangle.ToScreenCoordinates(buffer_.width_, buffer_.height_);
   }

private:
   buffer::ColorBuffer& buffer_;
   math::mat4x4 projectionMatrix_;
   std::shared_ptr<Triangle> triangles_;
   std::shared_ptr<VertexProcessor> vertexProcessor_;
};

#endif // !RESTERIZER_H