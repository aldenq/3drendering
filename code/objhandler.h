/**
 * @file objhandler.h
 * @author Alden Quigley (aldenaquigley@gmail.com)
 * @brief code for handeling .obj files
 * @version 0.1
 * @date 2022-12-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include "geometry.h"
#include "vectors.h"
/**
 * @brief loades and parses a .obj file
 * 
 * @param filepath path to .obj file
 * @return VertexBuffer* vertex buffer for that obj
 */
VertexBuffer *loadFromOBJ(char *filepath);
