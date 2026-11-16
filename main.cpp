#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>
using namespace std;

int main() {
    sf::Image image;

    if (!image.loadFromFile("image.jpg")) 
    {
        cerr << "Failed to load image!" << std::endl;
        return -1;
    }

    sf::Vector2u originalSize = image.getSize();
    int origWidth = originalSize.x;
    int origHeight = originalSize.y;
    
    int targetWidth = 500;
    int targetHeight = static_cast<int>(targetWidth * (static_cast<float>(origHeight) / origWidth) * 0.5f);

    vector<vector<char>> asciiGrid(targetHeight, vector<char>(targetWidth));
    string palette = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";
    int paletteLength = palette.length();

    // Calculate scale ratios for downscaling
    float xRatio = static_cast<float>(origWidth) / targetWidth;
    float yRatio = static_cast<float>(origHeight) / targetHeight;

    for (int targetY = 0; targetY < targetHeight; ++targetY)
    {
        for (int targetX = 0; targetX < targetWidth; ++targetX)
        {
            int startX = static_cast<int>(targetX * xRatio);
            int startY = static_cast<int>(targetY * yRatio);
            int endX = static_cast<int>((targetX + 1) * xRatio);
            int endY = static_cast<int>((targetY + 1) * yRatio);

            long long totalGray = 0;
            int pixelCount = 0;

            for (int y = startY; y < endY && y < origHeight; ++y) {
                for (int x = startX; x < endX && x < origWidth; ++x) {
                    sf::Color color = image.getPixel(sf::Vector2u(x, y));
                    unsigned char gray = static_cast<unsigned char>(0.299f * color.r + 0.587f * color.g + 0.114f * color.b);
                    totalGray += gray;
                    pixelCount++;
                }
            }

            unsigned char avgGray = (pixelCount > 0) ? static_cast<unsigned char>(totalGray / pixelCount) : 0;
            int paletteIndex = static_cast<int>((static_cast<float>(avgGray) / 255.0f) * (paletteLength - 1));
            asciiGrid[targetY][targetX] = palette[paletteIndex];
        }
    }

    ofstream outFile("output.txt");
    
    if (outFile.is_open()) {
        for (int y = 0; y < targetHeight; ++y) 
        {
            for (int x = 0; x < targetWidth; ++x) 
                outFile << asciiGrid[y][x]; 

            outFile << '\n'; 
        }

        outFile.close();
        cout << "ASCII art successfully saved to output.txt!" << endl;
    } 
    
    else 
        cerr << "Error opening file for writing!" << endl;
}