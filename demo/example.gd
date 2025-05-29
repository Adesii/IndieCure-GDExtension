extends Node


func _ready() -> void:
	var map = QuadtreeMap.new()
	var units = []
	units.append(testunit.get_random_unit())
	units.append(testunit.get_random_unit())
	units.append(testunit.get_random_unit())
	units.append(testunit.get_random_unit())
	units.append(testunit.get_random_unit())
	units.append(testunit.get_random_unit())
	units.append(testunit.get_random_unit())
	units.append(testunit.get_random_unit())
	units.append(testunit.get_random_unit())
	units.append(testunit.get_random_unit())
	units.append(testunit.get_random_unit())
	units.append(testunit.get_random_unit())
	map.calculate_avoidance(units,"global_position","key","avoidance_vector",5)
	map.calculate_avoidance(units,"global_position","key","avoidance_vector",5)
	map.calculate_avoidance(units,"global_position","key","avoidance_vector",5)
	map.calculate_avoidance(units,"global_position","key","avoidance_vector",5)
	print("--------------")
	for unit in units:
		print("unit: -",unit.global_position,"- ",unit.key,"- ",unit.avoidance_vector)

	
