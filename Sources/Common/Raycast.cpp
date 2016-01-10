#include "Raycast.h"
#include <cmath>
#include "Graphics/Color.h"
#include "GameMap.h"
using namespace Common;

glm::ivec2 Raycast::chunkToUpdate = glm::ivec2(0, 0);
Common::GameMap* Raycast::world = nullptr;

float mod(float value, float modulus) // So temporary
{
	//return value % modulus;
	//return fmod(value, modulus);
	return fmod((fmod(value, modulus) + modulus), modulus);
}
bool callback(int xCopy, int yCopy, int zCopy,
	glm::ivec3 face, glm::vec3 direction, bool active)
{
	int cx = (int)floor(xCopy / 16);
	int cy = (int)floor(zCopy / 16);
	int bx = (int)mod(xCopy, 16);
	int by = (int)mod(yCopy, 128);
	int bz = (int)mod(zCopy, 16);

	// bx = xCopy % 16;
	// by = yCopy % 16;
	// bz = zCopy % 16;

	if ((bx > -1 && bx < 16) && (by > -1 && by < 128) && (bz > -1 && bz < 16))
	{
		if (Raycast::world->GetChunk(cx, cy).GetBlock(bx, by, bz).Active)
		{
			if (active)
			{
				xCopy += face.x;
				yCopy += face.y;
				zCopy += face.z;
			}
			cx = (int)floor(xCopy / 16);
			cy = (int)floor(zCopy / 16);
			bx = (int)mod(xCopy, 16);
			by = (int)mod(yCopy, 128);
			bz = (int)mod(zCopy, 16);

			if (!active)
			{
				Raycast::world->GetChunk(cx, cy).GetBlock(bx, by, bz).Active = false;
			}
			if (active)
			{
				//if ((bx + (int)face.x > -1 && bx + (int)face.x < 16) && (by + (int)face.y > -1 && by + (int)face.y < 128) && (bz + (int)face.z > -1 && bz + (int)face.z < 16))
				//{
				//	world->GetChunk(cx, cy).GetBlock(bx + (int)face.x, by + (int)face.y, bz + (int)face.z).Active = true;
				//	world->GetChunk(cx, cy).GetBlock(bx + (int)face.x, by + (int)face.y, bz + (int)face.z).Color = Color(1, 1, 1);
				//}


				if ((bx > -1 && bx < 16) && (by > -1 && by < 128) && (bz > -1 && bz < 16))
				{
					Raycast::world->GetChunk(cx, cy).GetBlock(bx, by, bz).Active = true;
					Raycast::world->GetChunk(cx, cy).GetBlock(bx, by, bz).Color = Color(255, 255, 255);
				}
			}

			Raycast::chunkToUpdate = glm::ivec2(cx, cy);

			return true;
		}
	}
	return false;
}
static float intbound(float s, float ds)
{
	if (ds < 0)
		return intbound(-s, -ds);

	s = mod(s, 1);
	return (1 - s) / ds;

}
static int signum(float x)
{
	return x > 0 ? 1 : x < 0 ? -1 : 0;
}
//public static void DrawACube(glm::vec3 pos)
//{
//    GL.Begin(BeginMode.Quads);

//    GL.Vertex3(new glm::vec3(0.5f, 0.0f, 0.0f) + pos);
//    GL.Vertex3(new glm::vec3(0.5f, 0.0f, 0.0f) + pos);
//    GL.Vertex3(new glm::vec3(0.5f, 0.5f, 0.0f) + pos);
//    GL.Vertex3(new glm::vec3(0.0f, 0.5f, 0.0f) + pos);

//    GL.Vertex3(new glm::vec3(0.0f, 0.0f, -0.5f) + pos);
//    GL.Vertex3(new glm::vec3(0.5f, 0.0f, -0.5f) + pos);
//    GL.Vertex3(new glm::vec3(0.5f, 0.5f, -0.5f) + pos);
//    GL.Vertex3(new glm::vec3(0.0f, 0.5f, -0.5f) + pos);

//    GL.Vertex3(new glm::vec3(0.5f, 0.0f, 0.0f) + pos);
//    GL.Vertex3(new glm::vec3(0.5f, 0.0f, -0.5f) + pos);
//    GL.Vertex3(new glm::vec3(0.5f, 0.5f, -0.5f) + pos);
//    GL.Vertex3(new glm::vec3(0.5f, 0.5f, 0.0f) + pos);

//    GL.Vertex3(new glm::vec3(0.0f, 0.0f, 0.0f) + pos);
//    GL.Vertex3(new glm::vec3(0.0f, 0.0f, -0.5f) + pos);
//    GL.Vertex3(new glm::vec3(0.0f, 0.5f, -0.5f) + pos);
//    GL.Vertex3(new glm::vec3(0.0f, 0.5f, 0.0f) + pos);

//    GL.Vertex3(new glm::vec3(0.0f, 0.5f, 0.0f) + pos);
//    GL.Vertex3(new glm::vec3(0.5f, 0.5f, 0.0f) + pos);
//    GL.Vertex3(new glm::vec3(0.5f, 0.5f, -0.5f) + pos);
//    GL.Vertex3(new glm::vec3(0.0f, 0.5f, -0.5f) + pos);

//    GL.Vertex3(new glm::vec3(0.0f, 0.0f, 0.0f) + pos);
//    GL.Vertex3(new glm::vec3(0.5f, 0.0f, 0.0f) + pos);
//    GL.Vertex3(new glm::vec3(0.5f, 0.0f, -0.5f) + pos);
//    GL.Vertex3(new glm::vec3(0.0f, 0.0f, -0.5f) + pos);

//    GL.End();
//}
void Raycast::RaycastBlock(glm::vec3 direction, float radius, bool active, glm::vec3 cam, Common::GameMap* world)
{
	Raycast::world = world;
	Raycast::chunkToUpdate = glm::ivec2(0, 0);
	glm::vec3 origin(0, 0, 0);

	int x = (int)floor(cam.x);
	int y = (int)floor(cam.y);
	int z = (int)floor(cam.z);

	int wx = 256;
	int wy = 256;
	int wz = 256; // WORLD BOUNDS

	float dx = direction.x;
	float dy = direction.y;
	float dz = direction.z;

	int stepx = signum(dx);
	int stepy = signum(dy);
	int stepz = signum(dz);

	float tMaxx = intbound(cam.x, dx);
	float tMaxy = intbound(cam.y, dy);
	float tMaxz = intbound(cam.z, dz);

	float tDeltax = stepx / dx;
	float tDeltay = stepy / dy;
	float tDeltaz = stepz / dz;

	glm::ivec3 face(0, 0, 0);

	// Avoids an infinite loop.
	if (dx == 0 && dy == 0 && dz == 0)
		return;

	// Rescale from units of 1 cube-edge to units of 'direction' so we can
	// compare with 't'.
	radius /= sqrtf(dx * dx + dy * dy + dz * dz);

	while (/* ray has not gone past bounds of world */
		(stepx > 0 ? x < wx : x >= 0) &&
		(stepy > 0 ? y < wy : y >= 0) &&
		(stepz > 0 ? z < wz : z >= 0))
	{

		// Invoke the callback, unless we are not *yet* within the bounds of the
		// world.
		if (!(x < 0 || y < 0 || z < 0 || x >= wx || y >= wy || z >= wz))
		{
			if (callback(x, y, z, face, direction, active))
				break;
		}

		if (tMaxx < tMaxy)
		{
			if (tMaxx < tMaxz)
			{
				if (tMaxx > radius)
					break;
				// Update which cube we are now in.
				x += stepx;
				// Adjust tMaxx to the next x-oriented boundary crossing.
				tMaxx += tDeltax;
				// Record the normal vector of the cube face we entered.
				face.x = -stepx;
				face.y = 0;
				face.z = 0;
			}
			else
			{
				if (tMaxz > radius)
					break;
				z += stepz;
				tMaxz += tDeltaz;
				face.x = 0;
				face.y = 0;
				face.z = -stepz;
			}
		}
		else
		{
			if (tMaxy < tMaxz)
			{
				if (tMaxy > radius)
					break;
				y += stepy;
				tMaxy += tDeltay;
				face.x = 0;
				face.y = -stepy;
				face.z = 0;
			}
			else
			{
				// Identical to the second case, repeated for simplicity in
				// the conditionals.
				if (tMaxz > radius)
					break;
				z += stepz;
				tMaxz += tDeltaz;
				face.x = 0;
				face.y = 0;
				face.z = -stepz;
			}
		}
	}
}

