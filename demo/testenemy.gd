extends RefCounted
class_name testunit

var global_position: Vector2
var key:int
var avoidance_vector:Vector2

static func get_random_unit():
    var unit = testunit.new()
    unit.global_position = Vector2(randf_range(-10,10),randf_range(-10,10))
    return unit