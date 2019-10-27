#include <SFML/Graphics.hpp>
#include "main.hpp"

int createBackground(VertexArray& rVA, IntRect backgroundBoundaries)
{
    
    // How big is each tile/texture
    const int TILE_SIZE = 62;
    const int TILE_TYPES = 3;
    const int VERTS_IN_QUAD = 4;
    
    int worldWidth = backgroundBoundaries.width / TILE_SIZE;
    int worldHeight = backgroundBoundaries.height / TILE_SIZE;
    
    // Using Quads
    rVA.setPrimitiveType(Quads);
    
    // Set the size of the vertex array
    rVA.resize(worldWidth * worldHeight * VERTS_IN_QUAD);
    

    int currentVertex = 0;
    
    //New Rand for random background
    srand((int)time(0));
    
    for (int w = 0; w < worldWidth; w++)
    {
        for (int h = 0; h < worldHeight; h++)
        {
            // Vertex positioning
            
            rVA[currentVertex + 0].position = Vector2f(w * TILE_SIZE, h * TILE_SIZE);
            rVA[currentVertex + 1].position = Vector2f((w * TILE_SIZE) + TILE_SIZE, h * TILE_SIZE);
            rVA[currentVertex + 2].position = Vector2f((w * TILE_SIZE) + TILE_SIZE, (h * TILE_SIZE) + TILE_SIZE);
            rVA[currentVertex + 3].position = Vector2f((w * TILE_SIZE), (h * TILE_SIZE) + TILE_SIZE);
            
            {
                // Select random texture
                
                int mOrG = (rand() % TILE_TYPES);
                int verticalOffset = mOrG * TILE_SIZE;
                
                rVA[currentVertex + 0].texCoords = Vector2f(0, 0 + verticalOffset);
                rVA[currentVertex + 1].texCoords = Vector2f(TILE_SIZE, 0 + verticalOffset);
                rVA[currentVertex + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);
                rVA[currentVertex + 3].texCoords = Vector2f(0, TILE_SIZE + verticalOffset);
            }
            
            
            currentVertex = currentVertex + VERTS_IN_QUAD;
        }
    }
    
    return TILE_SIZE;
}
