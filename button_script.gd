extends Button

func __get_inputs_manager() -> InputsManager:
	return get_node("/root/Control/App/Content/InputsManager");
	
func __connect_input_changed_to_key():
	var mgr = __get_inputs_manager()
	mgr.input_changed.connect(__input_changed);
	
func __input_changed(current_input: String):
	match current_input:
		"Hex":
			disabled = false
		"Dec":
			disabled = ["A", "B", "C", "D", "E", "F"].has(name)
		"Oct":
			disabled = not ["0", "1", "2", "3", "4", "5", "6", "7"].has(name)
		"Bin":
			disabled = not ["0", "1"].has(name)
	pass

func _ready():
	if name == "SETTINGS":
		connect("pressed", change_settings)
	elif name == "CLR":
		connect("pressed", clear_input)
	elif [
		"0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
		"A", "B", "C", "D", "E", "F"
		].has(name):
			connect("pressed", num_input)
			__connect_input_changed_to_key();
		
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
		"Hex":
			pass
		"Dec":
			if not ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9"].has(name):
				return
		"Oct":
			if not ["0", "1", "2", "3", "4", "5", "6", "7"].has(name):
				return
		"Bin":
			if not ["0", "1"].has(name):
				return
				
	put_func.call(inp_mgr, name);
