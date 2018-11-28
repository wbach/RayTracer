#pragma once
#include <stdint.h>

namespace RayTracer
{
struct BmpHeader
{
    int32_t size_of_file;
    int32_t reserve;
    int32_t offset_of_pixle_data;
    int32_t size_of_header;
    int32_t width;
    int32_t hight;
    int16_t num_of_colour_plane;
    int16_t num_of_bit_per_pix;
    int32_t compression;
    int32_t size_of_pix_data;
    int32_t h_resolution;
    int32_t v_resolution;
    int32_t num_of_colour_in_palette;
    int32_t important_colours;
} ;
}  // namespace RayTracer
