#include <string>
#include <cstdint>
#include <iostream>
#include <cmath>
#include <vector>
#include <float.h>
#include "PerlinNoise.hpp"
#include <bits/stdc++.h>

class HeightMap
{
    private:
        uint16_t ** heightMap;
        uint16_t ** invertedHeightMap;
        int x, y, seed;

    public:
        //   +x: represent width of resulting height HeightMap
        //   +y: represent height of resulting HeightMap
        //   +seed: represent seed used to generate map (overloaded)
        HeightMap(uint16_t x, uint16_t y, int seed = time(NULL))
        {
            this->seed = seed;
            heightMap = new uint16_t*[x];
            invertedHeightMap = new uint16_t*[x];
            for(int i = 0; i < x; i++)
            {
                heightMap[i] = new uint16_t[y];
                invertedHeightMap[i] = new uint16_t[y];
            }


            this->x = x;
            this->y = y;
        }

        //Generates random height map
        //   +persistence: the persistence for noise
        //   +offsX: the number of chunks in X direction to offset the perlin noise generator by
        //   +offsY: the number of chunks in Y direction to offset the perlin noise generator by
        void generate(double persistence, int offsX, int offsY);

        uint16_t** getHeightMap()
        {
            return heightMap;
        }
        uint16_t** getInvertedHeightMap()
        {
            return invertedHeightMap;
        }

};
