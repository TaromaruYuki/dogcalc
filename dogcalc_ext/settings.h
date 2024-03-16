#ifndef DOGCALC_SETTINGS_H
#define DOGCALC_SETTINGS_H

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/node.hpp>

namespace godot {

class Settings : public Node {
    GDCLASS(Settings, Node)

private:
    bool is_signed;
    bool is_little_endian;
    uint8_t bits;

protected:
	static void _bind_methods() {
        ClassDB::bind_method(D_METHOD("get_is_signed"), &Settings::get_is_signed);
        ClassDB::bind_method(D_METHOD("set_is_signed", "value"), &Settings::set_is_signed);
        ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_signed"), "set_is_signed", "get_is_signed");

        ClassDB::bind_method(D_METHOD("get_is_little_endian"), &Settings::get_is_little_endian);
        ClassDB::bind_method(D_METHOD("set_is_little_endian", "value"), &Settings::set_is_little_endian);
        ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_little_endian"), "set_is_little_endian", "get_is_little_endian");

        ClassDB::bind_method(D_METHOD("get_bits"), &Settings::get_bits);
        ClassDB::bind_method(D_METHOD("set_bits", "value"), &Settings::set_bits);
        ADD_PROPERTY(PropertyInfo(Variant::INT, "bits"), "set_bits", "get_bits");
    }

public:
    Settings() {
        is_signed = false;
        is_little_endian = false;
        bits = 64;
    }

    ~Settings() {}

    bool get_is_signed() { return is_signed; }
    void set_is_signed(bool value) { is_signed = value; }

    bool get_is_little_endian() { return is_little_endian; }
    void set_is_little_endian(bool value) { is_little_endian = value; }

    uint8_t get_bits() { return bits; }
    void set_bits(uint8_t value) { bits = value; }
};

}

#endif