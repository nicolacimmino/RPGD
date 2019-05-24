//
// DiceThrow represents a single throw of an arbitrary amount of dice all with the same,
// arbitrary, amount of faces.
//
//  Copyright (C) 2019 Nicola Cimmino
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//   This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see http://www.gnu.org/licenses/.
//

#include "DiceThrow.h"

DiceThrow::DiceThrow(uint8_t diceCount, uint8_t dieFaces, TRNG *trng)
{
    this->diceCount = diceCount;
    this->dieFaces = dieFaces;
    this->trng = trng;
    this->description = new char[20];
    this->results = new uint8_t[diceCount];
}

DiceThrow::~DiceThrow()
{
    delete[] this->description;
    delete[] this->results;
}

uint8_t DiceThrow::GetDiceCount()
{
    return this->diceCount;
}

uint8_t DiceThrow::GetDieFaces()
{
    return this->dieFaces;
}

char *DiceThrow::GetTextualDescription()
{
    sprintf(this->description, "%d x D%d", this->diceCount, this->dieFaces);

    return this->description;
}

uint8_t *DiceThrow::Throw()
{
    for (int ix = 0; ix < this->diceCount; ix++)
    {
        while(!trng->isRandomDataReady()) {
            trng->loop();
        }

        this->results[ix] = 1 + (trng->getRandomByte() % this->dieFaces);
    }

    return this->results;
}
