class_name Theotokos
extends Area2D


# Enums
enum States {ROSARY, STILL}


# Declare member variables here. Examples:
# var a = 2
# var b = "text"
onready var anim: AnimatedSprite = $AnimatedSprite
var has_rosary: bool = true
var state = States.ROSARY

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	# State logic
	if state == States.ROSARY:
		anim.play("rosary")
	elif state == States.STILL:
		anim.play("still")
	else:
		pass
	# Transition logic
	if not has_rosary:
		state = States.STILL


func _on_Theotokos_body_entered(body):
	if body.name == "Luce":
		var chara := body as Luce
		chara.rosary_power = true
		has_rosary = false
