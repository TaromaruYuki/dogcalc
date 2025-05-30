extends GridContainer

const BUTTON_LAYOUT = [
	["SETTINGS", "&", "|", "!", "^", " "],
	["++", "--", "<<", ">>", "rand", "randi"],
	["(", ")", "rol", "ror", "%", "/"],
	["A", "B", "7", "8", "9", "*"],
	["C", "D", "4", "5", "6", "-"],
	["E", "F", "1", "2", "3", "+"],
	["CLR", "DEL", "  ", "0", "   ", "="],
]

# Called when the node enters the scene tree for the first time.
func _ready():
	var script = load("res://button_script.gd")
	for x in BUTTON_LAYOUT:
		for y in x:
			var button = Button.new()
			button.name = y
			button.text = y
			button.size_flags_horizontal = Control.SIZE_EXPAND_FILL
			button.size_flags_vertical = Control.SIZE_EXPAND_FILL
			#button.connect("pressed", Callable(self, "_button_pressed").bind(y))
			init_button(button, script)
			add_child(button)
	
func init_button(button: Button, script: Script):
	if button.text in "   ABCDEF":
		button.disabled = true
		
	if button.text.strip_edges().is_empty():
		button.name = "empty" + str(len(button.text))
		
	button.set_script(script)
