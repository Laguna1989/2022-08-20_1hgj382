﻿#ifndef GAME_STATE_GAME_HPP
#define GAME_STATE_GAME_HPP

#include "star.hpp"
#include "text.hpp"
#include <box2dwrapper/box2d_world_interface.hpp>
#include <game_state.hpp>
#include <memory>
#include <vector>

// fwd decls
namespace jt {
class Shape;
class Sprite;
class Vignette;
} // namespace jt

class Hud;

class StateGame : public jt::GameState {
public:
    std::string getName() const override;

private:
    std::shared_ptr<jt::Shape> m_background;
    std::shared_ptr<jt::Vignette> m_vignette;
    std::shared_ptr<Hud> m_hud;
    std::shared_ptr<jt::Box2DWorldInterface> m_world { nullptr };

    bool m_running { true };
    bool m_hasEnded { false };

    int m_scoreP1 { 0 };

    std::shared_ptr<jt::Shape> m_floor1;
    std::shared_ptr<jt::Shape> m_floor2;

    std::shared_ptr<jt::Shape> m_runner1;
    bool m_runner1ExpectedKey { false };
    float m_runner1Value { 0.0f };
    std::shared_ptr<jt::Shape> m_runner2;
    bool m_runner2ExpectedKey { false };
    float m_runner2Value { 0.0f };

    std::shared_ptr<jt::Shape> m_goal;

    std::shared_ptr<jt::Text> m_textR1;
    std::shared_ptr<jt::Text> m_textR2;
    bool m_lastBigger { false };

    std::vector<std::shared_ptr<Star>> m_stars;

    void doInternalCreate() override;
    void doInternalUpdate(float const elapsed) override;
    void doInternalDraw() const override;

    void endGame(int runner);
    void createPlayer();
    void updateLeaderText();
};

#endif
