#ifndef VOLUME_DATA_H
#define VOLUME_DATA_H

#include <string>
#include <vector>

struct vec3 {
    float x, y, z;
};

struct ivec3 {
    int x, y, z;
};

enum class Endianness {
    Little,
    Big,
};

enum class SampleType {
    UnsignedChar,
    UnsignedShort,
    Short,
    Float,
};

struct VolumeData {
    struct Info {
        std::string inf_file;
        std::string raw_file;
        Endianness endianness;
        SampleType sample_type;
        ivec3 resolution;
        vec3 voxel_size;
        std::string voxel_unit;
    };

    VolumeData::Info info;
    std::vector<float> data;
};

void read_inf_file(VolumeData& vd, const std::string& file);
void read_raw_file(VolumeData& vd, const std::string& file = "");

#endif
