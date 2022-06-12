// HUD extension for Gig Performer by @rank13

#pragma once

#include <gigperformer/sdk/GPMidiMessages.h>
#include <gigperformer/sdk/GPUtils.h>
#include <gigperformer/sdk/GigPerformerAPI.h>
#include <juce_gui_basics/juce_gui_basics.h>

#include "HUDWindow.h"

// Define an XML string describing your product
const std::string XMLProductDescription =           
    "<Library>" 
    "<Product Name=\"GP HUD\" Version=\"1.1\" BuildDate=\"12/6/2022\"></Product> "
    "<Description>Head-up Display</Description>"
    "<ImagePath></ImagePath>"
    "</Library>"; 

// Globals
extern std::string HUD_Text;
extern int HUD_Font_Size;
extern int HUD_Duration;
extern int HUD_Width;
extern int HUD_Height;
extern int HUD_Position_X;
extern int HUD_Position_Y;

// Define your class here - it MUST be called LibMain and it must inherit from GigPerformerAPI

class LibMain : public gigperformer::sdk::GigPerformerAPI
{
public:
    // These must be here but no need to do anything unless you want extra behavior
     LibMain(LibraryHandle handle) : GigPerformerAPI(handle) {}
    virtual ~LibMain() {}
    
    // List of GP Script functions to be made available to GP along with the address of the code to execute for each of those functions */
    int RequestGPScriptFunctionSignatureList( GPScript_AllowedLocations location, ExternalAPI_GPScriptFunctionDefinition* *list) override;
    
    void OnOpen() override
    {
        HUDWindow::initialize();
    }
    
    void OnClose() override
    {
        HUDWindow::finalize();
    }
    
    void Initialization() override
    {
        // Register all the methods that you are going to actually use, i.e, the ones you declared above as override
        registerCallback("OnOpen");
        registerCallback("OnClose");
    }
    
    // An XML description of your product
    std::string GetProductDescription() override // This MUST be defined in your class
    {
        return XMLProductDescription;
    }
};