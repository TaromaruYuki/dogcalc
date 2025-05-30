#include "inputs_manager.h"
#include <godot_cpp/core/class_db.hpp>
#include <string>

#define PRINT(x) emit_signal("print_crossover", x)

using namespace godot;

void InputsManager::_bind_methods() {
    ADD_SIGNAL(MethodInfo("print_crossover", PropertyInfo(Variant::STRING, "crossover")));
    ADD_SIGNAL(MethodInfo("remove_last_char"));
    // ADD_SIGNAL(MethodInfo("update_line_edits"));

    ClassDB::bind_method(D_METHOD("set_current_input", "value"), &InputsManager::set_current_input);
	ClassDB::bind_method(D_METHOD("get_current_input"), &InputsManager::get_current_input);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "current_input"), "set_current_input", "get_current_input");

    ClassDB::bind_method(D_METHOD("clear_inputs"), &InputsManager::clear_line_edits);
}

InputsManager::InputsManager() {
	current_input = "Dec";
    current_child = nullptr;
}


void InputsManager::_ready() {
    auto children = get_children();
    
    for (int i = 0; i < children.size(); i++) {
        auto child = Object::cast_to<HBoxContainer>(children[i]);
        auto line_edit = Object::cast_to<LineEdit>(child->get_child(1));
        
        Callable focus_callable = callable_mp(this, &InputsManager::_line_edit_focus_entered);
        focus_callable = focus_callable.bind(child);
        line_edit->connect("focus_entered", focus_callable);

        Callable text_callable = callable_mp(this, &InputsManager::_line_edit_text_changed);
        text_callable = text_callable.bind(line_edit);
        line_edit->connect("text_changed", text_callable);
    }

    // Callable update_lines_callable = callable_mp(this, &InputsManager::)

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

void InputsManager::clear_line_edits() {
    auto children = get_children();
    
    for (int i = 0; i < children.size(); i++) {
        auto child = Object::cast_to<HBoxContainer>(children[i]);
        auto line_edit = Object::cast_to<LineEdit>(child->get_child(1));

        line_edit->set_text("");
    }
}

void InputsManager::_line_edit_text_changed(String new_text, LineEdit* line_edit) {
    if(line_edit->get_text().is_empty()) {
        this->clear_line_edits();
        return;
    }

    switch(line_edit->get_parent()->get_name().hash()) {
        case 193458858: { // Hex
            uint64_t num;
            try {
                num = std::stoull(line_edit->get_text().ascii().ptr(), nullptr, 16);
            } catch (const std::out_of_range& e) {
                emit_signal("remove_last_char");
                return;
            }

            this->update_line_edits(num);
        } break;
        case 193454481: { // Dec
            uint64_t num;
            try {
                num = std::stoull(line_edit->get_text().ascii().ptr(), nullptr, 10);
            } catch (const std::out_of_range& e) {
                emit_signal("remove_last_char");
                return;
            }

            this->update_line_edits(num);
        } break;
        case 193466411: { // Oct
            uint64_t num;
            try {
                num = std::stoull(line_edit->get_text().ascii().ptr(), nullptr, 8);
            } catch (const std::out_of_range& e) {
                emit_signal("remove_last_char");
                return;
            }

            this->update_line_edits(num);
        } break;
        case 193452446: { // Bin
            uint64_t num;
            try {
                num = std::stoull(line_edit->get_text().ascii().ptr(), nullptr, 2);
            } catch (const std::out_of_range& e) {
                emit_signal("remove_last_char");
                return;
            }

            this->update_line_edits(num);
        } break;
    }
}

void InputsManager::update_line_edits(uint64_t value) {
    auto children = get_children();

    for(int i = 0; i < children.size(); i++) {
        auto child = Object::cast_to<HBoxContainer>(children[i]);
        auto line_edit = Object::cast_to<LineEdit>(child->get_child(1));

        if(child->get_name() == current_input) continue;

        switch(child->get_name().hash()) {
            case 193458858: { // Hex
                line_edit->set_text(String::num_int64(value, 16));
            } break;
            case 193454481: { // Dec
                line_edit->set_text(String::num_int64(value, 10));
            } break;
            case 193466411: { // Oct
                line_edit->set_text(String::num_int64(value, 8));
            } break;
            case 193452446: { // Bin
                line_edit->set_text(String::num_int64(value, 2));
            } break;
        }
    }
}
