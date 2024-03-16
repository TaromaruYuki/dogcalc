extends InputsManager

func _on_print_crossover(crossover):
	print(crossover)

func _on_remove_last_char():
	for child in get_children():
		if child.name == current_input:
			var line_edit: LineEdit = child.get_child(1)
			line_edit._on_text_changed(line_edit.text.left(line_edit.text.length() - 1))
