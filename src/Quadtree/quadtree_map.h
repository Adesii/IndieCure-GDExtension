#pragma once

#include "godot_cpp/classes/ref_counted.hpp"
#include "godot_cpp/core/defs.hpp"
#include "godot_cpp/core/math.hpp"
#include "godot_cpp/variant/array.hpp"
#include "godot_cpp/variant/string_name.hpp"
#include "godot_cpp/variant/typed_array.hpp"
#include "godot_cpp/variant/variant.hpp"
#include "godot_cpp/variant/vector2.hpp"
#include "godot_cpp/variant/vector2i.hpp"
#include <cstddef>
#include <cstdint>
#include <functional>
#include <unordered_map>


using namespace godot;

namespace cgb {
    inline void hash_combine(std::size_t& seed) { }

    template <typename T, typename... Rest>
    inline void hash_combine(std::size_t& seed, const T& v, Rest... rest) {
        std::hash<T> hasher;
        seed ^= hasher(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        hash_combine(seed, rest...);
    }
}



template <>
struct std::hash<Vector2i>
{
    
    std::size_t operator()(const Vector2i& k) const{
        size_t h = 0;
        cgb::hash_combine(h,hash<int32_t>()._Do_hash(k.x),hash<int32_t>()._Do_hash(k.y));
        return h;
    }
};


class QuadtreeMap : public RefCounted{
    GDCLASS(QuadtreeMap,RefCounted)

protected:
	static void _bind_methods();

    int map_cell_size = 16;
    int map_size_per_cell = 16;

    std::pmr::unordered_map<int32_t, Array> map_dictionary;

    int32_t get_unique_key_for_position(Vector2 position){
        return int32_t(position.x / map_cell_size) + int32_t(position.y / map_cell_size) * map_size_per_cell;
    }

public:
    QuadtreeMap();
    ~QuadtreeMap() override = default;


    void calculate_avoidance(const Array all_units,const StringName& positionmethodname,const StringName& positionKeyName,const StringName& avoidancevelkey,const StringName& velocity,const float radius);
    void free_unit(const Variant& unit, const int32_t key);
};
