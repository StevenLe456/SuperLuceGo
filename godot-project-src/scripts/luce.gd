class_name Luce
extends KinematicBody2D


# Enums
enum States {STILL, MOVE, JUMPING, IN_AIR}
enum SubStates {LEFT, RIGHT}


# Declare member variables here. Examples:
# var a = 2
# var b = "text"
export var jump: float = 500.0
export var gravity: float = 600.0
export var speed: float = 200.0
onready var anim: AnimatedSprite = $AnimatedSprite
var rosary_power: bool = false
var velocity: Vector2 = Vector2(0, 0)
var state = States.STILL
var substate = SubStates.RIGHT


# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	# State logic
	if state == States.JUMPING:
		velocity.y = -jump
		if substate == SubStates.RIGHT:
			anim.scale.x = 1
			anim.play("jump")
		elif substate == SubStates.LEFT:
			anim.scale.x = -1
			anim.play("jump")
		else:
			pass
	elif state == States.IN_AIR:
		velocity.y += gravity * delta
		if substate == SubStates.RIGHT:
			anim.scale.x = 1
			anim.play("jump")
		elif substate == SubStates.LEFT:
			anim.scale.x = -1
			anim.play("jump")
		else:
			pass
	elif state == States.MOVE:
		velocity.y += gravity * delta
		if substate == SubStates.RIGHT:
			velocity.x = speed
			anim.scale.x = 1
			anim.play("walk")
		elif substate == SubStates.LEFT:
			velocity.x = -speed
			anim.scale.x = -1
			anim.play("walk")
		else:
			pass
	elif state == States.STILL:
		velocity.x = 0
		velocity.y = 0
		if substate == SubStates.RIGHT:
			anim.scale.x = 1
			anim.play("stand")
		elif substate == SubStates.LEFT:
			anim.scale.x = -1
			anim.play("stand")
		else:
			pass
	else:
		pass
	# Move logic
	velocity = move_and_slide(velocity, Vector2.UP)
	# Transition logic
	if not is_on_floor():
		state = States.IN_AIR
		if Input.is_action_pressed("left"):
			substate = SubStates.LEFT
		elif Input.is_action_pressed("right"):
			substate = SubStates.RIGHT
		else:
			pass
	elif is_on_floor():
		if Input.is_action_just_pressed("jump"):
			state = States.JUMPING
		elif Input.is_action_pressed("left"):
			state = States.MOVE
			substate = SubStates.LEFT
		elif Input.is_action_pressed("right"):
			state = States.MOVE
			substate = SubStates.RIGHT
		else:
			state = States.STILL
	else:
		pass
