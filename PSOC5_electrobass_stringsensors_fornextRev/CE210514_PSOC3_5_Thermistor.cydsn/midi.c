/*==============================================================================

    leaf-midi.c
    Created: 30 Nov 2018 11:29:16am
    Author:  airship

==============================================================================*/

#if _WIN32 || _WIN64

#include "..\Inc\leaf-midi.h"

#else

#include "midi.h"
#include "main.h"
#endif

//====================================================================================
/* Stack */
//====================================================================================

tSimplePoly myPoly;
tStack myStack;

void tStack_init(tStack* const stack)
{
    tStack_initToPool(stack);
}

void    tStack_initToPool           (tStack* const stack)
{
    _tStack* ns = *stack = (_tStack*)myStack;
    
    ns->ordered = 0;
    ns->size = 0;
    ns->pos = 0;
    ns->capacity = STACK_SIZE;
    
    for (int i = 0; i < STACK_SIZE; i++) ns->data[i] = -1;
}

void    tStack_free        (tStack* const stack)
{
    _tStack* ns = *stack;
}

// If stack contains note, returns index. Else returns -1;
int tStack_contains(tStack* const stack, uint16_t noteVal)
{
    _tStack* ns = *stack;
    for (int i = 0; i < ns->size; i++)
    {
        if (ns->data[i] == noteVal)    return i;
    }
    return -1;
}

void tStack_add(tStack* const stack, uint16_t noteVal)
{
    _tStack* ns = *stack;
    
    uint8_t j;
    
    int whereToInsert = 0;
    if (ns->ordered)
    {
        for (j = 0; j < ns->size; j++)
        {
            if (noteVal > ns->data[j])
            {
                if ((noteVal < ns->data[j+1]) || (ns->data[j+1] == -1))
                {
                    whereToInsert = j+1;
                    break;
                }
            }
        }
    }
    
    //first move notes that are already in the stack one position to the right
    for (j = ns->size; j > whereToInsert; j--)
    {
        ns->data[j] = ns->data[(j - 1)];
    }
    
    //then, insert the new note into the front of the stack
    ns->data[whereToInsert] = noteVal;
    
    ns->size++;
}

int tStack_addIfNotAlreadyThere(tStack* const stack, uint16_t noteVal)
{
    _tStack* ns = *stack;
    
    uint8_t j;
    
    int added = 0;
    
    if (tStack_contains(stack, noteVal) == -1)
    {
        int whereToInsert = 0;
        if (ns->ordered)
        {
            for (j = 0; j < ns->size; j++)
            {
                if (noteVal > ns->data[j])
                {
                    if ((noteVal < ns->data[j+1]) || (ns->data[j+1] == -1))
                    {
                        whereToInsert = j+1;
                        break;
                    }
                }
            }
        }
        
        //first move notes that are already in the stack one position to the right
        for (j = ns->size; j > whereToInsert; j--)
        {
            ns->data[j] = ns->data[(j - 1)];
        }
        
        //then, insert the new note into the front of the stack
        ns->data[whereToInsert] = noteVal;
        
        ns->size++;
        
        added = 1;
    }
    
    return added;
}

// Remove noteVal. return 1 if removed, 0 if not
int tStack_remove(tStack* const stack, uint16_t noteVal)
{
    _tStack* ns = *stack;
    
    uint8_t k;
    int foundIndex = tStack_contains(stack, noteVal);
    int removed = 0;
    
    if (foundIndex >= 0)
    {
        for (k = 0; k < (ns->size - foundIndex); k++)
        {
            if ((k+foundIndex) >= (ns->capacity - 1))
            {
                ns->data[k + foundIndex] = -1;
            }
            else
            {
                ns->data[k + foundIndex] = ns->data[k + foundIndex + 1];
                if ((k + foundIndex) == (ns->size - 1))
                {
                    ns->data[k + foundIndex + 1] = -1;
                }
            }
            
        }
        // in case it got put on the stack multiple times
        foundIndex--;
        ns->size--;
        removed = 1;
    }
    
    return removed;
}

// Doesn't change size of data types
void tStack_setCapacity(tStack* const stack, uint16_t cap)
{
    _tStack* ns = *stack;
    
    if (cap <= 0)
        ns->capacity = 1;
    else if (cap <= STACK_SIZE)
        ns->capacity = cap;
    else
        ns->capacity = STACK_SIZE;
    
    for (int i = cap; i < STACK_SIZE; i++)
    {
        if ((int)ns->data[i] != -1)
        {
            ns->data[i] = -1;
            ns->size -= 1;
        }
    }
    
    if (ns->pos >= cap)
    {
        ns->pos = 0;
    }
}

int tStack_getSize(tStack* const stack)
{
    _tStack* ns = *stack;
    
    return ns->size;
}

void tStack_clear(tStack* const stack)
{
    _tStack* ns = *stack;
    
    for (int i = 0; i < STACK_SIZE; i++)
    {
        ns->data[i] = -1;
    }
    ns->pos = 0;
    ns->size = 0;
}

// Next item in order of addition to stack. Return 0-31 if there is a next item to move to. Returns -1 otherwise.
int tStack_next(tStack* const stack)
{
    _tStack* ns = *stack;
    
    int step = 0;
    if (ns->size != 0) // if there is at least one note in the stack
    {
        if (ns->pos > 0) // if you're not at the most recent note (first one), then go backward in the array (moving from earliest to latest)
        {
            ns->pos--;
        }
        else
        {
            ns->pos = (ns->size - 1); // if you are the most recent note, go back to the earliest note in the array
        }
        
        step = ns->data[ns->pos];
        return step;
    }
    else
    {
        return -1;
    }
}

int tStack_get(tStack* const stack, int which)
{
    _tStack* ns = *stack;
    return ns->data[which];
}

int tStack_first(tStack* const stack)
{
    _tStack* ns = *stack;
    return ns->data[0];
}

int   LEAF_clipInt(int min, int val, int max)
{
    int tempmin = min;
    int tempmax = max;
    if (min > max)
    {
        tempmin = max;
        tempmax = min;
    }
    if (val < tempmin) {
        return tempmin;
    } else if (val > tempmax) {
        return tempmax;
    } else {
        return val;
    }
}


//tSimplePoly = much more efficient implementation without ramps and glide


// SIMPLE POLY
void tSimplePoly_init(tSimplePoly* const polyh)
{
    tSimplePoly_initToPool(polyh);
}

int voices[4][3];


void    tSimplePoly_initToPool            (tSimplePoly* const polyh)
{

    _tSimplePoly* poly = *polyh = (_tSimplePoly*)myPoly;

    poly->numVoices = 1;
    poly->maxNumVoices = 4;

    for (int i = 0; i < 128; i++)
    {
        poly->notes[i][0] = -1;
        poly->notes[i][1] = 0;
    }
    poly->stealing_on = 1;
    poly->recover_stolen = 1;
    poly->voices = (int**) voices;

    for (int i = 0; i < poly->maxNumVoices; ++i)
    {
        poly->voices[i][0] = -1;
    }
    tStack_initToPool(&poly->stack);

}

void    tSimplePoly_free  (tSimplePoly* const polyh)
{
    _tSimplePoly* poly = *polyh;

}

int tSimplePoly_noteOn(tSimplePoly* const polyh, int note, uint8_t vel)
{
    _tSimplePoly* poly = *polyh;
    int whichVoice, whichNote, oldNote, alteredVoice;
    // if not in keymap or already on stack, dont do anything. else, add that note.
    if (tStack_contains(&poly->stack, note) >= 0) return -1;
    else
    {
        alteredVoice = -1;
        int found = 0;
        for (int i = 0; i < poly->numVoices; i++)
        {
            if (poly->voices[i][0] == -1)    // if inactive voice, give this note to voice
            {

                found = 1;

                poly->voices[i][0] = note;
                poly->voices[i][1] = vel;
                poly->notes[note][0] = i;
                poly->notes[note][1] = vel;
                poly->voices[i][2] = note; // voices[i][2] is the output midi note, (avoiding the -1 when a voice is inactive)

                alteredVoice = i;
                tStack_add(&poly->stack, note);
                break;
            }
        }
        if (!found)
        {
            //second preference is grabbing one that is in release phase but not finished sounding yet
            for (int i = 0 ; i < poly->numVoices; i++)
            {
                if (poly->voices[i][0] == -2)    // if voice is released but still sounding, take over this voice
                {

                    found = 1;

                    poly->voices[i][0] = note;
                    poly->voices[i][1] = vel;
                    poly->notes[note][0] = i;
                    poly->notes[note][1] = vel;
                    poly->voices[i][2] = note; // voices[i][2] is the output midi note, (avoiding the -1 when a voice is inactive)

                    alteredVoice = i;
                    tStack_add(&poly->stack, note);
                    break;
                }
            }
        }
        if ((!found) && (poly->stealing_on)) //steal
        {
            for (int j = tStack_getSize(&poly->stack) - 1; j >= 0; j--)
            {
                whichNote = tStack_get(&poly->stack, j);
                whichVoice = poly->notes[whichNote][0];
                if (whichVoice >= 0)
                {
                    oldNote = poly->voices[whichVoice][0];
                    poly->voices[whichVoice][0] = note;
                    poly->voices[whichVoice][1] = vel;
                    poly->notes[oldNote][0] = -3; //mark the stolen voice as stolen (in the second dimension of the notes array)
                    poly->notes[note][0] = whichVoice;
                    poly->notes[note][1] = vel;

                    poly->voices[whichVoice][2] = note;

                    alteredVoice = whichVoice;
                    tStack_add(&poly->stack, note);
                    break;
                }
            }
        }
        return alteredVoice;
    }
}



int tSimplePoly_noteOff(tSimplePoly* const polyh, uint8_t note)
{
    _tSimplePoly* poly = *polyh;
    int16_t noteToTest = -1;

    tStack_remove(&poly->stack, note);
    poly->notes[note][0] = -1;

    int deactivatedVoice = -1;
    for (int i = 0; i < poly->maxNumVoices; i++)
    {
        if (poly->voices[i][0] == note)
        {
            poly->voices[i][0] = -1;
            poly->voices[i][1] = 0;
            deactivatedVoice = i;
            break;
        }
    }

    if (poly->recover_stolen)
    {
        //grab old notes off the stack if there are notes waiting to replace the free voice
        if (deactivatedVoice >= 0)
        {
            for (int j = 0; j < tStack_getSize(&poly->stack); ++j)
            {
                noteToTest = tStack_get(&poly->stack, j);

                if (poly->notes[noteToTest][0] == -3) //if there is a stolen note waiting (marked inactive but on the stack)
                {
                    poly->voices[deactivatedVoice][0] = noteToTest; //set the newly free voice to use the old stolen note
                    poly->voices[deactivatedVoice][1] = poly->notes[noteToTest][1]; // set the velocity of the voice to be the velocity of that note
                    poly->voices[deactivatedVoice][2] = noteToTest;
                    poly->notes[noteToTest][0] = deactivatedVoice; //mark that it is no longer stolen and is now active
                    return -1;
                }
            }
        }
    }
    return deactivatedVoice;
}


void tSimplePoly_deactivateVoice(tSimplePoly* const polyh, uint8_t voice)
{
    _tSimplePoly* poly = *polyh;

    if (poly->voices[voice][0] == -2) //only do this if the voice is waiting for deactivation (not already reassigned while waiting)
    {
        poly->voices[voice][0] = -1;
        poly->voices[voice][1] = 0;
        if (poly->recover_stolen)
        {
            //grab old notes off the stack if there are notes waiting to replace the free voice
            for (int j = 0; j < tStack_getSize(&poly->stack); ++j)
            {
                int  noteToTest = tStack_get(&poly->stack, j);

                if (poly->notes[noteToTest][0] == -3) //if there is a stolen note waiting (marked inactive but on the stack)
                {
                    poly->voices[voice][0] = noteToTest; //set the newly free voice to use the old stolen note
                    poly->voices[voice][1] = poly->notes[noteToTest][1]; // set the velocity of the voice to be the velocity of that note
                    poly->voices[voice][2] = noteToTest;
                    poly->notes[noteToTest][0] = voice; //mark that it is no longer stolen and is now active
                }
            }
        }
    }
}

int tSimplePoly_findVoiceAssignedToNote(tSimplePoly* const polyh, uint8_t note)
{
    _tSimplePoly* poly = *polyh;


    int voiceWithThatNote = -1;
    for (int i = 0; i < poly->maxNumVoices; i++)
    {
        if (poly->voices[i][0] == note)
        {
            voiceWithThatNote = i;
            break;
        }
    }
    return voiceWithThatNote;
}


int tSimplePoly_markPendingNoteOff(tSimplePoly* const polyh, uint8_t note)
{
    _tSimplePoly* poly = *polyh;
    int deactivatedVoice = -1;

    if (tStack_remove(&poly->stack, note))
    {
        poly->notes[note][0] = -2;
        
        for (int i = 0; i < poly->maxNumVoices; i++)
        {
            if (poly->voices[i][0] == note)
            {
                poly->voices[i][0] = -2;
                poly->voices[i][1] = 0;
                deactivatedVoice = i;
                break;
            }
        }
    }
    return deactivatedVoice;
}

void tSimplePoly_setNumVoices(tSimplePoly* const polyh, uint8_t numVoices)
{
    _tSimplePoly* poly = *polyh;
    poly->numVoices = (numVoices > poly->maxNumVoices) ? poly->maxNumVoices : numVoices;
}


int tSimplePoly_getNumVoices(tSimplePoly* const polyh)
{
    _tSimplePoly* poly = *polyh;
    return poly->numVoices;
}

int tSimplePoly_getNumActiveVoices(tSimplePoly* const polyh)
{
    _tSimplePoly* poly = *polyh;
    return LEAF_clipInt(0, tStack_getSize(&poly->stack), poly->numVoices);
}


int tSimplePoly_getPitch(tSimplePoly* const polyh, uint8_t voice)
{
    _tSimplePoly* poly = *polyh;
    return poly->voices[voice][2];
}

//this one returns negative one if the voice is inactive
int tSimplePoly_getPitchAndCheckActive(tSimplePoly* const polyh, uint8_t voice)
{
    _tSimplePoly* poly = *polyh;
    return poly->voices[voice][0];
}

int tSimplePoly_getVelocity(tSimplePoly* const polyh, uint8_t voice)
{
    _tSimplePoly* poly = *polyh;
    return poly->voices[voice][1];
}

int tSimplePoly_isOn(tSimplePoly* const polyh, uint8_t voice)
{
    _tSimplePoly* poly = *polyh;
    return (poly->voices[voice][0] > 0) ? 1 : 0;
}
