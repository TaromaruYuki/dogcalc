#ifndef DOGCALC_INPUTSMANAGER_H
#define DOGCALC_INPUTSMANAGER_H

#include <godot_cpp/classes/v_box_container.hpp>
#include <godot_cpp/classes/h_box_container.hpp>
#include <godot_cpp/classes/line_edit.hpp>

namespace godot {

class InputsManager : public VBoxContainer {
	GDCLASS(InputsManager, VBoxContainer)

private:
	godot::String current_input;
    HBoxContainer* current_child;

protected:
	static void _bind_methods();

public:
	InputsManager();
	~InputsManager();

    void _ready() override;
    void change_input();
    void clear_line_edits();
    void _line_edit_focus_entered(HBoxContainer* child);
    void _line_edit_text_changed(String new_text, LineEdit* line_edit);
};

}

#endif