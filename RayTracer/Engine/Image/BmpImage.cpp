#include "BmpImage.h"
#include "BmpHader.h"
#include <fstream>

namespace RayTracer
{
BmpImage::BmpImage()
{
}
BmpImage::BmpImage(const vec2ui& size, uint8 channelCount)
{
    init(size, channelCount);
}
void BmpImage::init(const vec2ui& size, uint8 channelCount)
{
    size_ = size;
    channelCount_ = channelCount;
    data_.resize(size_.x * size_.y * channelCount);
}
void BmpImage::save(const std::string& filename) const
{
    const short BM = 0x4d42;
    BmpHeader header;
    auto dataSize                   = sizeof(uint8) * data_.size();

    header.size_of_file             = sizeof(header) + dataSize + sizeof(0x0000) * size_.y + 2;
    header.reserve                  = 0000;
    header.offset_of_pixle_data     = 54;
    header.size_of_header           = 40;
    header.width                    = size_.x;
    header.hight                    = size_.y;
    header.num_of_colour_plane      = 1;
    header.num_of_bit_per_pix       = 24;
    header.compression              = 0;
    header.size_of_pix_data         = dataSize + sizeof(0x0000) * size_.y;
    header.h_resolution             = 2835;
    header.v_resolution             = 2835;
    header.num_of_colour_in_palette = 0;
    header.important_colours        = 0;

    std::ofstream file;
    file.open(filename, std::ios::out | std::ios::trunc | std::ios::binary);
    file.write((char*)(&BM), 2);
    file.write((char*)(&header), sizeof(header));

    for (int n = 0; n != channelCount_ * size_.x * size_.y; n++)
    {
        file.write((char*)(&data_[n]), 1);
    }
    file.close();
}
void BmpImage::setPixel(const vec2ui& position, const vec3ui8& color)
{
    if (position.x >= size_.x || position.x < 0 || position.y >= size_.y || size_.y < 0)
    {
        return;
    }

    data_[3 * (position.x + position.y * size_.x)]     = color.z;  // B
    data_[3 * (position.x + position.y * size_.x) + 1] = color.y;  // G
    data_[3 * (position.x + position.y * size_.x) + 2] = color.x;  // R
}
const vec2ui& BmpImage::getSize() const
{
    return size_;
}
}  // namespace RayTracer
