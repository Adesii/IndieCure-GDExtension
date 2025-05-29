#pragma once

#include "godot_cpp/classes/ref_counted.hpp"
#include "godot_cpp/variant/array.hpp"
#include "godot_cpp/variant/string_name.hpp"
#include "godot_cpp/variant/typed_array.hpp"
#include "godot_cpp/variant/vector2.hpp"
#include <unordered_map>


using namespace godot;

class QuadObject : public RefCounted{
    GDCLASS(QuadObject,RefCounted)

public:
    QuadObject() = default;
    ~QuadObject() override = default;
    
    int keypos = 0;
    Vector2 avoidance_vel = Vector2();

};