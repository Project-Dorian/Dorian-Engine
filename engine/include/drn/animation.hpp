#ifndef DORIAN_ANIMATION
#define DORIAN_ANIMATION

namespace drn {
    template <class T>
    struct AnimationFrame {
        T value;
        float time;
    };

    template <class T>
    class Animated {
        private:
        T m_CurrentValue;
        std::vector<AnimationFrame<T>> m_AnimationFrames;
        Math::Vec2<int> m_currentFrameIndex;
        bool m_Playing{false};

        public:
        float Time{0};
        bool Looping;

        void operator=(T val) {m_CurrentValue = val;};

        Animated(T initialVal, std::vector<AnimationFrame<T>> frames, bool looping = false) {
            m_CurrentValue = initialVal;
            m_AnimationFrames = frames;
            m_currentFrameIndex = {0, (int)frames.size() - 1};
            Looping = looping;
        };

        void Play() {
            Time = 0;
            m_Playing = true;
        };

        void Play(Math::Vec2<int> range) {
            Time = m_AnimationFrames[range.X].time;
            m_currentFrameIndex = range;
            m_Playing = true;
        };

        T get() {return m_CurrentValue;};
        void Update(float t) {
            if (!m_Playing) return;
            Time += t;
            
            if (Time >= m_AnimationFrames[m_currentFrameIndex.Y].time && Looping) {
                Time -= m_AnimationFrames[m_currentFrameIndex.Y].time - m_AnimationFrames[m_currentFrameIndex.X].time;
            }

            for (int i{m_currentFrameIndex.X}; i < m_currentFrameIndex.Y; i++) {
                if (Time >= m_AnimationFrames[i].time && Time < m_AnimationFrames[i+1].time) {
                    m_CurrentValue = (m_AnimationFrames[i+1].value-m_AnimationFrames[i].value)/(m_AnimationFrames[i+1].time-m_AnimationFrames[i].time)
                    *(Time - m_AnimationFrames[i].time) + m_AnimationFrames[i].value;
                    break;
                }
            }
        }
    };
}

#endif