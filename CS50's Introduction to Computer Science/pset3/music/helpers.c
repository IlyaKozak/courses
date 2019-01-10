// Helper functions for music

#include <cs50.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
// X and Y as integers
    int x = fraction[0] - 48;
    int y = fraction[2] - 48;
    if (y == 8)
    {
        return x;
    }
    else
    {
        int mult = 8 / y;
        return mult * x;
    }
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    float f;

// Calculates frequencies of notes. The frequency, f, of some note is 2 to power of n/12 multiplied by 440, where n is the number of semitones from that note to A4.
    switch (note[0])
    {
        case 'C':
            f = 440.0 / pow(2.0, (9.0 / 12.0));
            break;
        case 'D':
            f = 440.0 / pow(2.0, (7.0 / 12.0));
            break;
        case 'E':
            f = 440.0 / pow(2.0, (5.0 / 12.0));
            break;
        case 'F':
            f = 440.0 / pow(2.0, (4.0 / 12.0));
            break;
        case 'G':
            f = 440.0 / pow(2.0, (2.0 / 12.0));
            break;
        case 'A':
            f = 440.0;
            break;
        case 'B':
            f = 440.0 * pow(2.0, (2.0 / 12.0));
            break;
        default:
            return 0;
    }

// Depending on octave frequency is adjusted
    int octave = note[strlen(note) - 1] - 48;

    if (4 - octave > 0)
    {
        f /= 2 * (4 - octave);
    }
    else if (4 - octave < 0)
    {
        f *= 2 * (octave - 4);
    }

// If there is an accidental (# or b) pitch of a note is adjusted by one semitone (higher or lower)
    if (note[1] == 'b')
    {
        f /= pow(2.0, (1.0 / 12.0));
    }
    else if (note[1] == '#')
    {
        f *= pow(2.0, (1.0 / 12.0));
    }

    int f_int = round(f);
    return f_int;
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    if (strcmp(s, "") == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
