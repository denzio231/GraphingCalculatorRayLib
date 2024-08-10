/*******************************************************************************************
*
*   TEST v1.0.0 - Tool Description
*
*   MODULE USAGE:
*       #define GUI_TEST_IMPLEMENTATION
*       #include "gui_TEST.h"
*
*       INIT: GuiTESTState state = InitGuiTEST();
*       DRAW: GuiTEST(&state);
*
*   LICENSE: Propietary License
*
*   Copyright (c) 2022 raylib technologies. All Rights Reserved.
*
*   Unauthorized copying of this file, via any medium is strictly prohibited
*   This project is proprietary and confidential unless the owner allows
*   usage in any other form by expresely written permission.
*
**********************************************************************************************/

#include "raylib.h"

// WARNING: raygui implementation is expected to be defined before including this header
#undef RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include <string.h>     // Required for: strcpy()

#ifndef GUI_TEST_H
#define GUI_TEST_H

typedef struct {
    bool TextBox000EditMode;
    char TextBox000Text[128];

    Rectangle layoutRecs[1];

    // Custom state variables (depend on development software)
    // NOTE: This variables should be added manually if required

} GuiTESTState;

#ifdef __cplusplus
extern "C" {            // Prevents name mangling of functions
#endif

//----------------------------------------------------------------------------------
// Defines and Macros
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
// ...

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
GuiTESTState InitGuiTEST(void);
bool GuiTEST(GuiTESTState *state);


#ifdef __cplusplus
}
#endif

#endif // GUI_TEST_H

/***********************************************************************************
*
*   GUI_TEST IMPLEMENTATION
*
************************************************************************************/
#if defined(GUI_TEST_IMPLEMENTATION)

#include "raygui.h"

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Internal Module Functions Definition
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
GuiTESTState InitGuiTEST(void)
{
    GuiTESTState state = { 0 };

    state.TextBox000EditMode = false;
    strcpy(state.TextBox000Text, "x*x");

    state.layoutRecs[0] = (Rectangle){ 0, 736, 800, 64 };

    // Custom variables initialization

    return state;
}


bool GuiTEST(GuiTESTState *state)
{
    int enterPressed = GuiTextBox(state->layoutRecs[0], state->TextBox000Text, 128, state->TextBox000EditMode);
    if ((bool)enterPressed) state->TextBox000EditMode = !state->TextBox000EditMode;
    return (bool)enterPressed;
}

#endif // GUI_TEST_IMPLEMENTATION
