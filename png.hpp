#include <cstdint>
#include <string>
#include <vector>
#include <lodepng.h>

    //Save heightmap to camera roll
    //    +filePath: is the path to the file including the desired file name.
    //    +heightMap: the heightMap
    //    +x: heightMap width
    //    +y: heightMap height
    //The plan is to normalize into a PNG of dimension x and y. We will save the image as a 16-bit grayscale png 
bool saveHeightMap(std::string filepath, uint16_t **heightMap, int x, int y)
{
    int idx = 0;
    unsigned char * png16 = new unsigned char[x * y * 2];
    for(int i = 0; i < x; i++)
    {
        for(int j = 0; j < y; j++)
        {
            png16[idx++] = static_cast<unsigned char>((heightMap[i][j] >> 8) & 0xFF);
            png16[idx++] = static_cast<unsigned char>(heightMap[i][j] & 0xFF);
        }
    }
    
    std::vector<unsigned char> data;
    unsigned error;
    if(error = lodepng::encode(data, png16, x, y, LCT_GREY, 16))
    {
        std::cerr << "Error encoding PNG file: " << lodepng_error_text(error) << std::endl;
        return 0;
    }

    if(error = lodepng::save_file(data, filepath))
    {
        std::cerr << "Error saving PNG file: " << lodepng_error_text(error) << std::endl;
        return 0;
    }
    return 1;
}

