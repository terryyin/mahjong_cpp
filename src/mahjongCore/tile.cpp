#include "tile.h"

struct tile_face_t {
	Tile tile;
	const char * tile_face_;
};

static tile_face_t tile_faces[] = {
		{C(1), "C(1)"},
		{C(2), "C(2)"},
		{C(3), "C(3)"},
		{C(4), "C(4)"},
		{C(5), "C(5)"},
		{C(6), "C(6)"},
		{C(7), "C(7)"},
		{C(8), "C(8)"},
		{C(9), "C(9)"},
		{R(1), "R(1)"},
		{R(2), "R(2)"},
		{R(3), "R(3)"},
		{R(4), "R(4)"},
		{R(5), "R(5)"},
		{R(6), "R(6)"},
		{R(7), "R(7)"},
		{R(8), "R(8)"},
		{R(9), "R(9)"},
		{R(1), "R(1)"},
		{R(2), "R(2)"},
		{R(3), "R(3)"},
		{R(4), "R(4)"},
		{R(5), "R(5)"},
		{R(6), "R(6)"},
		{R(7), "R(7)"},
		{R(8), "R(8)"},
		{R(9), "R(9)"},
		{MJ_EAST,"MJ_EAST"},
		{MJ_SOUTH,"MJ_SOUTH"},
		{MJ_WEST,"MJ_WEST"},
		{MJ_NORTH,"MJ_NORTH"},
		{MJ_ZHONG,"MJ_ZHONG"},
		{MJ_FA,"MJ_FA"},
		{MJ_BAI,"MJ_BAI"},
};

static const int tile_face_count = sizeof(tile_faces) / sizeof(tile_faces[0]);
Tile::operator const char *() const {
	for (int i = 0; i < tile_face_count; i++)
		if (tile_faces[i].tile == *this)
			return tile_faces[i].tile_face_;
	return "undef";
}

