#include "MuMaterial.h"
#include <vector>

using namespace std;

MuMaterial InvertMelody (MuMaterial material, long first_note_number,
                         long last_note_number);
MuMaterial GetMaterialNoteBlock (MuMaterial material, long first_note_number,
                                 long last_note_number);
MuMaterial RemoveNotesFromMelody (MuMaterial material_melody,
                                  float chance_of_remove_note);

MuMaterial NewMelody (unsigned int number_of_notes);
int GetNotePitch ();
float GetNoteDuration ();

const float BPM = 120.0;

int main()
{
    MuInit();

    unsigned int number_of_notes = 4;
    MuMaterial melody_material = NewMelody(number_of_notes);

    MuMaterial material, tmp;

    material += melody_material;
    material += InvertMelody(melody_material,
                             melody_material.NumberOfNotes() / 2,
                             melody_material.NumberOfNotes() - 1);

    material.SetDefaultFunctionTables();
    material.Score("./score");
    material.Orchestra("./orchestra");

    return 0;
}

MuMaterial InvertMelody (MuMaterial material, long first_note_number,
                         long last_note_number)
{
    MuMaterial first_block_material;
    if (first_note_number > 0)
    {
        first_block_material += GetMaterialNoteBlock(material, 0,
                                                     first_note_number - 1);
    }

    MuMaterial inverted_material;
    inverted_material = GetMaterialNoteBlock(material, first_note_number,
                                             last_note_number);
    inverted_material.Invert();

    MuMaterial new_material;
    new_material += first_block_material;
    new_material += inverted_material;

    return new_material;
}

MuMaterial GetMaterialNoteBlock (MuMaterial material, long first_note_number,
                                 long last_note_number)
{
    MuMaterial material_block;

    for (int index = first_note_number; index <= last_note_number; index++)
    {
        material_block += material.GetNote(index);
    }

    return material_block;
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
    note.SetInstr(3);
    note.SetAmp(0.75);

    note.SetPitch(60);
    note.SetDur(GetNoteDuration());
    // note.SetDur(0.5 * 60.0 / BPM);

    melody_material += note;

    for (unsigned int index = 0; index < number_of_notes - 1; index++)
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
    // vector<short> note_pitchs = { 60, 62, 64, 65, 67, 69, 71 };
    vector<short> note_pitchs =       { 48, 50, 52, 53, 55, 57, 59, 60, 62, 64, 65, 67, 69, 71, 72 };
    vector<int> note_pitchs_chances = {  3,  3,  4,  6,  7,  7,  7, 15,  9,  9,  9, 9,  6,  4,  4 };
    // vector<int> note_pitchs_chances = { 20, 10, 10, 20, 20, 10, 10 };

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
    vector<float> note_durations = { 1.5, 1.25, 1, 0.75, 0.5 };
    vector<int> note_duration_chances = { 15, 10, 37, 10, 28};

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
