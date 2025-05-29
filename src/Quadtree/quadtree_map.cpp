#include "quadtree_map.h"
#include "godot_cpp/classes/control.hpp"
#include "godot_cpp/classes/ref_counted.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/templates/vector.hpp"
#include "godot_cpp/variant/utility_functions.hpp"
#include "godot_cpp/variant/variant.hpp"
#include "godot_cpp/variant/vector2.hpp"
#include "godot_cpp/variant/vector2i.hpp"
#include <cstddef>
#include <cstdint>


void QuadtreeMap::_bind_methods(){
    godot::ClassDB::bind_method(D_METHOD("calculate_avoidance", "all_units","positioname","positionKeyName","avoidancevelkey","velocity","radius"), &QuadtreeMap::calculate_avoidance);
    godot::ClassDB::bind_method(D_METHOD("free_unit", "unit","positionkey"), &QuadtreeMap::free_unit);
}

void QuadtreeMap::calculate_avoidance(const Array all_units,const StringName& positioname,const StringName& positionKeyName,const StringName& avoidancevelkey,const StringName& velocitykey,const float radius){
    //godot::UtilityFunctions::print(all_units.size(),"----- calc avoidance");
    for (size_t i = 0; i < all_units.size(); i++) {
        auto unit = all_units[i];
        Vector2 global_position = unit.get(positioname);
        Vector2 velocity = unit.get(velocitykey);
        auto position =  get_unique_key_for_position(global_position+velocity*radius);
        auto oldKey = int32_t(unit.get(positionKeyName));
        //godot::UtilityFunctions::print("unit-cpp: ",unit,global_position,position,oldKey);
        unit.set(avoidancevelkey, -velocity *0.99);
        if (oldKey != position) {
            (unit).set(positionKeyName,position);
            if (map_dictionary[position].size() <= map_size_per_cell) {
                if(map_dictionary[oldKey].has(unit))
                {
                    map_dictionary[oldKey].erase(unit);
                }
                map_dictionary[position].append(unit);
            }else{
                
                continue;
            }
        }
        auto otherUnits = map_dictionary[position];
        Vector2 avoidvel = Vector2();
        float radiuss = 32 * 32;
        int32_t amount = 0;
        for (size_t u = 0; u < otherUnits.size(); u++) {
            auto other = otherUnits[u];
            if(other == unit){
                continue;
            }
            auto otherposition = other.get(positioname);
            auto distance = global_position.distance_squared_to(otherposition);
            if (distance < radiuss) {
                auto direction = (global_position - otherposition).normalized();
                avoidvel += direction;
                amount++;
            }
        }
        if(amount > 0)
            avoidvel /= amount;
        unit.set(avoidancevelkey,avoidvel);
        //godot::UtilityFunctions::print("unit-cpp: ",unit,avoidvel);
        
    }
}

void QuadtreeMap::free_unit(const Variant& unit, const int32_t key){
    map_dictionary[key].erase(unit);
}

QuadtreeMap::QuadtreeMap(){
    map_dictionary = std::pmr::unordered_map<int32_t, Array>();
}
