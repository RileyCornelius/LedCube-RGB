#include <Arduino.h>
#include <Logger.h>
#include "Animator.h"
#include "Display.h"
#include "config.h"

extern Animator animator;

static const char *TAG = "[Display]";

void writeDisplayCommand(DisplayType command)
{
    String messageToSend(static_cast<char>(command));

    LOG_DEBUG(TAG, "Command: %s", messageToSend);
    SerialDisplay.println(messageToSend);
}

void writeDisplayMessage(DisplayType type, String message)
{
    String messageToSend(static_cast<char>(type));

    messageToSend += message;
    LOG_DEBUG(TAG, "MessageToSend: %s", messageToSend);
    SerialDisplay.println(messageToSend);
}

void writeDisplayMessage(DisplayType type, char *message)
{
    writeDisplayMessage(type, String(message));
}

void handleDisplay()
{
#if DISPLAY_ENABLE

    while (SerialDisplay.available())
    {
        String data = SerialDisplay.readStringUntil('\n');
        data.trim(); // remove \n

        uint8_t displayType = data.charAt(0); // get the first char (DisplayType enum)
        data.remove(0, 1);                    // remove display type

        LOG_DEBUG(TAG, "type: %d", displayType);
        LOG_DEBUG(TAG, "data: %s", data);

        switch (displayType)
        {
        case CommandPlay:
            animator.play();
            break;

        case CommandPause:
            animator.pause();
            break;

        case CommandNext:
            animator.next();
            break;

        case CommandPrevious:
            animator.previous();
            break;

        case CommandStop:
            animator.stop();
            break;

        case CommandRotation:
            animator.rotate();
            break;

        case MessageRotationTime:
            animator.setRotation(data.toInt());
            break;
        }
    }
#endif
}