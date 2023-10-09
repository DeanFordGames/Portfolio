cmake_minimum_required(VERSION 3.0)
project(RAYTRACER)

include_directories(raytracer
	src
	contrib/windows-cl-amd64/include
)

link_directories(raytracer
	${PROJECT_SOURCE_DIR}/contrib/windows-cl-amd64/lib
)

add_executable(raytracer
	src/raytracer/main.cpp

	src/raytracer/Camera.cpp
	src/raytracer/Camera.h

	src/raytracer/MCG_GFX_Lib.cpp
	src/raytracer/MCG_GFX_Lib.h

	src/raytracer/Ray.cpp
	src/raytracer/Ray.h

	src/raytracer/Sphere.cpp
	src/raytracer/Sphere.h

	src/raytracer/Tracer.cpp
	src/raytracer/Tracer.h

	src/raytracer/Light.cpp
	src/raytracer/Light.h

	src/raytracer/ObjectHit.cpp
	src/raytracer/ObjectHit.h
)

target_link_libraries(raytracer SDL2 SDL2main SDL2test)