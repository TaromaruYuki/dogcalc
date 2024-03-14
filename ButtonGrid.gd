extends GridContainer

const BUTTON_LAYOUT = [
	["SETTINGS", "and", "or", "not", "xor", " "],
	["inc", "dec", "lsl", "lsr", "asr", "rand"],
	["(", ")", "rol", "ror", "mod", "/"],
	["A", "B", "7", "8", "9", "*"],
	["C", "D", "4", "5", "6", "-"],
	["E", "F", "1", "2", "3", "+"],
	["CLR", "DEL", ".", "0", "+/-", "="],
]

# Called when the node enters the scene tree for the first time.
func _ready():
	for x in BUTTON_LAYOUT:
		for y in x:
			var button = Button.new()
			button.name = y
			button.text = y
			button.size_flags_horizontal = Control.SIZE_EXPAND_FILL
			button.size_flags_vertical = Control.SIZE_EXPAND_FILL
			button.connect("pressed", Callable(self, "_button_pressed").bind(y))
			init_button(button)
			add_child(button)

func _button_pressed(id: String):
	print(id)
	
func init_button(button: Button):
	if button.text in " ABCDEF.":
		button.disabled = true
