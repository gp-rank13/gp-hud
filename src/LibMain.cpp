// HUD extension for Gig Performer by @rank13

#include "LibMain.h"

namespace gigperformer {
   namespace sdk {
      GigPerformerAPI *CreateGPExtension(LibraryHandle handle) {
         return new LibMain(handle);
      }
   } // namespace sdk
} // namespace gigperformer

// *** Global Variables *** 

std::string HUD_Text = "GP HUD";
int HUD_Duration = 2000;
int HUD_Font_Size = 80;

// *** GP Script *** 

extern "C" void DisplayString(GPRuntimeEngine* vm)
{
   char buffer[1000];   
   GP_VM_PopString(vm, buffer, 1000);
   std::string s = buffer;
   GP_VM_PushString(vm, s.c_str());
   HUD_Text = s;
   HUDWindow::showHUD();
}

extern "C" void SetSize(GPRuntimeEngine* vm)
{
   int height = GP_VM_PopInteger(vm);
   int width = GP_VM_PopInteger(vm);
   HUDWindow::setHUDSize(width, height);
}

extern "C" void SetPosition(GPRuntimeEngine* vm)
{
   int y = GP_VM_PopInteger(vm);
   int x = GP_VM_PopInteger(vm);
   HUDWindow::setHUDPosition(x, y);
}

extern "C" void SetPositionByName(GPRuntimeEngine* vm)
{
   char buffer[100];   
   GP_VM_PopString(vm, buffer, 100);
   std::string s = buffer;
   HUDWindow::setHUDPositionByName(s);
}

extern "C" void SetDuration(GPRuntimeEngine* vm)
{
   int ms = GP_VM_PopInteger(vm);
   HUD_Duration = ms;
   HUDWindow::setHUDDuration(ms);
}

extern "C" void SetFontSize(GPRuntimeEngine* vm)
{
   int size = GP_VM_PopInteger(vm);
   HUD_Font_Size = size;
}

extern "C" void SetPositionSize(GPRuntimeEngine* vm)
{
   int h = GP_VM_PopInteger(vm);
   int w = GP_VM_PopInteger(vm);
   int y = GP_VM_PopInteger(vm);
   int x = GP_VM_PopInteger(vm);
   HUDWindow::setHUDPositionSize(x, y, w, h);
}

extern "C" void SetNamedPositionSize(GPRuntimeEngine* vm)
{
   int h = GP_VM_PopInteger(vm);
   int w = GP_VM_PopInteger(vm);
   char buffer[100];   
   GP_VM_PopString(vm, buffer, 100);
   std::string s = buffer;
   HUDWindow::setHUDNamedPositionSize(s, w, h);
}

ExternalAPI_GPScriptFunctionDefinition functionList[] =
   {
      {"DisplayText",  "text : String",               "",       "Display text in the HUD window",   DisplayString},
      {"SetFontSize",  "size : Integer",               "",       "Set the font size for the HUD window",   SetFontSize},
      {"SetDuration",     "ms : Integer",               "",       "Set the duration in ms for the HUD window to be displayed",   SetDuration},
      {"SetPositionAndSize",     "x : Integer, y : Integer, width : Integer, height : Integer",               "",       "Set the position and size of the HUD window",   SetPositionSize},
      {"SetNamedPositionAndSize",     "positionName : String, width : Integer, height : Integer",               "",       "Set the position using defined names and set the size of the HUD window",   SetNamedPositionSize},
   };

int LibMain::RequestGPScriptFunctionSignatureList(GPScript_AllowedLocations location,  ExternalAPI_GPScriptFunctionDefinition* *list)
{
   // Allow these in ANY script so no need to check the location field  
   *list = functionList;
   int count = sizeof(functionList) / sizeof(ExternalAPI_GPScriptFunctionDefinition);
   return count; 
}