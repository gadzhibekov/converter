#include "theme.h"
#include "label.h"
#include "line_edit.h"
#include "button.h"
#include "utils.h"

#include <QWidget>

std::vector<std::pair<std::string, void *>> objPtrs;

void Switch2LightTheme()
{
    for (auto& obj : objPtrs)
    {
        if (obj.first == "Widget")              static_cast<QWidget *>(obj.second)->setStyleSheet(ReadAllFile("../styles/light/widget.css"));
        if (obj.first == "Button")              static_cast<Button  *>(obj.second)->setStyleSheet(ReadAllFile("../styles/light/button.css"));
        if (obj.first == "Button2")             static_cast<Button  *>(obj.second)->setStyleSheet(ReadAllFile("../styles/light/button_2.css"));
        if (obj.first == "Label")               static_cast<Label   *>(obj.second)->setStyleSheet(ReadAllFile("../styles/light/label.css"));
        if (obj.first == "LineEdit")            static_cast<Label   *>(obj.second)->setStyleSheet(ReadAllFile("../styles/light/line_edit.css"));
        if (obj.first == "Panel")               static_cast<Label   *>(obj.second)->setStyleSheet(ReadAllFile("../styles/light/panel.css"));
        if (obj.first == "PanelItem")           static_cast<Label   *>(obj.second)->setStyleSheet(ReadAllFile("../styles/light/panel_item.css"));
        if (obj.first == "Entity")              static_cast<Label   *>(obj.second)->setStyleSheet(ReadAllFile("../styles/light/entity.css"));
        if (obj.first == "LTP")                 static_cast<Label   *>(obj.second)->setStyleSheet(ReadAllFile("../styles/light/light_theme_phone.css"));
        if (obj.first == "DTP")                 static_cast<Label   *>(obj.second)->setStyleSheet(ReadAllFile("../styles/light/dark_theme_phone.css"));
        if (obj.first == "RadioButton")         static_cast<Label   *>(obj.second)->setStyleSheet(ReadAllFile("../styles/light/radio_button.css"));
        if (obj.first == "MessageBox")          static_cast<Label   *>(obj.second)->setStyleSheet(ReadAllFile("../styles/light/message_box_light.css"));
        if (obj.first == "MessageBoxLabel")     static_cast<Label   *>(obj.second)->setStyleSheet(ReadAllFile("../styles/light/ms_label_light.css"));
    }
}

void Switch2DarkTheme()
{
    for (auto& obj : objPtrs)
    {
        if (obj.first == "Widget")              static_cast<QWidget *>(obj.second)->setStyleSheet(ReadAllFile("../styles/dark/widget.css"));
        if (obj.first == "Button")              static_cast<Button  *>(obj.second)->setStyleSheet(ReadAllFile("../styles/dark/button.css"));
        if (obj.first == "Button2")             static_cast<Button  *>(obj.second)->setStyleSheet(ReadAllFile("../styles/dark/button_2.css"));
        if (obj.first == "Label")               static_cast<Label   *>(obj.second)->setStyleSheet(ReadAllFile("../styles/dark/label.css"));
        if (obj.first == "LineEdit")            static_cast<Label   *>(obj.second)->setStyleSheet(ReadAllFile("../styles/dark/line_edit.css"));
        if (obj.first == "Panel")               static_cast<Label   *>(obj.second)->setStyleSheet(ReadAllFile("../styles/dark/panel.css"));
        if (obj.first == "PanelItem")           static_cast<Label   *>(obj.second)->setStyleSheet(ReadAllFile("../styles/dark/panel_item.css"));
        if (obj.first == "Entity")              static_cast<Label   *>(obj.second)->setStyleSheet(ReadAllFile("../styles/dark/entity.css"));
        if (obj.first == "LTP")                 static_cast<Label   *>(obj.second)->setStyleSheet(ReadAllFile("../styles/dark/light_theme_phone.css"));
        if (obj.first == "DTP")                 static_cast<Label   *>(obj.second)->setStyleSheet(ReadAllFile("../styles/dark/dark_theme_phone.css"));
        if (obj.first == "RadioButton")         static_cast<Label   *>(obj.second)->setStyleSheet(ReadAllFile("../styles/dark/radio_button.css"));
        if (obj.first == "MessageBox")          static_cast<Label   *>(obj.second)->setStyleSheet(ReadAllFile("../styles/dark/message_box_dark.css"));
        if (obj.first == "MessageBoxLabel")     static_cast<Label   *>(obj.second)->setStyleSheet(ReadAllFile("../styles/dark/ms_label_dark.css"));
    }
}