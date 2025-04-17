#ifndef RESTERIZER_H
#define RESTERIZER_H

#include "Triangle.h"
#include "ColorBuffer.h"
#include "VertexProcessor.h"
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