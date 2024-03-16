extends MarginContainer

@onready var settings = $"../Settings"
@onready var signed_button = $Panel/VBoxContainer/SignedButton
@onready var little_endian = $Panel/VBoxContainer/LittleEndian
@onready var bits = $Panel/VBoxContainer/Bits
@onready var close = $Panel/VBoxContainer/Close

func _ready():
	signed_button.connect("pressed", update_signed)
	little_endian.connect("pressed", update_endianess)
	bits.connect("item_selected", update_bits)
	close.connect("pressed", hide)
	
func update_signed():
	settings.is_signed = signed_button.button_pressed
	
func update_endianess():
	settings.is_little_endian = little_endian.button_pressed
	
func update_bits(index: int):
	settings.bits = bits.get_item_id(index)
	print(settings.bits)
