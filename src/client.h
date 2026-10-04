// Reading the running client: the camera's and the local player's world positions. See client.cpp.
#pragma once

bool ClientCamera(float cam[3]);      // camera world position
bool ClientPlayer(float pos[3], bool* onShip = nullptr);   // local player world position (feet); on a ship
                                                          // or zeppelin, the camera's (see client.cpp)
bool ClientPlayerMounted(bool& mounted);   // whether the local player rides a mount
bool ClientHour(float& hour);         // the game's time of day, 0..24
int  ClientUnits(float (*out)[3], int max);   // every unit and player's world position (feet); the count
bool ClientMapName(char* out, int size);   // the current map's folder name ("Azeroth", "Kalimdor")

// A game object the server spawned (a torch, a lamppost, a brazier no map file places).
struct ClientObject
{
    float    pos[3];    // world position
    float    facing;    // radians about z, counter-clockwise from +x
    float    scale;
    unsigned display;   // GameObjectDisplayInfo.dbc row
};
int  ClientGameObjects(ClientObject* out, int max);   // every game object; the count

// Every player's position and facing, with a window of their update fields (2026-10-04): the visible item
// entries sit in it ([itemlights] fieldFrom..fieldTo, counted in dwords from the start of the fields).
constexpr int kClientFieldWindow = 0x100;   // dwords of fields a player entry holds, at most
struct ClientPlayerInfo
{
    float    pos[3];                        // world position (feet); on a ship, relative to the ship
    float    facing;                        // radians about z, counter-clockwise from +x
    bool     local;                         // the local player
    unsigned fields[kClientFieldWindow];    // fields fieldFrom .. fieldTo - 1
};
int  ClientPlayers(ClientPlayerInfo* out, int max, unsigned fieldFrom, unsigned fieldTo);   // the count
