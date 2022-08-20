#include "state_game.hpp"
#include <box2dwrapper/box2d_world_impl.hpp>
#include <color/color.hpp>
#include <game_interface.hpp>
#include <game_properties.hpp>
#include <hud/hud.hpp>
#include <screeneffects/vignette.hpp>
#include <shape.hpp>
#include <sprite.hpp>
#include <state_menu.hpp>
#include <tweens/tween_alpha.hpp>
#include <iostream>

void StateGame::doInternalCreate()
{
    m_world = std::make_shared<jt::Box2DWorldImpl>(jt::Vector2f { 0.0f, 0.0f });

    float const w = static_cast<float>(GP::GetWindowSize().x);
    float const h = static_cast<float>(GP::GetWindowSize().y);

    using jt::Shape;
    using jt::TweenAlpha;

    m_background = std::make_shared<Shape>();
    m_background->makeRect({ w, h }, textureManager());
    m_background->setColor(GP::PaletteBackground());
    m_background->setIgnoreCamMovement(true);
    m_background->update(0.0f);

    m_floor1 = std::make_shared<jt::Shape>();
    m_floor1->makeRect(jt::Vector2f { GP::GetScreenSize().x, 24 }, textureManager());
    m_floor1->setPosition(jt::Vector2f { 0, GP::GetScreenSize().y / 2 - 24 });
    m_floor1->setColor(GP::getPalette().getColor(3));

    m_floor2 = std::make_shared<jt::Shape>();
    m_floor2->makeRect(jt::Vector2f { GP::GetScreenSize().x, 24 }, textureManager());
    m_floor2->setPosition(jt::Vector2f { 0, GP::GetScreenSize().y - 24 });
    m_floor2->setColor(GP::getPalette().getColor(3));

    m_runner1 = std::make_shared<jt::Shape>();
    m_runner1->makeRect(jt::Vector2f { 24, 64 }, textureManager());
    m_runner1->setPosition(jt::Vector2f { 0, GP::GetScreenSize().y / 2 - 24 - 64 });

    m_runner2 = std::make_shared<jt::Shape>();
    m_runner2->makeRect(jt::Vector2f { 24, 64 }, textureManager());
    m_runner2->setPosition(jt::Vector2f { 0, GP::GetScreenSize().y - 24 - 64 });

    m_vignette = std::make_shared<jt::Vignette>(GP::GetScreenSize());
    add(m_vignette);
    m_hud = std::make_shared<Hud>();
    add(m_hud);

    // StateGame will call drawObjects itself.
    setAutoDraw(false);
}

void getInputRunner(std::shared_ptr<jt::Shape> runner, float& runnerValue, bool& runnerKey,
    float elapsed, jt::InputGetInterface& input, jt::KeyCode key1, jt::KeyCode key2)

{
    runnerValue -= elapsed;
    if (runnerValue <= 0.0f) {
        runnerValue = 0.0f;
    }

    auto expectedKey = key1;
    if (runnerKey) {
        expectedKey = key2;
    }
    if (input.keyboard()->justPressed(expectedKey)) {
        runnerKey = !runnerKey;
        runnerValue += 0.15f;
    }

    auto const maxSpeed = 0.6f;
    if (runnerValue >= maxSpeed) {
        runnerValue -= elapsed;
    }

    auto pos = runner->getPosition();
    pos += jt::Vector2f { elapsed * runnerValue * 13, 0 };

    runner->setPosition(pos);
}

void StateGame::doInternalUpdate(float const elapsed)
{
    if (m_running) {
        m_world->step(elapsed, GP::PhysicVelocityIterations(), GP::PhysicPositionIterations());
        // update game logic here

        getInputRunner(m_runner1, m_runner1Value, m_runner1ExpectedKey, elapsed, getGame()->input(),
            jt::KeyCode::Q, jt::KeyCode::W);

        getInputRunner(m_runner2, m_runner2Value, m_runner2ExpectedKey, elapsed, getGame()->input(),
            jt::KeyCode::O, jt::KeyCode::P);
    }

    m_background->update(elapsed);
    m_floor1->update(elapsed);
    m_floor2->update(elapsed);
    m_runner1->update(elapsed);
    m_runner2->update(elapsed);
    m_vignette->update(elapsed);
}

void StateGame::doInternalDraw() const
{
    m_background->draw(renderTarget());
    m_floor1->draw(renderTarget());
    m_floor2->draw(renderTarget());
    m_runner1->draw(renderTarget());
    m_runner2->draw(renderTarget());
    drawObjects();
    m_vignette->draw();
    m_hud->draw();
}

void StateGame::endGame()
{
    if (m_hasEnded) {
        // trigger this function only once
        return;
    }
    m_hasEnded = true;
    m_running = false;

    getGame()->stateManager().switchState(std::make_shared<StateMenu>());
}
std::string StateGame::getName() const { return "Game"; }
