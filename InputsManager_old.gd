extends VBoxContainer

@onready var current_input = "Dec"
@onready var current_child: HBoxContainer;

func _ready():
	for child in get_children():
		var line_edit = child.get_child(1)
		line_edit.connect("focus_entered", Callable(self, "_line_edit_focus_entered").bind(child))
		line_edit.connect("text_changed", Callable(self, "_line_edit_text_changed").bind(line_edit))
	
	change_input()

func change_input():
	for child in get_children():
		var line_edit: LineEdit = child.get_child(1)
		if child.name == current_input:
			line_edit.editable = true
			current_child = child
		else:
			line_edit.editable = false

func update_line_edits(value: int):
	for child in get_children():
		var line_edit: LineEdit = child.get_child(1)
		var old_pos = line_edit.caret_column
		match child.name:
			"Hex":
				line_edit.text = "%X" % value
			"Dec":
				line_edit.text = str(value)
			"Oct":
				line_edit.text = "%o" % value
			"Bin":
				line_edit.text = int_to_bin(value)
				
		line_edit.caret_column = old_pos
		
func clear_line_edits():
	for child in get_children():
		var line_edit: LineEdit = child.get_child(1)
		line_edit.text = ""
		

func _line_edit_focus_entered(root: HBoxContainer):
	current_input = root.name
	change_input()
	
func oct_to_int(value: String):
	var result = 0

	for char in value:
		var digit = char.to_int()
		result = result * 8 + digit

	return result
	
func int_to_bin(value: int):
	var result = ""
	while value > 0:
		result = str(value % 2) + result
		value = floori(value / 2)
		
	if result.is_empty():
		return "0"
	
	return result
	
func _line_edit_text_changed(new_text: String, line_edit: LineEdit):
	if line_edit.text == "":
		clear_line_edits()
		return
		
	match line_edit.get_parent().name:
		"Hex":
			update_line_edits(line_edit.text.hex_to_int())
		"Dec":
			update_line_edits(int(line_edit.text))
		"Oct":
			# Godot does not supply a oct_to_int function, so we make our own.
			update_line_edits(oct_to_int(line_edit.text))
		"Bin":
			update_line_edits(line_edit.text.bin_to_int())
