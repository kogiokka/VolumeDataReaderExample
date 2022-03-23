#include "VolumeData.hpp"

#include <cassert>
#include <filesystem>
#include <toml.hpp>

namespace fs = std::filesystem;

void read_inf_file(VolumeData& vd, const std::string& file)
{
    toml::table tbl = toml::parse_file(file);
    auto const& resoNode = tbl["resolution"];
    auto const& voxelNode = tbl["voxel"];

    vd.info.inf_file = file;

    // Relative path to the inf file
    auto inf_parent_dir = fs::path(file).parent_path();
    auto raw_name = tbl["raw_file"].value_or(fs::path(file).filename().replace_extension(".raw").string());
    vd.info.raw_file = (inf_parent_dir / raw_name).string();

    vd.info.resolution.x = resoNode["x"].value_or<int>(0);
    vd.info.resolution.y = resoNode["y"].value_or<int>(0);
    vd.info.resolution.z = resoNode["z"].value_or<int>(0);

    vd.info.voxel_size.x = voxelNode["size"]["x"].value_or<float>(0.0f);
    vd.info.voxel_size.y = voxelNode["size"]["y"].value_or<float>(0.0f);
    vd.info.voxel_size.z = voxelNode["size"]["z"].value_or<float>(0.0f);

    const std::string endianness_str = voxelNode["endianness"].value_or("little");
    if (endianness_str == "big") {
        vd.info.endianness = Endianness::Big;
    } else {
        vd.info.endianness = Endianness::Little;
    }

    const std::string sample_type_str = voxelNode["sample_type"].value_or("");
    if (sample_type_str == "unsigned char") {
        vd.info.sample_type = SampleType::UnsignedChar;
    } else if (sample_type_str == "unsigned short") {
        vd.info.sample_type = SampleType::UnsignedShort;
    } else if (sample_type_str == "short") {
        vd.info.sample_type = SampleType::Short;
    } else if (sample_type_str == "float") {
        vd.info.sample_type = SampleType::Float;
    }

    // Assertions in Debug mode
    assert(vd.info.resolution.x > 0 && vd.info.resolution.y > 0 && vd.info.resolution.z > 0);
    assert(vd.info.voxel_size.x > 0.0f && vd.info.voxel_size.y > 0.0f && vd.info.voxel_size.z > 0.0f);
    assert(!sample_type_str.empty());
}

void read_raw_file(VolumeData& vd, const std::string& file)
{
    if (!file.empty()) {
        vd.info.raw_file = file;
    }

    std::ifstream raw_file(vd.info.raw_file);
    auto raw_file_size = fs::file_size(vd.info.raw_file); // file size in bytes

    switch (vd.info.sample_type) {
    case SampleType::UnsignedChar: {
        std::vector<unsigned char> buffer;
        buffer.resize(raw_file_size);
        // std::ifstream::read, see https://en.cppreference.com/w/cpp/io/basic_istream/read
        raw_file.read(reinterpret_cast<char*>(buffer.data()), raw_file_size);
        // std::vector::assign, see https://en.cppreference.com/w/cpp/container/vector/assign
        vd.data.assign(buffer.begin(), buffer.end());
    }
    case SampleType::UnsignedShort: {
        // TODO
    }
    case SampleType::Short: {
        // TODO
    }
    case SampleType::Float: {
        // TODO
    }
    }
}
