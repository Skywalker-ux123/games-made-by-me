#include "colors.h"
#include <vector>

const Color BG_DARK = { 8, 10, 18, 255 };      
const Color NEON_CYAN = { 0, 255, 255, 255 };
const Color NEON_PURPLE = { 180, 0, 255, 255 };
const Color NEON_RED = { 255, 40, 70, 255 };
const Color NEON_YELLOW = { 255, 240, 0, 255 };
const Color NEON_GREEN = { 0, 255, 140, 255 };
const Color NEON_BLUE = { 0, 120, 255, 255 };
const Color NEON_ORANGE = { 255, 120, 0, 255 };

std::vector<Color> GetCellColours(){
    return {BG_DARK,NEON_BLUE,NEON_GREEN,NEON_RED,NEON_YELLOW,NEON_PURPLE,NEON_CYAN,NEON_ORANGE};
}