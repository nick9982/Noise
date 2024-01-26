#include "heightmap.hpp"
#include <iostream>

void HeightMap::generate(double persistence, int offsX, int offsY)
{
    float **tempMap = new float*[x];
    for(int i = 0;i<x; i++)
        tempMap[i] = new float[y];

    const siv::PerlinNoise::seed_type seed = time(NULL);
    const siv::PerlinNoise perlin{ seed };
    const siv::PerlinNoise perlin1{ seed+1 };

    double max = DBL_MIN, min = DBL_MAX;

    //generate the initial noise map
    for(int i = 0; i < y; i++)
    {
        for(int j = 0; j < x; j++)
        {
            double nx = (double)j/x+offsX, ny = (double)i/y+offsY;
            tempMap[j][i] = perlin.octave2D(nx, ny, 20, persistence)
                            +perlin1.octave2D(nx, ny, 8, persistence);
            if(tempMap[j][i] < min)
                min = tempMap[j][i];
            if(tempMap[j][i] > max)
                max = tempMap[j][i];
        }
    }


    
    float range = (max-min);
    for(int i = 0; i < x; i++)
    {
        for(int j = 0; j < y; j++)
        {
            heightMap[i][j] = (uint16_t)((tempMap[i][j] - min)/range*65535);
            invertedHeightMap[i][j] = 65535 - heightMap[i][j];
        }
    }
}
