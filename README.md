# Height map perlin noise to PNG

## Build instructions:
```bash
mkdir Build && cmake -S . -B Build && cd Build && make
```
## Examples
Generating one height map and saving it as an image:
```cpp
HeightMap heightMap(512, 512);
heightMap.generate(5, 0, 0);
uint16_t **map = heightMap.getHeightMap();
saveHeightMap("/your/target/directory/filename.png", map, 512, 512);
```

Generating a grid of 5x5 chunks:
```cpp
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
        uint16_t** tmpHm = chunks.getHeightMap();
        for(int r = 0; r < 512; r++)
        {
            for(int x = 0; x < 512; x++)
            {
                chnks[i][j][r][x] = tmpHm[r][x];
            }
        }
    }
}
```

### Perlin Noise
Using Reputeless header only perlin noise siv::PerlinNoise
https://github.com/Reputeless/PerlinNoise
