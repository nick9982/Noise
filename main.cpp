#include "heightmap.hpp"
#include "png.hpp"

int main(int argc, char *argv[])
{
    HeightMap heightMap(512, 512);
    heightMap.generate(0.7, 0, 0);

    //Save height map example:
    //saveHeightMap("/your/target/directory/fileName.png", heightMap.getHeightMap(), 512, 512);

    //Generating multiple chunks:

    //This will create a 9x9 assortment of chunks stored in the chnks array
    HeightMap chunks(512, 512, 12345);
    uint16_t**** chnks = new uint16_t***[9];
    for(int i = 0; i < 9; i++)
    {
        chnks[i] = new uint16_t**[9];
        for(int j = 0; j < 9; j++)
        {
            chnks[i][j] = new uint16_t*[512];
            for(int r = 0; r < 512; r++)
                chnks[i][j][r] = new uint16_t[512];
        }
    }

    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            chunks.generate(5, i, j);
            for(int r = 0; r < 512; r++)
            {
                for(int x = 0; x < 512; x++)
                {
                    chnks[i][j][r][x] = chunks.getHeightMap()[r][x];
                }
            }
        }
    }


    //How to save maps of chunks.
    /*system("mkdir chunks"); //Or create the directory yourself before running.
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            std::string path = "chunks/coord";
            path.append(std::to_string(i));
            path.append(std::to_string(j));
            path.append(".png");
            saveHeightMap(path, chnks[i][j], 512, 512);
        }
    }*/
}
