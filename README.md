# Head-Up Display (HUD) Extension for Gig Performer

## Overview
An extension for [Gig Performer](https://gigperformer.com) that adds GPScript functions to display a head-up display (HUD) window. A basic knowledge of Gig Performer's scripting language ([GPScript](https://gigperformer.com/support.html)) will be required in order to use this extension.  
<br />

![gp-hud](https://user-images.githubusercontent.com/107261652/173226307-dc64fd7b-d12c-48b2-bdff-eda20a4986a9.gif)




> _Disclaimer: This is a user-created extension and is not supported by Deskew Techologies. Extensions can cause unexpected behaviour in Gig Performer, and in extreme situations could cause it to crash. Please test it thoroughly before using it in any live performances!_

## Installation

Download the extension (library) files for either MacOS or Windows from the Releases page.  

Mac users will need to move the _libGP_HUD.dylib_ file into this folder and then restart Gig Performer:
```
/Users/Shared/Gig Performer/Extensions
```
Windows users will need to move the _GP_HUD.dll_ file into this folder and then restart Gig Performer:
```
C:\Users\Public\Documents\Gig Performer\Extensions
```
When opening Gig Perfomer, a prompt will appear asking to confirm whether to install the extension.

## Usage

After installing the extension, custom GPScript functions will be available to use, and are listed in the _Code Helper_ autocomplete list. They are all prefixed with _GPHUD_.

> **DisplayText** : _Display text in the HUD window_  
> - GPHUD_DisplayText (text : String)

<br />

> **SetFontSize** : _Set the font size for the HUD window. Example: 24 (small); 120 (large)_  
> - GPHUD_SetFontSize (size : Integer)

<br />

> **SetDuration** : _Set the duration in milliseconds for the HUD window to be displayed_
> - GPHUD_SetDuration (ms : Integer)

<br />

> **SetPositionAndSize** : _Set the position and size of the HUD window_
> - GPHUD_SetPositionAndSize (x : Integer, y : Integer, width : Integer, height : Integer)

<br />

> **SetNamedPositionAndSize** : _Set the position using defined names and set the size of the HUD_ window
> - GPHUD_SetNamedPositionAndSize (positionName : String, width : Integer, height : Integer)
> - positionName Options: Center, TopLeft, TopCenter, TopRight

**Example 1**

Add this as a _Gig Script_ in order to automatically display the Variation name in the upper-right corner.
```
Var
    FontSize : Integer = 80 // Set default font size
    Duration : Integer = 1500 // Set default duration to display the window (1.5 seconds)
    HUD_Size : Integer Array = [450,150] // Set default width and height

// Called automatically after script is loaded
Initialization
    GPHUD_SetFontSize(FontSize)
    GPHUD_SetDuration(Duration) 
End

// Function to display the variation name in the HUD in the upper-right corner
Function DisplayVariationName()
    GPHUD_SetNamedPositionAndSize("TopRight", HUD_Size[0], HUD_Size[1])
    GPHUD_DisplayText(GetVariationName(GetCurrentVariation()))

End

// Called when you switch to another rackspace
On Rackspace(oldRackspaceIndex : integer, newRackspaceIndex : integer)
    DisplayVariationName()
End

// Called when you switch variations
On Variation(oldVariation : integer, newVariation : integer)
    DisplayVariationName()
End
```

**Example 2**

Add this to a _Rackspace Script_ in order to display a custom message in the center of the screen when you press a button widget.
```
Var
   HUD_Widget : Widget // Add a button widget with this name
   FontSize : Integer = 48 // Default font size
   DisplayThis : String = "Message to Display" // Text to show in the HUD window
   Duration_On : Integer = -1 // Special duration value to permanently display the window
   Duration_Off : Integer = 0 // A duration of 0ms will hide it immediately
   
// Called automatically after script is loaded
Initialization
    GPHUD_SetFontSize(FontSize)
    GPHUD_SetNamedPositionAndSize("Center",500,100) // Window will appear in the center of the screen
End

// Called when a single widget value has changed
On WidgetValueChanged(newValue : double) from HUD_Widget
    If newValue == 1.0 Then
        GPHUD_SetDuration(Duration_On)
        GPHUD_DisplayText(DisplayThis)
    Else
        GPHUD_SetDuration(Duration_Off)
    End
End
```

## Building the Extension

To customize/build the extension, refer to the [Gig Performer SDK](https://github.com/gigperformer/gp-sdk) GitHub page.