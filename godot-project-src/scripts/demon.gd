class_name Demon
extends KinematicBody2D


# Enums
enum States {STILL, CHASE, EVADE, DIE, RESPAWN}


# Declare member variables here. Examples:
# var a = 2
# var b = "text"
export var jump: float = 500.0
export var gravity: float = 600.0
export var speed: float = 150.0
export var danger_zone: float = 500.0
onready var anim: AnimatedSprite = $AnimatedSprite
onready var luce: Luce = get_parent().get_parent().get_node('Luce')
onready var timer: Timer = $Timer
onready var coll1: CollisionShape2D = $CollisionShape2D
onready var hitbox: Area2D = $Area2D
onready var coll2: CollisionShape2D = $Area2D/CollisionShape2D
var velocity: Vector2 = Vector2(0, 0)
var state = States.STILL
var dying: bool = false
var respawn: bool = false


# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	# Calculate distance between Luce and demon
	var distance: float = luce.position.x - position.x
	# State logic
	if state == States.STILL:
		velocity.x = 0
		velocity.y = 0
		anim.play("still")
	elif state == States.CHASE:
		anim.play("move")
		if distance < 0.0:
			velocity.x = -speed
		else:
			velocity.x = speed
	elif state == States.EVADE:
		anim.play("move")
		if distance < 0.0:
			velocity.x = speed
		else:
			velocity.x = -speed
	elif state == States.DIE:
		hide()
		coll1.disabled = true
		hitbox.hide()
		coll2.disabled = true
		if dying:
			timer.start()
			dying = false
	elif state == States.RESPAWN:
		show()
		coll1.disabled = false
		hitbox.show()
		coll2.disabled = false
		respawn = false
	else:
		pass
	# Move logic
	velocity = move_and_slide(velocity, Vector2.UP)
	# Transition logic
	if dying:
		state = States.DIE
	elif respawn:
		state = States.RESPAWN
	elif abs(distance) <= danger_zone:
		if luce.rosary_power:
			state = States.EVADE
		else:
			state = States.CHASE
	else:
		state = States.STILL


func _on_Area2D_body_entered(body):
	if body.name == "Luce":
		dying = true


func _on_Timer_timeout():
	timer.stop()
	respawn = true
