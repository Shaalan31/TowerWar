#include"LoadFunction.h"
#pragma once

//function to check if all towers are dead
bool TowersAreDead(castle C);

//function to determine if game is win or loss
bool GameResult(castle C, ListE* Active[], QueueE* InActive);