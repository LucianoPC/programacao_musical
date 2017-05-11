#include "MuMaterial.h"
#include <vector>

using namespace std;

MuMaterial NewMelody (unsigned int number_of_notes);
int GetNotePitch ();
float GetNoteDuration ();

float BPM = 90.0;

int main()
{
    MuInit();

    unsigned int number_of_notes = Between(4, 8);
    MuMaterial melody_material = NewMelody(number_of_notes);

    melody_material.SetDefaultFunctionTables();
    melody_material.Score("./score");
    melody_material.Orchestra("./orchestra");

    return 0;
}

MuMaterial NewMelody (unsigned int number_of_notes)
{
    MuMaterial melody_material;
    MuNote note;
    note.SetInstr(2);
    note.SetAmp(0.75);

    note.SetPitch(60);
    note.SetDur(GetNoteDuration());
    // note.SetDur(0.5 * 60.0 / BPM);

    melody_material += note;

    for (unsigned int index = 0; index < number_of_notes; index++)
    {
        int note_pitch = GetNotePitch();
        float note_duration = GetNoteDuration();
        note.SetPitch(note_pitch);
        note.SetDur(note_duration);

        melody_material += note;
    }

    return melody_material;
}

int GetNotePitch ()
{
    int random_value = rand() % 100;
    vector<short> note_pitchs = { 60, 62, 64, 65, 67, 69, 71 };
    // vector<int> note_pitchs_chances = { 25, 10, 15, 20, 20, 5, 5 };
    vector<int> note_pitchs_chances = { 20, 10, 10, 20, 20, 10, 10 };

    int pitch_chance = 0;

    for (unsigned int index = 0; index < note_pitchs.size(); index++)
    {
        pitch_chance += note_pitchs_chances[index];

        if (random_value < pitch_chance) {
            return note_pitchs[index];
        }
    }

    return note_pitchs[0];
}

float GetNoteDuration ()
{
    int random_value = rand() % 100;
    vector<float> note_durations = { 1.5, 1.25, 1, 0.75, 0.5, 0.25 };
    vector<int> note_duration_chances = { 22, 10, 22, 10, 26, 10 };

    int duration_chance = 0;

    for (unsigned int index = 0; index < note_durations.size(); index++)
    {
        duration_chance += note_duration_chances[index];

        if (random_value < duration_chance) {
            return note_durations[index] * 60.0 / BPM;
        }
    }

    return 0.5;
}
