﻿#ifndef GAME_GAMEPROPERTIES_HPP
#define GAME_GAMEPROPERTIES_HPP

#include <color/color.hpp>
#include <color/palette.hpp>
#include <vector.hpp>
#include <string>

class GP {
public:
    GP() = delete;

    static std::string GameName() { return "Long distance runner"; }
    static std::string AuthorName() { return "Laguna_999"; }
    static std::string JamName() { return "1hgj382"; }
    static std::string JamDate() { return "2022-08-20"; }

    static jt::Vector2f GetWindowSize() { return jt::Vector2f { 1200, 800 }; }
    static float GetZoom() { return 2.0f; }
    static jt::Vector2f GetScreenSize() { return GetWindowSize() * (1.0f / GetZoom()); }

    static jt::Color PaletteBackground() { return GP::getPalette().getColor(0); }
    static jt::Color PaletteFontFront() { return GP::getPalette().getColor(3); }
    static jt::Color PaletteFontShadow() { return GP::getPalette().getColor(1); }
    static jt::Color PaletteFontCredits() { return GP::getPalette().getColor(3); }
    static jt::Color PaletteFontCreditsShadow() { return GP::getPalette().getColor(1); }

    static jt::Palette getPalette();

    static int PhysicVelocityIterations();
    static int PhysicPositionIterations();
    static jt::Vector2f PlayerSize();
};

#endif
