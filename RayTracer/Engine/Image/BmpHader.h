#pragma once

namespace RayTracer
{
struct BmpHeader
{
    long size_of_file;
    long reserve;
    long offset_of_pixle_data;
    long size_of_header;
    long width;
    long hight;
    short num_of_colour_plane;
    short num_of_bit_per_pix;
    long compression;
    long size_of_pix_data;
    long h_resolution;
    long v_resolution;
    long num_of_colour_in_palette;
    long important_colours;
} ;
}  // namespace RayTracer