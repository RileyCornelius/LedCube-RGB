#include <Arduino.h>
#include <Logger.h>
#include "ui/ui.h"
#include "config.h"
#include "cube_com.h"

static const char *TAG = "[Display]";

void writeDisplayCommand(DisplayType command)
{
    String messageToSend(static_cast<char>(command));

    LOG_DEBUG(TAG, "Command: %s", messageToSend);
    SerialCube.println(messageToSend);
}

void writeDisplayMessage(DisplayType type, String message)
{
    String messageToSend(static_cast<char>(type));

    messageToSend += message;
    LOG_DEBUG(TAG, "MessageToSend: %s", messageToSend);
    SerialCube.println(messageToSend);
}

void writeDisplayMessage(DisplayType type, char *message)
{
    writeDisplayMessage(type, String(message));
}

void handleCom()
{
    while (SerialCube.available())
    {
        String data = SerialCube.readStringUntil('\n');
        data.trim(); // remove \n

        uint8_t displayType = data.charAt(0); // get the first char (DisplayType enum)
        data.remove(0, 1);                    // remove display type

        LOG_DEBUG(TAG, "type: %d", displayType);
        LOG_DEBUG(TAG, "data: %s", data);

        switch (displayType)
        {
        case CommandPlay:
            lv_img_set_src(ui_play_image, &ui_img_pause_png);
            lv_obj_set_x(ui_play_image, 0);
            break;

        case CommandPause:
            lv_img_set_src(ui_play_image, &ui_img_play_png);
            lv_obj_set_x(ui_play_image, 0);
            break;

        case CommandOtaStart:
            lv_scr_load(ui_ota_screen);
            break;

        case CommandOtaEnd:
            lv_scr_load(ui_main_screen);
            break;

        case MessageOtaProgress:
            lv_bar_set_value(ui_progress_bar, data.toInt(), LV_ANIM_ON);
            data += "%";
            lv_label_set_text(ui_progress_text, data.c_str());
            break;

        case MessageAnimation:
            lv_label_set_text(ui_animation_text, data.c_str());
            break;
        }
    }
}