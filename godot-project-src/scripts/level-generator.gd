extends Node2D


# Declare member variables here. Examples:
# var a = 2
# var b = "text"
export(Array, PackedScene) var jesus_room
export(Array, PackedScene) var luce_start_room
export(Array, PackedScene) var demon_intro_room
export(Array, PackedScene) var mary_intercession_room
export(Array, PackedScene) var demon_task_room
export(Array, PackedScene) var moving_platform_room
export(Array, PackedScene) var open_space_room
export(Array, PackedScene) var easy_room
export(Array, PackedScene) var medium_room
export(Array, PackedScene) var hard_room
export(Array, PackedScene) var end_room
export(Array, PackedScene) var blank_room
var height: int
var width: int
var level: Array


# Called when the node enters the scene tree for the first time.
func _ready():
	# Create dictionary of rooms and room ids
	var rooms_list: Array = [jesus_room, luce_start_room, demon_intro_room, mary_intercession_room, demon_task_room, moving_platform_room, open_space_room, easy_room, medium_room, hard_room, end_room, blank_room]
	var rooms_name: Array = ["jesus", "luce_start", "demon_intro", "mary_intercession", "demon_task", 'moving_platform', "open_space", "easy", "medium", "hard", "end", "blank"]
	var rooms: Dictionary
	var cnt = 0
	for i in range(len(rooms_list)):
		rooms[rooms_name[i]] = range(cnt, cnt + len(rooms_list[i]))
		cnt += len(rooms_list[i])
	# Create reversed dictionary of room id and rooms
	var reversed_rooms: Dictionary
	for key in rooms:
		for id in rooms[key]:
			reversed_rooms[id] = key
	# Seed random number generator
	randomize()
	# Get random height and width of level
	height = (randi() % 11) + 10
	width = (randi() % 11) + 10
	# Create blank level
	for _h in range(height):
		var temp_arr: Array = []
		for _w in range(width):
			temp_arr.append(rand_room(rooms["blank"]))
		level.append(temp_arr)
	# Create a randomized path through the level
	var idx_1: int = -1
	var idx_2: int = -1
	var begins: Array = []
	var ends: Array = []
	for h in range(0, height):
		if idx_1 == -1:
			idx_1 = randi() % width
		else:
			idx_1 = idx_2
		begins.append(idx_1)
		idx_2 = randi() % width
		while (h == height - 1 and abs(idx_1 - idx_2) < 6) or (h < height - 1 and abs(idx_1 - idx_2) < 2):
			idx_2 = randi() % width
		if idx_1 < idx_2:
			for w in range(idx_1, idx_2 + 1):
				level[h][w] = 99
		else:
			for w in range(idx_2, idx_1 + 1):
				level[h][w] = 99
		ends.append(idx_2)
	# Put in open spaces and moving platforms at ends of rows
	for e in range(len(ends) - 1):
		level[e][ends[e]] = rand_room(rooms["open_space"])
		level[e + 1][ends[e]] = rand_room(rooms["moving_platform"])
	# Put in the first five rooms
	var start = ends[height - 1]
	if start < begins[height - 1]:
		level[height - 1][start] = rand_room(rooms["jesus"])
		level[height - 1][start + 1] = rand_room(rooms["luce_start"])
		level[height - 1][start + 2] = rand_room(rooms["demon_intro"])
		level[height - 1][start + 3] = rand_room(rooms["mary_intercession"])
		level[height - 1][start + 4] = rooms["demon_task"][0]
	else:
		level[height - 1][start] = rand_room(rooms["jesus"])
		level[height - 1][start - 1] = rand_room(rooms["luce_start"])
		level[height - 1][start - 2] = rand_room(rooms["demon_intro"])
		level[height - 1][start - 3] = rand_room(rooms["mary_intercession"])
		level[height - 1][start - 4] = rooms["demon_task"][0]
	# Put in the end room
	level[0][begins[0]] = rand_room(rooms["end"])
	# Put in the demon task rooms
	for i in range(1, len(rooms["demon_task"])):
		var h: int = int(i * height / len(rooms['demon_task']))
		if begins[h] < ends[h]:
			var idx = randi() % (ends[h] - begins[h] - 1) + begins[h] + 1
			level[h][idx] = rooms["demon_task"][i]
		else:
			var idx = randi() % (begins[h] - ends[h] - 1) + ends[h] + 1
			level[h][idx] = rooms["demon_task"][i]
	# Fill in the rest with random rooms based on difficulty
	for h in height:
		for w in width:
			if level[h][w] == 99:
				if h >= 0 and h <= height / 3:
					var p: float = randf()
					if p <= 0.5:
						level[h][w] = rand_room(rooms["hard"])
					elif p <= 0.8:
						level[h][w] = rand_room(rooms["medium"])
					else:
						level[h][w] = rand_room(rooms["easy"])
				elif h >= 2 * height / 3:
					level[h][w] = rand_room(rooms["easy"])
				else:
					var p: float = randf()
					if p <= 0.7:
						level[h][w] = rand_room(rooms["medium"])
					else:
						level[h][w] = rand_room(rooms["easy"])
	# Now, instantiate the scenes based on the level generated
	# Debug
	var debug_string: String = ""
	for h in height:
		for w in width:
			if level[h][w] / 10 < 1:
				debug_string += "0" + str(level[h][w]) + " "
			else:
				debug_string += str(level[h][w]) + " "
		debug_string += " " + str(h) + "\n"
	print(debug_string)


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass


func rand_room(rooms: Array) -> int:
	return rooms[randi() % rooms.size()]
