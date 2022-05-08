#pragma once
#include <iostream>
#include <ctime>
#include <string>
#include "winner.h"
#include "game.h"
#include "util.h"

//// + Initializing the static field of the main game class
Game* Game::game_instance = nullptr;
//// - 
