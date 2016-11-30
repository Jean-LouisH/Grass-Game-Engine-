#include "Suprannua.h"

void HUD_updateKernelStats()
{
    sprintf(textCache[0].text, SOFTWARE VERSION "Kernel time: %.0fs, Runtime: %.2fs, Frame count: %d, FPS: %.2f",
            kernelTime, timeCount, frameCount, framesPerSecond);
}

void HUD_setText(double xText, double yText, char newText)
{
    int i;
    textCache[1].text[0] = newText;
    //sprintf(textCache[1].text, "%c", newText);
    textCache[1].classification = HUD;

}

void HUD_removeText(int textCell)
{

}
