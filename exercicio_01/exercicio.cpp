#include "MuMaterial.h"
#include <vector>

using namespace std;

unsigned int GetNextNoteIndex (unsigned int current_note_index);
float GetNoteDuration ();


vector<short> note_pitchs = { 60, 62, 64, 65, 67, 69, 71 };
vector<short> pitchs_change = { 16, 13, 13, 24, 24, 7, 3 };

vector<float> note_durations = { 1, 0.75, 0.5, 0.25 };
// vector<float> durations_change = {  };


int main()
{
    srand(static_cast<unsigned int>(time(0)));

    MuNote note;
    MuMaterial material;

    note.SetInstr(1);
    note.SetAmp(0.75);

    unsigned int note_index = 0;
    float note_duration = GetNoteDuration();
    note.SetPitch(note_pitchs[note_index]);
    note.SetDur(note_duration);
    material += note;

    for (unsigned int index = 0; index < 50; index++)
    {
        note_index = GetNextNoteIndex(note_index);
        note_duration = GetNoteDuration();
        note.SetPitch(note_pitchs[note_index]);
        note.SetDur(note_duration);
        material += note;
    }

    material.SetDefaultFunctionTables();
    material.Score("./score");
    material.Orchestra("./orchestra");

    return 0;
}

unsigned int GetNextNoteIndex (unsigned int current_note_index)
{
    short value = 0;
    short random_value = rand() % 100;

    for (unsigned int index = 0; index < pitchs_change.size(); index++)
    {
        value += pitchs_change[index];

        if (random_value < value) {
            short next_note_index = current_note_index + index;
            next_note_index = next_note_index % note_pitchs.size();

            return next_note_index;
        }
    }
    return pitchs_change[0];
}

float GetNoteDuration ()
{
    unsigned int index = rand() % note_durations.size();

    return note_durations[index] * 0.5;
}
