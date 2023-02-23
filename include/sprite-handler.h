#pragma once

#include <concepts>
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <unordered_map>
#include <optional>
#include "sprite.h"
#include "sprite-animation.h"
#include "sprite-animation-structs.h"

class SpriteHandler {
    std::vector<Sprite> m_sprites{};
    std::unordered_map<std::string, SpriteAnimation> m_spriteAnimations{};
    // structs
    PacmanAnimations m_pacmanAnimations;
public:

    SpriteHandler() = default;

    explicit SpriteHandler(std::string_view path) noexcept;

    ~SpriteHandler() = default;

    std::optional<Sprite> getSprite(std::string_view name) const noexcept;

    void importSprites(std::string_view path) noexcept;

    void initAnimations() noexcept;

    void initStructs() noexcept;

    std::optional<SpriteAnimation> getSpriteAnimation(std::string_view name) noexcept;

    [[nodiscard]] const PacmanAnimations &pacmanAnimations() const noexcept { return m_pacmanAnimations; }


    template <typename... Args>
        requires (... && std::convertible_to<Args, std::string_view>)
    [[nodiscard]]
    std::vector<Sprite> getSprites(Args... p_sprites) const noexcept
    {
        std::array<std::string_view, sizeof...(p_sprites)> sprite_names = { { p_sprites... } };

        auto result = std::vector<Sprite>();
        std::transform(std::cbegin(sprite_names), std::cend(sprite_names),
                       std::back_inserter(result), // Write results to vector
                       [this](std::string_view p_spriteName) {
                           return getSprite(p_spriteName).value();
                       });
        return result;
    }

};