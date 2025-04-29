
#include <iostream>
#include "Rasterizer.h"
#include "Camera.h"
#include "VertexProcessor.h"
#include "Mesh.h"
#include "Sphere.h"
#include "Cone.h"
#include "Torus.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "ReflectorLight.h"
#include "vec.h"
#include "transformations.h"
#include "raytracer_math.h"

int main()
{
	buffer::ColorBuffer colorBuffer(2000, 2000);
	Color4 color(30, 30, 125, 255);
	colorBuffer.fillColorBuffer(color);
	Color4 colorT(255, 0, 255, 255);
	Color4 colorB(0, 0, 255, 255);
	Color4 colorG(0, 255, 0, 255);
	
	Camera camera(math::vec3(-5.0f, 0.0f, 0.0f),
		math::vec3(0.0f, 0.0f, 1.0f),
		math::vec3(0.0f, 1.0f, 0.0f), 
		90.0f, colorBuffer.width_ / colorBuffer.height_, 0.1f, 1000.0f);
	auto vertexProcessor = std::make_shared<VertexProcessor>();
	vertexProcessor->eyePosition_ = camera.GetPosition();

	// 2. Utwórz światło (DirectionalLight)
	math::vec3 lightDirection = math::normalized(math::vec3(1.0f, -2.0f, 0.5f));
	math::vec3 ambientLight(0.0f, 0.3f, 0.0f);
	math::vec3 diffuseLight(0.0f, 0.3f, 0.0f);
	math::vec3 specularLight(0.5f, 0.5f, 0.5f);
	float shininess = 4.0f;
	float cutoffAngle = 50.0f;
	float outerCutoffAngle = 70.0f;

	auto dirLight = std::make_shared<DirectionalLight>(lightDirection, ambientLight, diffuseLight, specularLight, shininess);
	auto pointLight = std::make_shared<PointLight>(math::vec3(1.5f, 4.0f, 2.0f), ambientLight, diffuseLight, specularLight, shininess);
	auto reflectorLight = std::make_shared<ReflectorLight>(math::vec3(5.5f, -1.0f, 0.0f), lightDirection,cutoffAngle, outerCutoffAngle, ambientLight, diffuseLight, specularLight, shininess);

	vertexProcessor->modelMatrix_ = math::mat4x4(1.0f);
	camera.UpdateViewMatrix();
	vertexProcessor->viewMatrix_ = camera.GetViewMatrix();
	vertexProcessor->projectionMatrix_ = camera.GetProjectionMatrix();

	
	/*std::cout << "Model matrix:" << std::endl;
	vertexProcessor.modelMatrix_.log();
	std::cout << "View matrix:" << std::endl;
	vertexProcessor.viewMatrix_.log();
	std::cout << "Projection matrix:" << std::endl;
	vertexProcessor.projectionMatrix_.log()*/;

	Rasterizer rasterizer(colorBuffer, vertexProcessor);
	rasterizer.setEyePosition(camera.GetPosition());
	//rasterizer.addLight(dirLight);
	//rasterizer.addLight(pointLight);
	rasterizer.addLight(reflectorLight);


	/*math::vec3 v0_1(0.0f, -0.5f, 1.0f);
	math::vec3 v1_1(-0.5f, 0.0f, 1.0f);
	math::vec3 v2_1(0.0f, 0.8f, 1.0f);

	math::vec3 v0_2(0.5f, 0.5f, 1.0f);
	math::vec3 v1_2(-0.4f, -0.5f, 1.0f);
	math::vec3 v2_2(0.0f, 1.0f, 1.0f);

	math::vec3 v0_3(-1.0f, 1.0f, 1.0f);
	math::vec3 v1_3(-0.5f, 0.5f, 1.0f);
	math::vec3 v2_3(-1.0f, 0.0f, 1.0f);


	Triangle triangle1(v0_1, v1_1, v2_1);
	Triangle triangle2(v0_2, v1_2, v2_2);
	Triangle triangle3(v0_3, v1_3, v2_3);

	triangle2.SetColors(colorT, colorT, colorT);
	triangle3.SetColors(colorB, colorB, colorB);

    int height = colorBuffer.height_;
    int width = colorBuffer.width_;

	math::mat4x4 translation = math::translation_matrix(0.5f, 0.5f, 0.0f);
	vertexProcessor->modelMatrix_ = translation;
	rasterizer.rasterize(triangle1);

	math::mat4x4 rotation = math::rotation_matrix_z_deg(45.0f);
	vertexProcessor->modelMatrix_ = rotation;

	vertexProcessor->modelMatrix_= math::translation_matrix(0.1f, 0.1f, 1.0f);
	vertexProcessor->modelMatrix_.log();
	rasterizer.rasterize(triangle1);

	vertexProcessor->modelMatrix_ = math::rotation_matrix_y_deg(25.0f);
	vertexProcessor->modelMatrix_.log();
	rasterizer.rasterize(triangle2);

	vertexProcessor->modelMatrix_ = math::scale_matrix(2.0f, 0.1f, 1.0f);
	vertexProcessor->modelMatrix_.log();
	rasterizer.rasterize(triangle3);*/


	mesh::Sphere sphere = mesh::Sphere(12, 12, 1.0f);
	sphere.SetMeshColors(colorT);
	

	rasterizer.RasterizeMeshVertexLight(sphere);

	vertexProcessor->modelMatrix_ = math::mat4x4(1.0f);
	vertexProcessor->invModelMatrix_ = math::transposed(math::inverse(vertexProcessor->modelMatrix_));

	mesh::Cone cone = mesh::Cone(15, 2.0f, 3.0f);
	cone.SetMeshColors(colorB);
	math::mat4x4 translation = math::translation_matrix(2.5f, 3.0f, 5.0f);
	math::mat4x4 rotation = math::rotation_matrix_x_deg(-15.0f);
	
	vertexProcessor->modelMatrix_ = math::matmul(translation, rotation);
	rasterizer.RasterizeMeshVertexLight(cone);

	mesh::Torus torus = mesh::Torus(8, 8, 3.0f, 1.0f);
	torus.SetMeshColors(colorG);
	math::mat4x4 T = math::translation_matrix(3.5f, 3.0f, -3.0f);
	math::mat4x4 R = math::rotation_matrix_z_deg(60.0f);

	vertexProcessor->modelMatrix_ = math::matmul(T, R);


	rasterizer.rasterizeMesh(torus);


	colorBuffer.generateBMP("test.bmp");
	return 0;
}

