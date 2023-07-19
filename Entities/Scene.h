#pragma once

#include <string>
#include "../Misc/Scrap.h"
#include "Entity.h"
#include "Carriage.h"
#include "Block.h"
#include "Ball.h"
#include "Wall.h"
#include "KillZone.h"
#include "Hud.h"
#include "Bonus.h"

class Scene : public Entity {
public:
    constexpr static Color DefaultColor = 0x00AABBCC;

    constexpr static float SceneWidth = 1024.0f;
    constexpr static float SceneHeight = 768.0f;

    constexpr static float FieldBaseX = 50.0f;
    constexpr static float FieldBaseY = 50.0f;

    constexpr static float FieldSizeX = SceneWidth - FieldBaseX;
    constexpr static float FieldSizeY = SceneHeight - FieldBaseY;

    constexpr static size_t Rows = 10;
    constexpr static size_t Columns = 30;
    constexpr static float BlockSpacing = 10.0f;
    constexpr static float BlockSize = 20.0f;
    constexpr static Color BlockColor = DefaultColor;
    constexpr static float BlockArrayBaseX = FieldBaseX + 15.0f;
    constexpr static float BlockArrayBaseY = FieldBaseY + 360.0f;

    constexpr static float CarriageSensitivity = 600.0f;
    constexpr static float CarriageWidth = 200.0f;
    constexpr static float CarriageHeight = 15.0f;
    constexpr static float CarriageOffsetX = (SceneWidth - CarriageWidth) / 2.0f;
    constexpr static float CarriageOffsetY = FieldBaseY + 10.0f;
    constexpr static Color CarriageColor = DefaultColor;

    constexpr static float BallSize = 25.0f;
    constexpr static float BallGap = 5.0f;
    constexpr static float BallBaseVelocity = 500.0f;
//    constexpr static float BallBaseVelocity = 0.0f;
    constexpr static Color KillZoneColor = 0x00'AA0000;

    constexpr static Color BallColor = 0x00'FFA500;

    constexpr static float HudBaseX = 20.0f;
    constexpr static float HudBaseY = 30.0f;

    constexpr static float BonusSize = 10.0f;
    constexpr static float BonusVelocity = 400.0f;
    constexpr static Color BonusColor = 0x00'00AA00;
    constexpr static size_t BonusKillCount = 4;
    constexpr static float BonusProbability = 0.0f;

    constexpr static Color ScreenEdgeColor = 0x00'FFFFFF;

    explicit Scene() : Entity() {

    }

    static int ScaleX(float x) { return static_cast<int>(x * ScaleWidth); }

    static int ScaleY(float y) { return static_cast<int>(y * ScaleHeight); }

    static void RemapPoint(const Point& point, int& i, int& j) {
        i = SCREEN_HEIGHT - ScaleY(point.y) - 1;
        j = ScaleX(point.x);

        if (i < 0 || i >= SCREEN_HEIGHT)
            throw std::runtime_error("Point out of screen by Y-axis");

        if (j < 0 || j >= SCREEN_WIDTH)
            throw std::runtime_error("Point out of screen by X-axis");
    }

    void Construct() override {
        m_initialized = true;

        BindComponent<Mesh>();
        BindComponent<Controller>();
        BindComponent<Dynamic>();

        SpawnChildEntityAt<KillZone>({0, 0}, SceneWidth, true, ScreenEdgeColor);
        SpawnChildEntityAt<KillZone>({0, 0}, SceneHeight, false, ScreenEdgeColor);
        SpawnChildEntityAt<KillZone>({0, SceneHeight}, SceneWidth, true, ScreenEdgeColor);
        SpawnChildEntityAt<KillZone>({SceneWidth, 0}, SceneHeight, false, ScreenEdgeColor);

        SpawnChildEntityAt<KillZone>({FieldBaseX, FieldBaseY}, FieldSizeX - FieldBaseX, true, KillZoneColor);
//        SpawnChildEntityAt<Wall>({FieldBaseX, FieldBaseY}, FieldSizeX - FieldBaseX, true, KillZoneColor);
        SpawnChildEntityAt<Wall>({FieldBaseX, FieldBaseY}, FieldSizeX - FieldBaseX, true, KillZoneColor);
        SpawnChildEntityAt<Wall>({FieldBaseX, FieldSizeY}, FieldSizeX - FieldBaseX, true, DefaultColor);

        SpawnChildEntityAt<Wall>({FieldBaseX, FieldBaseY}, FieldSizeY - FieldBaseY, false, DefaultColor);
        SpawnChildEntityAt<Wall>({FieldSizeX, FieldBaseY}, FieldSizeY - FieldBaseY, false, DefaultColor);

        m_hud = SpawnChildEntityAt<Hud>({HudBaseX, HudBaseY}, DefaultColor);

        m_carriage = SpawnChildEntityAt<Carriage>(
                {CarriageOffsetX, CarriageOffsetY},
                CarriageWidth,
                CarriageHeight,
                CarriageColor,
                CarriageSensitivity);

        const auto blockStepX = BlockSpacing + BlockSize;
        const auto blockStepY = BlockSpacing + BlockSize;
        for (size_t i = 0; i < Rows; i++) {
            for (size_t j = 0; j < Columns; j++) {
                auto x = static_cast<float>(j) * blockStepX;
                auto y = static_cast<float>(i) * blockStepY;
                auto block = SpawnChildEntityAt<Block>(
                        {BlockArrayBaseX + x, BlockArrayBaseY + y},
                        BlockSize,
                        BlockColor);
                m_blockCount++;
            }
        }

        SetHudBlockRemain();
    }

    void SpawnBall() {
        auto mesh = std::dynamic_pointer_cast<CubeMesh>(m_carriage->GetComponent<Mesh>());
        auto origin = mesh->GetOrigin();
        auto width = mesh->GetWidth();
        auto height = mesh->GetHeight();
        m_ball = SpawnChildEntityAt<Ball>(
                {origin.x + width / 2.0f, origin.y + height + BallGap},
                BallSize,
                BallBaseVelocity,
                BallColor);
    }

    bool IsGameEnd() const {
        return m_initialized && (!m_ball.lock() || m_blockCount == 0);
    }

    void KillBlock(std::shared_ptr<Block> block, bool spawnBonus) {
        m_blockCount--;
        block->ScheduleKill();
        SetHudBlockRemain();
        if (spawnBonus) {
            auto roll = RandomFloat(0.0f, 1.0f);
            if (roll > BonusProbability) {
                return;
            }

            auto mesh = std::dynamic_pointer_cast<CubeMesh>(block->GetComponent<Mesh>());
            auto origin = mesh->GetOrigin();
            auto width = mesh->GetWidth();
            auto height = mesh->GetHeight();
            SpawnChildEntityAt<Bonus>(
                    {origin.x + (width - BonusSize) / 2.0f, (origin.y - BonusSize) + height / 2.0f},
                    BonusSize,
                    BonusVelocity,
                    BonusColor,
                    BonusKillCount);
        }
    }

private:
    void SetHudBlockRemain() {
        auto text = std::string{"Blocks remain: "} + std::to_string(m_blockCount);
        m_hud->SetBlockRemain(text);
    }

    bool m_initialized = false;
    size_t m_blockCount = {};

    std::shared_ptr<Carriage> m_carriage = {};
    std::shared_ptr<Hud> m_hud = {};
    std::weak_ptr<Ball> m_ball = {};

    constexpr static float ScaleWidth = float(SCREEN_WIDTH - 1) / SceneWidth;
    constexpr static float ScaleHeight = float(SCREEN_HEIGHT - 1) / SceneHeight;
};