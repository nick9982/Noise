#include "heightmap.hpp"
#include <iostream>

void HeightMap::generate(double rangeMultiplier, int offsX, int offsY)
{
    double **tempMap = new double*[x];
    for(int i = 0;i<x; i++)
        tempMap[i] = new double[y];

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
            float persistence = 0.6;
            tempMap[j][i] = perlin.octave2D(nx, ny, 20, persistence)
                            +perlin1.octave2D(nx, ny, 8, persistence);
            if(tempMap[j][i] > max)
                max = tempMap[j][i];
            if(tempMap[j][i] < min)
                min = tempMap[j][i];
        }
    }


    
    //place the data within a smaller window within the range [0, 65535] to remove blotches.
    double range = (max-min)*rangeMultiplier;
    double avg = 0;
    uint16_t max_val = 0, min_val = 65535;

    for(int i = 0; i < x; i++)
    {
        for(int j = 0; j < y; j++)
        {
            heightMap[i][j] = (uint16_t)((tempMap[i][j] + min * rangeMultiplier)/range*65535);
            if(heightMap[i][j] > 65535) std::cout << "there is a value that is wrapping around." << std::endl;
            int cnt = i*x+j+1;
            avg = (double)(avg * (cnt-1) + heightMap[i][j]) / cnt;
            if(heightMap[i][j] > max_val) max_val = heightMap[i][j];
            if(heightMap[i][j] < min_val) min_val = heightMap[i][j];
        }
    }

    //shift all of the data so the minimum value and maximum value are the same distance from min_int and max_int respectively
    int distanceMax = 65535 - max_val;
    int distanceMin = min_val;
    int offset = 0;
    if(distanceMin <  distanceMax)
        offset = (double)(distanceMax - distanceMin)/2;
    else if(distanceMin > distanceMax)
        offset = -(double)(distanceMin - distanceMax)/2;

    //Find the new minimum value and the new maximum value after shifting all of the data
    //Also find the average after shifting all of the data
    max_val = 0;
    min_val = 65535;
    avg = 0;
    for(int i = 0; i < x; i++)
    {
        for(int j = 0; j < y; j++)
        {
            heightMap[i][j] += offset;
            if(heightMap[i][j] > max_val)
                max_val = heightMap[i][j];
            if(heightMap[i][j] < min_val)
                min_val = heightMap[i][j];

            int cnt = i*x+j+1;
            avg = (double)(avg * (cnt-1) + heightMap[i][j]) / cnt;
        }
    }

    //I am going to move all of the data away from the average towards min int if less than average and towards max int if greater than average.
    //The further the data is from average, the further I am going to move it from average.
    //In the below code I am finding a constant that will allow the transformed data to get as close to min int and max int as possible without leaving the bounds
    double constant = 0;
    for(int i = 0; i < 255000; i++)
    {
        constant = i*0.01;
        if(max_val + (constant * (max_val-avg)) > 65535 || min_val - (constant * (avg-min_val)) < 0)
        {
            constant -= 0.01;
            break;
        }
    }

    //Moving the data away from avg towards either min_int or max_int
    for(int i = 0; i < x; i++)
    {
        for(int j = 0; j < y; j++)
        {
            uint16_t val = heightMap[i][j];
            if(val > avg)
                heightMap[i][j] += constant*(val-avg);
            else
                heightMap[i][j] -= constant*(avg-val);
            
            //Creating an inverted height map.
            invertedHeightMap[i][j] = 65535 - heightMap[i][j];
        }
    }
}
