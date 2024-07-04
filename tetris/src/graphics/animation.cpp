#include <graphics/animation.h>
#include <graphics/graphics_helper.h>

#include <algorithm>

Sequence::~Sequence()
{
    for (auto comm: m_animationCommands) {
        if (comm) {
            delete comm;
            comm = nullptr;
        }
    }
}

void Sequence::PerformAnimation (DrawableObject* obj)
{
    if (!CanPerform()) {
        return;
    }
    for (auto comm: m_animationCommands) {
        comm->AnimateFrame (m_currentFrame, obj);
    }
    m_currentFrame++;
}

void Sequence::AddMoveCommand (int frameLength, Vector2 translation)
{
    m_sequenceLength = std::max (frameLength, m_sequenceLength);
    auto command = new MoveAnimationCommand (translation, frameLength);
    m_animationCommands.push_back (command);
}

void Sequence::AddScaleCommand (int frameLength, float scale)
{
    m_sequenceLength = std::max (frameLength, m_sequenceLength);
    auto command = new ScaleCommand (scale, frameLength);
    m_animationCommands.push_back (command);
}

void Sequence::AddSetPositionCommand (int frameLength, Vector2 targetPosition)
{
    m_sequenceLength = std::max (frameLength, m_sequenceLength);
    auto command = new SetPositionAnimationCommand (targetPosition, frameLength);
    m_animationCommands.push_back (command);
}

void Sequence::AddChangeColorCommand (int frameLength, Color targetColor)
{
    m_sequenceLength = std::max (frameLength, m_sequenceLength);
    auto command = new ShapeChangeColorCommand (targetColor, frameLength);
    m_animationCommands.push_back (command);
}

void Sequence::AddChangeOpacityCommand (int frameLength, unsigned char opacity)
{
    m_sequenceLength = std::max (frameLength, m_sequenceLength);
    auto command = new ChangeOpacityCommand (opacity, frameLength);
    m_animationCommands.push_back (command);
}

void Sequence::AddSetOpacityCommand (int frameLength, unsigned char opacity)
{
    m_sequenceLength = std::max (frameLength, m_sequenceLength);
    auto command = new SetOpacityCommand (opacity, frameLength);
    m_animationCommands.push_back (command);
}

void Sequence::AddSetColorCommand (int frameLength, Color targetColor)
{
    m_sequenceLength = std::max (frameLength, m_sequenceLength);
    auto command = new ShapeSetColorCommand (targetColor, frameLength);
    m_animationCommands.push_back (command);
}

void Animation::Tick()
{
    if (m_bIsPlaying) {
        if (m_animationSequences[m_currentSequenceIdx].CanPerform()) {
            m_animationSequences[m_currentSequenceIdx].PerformAnimation (m_obj);
        } else if (m_currentSequenceIdx+1 < m_animationSequences.size()) {
            m_currentSequenceIdx++;
            m_animationSequences[m_currentSequenceIdx].PerformAnimation (m_obj);
        } else {
            if (!m_bIsLooping) {
                m_bIsPlaying = false;
            }
            m_currentSequenceIdx = 0;
            for (auto& seq : m_animationSequences) {
                seq.Reset();
            }
        }
    }
}

void Animation::SetAlpha (unsigned char alpha)
{
    m_alphaCh = alpha;
    m_obj->SetAlpha (GetAlpha());
}

void Animation::Draw() const
{
    m_obj->Draw();
}

BoundingBox2d Animation::GetBoundingBox() const
{
    return m_obj->GetBoundingBox();
}

void Animation::Translate (const Vector2& translation)
{
    m_pos.x += translation.x;
    m_pos.y += translation.y;
    m_obj->Translate (translation);
}

void Animation::Scale (float scale)
{
    m_obj->Scale (scale);
}

void Animation::ResetObjectState()
{
    auto trsl = GraphicsHelper::ComputeTranslation (m_obj->GetPosition(), m_initialPos);
    m_obj->Translate (m_initialPos);
}

void MoveAnimationCommand::AnimateFrameImpl (int /*currentFrame*/, DrawableObject* obj)
{
    Vector2 frameTsl {m_translation.x/m_maxFrames, m_translation.y/m_maxFrames};
    obj->Translate (frameTsl);
}

void SetPositionAnimationCommand::AnimateFrameImpl (int currentFrame, DrawableObject* obj)
{
    auto trsl = GraphicsHelper::ComputeTranslation (obj->GetPosition(), m_targetPos);
    obj->Translate (trsl);
}

void ChangeOpacityCommand::AnimateFrameImpl (int currentFrame, DrawableObject* obj)
{
    auto currAlpha = obj->GetAlpha();
    if (m_maxFrames - currentFrame > 0) {
        int diff = (m_targetAlpha - currAlpha) / (m_maxFrames - currentFrame);
        int alpha = obj->GetAlpha() + diff;
        alpha = std::clamp (alpha, 0, 255);
        obj->SetAlpha (alpha);
    }
    else {
        obj->SetAlpha (m_targetAlpha);
    }
}

void ShapeChangeColorCommand::AnimateFrameImpl (int currentFrame, DrawableObject* obj)
{
    if (auto shape = dynamic_cast <shapes::Shape*> (obj)) {
        if (m_maxFrames - currentFrame > 0) {
            auto color = shape->GetColor ();
            float dr = (float)(m_targetColor.r - color.r) / (m_maxFrames - currentFrame);
            float dg = (float)(m_targetColor.g - color.g) / (m_maxFrames - currentFrame);
            float db = (float)(m_targetColor.b - color.b) / (m_maxFrames - currentFrame);
            int r = color.r + dr;
            int g = color.g + dg;
            int b = color.b + db;
            r = std::clamp (r, 0, 255);
            g = std::clamp (g, 0, 255);
            b = std::clamp (b, 0, 255);
            shape->SetColor ({(unsigned char)r, (unsigned char)g, (unsigned char)b, shape->GetAlpha()});
        }
        else {
            shape->SetColor ({m_targetColor.r, m_targetColor.g, m_targetColor.b, shape->GetAlpha()});
        }
    }

}

void ShapeSetColorCommand::AnimateFrameImpl (int currentFrame, DrawableObject* obj)
{
    if (auto shape = dynamic_cast <shapes::Shape*> (obj)) {
        shape->SetColor ({m_targetColor.r, m_targetColor.g, m_targetColor.b, shape->GetAlpha()});
    }
}

void ScaleCommand::AnimateFrameImpl (int currentFrame, DrawableObject* obj)
{
    float scale = 1.0;
    if (m_targetScale < 1.0){
        scale = 1.0 - m_targetScale / m_maxFrames;
    } else {
        scale = 1.0 + (m_targetScale - 1) / m_maxFrames;
    }
    obj->Scale (scale);
}

void SetOpacityCommand::AnimateFrameImpl (int currentFrame, DrawableObject* obj)
{
    obj->SetAlpha (m_targetAlpha);
}
