// HUD extension for Gig Performer by @rank13

#include <juce_events/juce_events.h>
#include "HUDWindow.h"
#include "LibMain.h"

HUDWindow* HUDWindow::myInstance = nullptr;

HUDWindow::HUDWindow ()
{
    showTransparentWindow();
    hudTimer.reset (new myHUDTimer);
}

HUDWindow::~HUDWindow()
{
    hud = nullptr;
}

void HUDWindow::initialize()
{
    MessageManager::getInstance()->callAsync([]() {
                                                        if (myInstance == nullptr)
                                                        {
                                                            myInstance = new HUDWindow();
                                                        }
                                                        jassert(myInstance != nullptr);
                                                    });
}

void HUDWindow::finalize()
{
    if (myInstance != nullptr)
    {
        delete myInstance;
        myInstance = nullptr;
    }
}

void HUDWindow::showHUD() {
    if (myInstance != nullptr)
    {
        MessageManager::getInstance()->callAsync([]() {
                                                        myInstance->hud->setVisible(false);
                                                        myInstance->hud->setVisible(true);
                                                        if (HUD_Duration >= 0)
                                                            myInstance->hudTimer->startTimer(HUD_Duration);
                                                            });
    }
}

void HUDWindow::hideHUD() {
    if (myInstance != nullptr)
    {
        MessageManager::getInstance()->callAsync([]() {
                                                        myInstance->hud->setVisible(false);
                                                            });
    }
}

void HUDWindow::setHUDSize(int width, int height) {
    if (myInstance != nullptr)
    {
        auto bounds = myInstance->hud->getBounds();
        int x = bounds.getX();
        int y = bounds.getY();
        MessageManager::getInstance()->callAsync([x,y,width,height]() {
                                                        myInstance->hud->setBounds(x, y, width, height);
                                                        myInstance->hud->setVisible(false);
                                                        myInstance->hud->setVisible(true);
                                                            });
    }

}

void HUDWindow::setHUDPosition(int x, int y) {
    if (myInstance != nullptr)
    {
        auto bounds = myInstance->hud->getBounds();
        int width = bounds.getWidth();
        int height = bounds.getHeight();
        MessageManager::getInstance()->callAsync([x,y,width,height]() {
                                                        myInstance->hud->setBounds(x, y, width, height);
                                                        myInstance->hud->setVisible(false);
                                                        myInstance->hud->setVisible(true);
                                                            });
    }

}

void HUDWindow::setHUDPositionSize(int x, int y, int width, int height) {
    if (myInstance != nullptr)
    {
        MessageManager::getInstance()->callAsync([x,y,width,height]() {
                                                        myInstance->hud->setBounds(x, y, width, height);
                                                            });
    }
}

void HUDWindow::setHUDPositionByName(std::string positionName) {
    if (myInstance != nullptr)
    {
        auto bounds = myInstance->hud->getBounds();
        Rectangle<int> area (0, 0, bounds.getWidth(), bounds.getHeight());
        Rectangle<int> result; 
        if (positionName == "Center") {
                RectanglePlacement placement (RectanglePlacement::xMid
                                       | RectanglePlacement::yMid
                                       | RectanglePlacement::doNotResize);

        result = placement.appliedTo (bounds, Desktop::getInstance().getDisplays()
                                                         .getPrimaryDisplay()->userArea.reduced (0));
        } else if (positionName == "TopRight") {
            RectanglePlacement placement (RectanglePlacement::xRight
                                       | RectanglePlacement::yTop
                                       | RectanglePlacement::doNotResize);

        result = placement.appliedTo (bounds, Desktop::getInstance().getDisplays()
                                                         .getPrimaryDisplay()->userArea.reduced (0));
        } else if (positionName == "TopRight") {
            RectanglePlacement placement (RectanglePlacement::xRight
                                       | RectanglePlacement::yTop
                                       | RectanglePlacement::doNotResize);

        result = placement.appliedTo (bounds, Desktop::getInstance().getDisplays()
                                                         .getPrimaryDisplay()->userArea.reduced (0));
        } else if (positionName == "TopLeft") {
            RectanglePlacement placement (RectanglePlacement::xLeft
                                       | RectanglePlacement::yTop
                                       | RectanglePlacement::doNotResize);

        result = placement.appliedTo (bounds, Desktop::getInstance().getDisplays()
                                                         .getPrimaryDisplay()->userArea.reduced (0));
        } else if (positionName == "TopCenter") {
            RectanglePlacement placement (RectanglePlacement::xMid
                                       | RectanglePlacement::yTop
                                       | RectanglePlacement::doNotResize);

        result = placement.appliedTo (bounds, Desktop::getInstance().getDisplays()
                                                         .getPrimaryDisplay()->userArea.reduced (0));
        } else {
            
            result = bounds;
        }
        MessageManager::getInstance()->callAsync([result]() {
                                                        myInstance->hud->setTopLeftPosition(result.getX(),result.getY());
                                                        myInstance->hud->setVisible(false);
                                                        myInstance->hud->setVisible(true);
                                                            });
    }
}

void HUDWindow::setHUDNamedPositionSize(std::string positionName, int width, int height) {
   if (myInstance != nullptr)
    {
        Rectangle<int> area (0, 0, width, height);
        Rectangle<int> result; 
        if (positionName == "Center") {
                RectanglePlacement placement (RectanglePlacement::xMid
                                       | RectanglePlacement::yMid
                                       | RectanglePlacement::doNotResize);

        result = placement.appliedTo (area, Desktop::getInstance().getDisplays()
                                                         .getPrimaryDisplay()->userArea.reduced (0));
        } else if (positionName == "TopRight") {
            RectanglePlacement placement (RectanglePlacement::xRight
                                       | RectanglePlacement::yTop
                                       | RectanglePlacement::doNotResize);

        result = placement.appliedTo (area, Desktop::getInstance().getDisplays()
                                                         .getPrimaryDisplay()->userArea.reduced (0));
        } else if (positionName == "TopRight") {
            RectanglePlacement placement (RectanglePlacement::xRight
                                       | RectanglePlacement::yTop
                                       | RectanglePlacement::doNotResize);

        result = placement.appliedTo (area, Desktop::getInstance().getDisplays()
                                                         .getPrimaryDisplay()->userArea.reduced (0));
        } else if (positionName == "TopLeft") {
            RectanglePlacement placement (RectanglePlacement::xLeft
                                       | RectanglePlacement::yTop
                                       | RectanglePlacement::doNotResize);

        result = placement.appliedTo (area, Desktop::getInstance().getDisplays()
                                                         .getPrimaryDisplay()->userArea.reduced (0));
        } else if (positionName == "TopCenter") {
            RectanglePlacement placement (RectanglePlacement::xMid
                                       | RectanglePlacement::yTop
                                       | RectanglePlacement::doNotResize);

        result = placement.appliedTo (area, Desktop::getInstance().getDisplays()
                                                         .getPrimaryDisplay()->userArea.reduced (0));
        } else {
            auto bounds = myInstance->hud->getBounds();
            bounds.setWidth(width);
            bounds.setHeight(height);
            result = bounds;
        }
        MessageManager::getInstance()->callAsync([result]() {

                                                        myInstance->hud->setBounds(result);
                                                        myInstance->hud->setVisible(false);
                                                            });
    }
}

void HUDWindow::setHUDDuration(int ms) {
    if (myInstance != nullptr)
    {
        MessageManager::getInstance()->callAsync([ms]() {
                                                        myInstance->hudTimer->stopTimer();
                                                        if (HUD_Duration >= 0)
                                                            myInstance->hudTimer->startTimer(ms);
                                                        });
    }

}

void HUDContainer::paint (Graphics& g)
    {
       auto area = getLocalBounds().toFloat().reduced (0.8f);
        float cornerSize = 8.f;
        g.setColour (Colour(0xdd151515));
        g.fillRoundedRectangle (area, cornerSize);
        auto fontSize = (float) HUD_Font_Size;
        g.setFont (fontSize);
        g.setColour (Colours::white);
        g.drawFittedText (HUD_Text,
                          getLocalBounds().reduced (8, 0),
                          Justification::centred, 5);
    }

    void myHUDTimer::timerCallback() {
        HUDWindow::hideHUD();
        this->stopTimer();
    }