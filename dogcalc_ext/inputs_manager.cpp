#include "inputs_manager.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void InputsManager::_bind_methods() {
}

InputsManager::InputsManager() {
	current_input = "Dec";
    current_child = nullptr;

    auto children = get_children();
    
    for (int i = 0; i < children.size(); i++) {
        auto child = Object::cast_to<HBoxContainer>(children[i]);
        auto line_edit = Object::cast_to<LineEdit>(child->get_child(1));
        
        Callable focus_callable(this, "_line_edit_focus_entered");
        focus_callable.bind(child);
        line_edit->connect("focus_entered", focus_callable);

        Callable text_callable(this, "_line_edit_text_changed");
        text_callable.bind(line_edit);
        line_edit->connect("text_changed", text_callable);
    }

    this->change_input();
}

InputsManager::~InputsManager() {}

void InputsManager::change_input() {
    auto children = get_children();
    
    for (int i = 0; i < children.size(); i++) {
        auto child = Object::cast_to<HBoxContainer>(children[i]);
        auto line_edit = Object::cast_to<LineEdit>(child->get_child(1));

        if(child->get_name() == current_input) {
            current_child = child;
            line_edit->grab_focus();
            line_edit->set_editable(true);
        } else {
            line_edit->set_editable(false);
        }
    }
}

void InputsManager::_line_edit_focus_entered(HBoxContainer* child) {
    current_input = child->get_name();
    this->change_input();
}

void InputsManager::_line_edit_text_changed(LineEdit* line_edit) {
    if(line_edit->get_text().is_empty()) {
        this->clear_line_edits();
        return;
    }

    auto parent = Object::cast_to<HBoxContainer>(line_edit->get_parent());

    auto name = parent->get_name();

    if(name.match("Hex")) {
        printf("Hex");
    } else if(name.match("Dec")) {
        printf("Dec");
    } else if(name.match("Oct")) {
        printf("Oct");
    } else if(name.match("Bin")) {
        printf("Bin");
    }
}

void InputsManager::clear_line_edits() {
    auto children = get_children();
    
    for (int i = 0; i < children.size(); i++) {
        auto child = Object::cast_to<HBoxContainer>(children[i]);
        auto line_edit = Object::cast_to<LineEdit>(child->get_child(1));

        line_edit->set_text("");
    }
}