extends Button

func _ready():
	print(name + " is attached!")
	
	if name == "SETTINGS":
		connect("pressed", change_settings)
		
func change_settings():
	# Using `$SettingsPanel` doesn't work and is null? Gotta get node.
	var panel = get_node("/root/Control/SettingsPanel")
	panel.show()
	release_focus()
	panel.grab_focus()
