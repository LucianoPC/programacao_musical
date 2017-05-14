#include "MuMaterial.h"
#include <vector>

using namespace std;


MuMaterial NewMelody (unsigned int number_of_notes);
MuMaterial NewMotive (MuMaterial melody_material);
MuMaterial NewMotive (MuMaterial material_original,
                      MuMaterial material_changed);
MuNote CreateNote ();
int GetNotePitch ();
float GetNoteDuration ();


float BPM = 90.0;


int main()
{
    srand(static_cast<unsigned int>(time(0)));

    MuMaterial material;

    unsigned int number_of_notes = (rand() % 4) + 5;
    MuMaterial melody_material = NewMelody(number_of_notes);

    MuMaterial motive = NewMotive(melody_material);


    material += melody_material;

    unsigned int number_of_motives = (rand() % 2) + 2;
    for(unsigned int index = 0; index < number_of_motives; index++)
    {
        motive = NewMotive(melody_material, motive);
        material += motive;
    }

    MuNote note = CreateNote();
    note.SetPitch(60);
    note.SetDur(1.0 * 60.0 / BPM);
    material += note;

    note.SetPitch(65);
    note.SetDur(1.0 * 60.0 / BPM);
    material += note;

    note.SetPitch(60);
    note.SetDur(0.5 * 60.0 / BPM);
    material += note;

    material.SetDefaultFunctionTables();
    material.Score("./score");
    material.Orchestra("./orchestra");

    return 0;
}

MuMaterial NewMotive (MuMaterial material_original,
                      MuMaterial material_changed)
{
    int random_value = rand() % 100;
    int material_original_chance = 60;

    if (random_value < material_original_chance) {
        return NewMotive(material_original);
    } else {
        return NewMotive(material_changed);
    }
}

MuMaterial NewMotive (MuMaterial material)
{
    vector<int> options = { 0, 1, 2, 3, 4, 5 };
    vector<int> option_chances = { 5, 60, 15, 15, 30, 50 };

    MuMaterial motive = material;

    for (unsigned int index = 0; index < options.size(); index++)
    {
        int random_value = rand() % 100;
        int chance = option_chances[index];

        if (random_value < chance) {
            if(options[index] == 1)
            {
                unsigned int operations = (rand() % 5) + 1;
                for (int i = 0; i < operations; i++)
                {
                    cout << "Invert" << endl;
                    motive.Invert();
                }
            }
            else if(options[index] == 2)
            {
                motive.Retro();
            }
            else if(options[index] == 3)
            {
                cout << "ExpandInterval" << endl;
                motive.ExpandInterval(Between(1, 3));
            }
            else if(options[index] == 4)
            {
                cout << "CyclePitch" << endl;
                motive.CyclePitch(0, Between(1, 2));
            }
            else if(options[index] == 5)
            {
                cout << "DiatonicTranspose" << endl;
                unsigned int transpose = (rand() % 5) + 1;
                motive.DiatonicTranspose(0,MAJOR_MODE,transpose,ASCENDING);
            }
        }
    }

    return motive;
}

MuMaterial NewMelody (unsigned int number_of_notes)
{
    MuMaterial melody_material;
    MuNote note = CreateNote();

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

MuNote CreateNote ()
{
    MuNote note;
    note.SetInstr(2);
    note.SetAmp(0.75);

    return note;
}

int GetNotePitch ()
{
    int random_value = rand() % 100;
    vector<short> note_pitchs = { 60, 62, 64, 65, 67, 69, 71 };
    vector<int> note_pitchs_chances = { 25, 10, 15, 20, 20, 5, 5 };
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
