
// HUD extension for Gig Performer by @rank13

#pragma once
#include <juce_core/juce_core.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>

using namespace juce;

class HUDContainer : public Component
{
public:
  HUDContainer () {}
  
  void mouseUp(const MouseEvent &e) override
  {
    const int nbOfClicks = e.getNumberOfClicks();
    if (nbOfClicks == 2)
      {
        this->setVisible(false);
      }
  }
    void mouseDown (const MouseEvent& e) override
    {
        dragger.startDraggingComponent (this, e);
    }

    void mouseDrag (const MouseEvent& e) override
    {
        // As there's no titlebar we have to manage the dragging ourselves
        dragger.dragComponent (this, e, nullptr);
    }

    void paint (Graphics& g) override;

private:
  ComponentDragger dragger;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HUDContainer)
};

class myHUDTimer : public Timer
{
public:
  virtual void timerCallback() override;
};

class HUDWindow  : public Component 
{
public:
    HUDWindow ();
    ~HUDWindow() override;

    void static initialize(); // Call this to show the component
    void static finalize(); // Call this when library is about to be unloaded to free resources
    void static showHUD();
    void static hideHUD();
    void static setHUDSize(int width, int height);
    void static setHUDPosition(int x, int y);
    void static setHUDPositionByName(std::string positionName);
    void static setHUDDuration(int ms);
    void static setHUDPositionSize(int x, int y, int width, int height);
    void static setHUDNamedPositionSize(std::string positionName, int width, int height);

    std::unique_ptr<Component> hud;
    static HUDWindow* myInstance;

private:
    std::unique_ptr<myHUDTimer> hudTimer;

  void showTransparentWindow()
    {
        hud.reset (new HUDContainer ());
        hud->addToDesktop (ComponentPeer::windowIsTemporary);
        Rectangle<int> area (0, 0, 200, 100);
        hud->setBounds (area);
        hud->setAlwaysOnTop (true);
        hud->setVisible (false);
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HUDWindow)
};



