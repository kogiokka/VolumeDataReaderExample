#include "VolumeData.hpp"

#include <iostream>

std::string endiannessString(Endianness e)
{
    switch (e) {
    case Endianness::Big:
        return "big-endian";
    case Endianness::Little:
        return "little-endian";
    default:
        return "";
    }
}

std::string sampleTypeString(SampleType t)
{
    switch (t) {
    case SampleType::UnsignedChar:
        return "unsigned char";
    case SampleType::UnsignedShort:
        return "unsigned short";
    case SampleType::Short:
        return "short";
    case SampleType::Float:
        return "float";
    default:
        return "";
    }
}

int main(int argc, char** argv)
{
    using namespace std;

    VolumeData vd;

    read_inf_file(vd, "res/engine.toml");

    cout << "Info file: " << vd.info.inf_file << endl;
    cout << "Raw file: " << vd.info.raw_file << endl;
    cout << "Resolution (x, y, z): " << vd.info.resolution.x << ", " << vd.info.resolution.y << ", "
         << vd.info.resolution.z << endl;
    cout << "Size (x, y, z): " << vd.info.voxel_size.x << ", " << vd.info.voxel_size.y << ", " << vd.info.voxel_size.z
         << endl;
    cout << "Sample Type: " << sampleTypeString(vd.info.sample_type) << endl;
    cout << "Endianness: " << endiannessString(vd.info.endianness) << endl;

    read_raw_file(vd);

    cout << "Size of Raw Data: " << vd.data.size() << " voxels" << endl;
    cout << "engine[80]: " << vd.data[80] << endl;

    return 0;
}
