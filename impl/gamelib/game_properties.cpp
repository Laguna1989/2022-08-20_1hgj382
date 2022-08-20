#include "game_properties.hpp"

jt::Palette GP::getPalette()
{
    static auto const p = jt::Palette::parseGPL(R"(GIMP Palette
#Palette Name: LIBRA-8
#Description:
#Colors: 8
86	70	94	56465e
142	55	133	8e3785
192	67	148	c04394
231	174	67	e7ae43
205	205	116	cdcd74
126	168	129	7ea881
241	237	215	f1edd7
255	181	135	ffb587
)");
    return p;
}

int GP::PhysicVelocityIterations() { return 20; }

int GP::PhysicPositionIterations() { return 20; }
jt::Vector2f GP::PlayerSize() { return jt::Vector2f { 16.0f, 16.0f }; }
