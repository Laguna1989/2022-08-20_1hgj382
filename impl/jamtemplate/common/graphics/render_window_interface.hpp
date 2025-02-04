﻿#ifndef JAMTEMPLATE_RENDERWINDOW_INTERFACE_HPP
#define JAMTEMPLATE_RENDERWINDOW_INTERFACE_HPP

#include <render_target.hpp>
#include <sprite.hpp>
#include <vector.hpp>
#include <memory>
#include <string>

namespace jt {

class RenderWindowInterface {
public:
    // no copy, no move. Avoid slicing.
    RenderWindowInterface(const RenderWindowInterface&) = delete;
    RenderWindowInterface(RenderWindowInterface&&) = delete;
    RenderWindowInterface& operator=(const RenderWindowInterface&) = delete;
    RenderWindowInterface& operator=(RenderWindowInterface&&) = delete;

    /// Destructor
    virtual ~RenderWindowInterface() = default;

    /// Check if window is open
    /// \return true if window is open, false otherwise
    virtual bool isOpen() const = 0;

    /// Check if window was closed
    virtual void checkForClose() = 0;

    /// Create the RenderTarget to render to
    /// \return shared pointer to render target
    virtual std::shared_ptr<jt::RenderTarget> createRenderTarget() = 0;

    /// Get the size of the window
    /// \return
    virtual jt::Vector2f getSize() const = 0;

    /// Draw a sprite to the window
    /// \param sprite the sprite to be drawn
    virtual void draw(std::unique_ptr<jt::Sprite>& sprite) = 0;

    /// Display the current frame
    virtual void display() = 0;

    /// Get the mouse position
    /// \return the mouse position
    virtual jt::Vector2f getMousePosition() = 0;

    /// Set the mouse cursor visible state
    /// \param visible
    virtual void setMouseCursorVisible(bool visible) = 0;

    /// Get the mouse cursor visible state
    /// \return
    virtual bool getMouseCursorVisible() const = 0;

    virtual void updateGui(float elapsed) = 0;

    virtual void startRenderGui() = 0;

    virtual bool shouldProcessKeyboard() = 0;
    virtual bool shouldProcessMouse() = 0;

protected:
    // constructor can only be called from derived classes
    RenderWindowInterface() = default;
};
} // namespace jt
#endif
