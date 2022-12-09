/**
 * @file vectors.h
 * @author Alden Quigley (aldenaquigley@gmail.com)
 * @brief describes a bunch of useful vectors
 * @version 0.1
 * @date 2022-12-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */



#pragma once

/**
 * @brief vector composed of 3 single precision floats
 * 
 */
typedef struct __attribute__((packed)) Vect3f{
    float x;
    float y;
    float z;
} Vect3f;

/**
 * @brief vector composed of 3 32 bit ints
 * 
 *  
 */
typedef struct __attribute__((packed)) Vect3i{
    int x;
    int y;
    int z;
} Vect3i;

/**
 * @brief vector composed of 3 chars
 * 
 */
typedef struct __attribute__((packed)) Vect3c{
    char x;
    char y;
    char z;
} Vect3c;
