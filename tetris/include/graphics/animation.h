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

protected:
    template <typename CommandType, typename ... Ts>
    void AddCommand (int frameLength, Ts... Args)
    {
        m_sequenceLength = std::max (frameLength, m_sequenceLength);
        auto command = new CommandType (frameLength, Args...);
        m_animationCommands.push_back (command);
    }

    //void AddMoveCommand (int frameLength, Vector2 translation);
    //void AddScaleCommand (int frameLength, float scale);
    //void AddSetPositionCommand (int frameLength, Vector2 targetPosition);
    //void AddChangeColorCommand (int frameLength, Color targetColor);
    //void AddChangeOpacityCommand (int frameLength, unsigned char opacity);
    //void AddSetOpacityCommand (int frameLength, unsigned char opacity);
    //void AddSetColorCommand (int frameLength, Color targetColor);

private:
    int                             m_currentFrame;
    int                             m_sequenceLength;
    std::vector <AnimationCommand*> m_animationCommands;

    friend class Animation;
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

public:
    void AddMoveAnimStep          (int frameLength, Vector2 translation   , bool joinWithPrevious = false);
    void AddScaleAnimStep         (int frameLength, float scale           , bool joinWithPrevious = false);
    void AddSetPositionAnimStep   (int frameLength, Vector2 targetPosition, bool joinWithPrevious = false);
    void AddChangeColorAnimStep   (int frameLength, Color targetColor     , bool joinWithPrevious = false);
    void AddChangeOpacityAnimStep (int frameLength, unsigned char opacity , bool joinWithPrevious = false);
    void AddSetOpacityAnimStep    (int frameLength, unsigned char opacity , bool joinWithPrevious = false);
    void AddSetColorAnimStep      (int frameLength, Color targetColor     , bool joinWithPrevious = false);
    void AddWaitAnimStep          (int frameLength,                         bool joinWithPrevious = false);

private:
    template <typename Command, typename ... Ts>
    void AddSequence (bool joinWithPrevious, Ts... Args) {
        if (joinWithPrevious && m_animationSequences.size() > 0) {
            m_animationSequences.back().AddCommand <Command> (Args...);
        } else {
            Sequence seq;
            seq.AddCommand <Command> (Args...);
            m_animationSequences.push_back (std::move (seq));
        }
    }
    void ResetObjectState();

private:
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
    MoveAnimationCommand (int maxFrames, Vector2 translation):
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
    SetPositionAnimationCommand (int maxFrames, Vector2 targetPos):
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
    ChangeOpacityCommand (int maxFrames, unsigned char targetAlpha):
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
    SetOpacityCommand (int maxFrames, unsigned char targetAlpha):
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
    ShapeChangeColorCommand (int maxFrames, Color targetColor):
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
    ShapeSetColorCommand (int maxFrames, Color targetColor):
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
    ScaleCommand (int maxFrames, float scale):
        AnimationCommand (maxFrames),
        m_targetScale (scale)
    {}

protected:
    virtual void AnimateFrameImpl (int currentFrame, DrawableObject* obj) override;

private:
    float m_targetScale;
};

class WaitCommand: public AnimationCommand
{
public:
    WaitCommand (int maxFrames):
        AnimationCommand (maxFrames)
    {}

protected:
    virtual void AnimateFrameImpl (int currentFrame, DrawableObject* obj) override {}

};

