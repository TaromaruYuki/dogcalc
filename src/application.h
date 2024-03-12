#pragma once

#include <gtkmm/button.h>
#include <gtkmm/window.h>

class Application : public Gtk::Window {
public:
    Application();
    virtual ~Application();

protected:
    //Signal handlers:
    void on_button_clicked();

    //Member widgets:
    Gtk::Button m_button;
};