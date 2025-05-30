extends Button

func __get_inputs_manager() -> InputsManager:
	return get_node("/root/Control/App/Content/InputsManager");

func _ready():
	print(name + " is attached!")
	
	if name == "SETTINGS":
		connect("pressed", change_settings)
	elif name == "CLR":
		connect("pressed", clear_input)
	elif [
		"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"
		].has(name):
			connect("pressed", num_input)
		
func change_settings():
	# Using `$SettingsPanel` doesn't work and is null? Gotta get node.
	var panel = get_node("/root/Control/SettingsPanel")
	panel.show()
	release_focus()
	panel.grab_focus()
	
func clear_input():
	__get_inputs_manager().clear_inputs();
	
func num_input():
	var inp_mgr = __get_inputs_manager();
	
	var put_func = func(inp_mgr: InputsManager, char: String):
		for child in inp_mgr.get_children():
			if child.name == inp_mgr.current_input:
				var line_edit: LineEdit = child.get_child(1)
				line_edit._on_text_changed(line_edit.text + char)
	
	match inp_mgr.current_input:
		"Oct":
			if not [0, 1, 2, 3, 4, 5, 6, 7].has(int(name)):
				return
		"Bin":
			if not [0, 1].has(int(name)):
				return
				
	put_func.call(inp_mgr, name);
