#ifndef NOTATIONREADER_H
#define NOTATIONREADER_H

#include "game_legend.h"


class NotationReader
{
public:
    NotationReader();
    void ReadGameNotationFromFile(GameLegend &gameLegend);
    void SaveGameNotationToFile(GameLegend gameLegend);

};

#endif // NOTATIONREADER_H
