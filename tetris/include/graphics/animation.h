#pragma once
#include <engine/game_object.h>
#include <graphics/drawable_object.h>
#include <graphics/shapes.h>
#include <raylib/raylib.h>
#include <vector>

class AnimationCommand
{
public:
    AnimationCommand (int maxFrames):
        m_maxFrames (maxFrames)
    {}

    void AnimateFrame (int currentFrame, DrawableObject* obj) {
        if (currentFrame <= m_maxFrames) {
            AnimateFrameImpl (currentFrame, obj);
        }
    }

protected:
    virtual void AnimateFrameImpl (int currentFrame, DrawableObject* obj) = 0;

protected:
    int m_maxFrames;
};

class Sequence
{
public:
    Sequence():
        m_currentFrame (0),
        m_sequenceLength (0)
    {}
    ~Sequence();

    Sequence (Sequence&& seq)
    {
        m_currentFrame = seq.m_currentFrame;
        m_sequenceLength = seq.m_sequenceLength;
        m_animationCommands = std::move (seq.m_animationCommands);
    }

public:
    bool CanPerform() const { return m_currentFrame < m_sequenceLength; }
    void PerformAnimation (DrawableObject* obj);
    int GetFrameLength() const { return m_sequenceLength; }
    void Reset() { m_currentFrame = 0; }

public:
    void AddMoveCommand (int frameLength, Vector2 translation);
    void AddScaleCommand (int frameLength, float scale);
    void AddSetPositionCommand (int frameLength, Vector2 targetPosition);
    void AddChangeColorCommand (int frameLength, Color targetColor);
    void AddChangeOpacityCommand (int frameLength, unsigned char opacity);
    void AddSetOpacityCommand (int frameLength, unsigned char opacity);
    void AddSetColorCommand (int frameLength, Color targetColor);

private:
    int                             m_currentFrame;
    int                             m_sequenceLength;
    std::vector <AnimationCommand*> m_animationCommands;
};


class Animation: public DrawableObject, public GameObject
{
public:
    Animation (DrawableObject* obj):
        m_obj (obj),
        m_initialPos (obj->GetPosition()),
        m_bIsPlaying (false),
        m_bIsLooping (false),
        m_currentSequenceIdx (0)
    {
        m_pos = obj->GetPosition();
    }

    virtual void Tick() override;
    void Play() { m_bIsPlaying = true; }
    void Pause() { m_bIsPlaying = false;}
    bool IsPlaying() const { return m_bIsPlaying; }
    void EnableLooping() { m_bIsLooping = true; };
    void AddSequence (Sequence&& seq) { m_animationSequences.push_back (std::move (seq)); }

    virtual void SetAlpha (unsigned char alpha) override;
    virtual void Draw() const override;
    virtual BoundingBox2d GetBoundingBox() const override;
    virtual void Translate (const Vector2& translation) override;
    virtual void Scale (float scale) override;

protected:
    void ResetObjectState();

protected:
    DrawableObject*        m_obj;
    Vector2                m_initialPos;
    bool                   m_bIsPlaying;
    bool                   m_bIsLooping;
    size_t                 m_currentSequenceIdx;
    std::vector <Sequence> m_animationSequences;
};


class MoveAnimationCommand: public AnimationCommand
{
public:
    MoveAnimationCommand (Vector2 translation, int maxFrames):
        AnimationCommand (maxFrames),
        m_translation (translation)
    {}

protected:
    virtual void AnimateFrameImpl (int currentFrame, DrawableObject* obj) override;

private:
    Vector2 m_translation;
};

class SetPositionAnimationCommand: public AnimationCommand
{
public:
    SetPositionAnimationCommand (Vector2 targetPos, int maxFrames):
        AnimationCommand (maxFrames),
        m_targetPos (targetPos)
    {}

protected:
    virtual void AnimateFrameImpl (int currentFrame, DrawableObject* obj) override;

private:
    Vector2 m_targetPos;
};

class ChangeOpacityCommand: public AnimationCommand
{
public:
    ChangeOpacityCommand (unsigned char targetAlpha, int maxFrames):
        AnimationCommand (maxFrames),
        m_targetAlpha (targetAlpha)
    {}

protected:
    virtual void AnimateFrameImpl (int currentFrame, DrawableObject* obj) override;

private:
    int m_targetAlpha;
};

class SetOpacityCommand: public AnimationCommand
{
public:
    SetOpacityCommand (unsigned char targetAlpha, int maxFrames):
        AnimationCommand (maxFrames),
        m_targetAlpha (targetAlpha)
    {}

protected:
    virtual void AnimateFrameImpl (int currentFrame, DrawableObject* obj) override;

private:
    int m_targetAlpha;
};

class ShapeChangeColorCommand: public AnimationCommand
{
public:
    ShapeChangeColorCommand (Color targetColor, int maxFrames):
        AnimationCommand (maxFrames),
        m_targetColor (targetColor)
    {}

protected:
    virtual void AnimateFrameImpl (int currentFrame, DrawableObject* obj) override;

private:
    Color m_targetColor;
};

class ShapeSetColorCommand: public AnimationCommand
{
public:
    ShapeSetColorCommand (Color targetColor, int maxFrames):
        AnimationCommand (maxFrames),
        m_targetColor (targetColor)
    {}

protected:
    virtual void AnimateFrameImpl (int currentFrame, DrawableObject* obj) override;

private:
    Color m_targetColor;
};

class ScaleCommand: public AnimationCommand
{
public:
    ScaleCommand (float scale, int maxFrames):
        AnimationCommand (maxFrames),
        m_targetScale (scale)
    {}

protected:
    virtual void AnimateFrameImpl (int currentFrame, DrawableObject* obj) override;

private:
    float m_targetScale;
};

