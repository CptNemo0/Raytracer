
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
	
	Camera camera(math::vec3(0.0f, 0.0f, 0.0f),
		math::vec3(1.0f, 0.0f, 0.0f),
		math::vec3(0.0f, 1.0f, 0.0f), 
		80.0f, colorBuffer.width_ / colorBuffer.height_, 0.1f, 1000.0f);
	auto vertexProcessor = std::make_shared<VertexProcessor>();
	vertexProcessor->eyePosition_ = camera.GetPosition();

	// 2. Utwórz światło (DirectionalLight)
	math::vec3 lightDirection = math::normalized(math::vec3(-2.0f, -1.0f, -3.0f));
	math::vec3 ambientLight(0.0f, 0.3f, 0.0f);
	math::vec3 diffuseLight(0.0f, 0.3f, 0.0f);
	math::vec3 specularLight(0.5f, 0.3f, 0.0f);
	float shininess = 16.0f;
	float cutoffAngle = 20.0f;
	float outerCutoffAngle = 30.0f;

	auto dirLight = std::make_shared<DirectionalLight>(lightDirection, ambientLight, diffuseLight, specularLight, shininess);
	auto pointLight = std::make_shared<PointLight>(math::vec3(0.0f, 0.0f, -2.0), ambientLight, diffuseLight, specularLight, shininess, 1.1f);
	auto reflectorLight = std::make_shared<ReflectorLight>(math::vec3(0.0f, 0.0f, 0.0f), lightDirection,cutoffAngle, outerCutoffAngle, ambientLight, diffuseLight, specularLight, shininess);

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


	/*mesh::Sphere sphere = mesh::Sphere(12, 12, 1.0f);
	sphere.SetMeshColors(colorT);
	

	rasterizer.ResterizeMeshPixelLight(sphere);

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


	rasterizer.rasterizeMesh(torus);*/

	
    mesh::Sphere sphere1 = mesh::Sphere(12, 12, 1.3f);
    sphere1.SetMeshColors(colorT);
    math::mat4x4 translation1 = math::translation_matrix(-2.0f, -1.0f, -3.0f);
    vertexProcessor->modelMatrix_ = translation1;
    rasterizer.RasterizeMeshPixelLight(sphere1);

    mesh::Sphere sphere2 = mesh::Sphere(12, 12, 1.3f);
    sphere2.SetMeshColors(colorB);
    math::mat4x4 translation2 = math::translation_matrix(0.0f, -1.0f, -3.0f);
    vertexProcessor->modelMatrix_ = translation2;
    rasterizer.RasterizeMeshPixelLight(sphere2);

    mesh::Sphere sphere3 = mesh::Sphere(12, 12, 1.3f);
    sphere3.SetMeshColors(colorG);
    math::mat4x4 translation3 = math::translation_matrix(2.0f, -1.0f, -3.0f);
    vertexProcessor->modelMatrix_ = translation3;
    rasterizer.RasterizeMeshPixelLight(sphere3);

	///////

    mesh::Sphere sphere4 = mesh::Sphere(12, 12, 1.3f);
    sphere4.SetMeshColors(colorT);
    math::mat4x4 translation4 = math::translation_matrix(-2.0f, 1.0f, -3.0f);
    vertexProcessor->modelMatrix_ = translation4;
    rasterizer.RasterizeMeshVertexLight(sphere4);

    mesh::Sphere sphere5 = mesh::Sphere(12, 12, 1.3f);
    sphere5.SetMeshColors(colorB);
    math::mat4x4 translation5 = math::translation_matrix(0.0f, 1.0f, -3.0f);
    vertexProcessor->modelMatrix_ = translation5;
    rasterizer.RasterizeMeshVertexLight(sphere5);

    mesh::Sphere sphere6 = mesh::Sphere(12, 12, 1.3f);
    sphere6.SetMeshColors(colorG);
    math::mat4x4 translation6 = math::translation_matrix(2.0f, 1.0f, -3.0f);
    vertexProcessor->modelMatrix_ = translation6;
    rasterizer.RasterizeMeshVertexLight(sphere6);

	colorBuffer.generateBMP("test.bmp");
	return 0;
}

