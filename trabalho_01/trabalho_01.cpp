#include "MuMaterial.h"
#include <vector>

using namespace std;

MuMaterial RemoveNotesFromMelody (MuMaterial material_melody,
                                  float chance_of_remove_note);

MuMaterial NewMelody (unsigned int number_of_notes);
int GetNotePitch ();
float GetNoteDuration ();

const float BPM = 120.0;

int main()
{
    MuInit();

    unsigned int number_of_notes = Between(4, 8);
    MuMaterial melody_material = NewMelody(number_of_notes);

    MuMaterial material;
    material += melody_material;
    material += RemoveNotesFromMelody(melody_material, 0.25f);
    material += RemoveNotesFromMelody(melody_material, 0.50f);
    material += RemoveNotesFromMelody(melody_material, 0.75f);
    material += RemoveNotesFromMelody(melody_material, 1.0f);


    material.SetDefaultFunctionTables();
    material.Score("./score");
    material.Orchestra("./orchestra");

    return 0;
}

MuMaterial RemoveNotesFromMelody (MuMaterial material_melody,
                                  float chance_of_remove_note)
{
    MuMaterial material;
    long number_of_notes = material_melody.NumberOfNotes();

    material += material_melody.GetFirstNote();

    for (int index = 1; index < (number_of_notes - 1); index++)
    {
        float sorted_number = Between(0.0f, 1.0f);
        bool use_note = sorted_number > chance_of_remove_note;
        if (use_note) material += material_melody.GetNote(index);
    }

    material += material_melody.GetNote(number_of_notes - 1);

    material.Fit(material_melody.Dur());

    return material;
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
