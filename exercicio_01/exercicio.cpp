#include "MuMaterial.h"
#include <vector>

using namespace std;

unsigned int GetNextNoteIndex (unsigned int current_note_index);


vector<short> note_values = { 60, 62, 64, 65, 67, 69, 71 };
vector<short> note_chance = { 15, 15, 30, 30, 7, 3 };


int main()
{
    srand(static_cast<unsigned int>(time(0)));

    MuNote note;
    MuMaterial material;

    note.SetInstr(1);
    note.SetDur(0.5);
    note.SetAmp(0.75);

    unsigned int note_index = 0;
    note.SetPitch(note_values[note_index]);
    material += note;

    for (unsigned int index = 0; index < 20; index++)
    {
        note_index = GetNextNoteIndex(note_index);
        note.SetPitch(note_values[note_index]);
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

    for (int index = 0; index < note_chance.size(); index++)
    {
        value += note_chance[index];

        if (random_value < value) {
            short next_note_index = current_note_index + index;
            next_note_index = next_note_index % note_values.size();

            return next_note_index;
        }
    }
    return note_chance[0];
}
