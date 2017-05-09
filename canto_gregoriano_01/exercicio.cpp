#include "MuMaterial.h"
#include <vector>

using namespace std;

vector<short> note_pitchs = { 57, 59, 60, 62, 64, 65, 67, 69, 71 };

vector<float> note_durations = { 1, 0.5 };

float bpm = 40.0;

int main()
{
    srand(static_cast<unsigned int>(time(0)));

    MuNote note;
    MuMaterial material;

    note.SetInstr(3);
    note.SetAmp(0.75);

    unsigned int current_note_index = 4;
    float note_duration = note_durations[1] * 60.0 / bpm;
    float direction = rand() % 2 == 0 ? 1 : -1;

    note.SetPitch(note_pitchs[current_note_index]);
    note.SetDur(note_duration);
    material += note;


    for (unsigned int index = 0; index < 50; index++)
    {
        int random_value = rand() % 100;

        bool is_last_note = current_note_index == 0 ||
                            current_note_index == note_pitchs.size() - 1;
        if (!is_last_note && random_value < 60)
        {
            current_note_index += direction;
            note_duration = note_durations[1] * 60.0 / bpm;
        } else {
            current_note_index -= direction;
            note_duration = note_durations[0] * 60.0 / bpm;
            direction *= -1;
        }

        note.SetPitch(note_pitchs[current_note_index]);
        note.SetDur(note_duration);
        material += note;
    }

    current_note_index -= direction;
    note_duration = note_durations[0] * 60.0 / bpm;
    note.SetPitch(note_pitchs[current_note_index]);
    note.SetDur(note_duration);
    material += note;

    material.SetDefaultFunctionTables();
    material.Score("./score");
    material.Orchestra("./orchestra");

    return 0;
}
